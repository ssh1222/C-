#include "RSA.h"

void TestString()
{
	RSA rsa;
	Key key = rsa.GetKey();
	std::string strin;
	std::cout << "输入加密信息" << std::endl;
	std::cin >> strin;
	std::vector<bm::int1024_t> strecrept = rsa.Ecrept(strin, key.public_key, key.share_key);
	std::string strout = rsa.DEcrept(strecrept, key.private_key, key.share_key);
	std::cout << "加密信息" << std::endl;
	rsa.PrintInfo(strecrept);
	std::cout << "解密信息" << std::endl;
	std::cout << strout << std::endl;
}

void TestFile()
{
	RSA rsa;
	Key key = rsa.GetKey();
	rsa.Ecrept("plain.txt", "ecrept.out.txt", key.public_key, key.share_key);
	rsa.DEcrept("ecrept.out.txt", "decrept.out.txt", key.private_key, key.share_key);
}

int main(){
	TestString();
	TestFile();
	system("pause");
	return 0;
}