// 문제: https://www.acmicpc.net/problem/14500

/* 풀이가 도저히 떠오르지 않아 다른 사람의 풀이를 참고했다 */
/*
참고한 풀이: https://wantchicken.tistory.com/8
(1) 한 점에서 시작해서 상하좌우에 있는 점으로 이동하며 총 4개의 점을 방문
	→ 분홍색 테트로미노를 제외하고는 모두 확인할 수 있음 (상하좌우로 이어지기 때문)
(2) 분홍색 테트로미노만 따로 처리해주면 됨 → 따로 구현
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M;
vector<vector<int>> Map;

vector<vector<bool>> visit;
int maxSum = 0;

int dr[4] = { 0, 0, 1, -1 }; // 우 좌 하 상
int dc[4] = { 1, -1, 0, 0 };

void DFS(int NR, int NC, int Sum, int depth)
{
	if (depth == 4)
	{
		maxSum = max(Sum, maxSum);
		return;
	}

	for (int i = 0; i < 4; i++)
	{
		int R = NR + dr[i];
		int C = NC + dc[i];

		if (R < 0 || R >= N || C < 0 || C >= M) continue;
		if (visit[R][C]) continue;

		visit[R][C] = true;
		DFS(R, C, Sum + Map[R][C], depth + 1);
		visit[R][C] = false;
	}
}

void check_pink()
{
	for (int R = 0; R < N; R++)
	{
		for (int C = 0; C < M; C++)
		{
			for (int dir = 0; dir < 4; dir++)
			{
				int Sum = Map[R][C];

				int NR = R + dr[dir];
				int NC = C + dc[dir];

				if (NR < 0 || NR >= N || NC < 0 || NC >= M) continue;

				if (dir == 0 || dir == 1) // 우 좌
				{
					int NR_up = NR + dr[3];
					int NC_up = NC + dc[3];

					int NR_down = NR + dr[2];
					int NC_down = NC + dc[2];

					if (NR_up < 0 || NR_up >= N || NC_up < 0 || NC_up >= M) continue;
					if (NR_down < 0 || NR_down >= N || NC_down < 0 || NC_down >= M) continue;
				
					Sum += (Map[NR][NC] + Map[NR_up][NC_up] + Map[NR_down][NC_down]);
				}
				else if (dir == 2 || dir == 3) // 하 상
				{
					int NR_r = NR + dr[0];
					int NC_r = NC + dc[0];

					int NR_l = NR + dr[1];
					int NC_l = NC + dc[1];

					if (NR_r < 0 || NR_r >= N || NC_r < 0 || NC_r >= M) continue;
					if (NR_l < 0 || NR_l >= N || NC_l < 0 || NC_l >= M) continue;

					Sum += (Map[NR][NC] + Map[NR_r][NC_r] + Map[NR_l][NC_l]);
				}

				maxSum = max(Sum, maxSum);
			}
		}
	}
}

int main()
{
	cin >> N >> M;
	Map.resize(N);
	visit.resize(N);

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			int temp;
			cin >> temp;

			Map[i].push_back(temp);
			visit[i].push_back(false);
		}
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			visit[i][j] = true;
			DFS(i, j, Map[i][j], 1);
			visit[i][j] = false;
		}
	} // 분홍색을 제외한 테트로미노 확인
	check_pink(); //분홍색 테트로미노 확인

	cout << maxSum;
	return 0;
}