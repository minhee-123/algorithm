// 문제: https://www.acmicpc.net/problem/2750

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int N;
	cin >> N;

	vector<int> A(N, 0);
	for (int i = 0; i < N; i++)
	{
		cin >> A[i];
	}

	for (int i = 0; i < N - 1; i++)
	{
		for (int j = i; j < N; j++)
		{
			if (A[i] > A[j])
			{
				int temp = A[i];
				A[i] = A[j];
				A[j] = temp;
			}
		}
	}

	for (int i = 0; i < N; i++)
	{
		cout << A[i] << '\n';
	}
	return 0;
}