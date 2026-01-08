// 문제: https://www.acmicpc.net/problem/14503
// 알고리즘: 그래프(는 아니고 그냥 시뮬레이션)
#include <iostream>
using namespace std;

int N, M;
int Map[50][50]; // 0은 청소해야 하는 칸, 1은 벽, 2는 청소가 완료된 칸

int dr[4] = {-1, 0, 1, 0}; // 북 동 남 서
int dc[4] = {0, 1, 0, -1};

int clean_space = 0;
int NR, NC, Ndir;

int main()
{
	cin >> N >> M;
	cin >> NR >> NC >> Ndir;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++) cin >> Map[i][j];
	}

	while (1)
	{
		// 현재 칸이 청소되지 않은 경우, 현재 칸을 청소한다
		if (Map[NR][NC] == 0)
		{
			Map[NR][NC] = 2;
			clean_space++;
			continue;
		}

		// 현재 칸의 주변 4칸 중에 청소 가능한 칸을 찾음
		bool can_clean = false;
		int nextdir = Ndir;
		for (int i = 0; i < 4; i++) // 반시계 방향으로 회전하며 찾음
		{
			nextdir--;
			if (nextdir == -1) nextdir = 3;

			int nextR = NR + dr[nextdir];
			int nextC = NC + dc[nextdir];

			if (nextR < 0 || nextR >= N || nextC < 0 || nextC >= M) continue;
			if (Map[nextR][nextC] > 0) continue;

			// 청소 가능한 칸이 있는 경우
			NR = nextR;
			NC = nextC;
			Ndir = nextdir;
			can_clean = true;
			break;
		}

		if (can_clean) continue;
		else // 청소 가능한 칸이 없는 경우
		{
			int nextR = NR - dr[Ndir];
			int nextC = NC - dc[Ndir];

			if (nextR < 0 || nextR >= N || nextC < 0 || nextC >= M) break;
			if (Map[nextR][nextC] == 1) break;

			NR = nextR;
			NC = nextC;
		}
	}
	cout << clean_space;
	return 0;
}