// 문제: https://www.acmicpc.net/problem/1377

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	int N;
	cin >> N;

	vector<pair<int, int>> A(N); //N개의 비어있는 vector<int, int> 배열 생성
	for (int i = 0; i < N; i++)
	{
		cin >> A[i].first;
		A[i].second = i;
	}

	sort(A.begin(), A.end()); //first 값을 기준으로 정렬됨

	int M = 0;
	for (int i = 0; i < N; i++)
	{
		M = max(M, A[i].second - i);
	}

	cout << M + 1 << '\n';
	return 0;
}