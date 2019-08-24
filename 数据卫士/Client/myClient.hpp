#ifndef __M_CLIENT_H__
#define __M_CLIENT_H__

#pragma warning(disable : 4996)
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include "httplib.h"

#define CLIENT_BACKUP_DIR "backup"
#define CLIENT_BACKUP_INFO_FILE "back.list"
#define RANGE_MAX_SIZE (10 << 20)
#define SERVER_IP "192.168.218.137"
#define SERVER_PORT 9000
#define BACKUP_URI "/list/"

class ThreadBackUp{
public:
	ThreadBackUp(const std::string &file, int64_t start, int64_t len)
		:_res(true)
		, _file(file)
		, _range_start(start)
		, _range_len(len)
	{}

	//开始上传
	void Start() {
		//打印上传信息
		std::stringstream tmp1;
		tmp1 << "backup file" << _file << "range:[" << _range_start << "-" << _range_len << "]";
		std::cout << tmp1.str() << std::endl;
		//获取文件的range分块数据
		std::ifstream path(_file, std::ios::binary);
		if (!path.is_open()){
			std::cerr << "range backup file " << _file << " failed" << std::endl;
			_res = false;
		}
		//跳转到range的起始位置
		path.seekg(_range_start, std::ios::beg);
		std::string body;
		body.resize(_range_len);
		//读取文件中range分块的文件数据
		path.read(&body[0], _range_len);
		if (!path.good()){
			std::cerr << "read file " << _file << " range data failed" << std::endl;
			_res = false;
		}
		path.close();

		//上传range数据
		boost::filesystem::path name(_file);
		//组织上传的url路径 method url version
		//PUT /list/filename HTTP/1.1
		std::string url = BACKUP_URI + name.filename().string();
		//实例化一个httplib的客户端对象
		httplib::Client cli(SERVER_IP, SERVER_PORT);
		//定义http请求头信息
		httplib::Headers hdr;
		hdr.insert(std::make_pair("Contnet-Length", std::to_string(_range_len)));
		std::stringstream tmp2;
		tmp2 << "bytes=" << _range_start << "-" << (_range_start + _range_len - 1);
		hdr.insert(std::make_pair("Range", tmp2.str().c_str()));
		//通过实例化的Client向服务端发送PUT请求
		auto rsp = cli.Put(url.c_str(), hdr, body, "text/plain");
		if (rsp->status != 200){
			_res = false;
		}	
		std::stringstream ss;
		ss << "backup file:[" << _file << "] range:[" << _range_start << "-" << _range_len << "]" << std::endl;
		std::cout << ss.str();
		return;
	}
public:
	bool _res;
private:
	std::string _file;
	int64_t _range_start;
	int64_t _range_len;
};

class myClient{
public:
	myClient() {
		boost::filesystem::path file(CLIENT_BACKUP_DIR);
		if (!boost::filesystem::exists(file)){
			boost::filesystem::create_directory(file);
		}
	}
	bool Start() {
		GetBackupInfo();
		while (1){
			BackupDirListen(CLIENT_BACKUP_DIR);
			SetBackupInfo();
			Sleep(3000);
		}
		return true;
	}
private:
	//获取备份信息
	//每次客户端启动时，读取备份信息文件，获取已有备份信息
	bool GetBackupInfo() {
		boost::filesystem::path path(CLIENT_BACKUP_INFO_FILE);
		if (!boost::filesystem::exists(path)){
			std::cerr << "list file " << path.string() << " is not exist" << std::endl;
			return false;
		}
		int64_t fsize = boost::filesystem::file_size(path);
		if (fsize == 0){
			std::cerr << "have no bcakup info" << std::endl;
			return false;
		}

		std::string body;
		body.resize(fsize);
		//打开文件
		std::ifstream file(CLIENT_BACKUP_INFO_FILE, std::ios::binary);
		if (file.is_open()){
			std::cerr << "list file open error" << std::endl;
			return false;
		}
		file.read(&body[0], fsize);
		if (!file.good()){
			std::cerr << "read list file body error" << std::endl;
			return false;
		}
		file.close();

		std::vector<std::string> list;
		boost::split(list, body, boost::is_any_of("\n"));
		for (auto i : list){
			size_t pos = i.find(" ");
			if (pos == std::string::npos){
				continue;
			}
			std::string key = i.substr(0, pos);
			std::string val = i.substr(pos + 1);
			_backup_list[key] = val;
		}
		return true;
	}
	//对文件目录进行监控：使用boost库实现迭代获取目录下文件名称
	bool BackupDirListen(const std::string &path){
		//迭代获取文件名
		//boost::filesystem::path file(path);
		boost::filesystem::directory_iterator item_begin(path);
		boost::filesystem::directory_iterator item_end;
		for (; item_begin != item_end; ++item_begin){
			if (boost::filesystem::is_directory(item_begin->status())){
				BackupDirListen(item_begin->path().string());
				continue;
			}

			if (FileIsNeedBackup(item_begin->path().string()) == false){
				continue;
			}
			std::cerr << "file:[" << item_begin->path().string() << "] need backup" << std::endl;
			if (PutFileData(item_begin->path().string()) == false){
				continue;
			}
			AddBackInfo(item_begin->path().string());
		}
		return true;
	}

	//将所有备份信息刷新存储到文件中（在还没有存储到文件中之前，程序退出）
	bool SetBackupInfo() {
		std::string body;
		for (auto i : _backup_list){
			body += i.first + " " + i.second + "\n";
		}
		
		//写文件
		std::ofstream file(CLIENT_BACKUP_INFO_FILE, std::ios::binary);
		if (!file.is_open()){
			std::cerr << "open list file error" << std::endl;
			return false;
		}

		file.write(&body[0], body.size());
		if (!file.good()){
			std::cerr << "set backup info error" << std::endl;
			return false;
		}

		file.close();
		return true;
	}

	//添加文件的备份信息
	bool AddBackInfo(const std::string &file) {
		std::string etag;
		if (GetFileEtag(file, etag) == false){
			return false;
		}
		_backup_list[file] = etag;
	}
	//判断文件是否需要更新、备份：根据_backup_list中备份信息中etag与新计算的etag进行比较
	bool FileIsNeedBackup(const std::string &file){
		std::string etag;
		if (GetFileEtag(file, etag) == false){
			return false;
		}
		auto it = _backup_list.find(file);
		if (it != _backup_list.end() && it->second == etag){
			return false;
		}

		return true;
	}
	//获取文件的etag信息
	bool GetFileEtag(const std::string &file, std::string &etag)
	{
		boost::filesystem::path path(file);
		if (!boost::filesystem::exists(path)){
			std::cerr << "get file " << file << " etag error" << std::endl;
			return false;
		}
		int64_t fsize = boost::filesystem::file_size(path);
		int64_t mtime = boost::filesystem::last_write_time(path);
		std::stringstream tmp;
		tmp << std::hex << fsize << "-" << std::hex << mtime;
		etag = tmp.str();
		return true;
	}
	//文件上传、备份文件：将文件新计算的etag信息，添加到map中_backup_list
	bool PutFileData(const std::string &file){
		//按大小对文件内容进行分块传输
		//并且获取分块传输是否成功判断整个文件是否上传成功
		//选择多线程处理
		//1.获取文件大小
		int64_t fsize = boost::filesystem::file_size(file);
		if (fsize <= 0){
			std::cerr << "file" << file << "unnecessary backup" << std::endl;
			return false;
		}
		//2.计算总共需要分多少块，得到每块大小以及起始位置
		//3.循环创建线程，在线程中上传文件数据
		int count = (int)(fsize / RANGE_MAX_SIZE);
		std::vector<ThreadBackUp> thr_res;
		std::vector<std::thread> thr_list;
		std::cerr << "file[ " << file << "] fsize:[" << fsize << "] count:[" << count + 1 << "]" <<std::endl;
		for (int i = 0; i <= count; ++i){
			int64_t range_start = i * RANGE_MAX_SIZE;
			int64_t range_end = ((i + 1) * RANGE_MAX_SIZE) - 1;
			if (i == count){
				range_end = fsize - 1;
			}
			
			int64_t range_len = range_end - range_start + 1;
			ThreadBackUp backup_info(file, range_start, range_len);
			std::cout << "file:[" << file << "] range:[" << range_start << "-" << range_end << "-" << range_len << "]" << std::endl;
			thr_res.push_back(backup_info);
		}
		for (int i = 0; i <= count; ++i){
			thr_list.push_back(std::thread(thr_start, &thr_res[i]));
		}
		//4.等待所有线程退出，判断文件上传结果
		bool ret = true;
		for (int i = 0; i <= count; ++i){
			thr_list[i].join();
			if (thr_res[i]._res == true){
				continue;
			}

			ret = false;
		}
		//5.上传成功，则添加文件的备份信息记录
		if (ret == false){
			return false;
		}

		std::cout << "file:[" << file << "] bcakup success" << std::endl;
		return true;
	}

	static void thr_start(ThreadBackUp *backup_info) {
		std::cout << "into thr_start" << std::endl;
		backup_info->Start();
		return;
	}
private:
	std::unordered_map<std::string, std::string> _backup_list;
};

#endif 