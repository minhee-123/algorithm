// 문제: https://www.acmicpc.net/problem/1427

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
	string N;
	cin >> N;

	vector<int> A(N.size(), 0);
	for (int i = 0; i < N.size(); i++)
	{
		A[i] = N[i] - '0';
	}

	for (int i = 0; i < A.size() - 1; i++) //0부터 N-2 index까지만 바꾸기가 수행됨 (N-1 index는 자동적으로 값이 결정)
	{
		int M = A[i];
		int M_index = i;
		for (int j = i; j < A.size(); j++)
		{
			if (A[j] > M)
			{
				M = A[j];
				M_index = j;
			} //최대값을 찾음
		}

		if (M_index != i) //index i 자리가 아닌 곳에 최대값이 있다면
		{
			A[M_index] = A[i];
			A[i] = M;
		}
	}

	for (int i = 0; i < A.size(); i++)
	{
		cout << A[i];
	}
	return 0;
}