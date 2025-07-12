// 문제: https://www.acmicpc.net/problem/1463
#include <iostream>
#include <vector>
using namespace std;

// 연산을 거꾸로 생각해보면 된다
// 나누고 빼고해서 1을 만듬 → 곱하고 더해서 원래의 숫자로 돌아갈 것
// DP[i] = DP[i/3] + 1; → 마지막에 3으로 나누어줌 (마지막 연산: 3으로 나누기)
// DP[i] = DP[i/2] + 1; → 마지막에 2로 나누어줌 (마지막 연산: 2로 나누기)
// DP[i] = DP[i-1] + 1; → 마지막에 1로 빼줌 (마지막 연산: 1을 빼기)
// 위에 값 중에 최소가 DP[i]가 됨

int main()
{
	int N;
	cin >> N;

	vector<int> DP(N + 1, 0);
	DP[1] = 0;

	if (N == 1) cout << 0;
	else
	{
		for (int i = 2; i <= N; i++)
		{
			DP[i] = DP[i - 1] + 1;
			if (i % 3 == 0) DP[i] = min(DP[i], DP[i / 3] + 1);
			if (i % 2 == 0) DP[i] = min(DP[i], DP[i / 2] + 1);
		}
		cout << DP[N];
	}
	return 0;
}