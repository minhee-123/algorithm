// 문제: https://www.acmicpc.net/problem/2178

#include <iostream>
#include <queue>
#include <string>
using namespace std;

int N, M;

int MAP[101][101] = { 0 };
int cnt[101][101] = { 0 };
bool visit[101][101];

int dr[4] = {1, 0, 0, -1}; //상 우 좌 하
int dc[4] = {0, 1, -1, 0};

void BFS(int r, int c)
{
	queue<pair<int, int>> q;
	q.push({ r, c });
	cnt[r][c] = 1;
	visit[r][c] = true;

	while (!q.empty())
	{
		int now_r = q.front().first;
		int now_c = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int new_r = now_r + dr[i];
			int new_c = now_c + dc[i];

			if (new_r <= 0 || new_r >= N + 1 || new_c <= 0 || new_c >= M + 1) continue; //범위는 항상 주의하자 (M+1을 N+1이라고 써서 틀림)
			if (visit[new_r][new_c] || MAP[new_r][new_c] == 0) continue;

			visit[new_r][new_c] = true;
			cnt[new_r][new_c] = cnt[now_r][now_c] + 1;
			q.push({ new_r, new_c });
		}
	}
}

int main()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		string temp;
		cin >> temp;
		for (int j = 0; j < M; j++)
		{
			int val = temp[j] - '0';
			MAP[i + 1][j + 1] = val;
		}
	}

	BFS(1, 1);
	cout << cnt[N][M] << '\n';

	return 0;
}