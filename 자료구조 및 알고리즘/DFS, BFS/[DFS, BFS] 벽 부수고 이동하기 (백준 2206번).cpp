// 문제: https://www.acmicpc.net/problem/2206
#include <iostream>
#include <string>
#include <queue>
using namespace std;

// 최단거리 이동 문제 + 벽 하나 부셔도 됨 (장애물 하나 무시 가능)
int dr[4] = { 0, 0, 1, -1 };
int dc[4] = { 1, -1, 0, 0 };

int N, M;
int Map[1000][1000]; // (0, 0)과 (N-1, M-1)은 항상 0 → 장애물 없음
bool visit[1000][1000][2]; // 0은 벽을 부순 상태, 1은 벽을 아직 부수지 않은 상태 (벽을 부술 기회는 1)
int answer = -1;

struct inform
{
	int R;
	int C;
	int moveCNT;
	int chance;
};

int main()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		string temp;
		cin >> temp;
		for (int j = 0; j < M; j++)
		{
			int num = temp[j] - '0';
			Map[i][j] = num;
		}
	}

	queue<inform> que;
	que.push({ 0, 0, 1, 1 }); // 시작하는 칸과 끝나는 칸도 포함해서 count
	visit[0][0][1] = true; // 벽은 하나까지 부술 수 있음

	while (!que.empty())
	{
		int R = que.front().R;
		int C = que.front().C;
		int moveCNT = que.front().moveCNT;
		int chance = que.front().chance; // 벽을 부술 수 있는 기회

		que.pop();

		if (R == N - 1 && C == M - 1)
		{
			answer = moveCNT;
			break;
		}

		for (int i = 0; i < 4; i++)
		{
			int NR = R + dr[i];
			int NC = C + dc[i];
			int Nchance = chance;

			if (NR < 0 || NR >= N || NC < 0 || NC >= M) continue;
			if (Map[NR][NC] == 1)
			{
				if (Nchance == 0) continue; // 벽 부수기 기회가 없는 상태
				else Nchance--; // 벽 부수기 기회가 있는 상태 (벽을 부수고 도착) 
			}
			if (visit[NR][NC][Nchance]) continue; // 같은 상태의 최단거리를 관리
			// 벽 부수기를 따지고 visit 체크 → 벽을 부순 경우 벽을 부순 상태에 진입하기 때문 (이전에 visit을 체크하면 동일 상태를 중복 탐색)

			visit[NR][NC][Nchance] = true;
			que.push({ NR, NC, moveCNT + 1, Nchance });
		}
	}

	cout << answer;
	return 0;
}

/*
너무 오랜만에 풀어서 감각이 아직 안 돌아오나 보다
어이없는 실수를 너무 많이 함
구현은 집중이 핵심! 조건을 하나씩 잘 처리하는 게 핵심!
*/