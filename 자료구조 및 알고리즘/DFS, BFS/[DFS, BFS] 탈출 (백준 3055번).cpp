// 문제: https://www.acmicpc.net/problem/3055
#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

// 고슴도치는 다음 시간에 물이 찰 예정인 칸으로 이동할 수 없다는 조건
// → 해당 지문이 없었으면 더 빨리 풀었을 것 같다
// → 문제 설명이 똥 같음
// → 물이랑 고슴도치는 동시에 이동하기 때문에 물이 덮쳐오는 순간 고슴도치가 이동할 수 있음
// → 저 조건이 제대로 적용이 안되는데 왜 써져있던 거임? (다음 시간이라는게 그냥 동시 이동을 말한듯)

int dr[4] = { 0, 0, 1, -1 };
int dc[4] = { 1, -1, 0, 0 };

int N, M;
int Map[50][50];
// 0: 비어있음
// 1: 물
// 2: 돌
// 3: 비버의 굴 (도착점)

int DR, DC; // 비버의 굴 위치
int SR, SC; // 고슴도치의 위치
vector<pair<int, int>> water; // 물의 위치

void Input()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		string temp;
		cin >> temp;

		for (int j = 0; j < M; j++)
		{
			char tp = temp[j];
			if (tp == '.') Map[i][j] = 0;
			else if (tp == '*')
			{
				Map[i][j] = 1;
				water.push_back({ i, j });
			}
			else if (tp == 'X') Map[i][j] = 2;
			else if (tp == 'D')
			{
				Map[i][j] = 3;
				DR = i;
				DC = j;
			}
			else if (tp == 'S')
			{
				SR = i;
				SC = j;
			}
		}
	}
}

struct inform
{
	int R;
	int C;
	int turn; // 현재 몇번째 턴인지 (턴이 증가하면 물 확장)
};
bool visit[50][50];

int main()
{
	Input();

	queue<inform> que;
	que.push({ SR, SC, 0 });

	visit[SR][SC] = true;
	int nowTurn = -1;

	while (!que.empty())
	{
		int R = que.front().R; // 고슴도치의 현재 위치 R
		int C = que.front().C; // 고슴도치의 현재 위치 C
		int turn = que.front().turn;

		que.pop();

		if (R == DR && C == DC) // 비버굴 도착 확인
		{
			std::cout << turn;
			return 0;
		}
		
		if (turn > nowTurn) // 물 확장 수행
		{
			int water_size = water.size();
			for (int i = 0; i < water_size; i++)
			{
				int wr = water[i].first;
				int wc = water[i].second;

				for (int j = 0; j < 4; j++)
				{
					int nwr = wr + dr[j];
					int nwc = wc + dc[j];

					if (nwr < 0 || nwr >= N || nwc < 0 || nwc >= M) continue;
					if (Map[nwr][nwc] >= 1) continue;

					Map[nwr][nwc] = 1;
					water.push_back({ nwr, nwc });
				}
			}
			nowTurn = turn;
		}

		for (int i = 0; i < 4; i++)
		{
			int NR = R + dr[i];
			int NC = C + dc[i];

			if (NR < 0 || NR >= N || NC < 0 || NC >= M) continue;
			if (visit[NR][NC]) continue;
			if (Map[NR][NC] == 1 || Map[NR][NC] == 2) continue;

			visit[NR][NC] = true;
			que.push({ NR, NC, turn + 1 });
		}
	}
	std::cout << "KAKTUS";
	return 0;
}