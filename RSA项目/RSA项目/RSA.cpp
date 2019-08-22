#include "RSA.h"

RSA::RSA() {
	ProduceKeys();
}

//���ļ����м��������
void RSA::Ecrept(const char* plain_file_in, const char* ecrept_file_out,
	long public_key, long share_key){
	std::ifstream fin(plain_file_in);
	std::ofstream fout(ecrept_file_out, std::ofstream::app);
	if (!fin.is_open()){
		std::cout << "open file failed" << std::endl;
		return;
	}
	//һ�ζ�ȡ�ļ���С�������п�����Ϊ�ļ������޷����м���
	//fin.seekg(0, fin.end);
	//long fsize = fin.tellg();
	//�����ȡ����μ���
	const int NUM = 256;
	char buf[NUM];
	long buf_out[NUM];
	int cur_num;
	while (!fin.eof()){
		fin.read(buf, NUM);
		//��ǰ����ȡ���ֽ���
		cur_num = fin.gcount();
		for (int i = 0; i < cur_num; ++i){
			buf_out[i] = Ecrept((long)buf[i], public_key, share_key);
		}
		fout.write((char*)buf_out, cur_num * sizeof(long));
	}
	fin.close();
	fout.close();
}
void RSA::DEcrept(const char* plain_file_in, const char* ecrept_file_out,
	long private_key, long share_key){
	std::ifstream fin(plain_file_in);
	std::ofstream fout(ecrept_file_out, std::ofstream::app);
	if (!fin.is_open()){
		std::cout << "open file failed" << std::endl;
		return;
	}
	//һ�ζ�ȡ�ļ���С�������п�����Ϊ�ļ������޷����м���
	//fin.seekg(0, fin.end);
	//long fsize = fin.tellg();
	//�����ȡ����μ���
	const int NUM = 256;
	long buf[NUM];
	char buf_out[NUM];
	int cur_num;
	while (!fin.eof()){
		fin.read((char*)buf, NUM * sizeof(long));
		//��ǰ����ȡ���ֽ���
		cur_num = fin.gcount();
		cur_num /= sizeof(long);
		for (int i = 0; i < cur_num; ++i){
			buf_out[i] = (char)Ecrept((long)buf[i], private_key, share_key);
		}
		fout.write(buf_out, cur_num);
	}
	fin.close();
	fout.close();
}

//���ַ������м��������
std::vector<long> RSA::Ecrept(std::string& str_in, long public_key, long share_key) {
	std::vector<long> vecout;
	for (const auto& e : str_in){
		vecout.push_back(Ecrept(e, public_key, share_key));
	}
	return vecout;
}
std::string RSA::DEcrept(std::vector<long>& ecrept_str, long private_key, long share_key) {
	std::string strout;
	for (const auto& e : ecrept_str){
		strout.push_back((char)Ecrept(e, private_key, share_key));
	}
	return strout;
}

//��ӡ����֮�����Ϣ
void RSA::PrintInfo(std::vector<long>& ecrept_str) {
	for (const auto& e : ecrept_str){
		std::cout << e << " ";
	}
	std::cout << std::endl;
}

//���ܵ�����Ϣ��ģ������
long RSA::Ecrept(long msg, long key, long share_key){
	long msg_out = 1;
	long a = msg;
	long b = key;
	int c = share_key;
	while (b){
		if (b & 1){
			//msg_out = (A0*A1...Ai...An) % c
			msg_out = (msg_out * a) % c;
		}
		b >>= 1;
		a = (a * a) % c;
	}
	return msg_out;
}

//�������������������������
long RSA::ProducePrime()
{
	srand(time(nullptr));
	long prime = 0;
	while (1){
		prime = rand() % 50 + 2; 
		if (IsPrime(prime))
			break;
	}
	return prime;
}

//�ж�һ�����Ƿ�������
bool RSA::IsPrime(long prime) {
	if (prime < 2)
		return false;
	for (int i = 2; i < sqrt(prime); ++i){
		if (prime % i == 0)
			return false;
	}
	return true;
}

//�������е�keyֵ
void RSA::ProduceKeys() {
	//ѡ����������ȵ�����
	long prime1 = ProducePrime();
	long prime2 = ProducePrime();
	while (prime1 == prime2)
		prime2 = ProducePrime();
	_key.share_key = ProduceShareKey(prime1, prime2);
	long orla = ProduceOrla(prime1, prime2);
	_key.public_key = ProducePublicKey(orla);
	_key.private_key = ProducePrivateKey(_key.public_key, orla);
}

//��share_kay
long RSA::ProduceShareKey(long prime1, long prime2) {
	return prime1 * prime2;
}

//����ŷ��������˻�
long RSA::ProduceOrla(long prime1, long prime2) {
	return (prime1 - 1) * (prime2 - 1);
}

//��public_key�����ѡ��һ������ 1 < public_key < orla��public_key,oala����
long RSA::ProducePublicKey(long orla) {
	long public_key;
	srand(time(nullptr));
	while (1){
		public_key = rand() % orla;
		if (public_key > 1 && ProduceGcd(public_key, orla) == 1)
			break;
	}
	return public_key;
}

//�ж�������֮������Լ�Ƿ�Ϊ1
long RSA::ProduceGcd(long public_key, long orla) {
	long residual;
	while (residual = public_key % orla){
		public_key = orla;
		orla = residual;
	}
	return orla;
}

//��private_key
long RSA::ProducePrivateKey(long public_key, long orla) {
	//(public_key * private_key) % orla == 1
	long private_key = orla / public_key;
	while (1){
		if ((public_key * private_key) % orla == 1)
			break;
		++private_key;
	}
	return private_key;
}