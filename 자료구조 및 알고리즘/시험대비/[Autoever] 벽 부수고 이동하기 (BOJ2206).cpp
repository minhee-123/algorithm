// 문제: https://www.acmicpc.net/problem/2206
// 알고리즘: 그래프
#include <iostream>
#include <queue>
#include <string>
#include <cstring>
using namespace std;

int N, M;
int Map[1001][1001];
int visit[1001][1001][2]; // 마지막 값: 벽을 부쉈는지 여부 (0:안부쉈음, 1:부쉈음)

int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0, 1, 0, -1 };

struct VALUE
{
	int R;
	int C;
	int use = 0;
};

int main()
{
	cin >> N >> M;
	for (int i = 1; i <= N; i++)
	{
		string st;
		cin >> st;
		for (int j = 1; j <= M; j++) Map[i][j] = st[j - 1] - '0';
	} // 입력을 받아옴

	queue<VALUE> que;
	que.push({ 1, 1, 0 });

	memset(visit, -1, sizeof(visit));
	visit[1][1][0] = 1;

	int answer = -1;

	while (!que.empty())
	{
		int nowR = que.front().R;
		int nowC = que.front().C;
		int use = que.front().use;
		que.pop();

		if (nowR == N && nowC == M)
		{
			answer = visit[N][M][use];
			break;
		}

		for (int i = 0; i < 4; i++)
		{
			int nextR = nowR + dr[i];
			int nextC = nowC + dc[i];

			if (nextR <= 0 || nextR > N || nextC <= 0 || nextC > M) continue;
			
			if (Map[nextR][nextC] == 0)
			{
				// 맵이 0인 경우 이전에 들리지 않았다면 방문
				if (visit[nextR][nextC][use] == -1)
				{
					visit[nextR][nextC][use] = visit[nowR][nowC][use] + 1;
					que.push({ nextR, nextC, use });
				}
			}
			else // Map[nextR][nextC] == 1
			{
				// 맵이 1인 경우 아직 벽을 부수지 않았고, 이전에 들리지 않았다면 방문
				if (use == 0 && visit[nextR][nextC][1] == -1)
				{
					visit[nextR][nextC][1] = visit[nowR][nowC][use] + 1;
					que.push({ nextR, nextC, 1 });
				}
			}
		}
	}

	cout << answer;
	return 0;
}