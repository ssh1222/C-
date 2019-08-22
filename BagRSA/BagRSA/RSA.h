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
	//��Կ(public_key, share_key)
	bm::int1024_t share_key;
	bm::int1024_t public_key;
	//˽Կ(private_key, share_key)
	bm::int1024_t private_key;
};

class RSA{
public:
	RSA();
	Key GetKey()
	{
		return _key;
	}
	//���ļ����м���
	void Ecrept(const char* plain_file_in, const char* ecrept_file_out,
		bm::int1024_t public_key, bm::int1024_t share_key);
	void DEcrept(const char* plain_file_in, const char* ecrept_file_out,
		bm::int1024_t private_key, bm::int1024_t share_key);

	//���ַ������м���
	std::vector<bm::int1024_t> Ecrept(std::string& str_in, bm::int1024_t public_key, bm::int1024_t share_key);
	std::string DEcrept(std::vector<bm::int1024_t>& ecrept_str, bm::int1024_t private_key, bm::int1024_t share_key);

	//��ӡ����֮�����Ϣ
	void PrintInfo(std::vector<bm::int1024_t>& ecrept_str);
private:
	//��������
	bm::int1024_t ProducePrime();
	//�ж�һ�����Ƿ�������
	bool IsBagPrime(bm::int1024_t prime);
	//�������е�keyֵ
	void ProduceKeys();
	//��share_kay
	bm::int1024_t ProduceShareKey(bm::int1024_t prime1, bm::int1024_t prime2);
	//����ŷ��������˻�
	bm::int1024_t ProduceOrla(bm::int1024_t prime1, bm::int1024_t prime2);
	//��public_key
	bm::int1024_t ProducePublicKey(bm::int1024_t orla);
	//�ж�������֮������Լ�Ƿ�Ϊ1
	bm::int1024_t ProduceGcd(bm::int1024_t public_key, bm::int1024_t orla);
	//��private_key
	bm::int1024_t ProducePrivateKey(bm::int1024_t public_key, bm::int1024_t orla);
	bm::int1024_t BagProducePrivateKey(bm::int1024_t public_key, bm::int1024_t orla,
		bm::int1024_t& x, bm::int1024_t& y);
	//���ܵ�����Ϣ
	bm::int1024_t Ecrept(bm::int1024_t msg, bm::int1024_t key, bm::int1024_t share_key);
private:
	Key _key;
};