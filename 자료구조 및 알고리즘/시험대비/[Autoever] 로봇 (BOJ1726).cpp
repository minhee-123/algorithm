// 문제: https://www.acmicpc.net/problem/1726
// 알고리즘: 그래프
#include <iostream>
#include <queue>
using namespace std;

int N, M;
int Map[100][100];
int visit[100][100][4]; // 바라보는 방향 또한 구분
// 특정 위치에 도착한 방향에 따라 결과가 달라짐 (해당 위치와 방향에 명령 몇번을 소요했는지)

int dr[4] = {-1, 0, 1, 0}; // 북 동 남 서
int dc[4] = {0, 1, 0, -1};

int SR, SC, Sdir;
int ER, EC, Edir;

struct ELEMENT
{
	int R;
	int C;
	int dir;
};

int main()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++) cin >> Map[i][j];
	}

	cin >> SR >> SC >> Sdir;
	SR--;
	SC--;
	if (Sdir == 2) Sdir = 3;
	else if (Sdir == 3) Sdir = 2;
	else if (Sdir == 4) Sdir = 0;

	cin >> ER >> EC >> Edir;
	ER--;
	EC--;
	if (Edir == 2) Edir = 3;
	else if (Edir == 3) Edir = 2;
	else if (Edir == 4) Edir = 0;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			for (int k = 0; k < 4; k++) visit[i][j][k] = -1;
		}
	} // visit 배열 -1로 초기화

	queue<ELEMENT> que;
	que.push({ SR, SC, Sdir });
	visit[SR][SC][Sdir] = 0;

	while (!que.empty())
	{
		int nowR = que.front().R;
		int nowC = que.front().C;
		int nowdir = que.front().dir;
		que.pop();

		int command_cnt = visit[nowR][nowC][nowdir];

		// 명령 1
		for (int k = 1; k <= 3; k++)
		{
			int nextR = nowR + dr[nowdir] * k;
			int nextC = nowC + dc[nowdir] * k;

			if (nextR < 0 || nextR >= N || nextC < 0 || nextC >= M) continue; // 격자를 벗어나는 경우
			if (Map[nextR][nextC] == 1) break; // 길이 막혀있는 경우 명령1을 더이상 진행할 수 없음
			if (visit[nextR][nextC][nowdir] != -1) continue; // 이미 방문한 경우

			visit[nextR][nextC][nowdir] = command_cnt + 1;
			que.push({ nextR, nextC, nowdir });
		}

		// 명령 2
		for (int k = 0; k < 2; k++)
		{
			if (k == 0) // turn right
			{
				int nextdir = nowdir + 1;
				if (nextdir == 4) nextdir = 0;
				if (visit[nowR][nowC][nextdir] != -1) continue;

				visit[nowR][nowC][nextdir] = command_cnt + 1;
				que.push({ nowR, nowC, nextdir });
			}
			else // turn left
			{
				int nextdir = nowdir - 1;
				if (nextdir == -1) nextdir = 3;
				if (visit[nowR][nowC][nextdir] != -1) continue;

				visit[nowR][nowC][nextdir] = command_cnt + 1;
				que.push({ nowR, nowC, nextdir });
			}
		}

		if (visit[ER][EC][Edir] != -1) break;
	}

	cout << visit[ER][EC][Edir];
	return 0;
}
// 자잘한 실수 조심하자 (정신차리고 풀어라!!)