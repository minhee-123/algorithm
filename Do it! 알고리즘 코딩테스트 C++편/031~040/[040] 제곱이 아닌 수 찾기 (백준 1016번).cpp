// 문제: https://www.acmicpc.net/problem/1016

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	long Min, Max;
	cin >> Min >> Max;

	vector<bool> check(Max - Min + 1, false);

	for (long i = 2; i * i <= Max; i++)
	{
		long pow = i * i; //제곱수

		long start_index = Min / pow;
		if (Min % pow != 0) start_index++; //pow가 Min보다 크다면 0이니까 1로 만들고, Min보다 pow가 작다면 범위내에 들기 위해 +1

		for (long j = start_index; j * pow <= Max; j++) check[(j * pow) - Min] = true; //index 0의 값 == Min
	}

	int cnt = 0;
	for (int i = 0; i < Max - Min + 1; i++)
	{
		if (!check[i]) cnt++;
	}
	cout << cnt;
	return 0;
}