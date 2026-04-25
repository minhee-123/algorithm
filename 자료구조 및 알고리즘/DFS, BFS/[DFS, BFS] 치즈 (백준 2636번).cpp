// 문제: https://www.acmicpc.net/problem/2636
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

int N, M;
int Map[101][101];
int Copy_Map[101][101];

int dr[4] = { 0, 0, 1, -1 }; // 우 좌 하 상
int dc[4] = { 1, -1, 0, 0 };
bool visit[101][101];
int cnt_cheese = 0;

int answerT;
vector<int> cheese;

void DFS(int R, int C)
{
	if (visit[R][C]) return;
	visit[R][C] = true;

	for (int i = 0; i < 4; i++)
	{
		int NR = R + dr[i];
		int NC = C + dc[i];

		if (NR < 0 || NR >= N || NC < 0 || NC >= M) continue;
		if (visit[NR][NC]) continue;

		if (Copy_Map[NR][NC] == 0) DFS(NR, NC);
		else // 0을 탐색하던 중 만난 1은 치즈 가장자리
		{
			Map[NR][NC] = 0;
			cnt_cheese--;
			visit[NR][NC] = true; // 더 안쪽으로 방문할 수 없도록 방문처리
		}
	}
}

void Copy() // Map 정보를 Copy_Map으로 복사
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++) Copy_Map[i][j] = Map[i][j];
	}
}

int main()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> Map[i][j];
			if (Map[i][j] == 1) cnt_cheese++;
		}
	}
	Copy();
	cheese.push_back(cnt_cheese);

	while (1)
	{
		memset(visit, false, sizeof(visit));
		answerT++;

		DFS(0, 0);
		if (cnt_cheese == 0) break;

		Copy();
		cheese.push_back(cnt_cheese);
	}

	cout << answerT << '\n' << cheese[answerT - 1];
	return 0;
}

// 문제를 좀 잘못 읽어서 다시 품
// 영역 내에 빈 공간이 있을 수 있는 상황 → 가장자리 찾기
// 외부에서 시작해 0을 탐색하다가 처음 1을 만나는 경우가 가장자리임
// (가장자리를 visit 처리해서 내부로 못 들어가도록 처리, 값이 0인 경우만 DSF 진행)