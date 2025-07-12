// 문제: https://www.acmicpc.net/problem/16236
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

int dr[4] = { -1, 0, 0, 1 }; //상 좌 우 하
int dc[4] = { 0, -1, 1, 0 };

int N;
int MAP[20][20];

int sharkR, sharkC;
int sharkSize = 2; //시작 크기는 2
int sharkEat = 0; //먹은 물고기의 수

struct Move
{
	int dis;
	int row;
	int col;
};

bool comp(Move A, Move B)
{
	if (A.dis != B.dis) return A.dis < B.dis;
	else if (A.row != B.row) return A.row < B.row;
	else return A.col < B.col;
}

int main()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> MAP[i][j];

			if (MAP[i][j] == 9)
			{
				sharkR = i;
				sharkC = j;
			} //아기상어의 시작 위치
		}
	} //맵 정보 저장

	int Time = 0;
	while (1)
	{
		queue<pair<int, int>> que;
		que.push({ sharkR, sharkC });

		bool visit[20][20];
		memset(visit, false, sizeof(visit));
		visit[sharkR][sharkC] = true;

		int record[20][20] = { 0 };
		record[sharkR][sharkC] = 0;

		vector<Move> can_move;

		while (!que.empty())
		{
			int R = que.front().first;
			int C = que.front().second;
			que.pop();

			for (int i = 0; i < 4; i++)
			{
				int NR = R + dr[i];
				int NC = C + dc[i];

				if (NR < 0 || NR >= N || NC < 0 || NC >= N) continue;
				if (visit[NR][NC]) continue;
				if (MAP[NR][NC] > sharkSize) continue; //아기상어보다 크면 지나갈 수 없음

				record[NR][NC] = record[R][C] + 1;
				visit[NR][NC] = true;
				
				que.push({ NR, NC });
				if (MAP[NR][NC] != 0 && MAP[NR][NC] < sharkSize) can_move.push_back({ record[NR][NC], NR, NC });
			}
		}

		if (can_move.empty()) break; //먹을 수 없다면
		else
		{
			sort(can_move.begin(), can_move.end(), comp);

			MAP[sharkR][sharkC] = 0;
			sharkR = can_move[0].row;
			sharkC = can_move[0].col;
			MAP[sharkR][sharkC] = 9;

			Time += can_move[0].dis;
			sharkEat++;

			if (sharkEat == sharkSize) //아기상어 성장
			{
				sharkSize++;
				sharkEat = 0;
			}
		}
	}

	cout << Time;
	return 0;
}