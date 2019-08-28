//1.给定两个字符串A和B ，判断A是否能由B中的含有的字符组成，B中的每个字符只能使用一次。
//例：("a", "b") -> false
//("aa", "ab") -> false
//("aa", "aab") -> true

#include <iostream>
#include <string>
#include <map>

bool JudgeStr(std::string s1, std::string s2)
{
	std::map<char, int> m1, m2;
	for (auto e : s1)
		m1[e]++;
	for (auto e : s2)
		m2[e]++;
	if (m1.size() > m2.size())
		return false;
	auto& sit1 = m1.begin();
	auto& sit2 = m2.begin();
	while (sit1 != m1.end()){
		if (sit1->second > sit2->second)
			return false;
		++sit1;
		++sit2;
	}
	return true;
}

int main() {
	std::string s1, s2;
	std::cout << "请输入第一个字符串：";
	std::cin >> s1;
	std::cout << "请输入第二个字符串：";
	std::cin >> s2;
	bool ret = JudgeStr(s1, s2);
	std::cout << "结果输出（1代表成功，0代表失败）：";
	std::cout << ret << std::endl;
	system("pause");
	return 0;
}