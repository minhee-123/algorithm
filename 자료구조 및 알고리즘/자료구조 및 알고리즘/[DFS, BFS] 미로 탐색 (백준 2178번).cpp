// 미로탐색 (https://www.acmicpc.net/problem/2178)

#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

int main()
{
	int N, M;
	int MAP[105][105] = { 0 };

	cin >> N >> M;
	for (int i = 1; i <= N; i++)
	{
		string temp_st;
		cin >> temp_st;
		for (int j = 1; j <= M; j++)
		{
			int temp_int = temp_st[j - 1] - '0';
			MAP[i][j] = temp_int;
		}
	}

	int visit[105][105] = { 0 }; //false
	int score[105][105] = { 0 }; //도착하기까지 거쳐온 칸 수 저장
	int dr[4] = { 0, 1, 0, -1 }; //좌 상 우 하 (방향 부분 정신차리고 봐야할듯)
	int dc[4] = { -1, 0, 1, 0 };

	queue<pair <int, int>> q;
	q.push({ 1, 1 });
	visit[1][1] = 1;
	score[1][1] = 1;

	while (!q.empty())
	{
		int now_r = q.front().first;
		int now_c = q.front().second;
		visit[now_r][now_c] = 1;
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int new_r = now_r + dr[i];
			int new_c = now_c + dc[i];

			if (new_r <= 0 || new_r > N || new_c <= 0 || new_c > M) continue;
			if (MAP[new_r][new_c] == 0) continue;
			if (visit[new_r][new_c] == 1) continue;

			q.push({ new_r, new_c });
			visit[new_r][new_c] = 1;
			score[new_r][new_c] = score[now_r][now_c] + 1;
		}
	}

	cout << score[N][M] << '\n';
	return 0;
}