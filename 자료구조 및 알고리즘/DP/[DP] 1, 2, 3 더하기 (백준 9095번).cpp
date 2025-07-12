// 문제: https://www.acmicpc.net/problem/9095
// DP 문제는 점화식을 찾는 게 관건이다
// 점화식이 잘 보이지 않는다면 초반을 직접 계산하면서 점화식을 찾아보자

// DP에 꽂혀서 그렇지 모든 조합을 체크하는 DFS로도 풀 수 있다 
// → N이면 cnt++, N을 초과하면 그냥 return)

#include <iostream>
using namespace std;

int T;
int N; //정수 N
int DP[12];

int main()
{
	DP[0] = 0;
	DP[1] = 1;
	DP[2] = 2;
	DP[3] = 4;

	for (int i = 4; i <= 11; i++)
	{
		DP[i] = DP[i - 1] + DP[i - 2] + DP[i - 3];
	}

	cin >> T;
	for (int i = 0; i < T; i++)
	{
		cin >> N;
		cout << DP[N] << '\n';
	}
	return 0;
}