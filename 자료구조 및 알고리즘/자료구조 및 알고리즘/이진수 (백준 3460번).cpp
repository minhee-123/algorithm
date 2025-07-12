// 이진수 (https://www.acmicpc.net/problem/3460)
// 10진수를 2진수로 변환하는 방법: 2로 계속 나눈 뒤 나머지를 역순으로 읽으면 됨
// (역순으로 읽는 거니까 첫번째 나머지가 0번째 위치)

#include <iostream>
#include <vector>
using namespace std;

int num10 = 0;
vector<int> num2;

void calculate()
{
	num2.clear();

	cin >> num10;

	int temp = num10;
	while (1)
	{
		num2.push_back(temp % 2);
		temp = temp / 2;

		if (temp == 0) break;
	}

	for (int i = 0; i < num2.size(); i++)
	{
		if (num2[i] == 1) cout << i << " ";
	}
}

int main()
{
	int T; cin >> T;
	for (int i = 0; i < T; i++)
	{
		calculate();
	}
	return 0;
}