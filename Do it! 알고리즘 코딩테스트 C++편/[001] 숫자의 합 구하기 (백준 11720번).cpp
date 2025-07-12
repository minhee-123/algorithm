// 문제: https://www.acmicpc.net/problem/11720

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
	int cnt;
	string numbers;
	cin >> cnt >> numbers;

	int sum = 0;
	for (int i = 0; i < cnt; i++)
	{
		int num = numbers[i] - '0';
		sum += num;
	}
	cout << sum;
	return 0;
}