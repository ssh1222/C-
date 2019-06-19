//上面都有一个号码(拥有相同号码的球是无区别的)。如果一个袋子是幸运的当且仅当所有球的号码的和大于所有球的号码的积。
//例如：如果袋子里面的球的号码是{ 1, 1, 2, 3 }，这个袋子就是幸运的，因为1 + 1 + 2 + 3 > 1 * 1 * 2 * 3
//你可以适当从袋子里移除一些球(可以移除0个, 但是别移除完)，要使移除后的袋子是幸运的。现在让你编程计算一下你可以获得的多少种不同的幸运的袋子。
//输入描述 :
//第一行输入一个正整数n(n ≤ 1000)
//第二行为n个数正整数xi(xi ≤ 1000)
//输出描述 :
//	 输出可以产生的幸运的袋子数

#include <iostream>
#include <algorithm>
using namespace std;

int getLuckyPacket(int x[], int n, int pos, int sum, int multi)
{
	int count = 0;
	//循环，搜索以位置i开始所有可能的组合
	for (int i = pos; i < n; ++i){
		sum += x[i];
		multi *= x[i];
		if (sum > multi)
			count += 1 + getLuckyPacket(x, n, i + 1, sum, multi);
		else if (x[i] == 1)
			count += getLuckyPacket(x, n, i + 1, sum, multi);
		else
			break;
		sum -= x[i];
		multi /= x[i];
		while (i < n - 1 && x[i] == x[i + 1])
			++i;
	}
	return count;
}

int main()
{
	int n;
	while (cin >> n){
		int x[n];
		for (int i = 0; i < n; ++i)
			cin >> x[i];
		sort(x, x + n);
		cout << getLuckyPacket(x, n, 0, 0, 1) << endl;
	}
	return 0;
}