// 문제: https://www.acmicpc.net/problem/2775
#include <iostream>
using namespace std;

int T;
int A, B;
int DP[15][15];

int main()
{
	// 층은 0부터 14까지 (a)
	// 호수는 1부터 14까지 (b)

	for (int i = 1; i <= 14; i++)
	{
		DP[0][i] = i;
		DP[i][1] = 1;
	} 
	// 0층의 i호에는 i명이 거주
	// i층의 1호에는 1명이 거주 (0층 1호에 1명이 거주하기 때문)

	for (int a = 1; a <= 14; a++)
	{
		for (int b = 2; b <= 14; b++)
		{
			DP[a][b] = DP[a][b - 1] + DP[a - 1][b];
			// a층의 b-1호는 a-1층의 1호부터 b-1호까지 포함, 여기에 a-1층의 b호를 더하면 a층의 b호가 됨
			// 점화식을 도출하는 연습을 할 필요가 있음
		}
	}

	cin >> T;
	for (int i = 0; i < T; i++)
	{
		cin >> A >> B;
		cout << DP[A][B] << '\n';
	}
	return 0;
}