// 문제: https://www.acmicpc.net/problem/16234
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

int N, Min, Max;
int Map[51][51];

int visit[51][51]; // 영역표시 + visit 관리
int union_cnt[2501]; // 각 연합의 인구 수
int island_cnt[2501]; // 각 연합에 속한 칸의 개수
// 50x50=2500 최대는 2500이라 널널하게 선언해야 함 (계산 실수해서 작게 선언하니 바로 틀림)

int union_cnt_now = 0;
int island_cnt_now = 0;

int dr[4] = { 1, -1, 0, 0 };
int dc[4] = { 0, 0, 1, -1 };

void DFS(int R, int C, int num)
{
	if (visit[R][C] > 0) return;
	visit[R][C] = num;
	union_cnt_now += Map[R][C];
	island_cnt_now++;

	for (int i = 0; i < 4; i++)
	{
		int NR = R + dr[i];
		int NC = C + dc[i];

		if (NR < 0 || NR >= N || NC < 0 || NC >= N) continue;
		if (visit[NR][NC] > 0) continue;

		int diff = abs(Map[R][C] - Map[NR][NC]);
		if (diff >= Min && diff <= Max) DFS(NR, NC, num);
	}
}

bool Move() // 한 번 인구이동 (인구이동이 불가능할 경우 false 반환)
{
	memset(union_cnt, 0, sizeof(union_cnt));
	memset(island_cnt, 0, sizeof(island_cnt));
	memset(visit, 0, sizeof(visit));

	int num = 1;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (visit[i][j] > 0) continue;

			union_cnt_now = 0;
			island_cnt_now = 0;
			DFS(i, j, num);

			if (island_cnt_now > 1) // 2개 이상의 칸이 연결
			{
				union_cnt[num] = union_cnt_now;
				island_cnt[num] = island_cnt_now;
				num++;
			}
			else visit[i][j] = 0; // 방문 취소
		}
	}

	if (num == 1) return false; // 연합이 생성되지 않음 (인구이동 불가능)

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (visit[i][j] == 0) continue;
			Map[i][j] = union_cnt[visit[i][j]] / island_cnt[visit[i][j]];
		}
	}
	return true;
}

int main()
{
	cin >> N >> Min >> Max;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++) cin >> Map[i][j];
	}

	int answer = 0;
	while (1)
	{
		bool flag = Move();
		if (flag) answer++;
		else break;

		if (answer > 2000) break; // 정답은 2000 이하
	}

	cout << answer;
	return 0;
}