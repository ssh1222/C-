#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <fstream>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/random.hpp>
#include <boost/multiprecision/miller_rabin.hpp>
namespace bm = boost::multiprecision;

struct Key{
	//公钥(public_key, share_key)
	bm::int1024_t share_key;
	bm::int1024_t public_key;
	//私钥(private_key, share_key)
	bm::int1024_t private_key;
};

class RSA{
public:
	RSA();
	Key GetKey()
	{
		return _key;
	}
	//给文件进行加密
	void Ecrept(const char* plain_file_in, const char* ecrept_file_out,
		bm::int1024_t public_key, bm::int1024_t share_key);
	void DEcrept(const char* plain_file_in, const char* ecrept_file_out,
		bm::int1024_t private_key, bm::int1024_t share_key);

	//对字符串进行加密
	std::vector<bm::int1024_t> Ecrept(std::string& str_in, bm::int1024_t public_key, bm::int1024_t share_key);
	std::string DEcrept(std::vector<bm::int1024_t>& ecrept_str, bm::int1024_t private_key, bm::int1024_t share_key);

	//打印加密之后的信息
	void PrintInfo(std::vector<bm::int1024_t>& ecrept_str);
private:
	//产生素数
	bm::int1024_t ProducePrime();
	//判断一个数是否是素数
	bool IsBagPrime(bm::int1024_t prime);
	//产生所有的key值
	void ProduceKeys();
	//求share_kay
	bm::int1024_t ProduceShareKey(bm::int1024_t prime1, bm::int1024_t prime2);
	//根据欧拉函数求乘积
	bm::int1024_t ProduceOrla(bm::int1024_t prime1, bm::int1024_t prime2);
	//求public_key
	bm::int1024_t ProducePublicKey(bm::int1024_t orla);
	//判断两个数之间的最大公约是否为1
	bm::int1024_t ProduceGcd(bm::int1024_t public_key, bm::int1024_t orla);
	//求private_key
	bm::int1024_t ProducePrivateKey(bm::int1024_t public_key, bm::int1024_t orla);
	bm::int1024_t BagProducePrivateKey(bm::int1024_t public_key, bm::int1024_t orla,
		bm::int1024_t& x, bm::int1024_t& y);
	//加密单个信息
	bm::int1024_t Ecrept(bm::int1024_t msg, bm::int1024_t key, bm::int1024_t share_key);
private:
	Key _key;
};