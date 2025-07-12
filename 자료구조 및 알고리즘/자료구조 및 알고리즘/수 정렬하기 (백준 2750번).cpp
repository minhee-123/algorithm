// 문제: https://www.acmicpc.net/problem/2750

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	int N;
	cin >> N;

	vector<int> A(N, 0);
	for (int i = 0; i < N; i++) cin >> A[i];

	sort(A.begin(), A.end());

	for (int i = 0; i < N; i++) cout << A[i] << '\n';
	return 0;
}