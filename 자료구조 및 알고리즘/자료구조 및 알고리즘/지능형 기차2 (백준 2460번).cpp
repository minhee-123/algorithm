// 지능형 기차2 (https://www.acmicpc.net/problem/2460)

#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	int train[10] = {}, people[10][2] = {};
	for (int i = 0; i < 10; i++)
	{
		cin >> people[i][0] >> people[i][1];
	}

	train[0] = people[0][1];
	for (int i = 1; i < 10; i++)
	{
		train[i] = train[i - 1] - people[i][0] + people[i][1];
	}
	int *max = max_element(train, train + 10);

	cout << *max;
	return 0;
}