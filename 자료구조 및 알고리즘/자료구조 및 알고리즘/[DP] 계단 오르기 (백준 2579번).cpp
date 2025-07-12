// 문제: https://www.acmicpc.net/problem/2579
// DP는 손으로 푸는 과정이 좀 필요할 것 같음
// 초반 케이스부터 하나씩 손으로 풀어보며 일반식을 도출해야 함
#include <iostream>
#include <algorithm>
using namespace std;

int N;
int stair[301];
int DP[301]; //n번 계단을 반드시 밟았을 때 얻을 수 있는 최대 점수
// DP[n] = max(DP[n-2] + stair[n], DP[n-3] + stair[n] + stair[n-1])
// n-2번째 계단을 밟았을 때 최대 + n번째 계단 값 (n-1번째를 안밟으니 연속 3번 밟는 것을 예방)
// n-3번째 계단을 밟았을 때 최대 + n-1번째 계단 값 + n번째 계단값 (n-2번째를 안 밟았으니 연속 3번 밟는 것을 예방)
// 설명: https://yabmoons.tistory.com/510

int main()
{
	cin >> N;
	for (int i = 1; i <= N; i++) cin >> stair[i];

	if (N == 1) cout << stair[1];
	else if (N == 2) cout << stair[1] + stair[2];
	else
	{
		DP[0] = 0;
		DP[1] = stair[1];
		DP[2] = stair[1] + stair[2];

		for (int n = 3; n <= N; n++)
		{
			DP[n] = max(DP[n - 2] + stair[n], DP[n - 3] + stair[n] + stair[n - 1]);
		}
		cout << DP[N];
	}
	return 0;
}