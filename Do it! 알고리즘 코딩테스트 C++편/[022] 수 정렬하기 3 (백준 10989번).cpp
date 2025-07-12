// 문제: https://www.acmicpc.net/problem/10989

#include <iostream>
using namespace std;

int main()
{
	int N;
	cin >> N;

	int A[10001] = { 0 };
	for (int i = 0; i < N; i++)
	{
		int temp;
		cin >> temp;
		A[temp]++;
	}

	for (int i = 1; i <= 10000; i++)
	{
		if (A[i] > 0)
		{
			int cnt = A[i];
			while (cnt--) cout << i << '\n';
		}
	}
	return 0;
}