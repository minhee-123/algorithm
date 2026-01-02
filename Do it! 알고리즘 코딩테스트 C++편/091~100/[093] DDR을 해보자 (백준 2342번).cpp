// 문제: https://www.acmicpc.net/problem/2342
#include <iostream>
#include <queue>
using namespace std;

// 내용만 보면 완탐(백트래킹)을 해야되지 않나 싶은데
// command의 수가 최대 10^5으로 완탐을 할 경우 시간이 터짐 → 무조건 DP 적용해야 함

long D[100001][5][5]; // D[N][L][R] = N번째 명령에서 (L(왼발), R(오른발)) 위치의 최소로 사용한 힘
int mp[5][5] =
{
	{0, 2, 2, 2, 2},
	{2, 1, 3, 4, 3},
	{2, 3, 1, 3, 4},
	{2, 4, 3, 1, 3},
	{2, 3, 4, 3, 1}
}; // mp[i][j] = i에서 j로 이동할 때 소요되는 힘

int main()
{
	for (int i = 0; i <= 100000; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			for (int k = 0; k < 5; k++) D[i][j][k] = 100001 * 5; // 매우 큰 수로 초기화
		}
	}
	D[0][0][0] = 0; // 시작 점은 0

	int command = -1;
	int cnt = 0;
	while (1)
	{
		cin >> command;
		if (command == 0) break;
		cnt++;

		// 왼발이 command로 이동하는 경우
		for (int L = 0; L < 5; L++)
		{
			for (int R = 0; R < 5; R++)
			{
				if (R == command) continue; // 두 발이 같은 지점에 있는 것이 허용되지 않음
				// 이전 명령에서 (L, R) 위치를 현재 명령 (command, R) 위치로 옮길 때 최소힘 찾기
				D[cnt][command][R] = min(D[cnt - 1][L][R] + mp[L][command], D[cnt][command][R]);
			}
		}

		// 오른발이 command로 이동하는 경우
		for (int R = 0; R < 5; R++)
		{
			for (int L = 0; L < 5; L++)
			{
				if (L == command) continue;
				D[cnt][L][command] = min(D[cnt - 1][L][R] + mp[R][command], D[cnt][L][command]);
			}
		}
	}

	long answer = 100001 * 5;
	for (int L = 0; L < 5; L++)
	{
		for (int R = 0; R < 5; R++)
		{
			answer = min(answer, D[cnt][L][R]);
		}
	}

	cout << answer;
	return 0;
}