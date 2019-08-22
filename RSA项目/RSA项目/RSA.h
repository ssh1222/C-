#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <fstream>

struct Key{
	//��Կ(public_key, share_key)
	long long share_key;   
	long long public_key; 
	//˽Կ(private_key, share_key)
	long long private_key;
};

class RSA{
public:
	RSA();
	Key GetKey() {
		return _key;
	}
	//���ļ����м���
	void Ecrept(const char* plain_file_in, const char* ecrept_file_out,
		long public_key, long share_key);
	void DEcrept(const char* plain_file_in, const char* ecrept_file_out,
		long private_key, long share_key);

	//���ַ������м���
	std::vector<long> Ecrept(std::string& str_in, long public_key, long share_key);
	std::string DEcrept(std::vector<long>& ecrept_str, long private_key, long share_key);

	//��ӡ����֮�����Ϣ
	void PrintInfo(std::vector<long>& ecrept_str);
private:
	//��������
	long ProducePrime();
	//�ж�һ�����Ƿ�������
	bool IsPrime(long prime);
	//�������е�keyֵ
	void ProduceKeys();
	//��share_kay
	long ProduceShareKey(long prime1, long prime2);
	//����ŷ��������˻�
	long ProduceOrla(long prime1, long prime2);
	//��public_key
	long ProducePublicKey(long orla);
	//�ж�������֮������Լ�Ƿ�Ϊ1
	long ProduceGcd(long public_key, long orla);
	//��private_key
	long ProducePrivateKey(long public_key, long orla);
	//���ܵ�����Ϣ
	long Ecrept(long msg, long key, long share_key);
private:
	Key _key;
};