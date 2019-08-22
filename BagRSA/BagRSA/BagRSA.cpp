#include "RSA.h"

RSA::RSA()
{
	ProduceKeys();
}

//���ļ����м��������
void RSA::Ecrept(const char* plain_file_in, const char* ecrept_file_out,
	bm::int1024_t public_key, bm::int1024_t share_key)
{
	std::ifstream fin(plain_file_in);
	std::ofstream fout(ecrept_file_out, std::ofstream::app);
	if (!fin.is_open()){
		std::cout << "open file failed" << std::endl;
		return;
	}
	//һ�ζ�ȡ�ļ���С�������п�����Ϊ�ļ������޷����м���
	//fin.seekg(0, fin.end);
	//bm::int1024_t fsize = fin.tellg();
	//�����ȡ����μ���
	const int NUM = 256;
	char buf[NUM];
	bm::int1024_t buf_out[NUM];
	int cur_num;
	while (!fin.eof()){
		fin.read(buf, NUM);
		//��ǰ����ȡ���ֽ���
		cur_num = fin.gcount();
		for (int i = 0; i < cur_num; ++i){
			buf_out[i] = Ecrept((bm::int1024_t)buf[i], public_key, share_key);
		}
		fout.write((char*)buf_out, cur_num * sizeof(bm::int1024_t));
	}
	fin.close();
	fout.close();
}
void RSA::DEcrept(const char* plain_file_in, const char* ecrept_file_out,
	bm::int1024_t private_key, bm::int1024_t share_key)
{
	std::ifstream fin(plain_file_in);
	std::ofstream fout(ecrept_file_out, std::ofstream::app);
	if (!fin.is_open()){
		std::cout << "open file failed" << std::endl;
		return;
	}
	//һ�ζ�ȡ�ļ���С�������п�����Ϊ�ļ������޷����м���
	//fin.seekg(0, fin.end);
	//bm::int1024_t fsize = fin.tellg();
	//�����ȡ����μ���
	const int NUM = 256;
	bm::int1024_t buf[NUM];
	char buf_out[NUM];
	int cur_num;
	while (!fin.eof()){
		fin.read((char*)buf, NUM * sizeof(bm::int1024_t));
		//��ǰ����ȡ���ֽ���
		cur_num = fin.gcount();
		cur_num /= sizeof(bm::int1024_t);
		for (int i = 0; i < cur_num; ++i){
			buf_out[i] = (char)Ecrept((bm::int1024_t)buf[i], private_key, share_key);
		}
		fout.write(buf_out, cur_num);
	}
	fin.close();
	fout.close();
}

//���ַ������м��������
std::vector<bm::int1024_t> RSA::Ecrept(std::string& str_in, 
	bm::int1024_t public_key, bm::int1024_t share_key)
{
	std::vector<bm::int1024_t> vecout;
	for (const auto& e : str_in){
		vecout.push_back(Ecrept(e, public_key, share_key));
	}
	return vecout;
}
std::string RSA::DEcrept(std::vector<bm::int1024_t>& ecrept_str,
	bm::int1024_t private_key, bm::int1024_t share_key)
{
	std::string strout;
	for (const auto& e : ecrept_str){
		strout.push_back((char)Ecrept(e, private_key, share_key));
	}
	return strout;
}

//��ӡ����֮�����Ϣ
void RSA::PrintInfo(std::vector<bm::int1024_t>& ecrept_str)
{
	for (const auto& e : ecrept_str){
		std::cout << e << " ";
	}
	std::cout << std::endl;
}

//���ܵ�����Ϣ��ģ������
bm::int1024_t RSA::Ecrept(bm::int1024_t msg, bm::int1024_t key, bm::int1024_t share_key)
{
	bm::int1024_t msg_out = 1;
	bm::int1024_t a = msg;
	bm::int1024_t b = key;
	bm::int1024_t c = share_key;
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
bm::int1024_t RSA::ProducePrime()
{
	//mt19937�����������
	boost::random::mt19937 gen(time(nullptr));
	//ָ���������Χ0 ~ ��1 << 786��
	boost::random::uniform_int_distribution<bm::int1024_t> dist(2, bm::int1024_t(1) << 128);
	srand(time(nullptr));
	bm::int1024_t prime = 0;
	while (1){
		prime = dist(gen);
		if (IsBagPrime(prime))
			break;
	}
	return prime;
}

//�ж�һ�������Ƿ�������
bool RSA::IsBagPrime(bm::int1024_t prime){
	boost::random::mt11213b gen(time(nullptr));
	if (miller_rabin_test(prime, 25, gen)){
		if (miller_rabin_test((prime - 1) / 2, 25, gen));
			return true;
	}
	return false;
}
//�������е�keyֵ
void RSA::ProduceKeys()
{
	//ѡ����������ȵ�����
	bm::int1024_t prime1 = ProducePrime();
	bm::int1024_t prime2 = ProducePrime();
	while (prime1 == prime2)
		prime2 = ProducePrime();
	_key.share_key = ProduceShareKey(prime1, prime2);
	bm::int1024_t orla = ProduceOrla(prime1, prime2);
	_key.public_key = ProducePublicKey(orla);
	_key.private_key = ProducePrivateKey(_key.public_key, orla);
}

//��share_kay
bm::int1024_t RSA::ProduceShareKey(bm::int1024_t prime1, bm::int1024_t prime2)
{
	return prime1 * prime2;
}

//����ŷ��������˻�
bm::int1024_t RSA::ProduceOrla(bm::int1024_t prime1, bm::int1024_t prime2)
{
	return (prime1 - 1) * (prime2 - 1);
}

//��public_key�����ѡ��һ������ 1 < public_key < orla��public_key,oala����
bm::int1024_t RSA::ProducePublicKey(bm::int1024_t orla)
{
	bm::int1024_t public_key;
	srand(time(nullptr));
	while (1){
		public_key = rand() % orla;
		if (public_key > 1 && ProduceGcd(public_key, orla) == 1)
			break;
	}
	return public_key;
}

//�ж�������֮������Լ�Ƿ�Ϊ1
bm::int1024_t RSA::ProduceGcd(bm::int1024_t public_key, bm::int1024_t orla)
{
	bm::int1024_t residual;
	while (residual = public_key % orla){
		public_key = orla;
		orla = residual;
	}
	return orla;
}

//��private_key
bm::int1024_t RSA::ProducePrivateKey(bm::int1024_t public_key, bm::int1024_t orla)
{
	bm::int1024_t x, y;
	BagProducePrivateKey(public_key, orla, x, y);
	return (x % orla + orla) % orla;
}

//ŷ������㷨-->շת�����
bm::int1024_t RSA::BagProducePrivateKey(bm::int1024_t public_key, 
	bm::int1024_t orla,bm::int1024_t& x, bm::int1024_t& y)
{
	if (orla == 0){
		x = 1;
		y = 0;
		return public_key;
	}

	bm::int1024_t ret = RSA::BagProducePrivateKey(orla, public_key % orla, x, y);
	bm::int1024_t x1 = x, y1 = y;
	x = y1;
	y = x1 - (public_key / orla) * y1;
	return ret;
}