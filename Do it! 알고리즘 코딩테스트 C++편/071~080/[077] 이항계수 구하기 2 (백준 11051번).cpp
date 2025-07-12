// 문제: https://www.acmicpc.net/problem/11051
#include <iostream>
using namespace std;

#define MOD (10007)

int N, K;
int DP[1001][1001];

int main()
{
	cin >> N >> K;

	for (int i = 0; i <= N; i++)
	{
		DP[i][0] = 1;
		DP[i][1] = i;
		DP[i][i] = 1;
	}

	for (int i = 2; i <= N; i++)
	{
		for (int j = 2; j < i; j++)
		{
			DP[i][j] = ((DP[i - 1][j] % MOD) + (DP[i - 1][j - 1] % MOD)) % MOD;
			//앞의 문제에 MOD 연산만 추가
		}
	}

	cout << DP[N][K];
	return 0;
}