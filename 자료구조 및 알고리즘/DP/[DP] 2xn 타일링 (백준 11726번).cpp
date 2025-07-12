// 문제: https://www.acmicpc.net/problem/11726
#include <iostream>
using namespace std;

int main()
{
	int N;
	cin >> N;

	int DP[1001];
	DP[0] = 0;
	DP[1] = 1;
	DP[2] = 2;

	for (int i = 3; i <= N; i++)
	{
		DP[i] = (DP[i - 2] + DP[i - 1]) % 10007;
	}
	cout << DP[N] % 10007;
	return 0;
}