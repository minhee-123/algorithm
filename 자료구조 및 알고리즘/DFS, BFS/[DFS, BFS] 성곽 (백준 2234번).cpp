// 문제: https://www.acmicpc.net/problem/2234
#include <iostream>
using namespace std;

// 벽이 있으면 서쪽 (+1), 북쪽 (+2), 동쪽 (+4), 남쪽 (+8) → 비트마스크 활용
// 비트마스크 문법: https://kimtaesoo99.tistory.com/121

// 문제에서 세번째로 구해야하는 값의 경우
// 한번 DFS를 할때 각 방의 영역을 저장해둬서 이용하면 편리함 (벽으로 분리된 두 방을 찾아서 더함)

int N, M;
int Map[50][50];

int dr[4] = { 0, -1, 0, 1 };
int dc[4] = { -1, 0, 1, 0 };
int mask[4] = { 1, 2, 4, 8 };

void Input()
{
	cin >> M >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++) cin >> Map[i][j];
	}
}

int room_cnt = 0;
int max_room_area = 0;

int Map_divide[50][50];
int room_area[2500]; // 벽이 전부 설치되어 있는 경우: 2500 (max)

bool visit[50][50];
int temp_area = 0;

void DFS(int R, int C, int num)
{
	if (visit[R][C]) return;
	visit[R][C] = true;

	temp_area++;
	Map_divide[R][C] = num;

	for (int i = 0; i < 4; i++)
	{
		if (Map[R][C] & mask[i]) continue; // 해당 방향으로 벽이 있는 경우
		int NR = R + dr[i];
		int NC = C + dc[i];

		if (NR < 0 || NR >= N || NC < 0 || NC >= M) continue;
		if (visit[NR][NC]) continue;

		DFS(NR, NC, num);
	}
}

int Find_Max_Broken()
{
	int max_broken = 0;

	for (int R = 0; R < N; R++)
	{
		for (int C = 0; C < M; C++)
		{
			for (int i = 0; i < 4; i++)
			{
				if (Map[R][C] & mask[i]) // 벽이 있는 경우 broken
				{
					int NR = R + dr[i];
					int NC = C + dc[i];
					if (NR < 0 || NR >= N || NC < 0 || NC >= M) continue;
					if (Map_divide[R][C] == Map_divide[NR][NC]) continue;

					int broken = room_area[Map_divide[R][C]] + room_area[Map_divide[NR][NC]];
					if (broken > max_broken) max_broken = broken;
				}
			}
		}
	}

	return max_broken;
}

void Solution()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			temp_area = 0;
			DFS(i, j, room_cnt);

			if (temp_area > 0)
			{
				room_area[room_cnt++] = temp_area;
				if (temp_area > max_room_area) max_room_area = temp_area;
			}
		}
	}
	cout << room_cnt << '\n';
	cout << max_room_area << '\n'; // answer 1

	int max_broken_area = Find_Max_Broken();
	cout << max_broken_area;
}

int main()
{
	Input();
	Solution();
	return 0;
}