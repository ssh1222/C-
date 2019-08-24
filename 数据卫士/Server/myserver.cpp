/*************************************************************************
	> File Name: myserver.cpp
	> Author: ssh
	> Mail: sunshihao1222@163.com 
	> Created Time: Fri 26 Jul 2019 08:46:28 AM CST
	> Describe: 
 ************************************************************************/
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <iostream>
#include <boost/filesystem.hpp>
#include "httplib.h"
#include <unistd.h>
#include <fcntl.h>
#include "mycompress.hpp"

#define SERVER_BASE_DIR "www"
#define SERVER_ADDR "0.0.0.0"
#define SERVER_PORT 9000
#define SERVER_BACKUP_DIR SERVER_BASE_DIR"/list/"

myCompressStore cstor;

class myCloudServer{
public:
	myCloudServer(const char *cert, const char *key)
		:_srv(cert, key)
	{
		boost::filesystem::path base_path(SERVER_BASE_DIR);
		//判断文件是否存在，不存在则创建
		if(!boost::filesystem::exists(base_path)){
			boost::filesystem::create_directory(base_path);
		}
		boost::filesystem::path list_path(SERVER_BACKUP_DIR);
		if(!boost::filesystem::exists(list_path)){
			boost::filesystem::create_directory(list_path);
		}
	}

	bool Start(){
		//设置相对根目录
		_srv.set_base_dir(SERVER_BASE_DIR);
		//处理请求
		_srv.Get("/(list(/){0,1}){0,1}", GetFileList);
		std::cout << "list" << std::endl;
		_srv.Get("/list/(.*)", GetFileData);
		std::cout << "data" << std::endl;
		//上传文件
		_srv.Put("/list/(.*)", PutFileData);
		std::cout << "put" << std::endl;
		//开始监听本机任意地址
		_srv.listen(SERVER_ADDR, SERVER_PORT);
		std::cout << "listen" << std::endl;
		return true;
	}
private:
	//获取文件列表
	static void GetFileList(const httplib::Request& req, httplib::Response& rsp){
		//上传文件的目录路径
		std::vector<std::string> list;
		cstor.GetFileList(list);
		std::string body;
		body = "<html><body><ol><hr />";
		//遍历目录里面的文件，生成html网页标签信息
		for(auto e : list){
			boost::filesystem::path path(e);
			std::string file = path.filename().string();
			std::string uri = "/list/" + file;
			body += "<h4><li>";
			body += "<a href='";
			body += uri;
			body += "'>";
			body += file;
			body += "</a>";
			body += "</li></h4>";
		}

		body += "<hr /></ol></body></html>";
		//设置text/html标签信息
		rsp.set_content(&body[0], "text/html");
		return;
	}
	//文件下载
	static void GetFileData(const httplib::Request& req, httplib::Response& rsp){
		std::string file = SERVER_BASE_DIR + req.path;
		std::string body;
		cstor.GetFileData(file, body);
		rsp.set_header("Content-Length", std::to_string(body.size()).c_str());
		rsp.set_content(&body[0], body.size(), "text/plain");
	}

	//备份文件
	static void PutFileData(const httplib::Request& req, httplib::Response& rsp){
		std::cout << 1 << std::endl;
		if(!req.has_header("Range")){
			rsp.status = 400;
			return;
		}

		std::cout << 2 << std::endl;
		std::string range = req.get_header_value("Range");
		int64_t range_start;
		if(RangeParse(range, range_start) == false){
			rsp.status = 400;
			return;
		}
		std::cout << 3 << std::endl;
		//打开文件
		std::cout << "backup file:[" << req.path << "] range:[" << range << "]" << std::endl;
		std::string real = SERVER_BASE_DIR + req.path;
		cstor.SetFileData(real, req.body, range_start);
		return;
	}
	//获取发送的数据大小
	static bool RangeParse(std::string &range, int64_t &start){
		size_t pos1 = range.find("=");
		size_t pos2 = range.find("-");
		if(pos1 == std::string::npos || pos2 == std::string::npos){
			std::cerr << "range:[" << range << "] format error" << std::endl;
			return false;
		}
		std::stringstream rs;
		rs << range.substr(pos1 + 1, pos2 - pos1 - 1);
		rs >> start;
		return true;
	}
private:
	httplib::SSLServer _srv;
}; 

void thr_start(){
	cstor.LowHeatFileStore();
}

int main(){
	std::thread thr(thr_start);
	thr.detach();
	myCloudServer srv("./cert.pem", "./key.pem");
	srv.Start();
	std::cout << "last" << std::endl;
	return 0;
}
