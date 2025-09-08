// 문제: https://www.acmicpc.net/problem/19237

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M, K;
int dr[5] = { 0, -1, 1, 0, 0 }; // 위, 아래, 왼쪽, 오른쪽
int dc[5] = { 0, 0, 0, -1, 1 };

struct SHARK_INFORM
{
	int number = 0; //1부터 시작
	int row = 0; //0부터 시작
	int col = 0; //0부터 시작
	int now_dir = 0;

	int move_dir[5][5];
	bool death = false;
};

pair<int, int> Map[21][21]; //첫번째는 상어번호, 두번째는 냄새 시간 (0이 되면 상어번호도 0으로 변함)
vector<SHARK_INFORM> shark;

int visit[21][21];

void Input()
{
	cin >> N >> M >> K;
	shark.resize(M + 1);

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> Map[i][j].first;

			if (Map[i][j].first > 0)
			{
				Map[i][j].second = K;
				visit[i][j] = Map[i][j].first;

				shark[Map[i][j].first].number = Map[i][j].first;
				shark[Map[i][j].first].row = i;
				shark[Map[i][j].first].col = j;
			}
		}
	}

	for (int i = 1; i <= M; i++) cin >> shark[i].now_dir;

	for (int i = 1; i <= M; i++)
	{
		for (int j = 1; j <= 4; j++)
		{
			for (int k = 1; k <= 4; k++) cin >> shark[i].move_dir[j][k];
		}
	}
}

int time_cnt = 0;
int alive_shark;
bool no_answer = false;

void Shark_move()
{
	for (int index = 1; index <= M; index++)
	{
		if (shark[index].death) continue;

		int R = shark[index].row;
		int C = shark[index].col;
		int dir = shark[index].now_dir;

		bool empty_flag = false;
		bool self_flag = false;

		for (int i = 1; i <= 4; i++)
		{
			int NR = R + dr[i];
			int NC = C + dc[i];

			if (NR < 0 || NR >= N || NC < 0 || NC >= N) continue;

			int shark_location = Map[NR][NC].first;
			if (shark_location == 0) empty_flag = true;
			else if (shark_location == index) self_flag = true;
		}

		if (!empty_flag && !self_flag) continue; //움직일 수 없는 경우

		int moveR = 0;
		int moveC = 0;
		int move_dir = 0;

		for (int i = 1; i <= 4; i++)
		{
			int NR = R + dr[shark[index].move_dir[dir][i]];
			int NC = C + dc[shark[index].move_dir[dir][i]];

			if (NR < 0 || NR >= N || NC < 0 || NC >= N) continue;
			if (empty_flag)
			{
				if (Map[NR][NC].first == 0)
				{
					moveR = NR;
					moveC = NC;
					move_dir = shark[index].move_dir[dir][i];
					break;
				}
			}
			else if (self_flag)
			{
				if (Map[NR][NC].first == index)
				{
					moveR = NR;
					moveC = NC;
					move_dir = shark[index].move_dir[dir][i];
					break;
				}
			}
		}

		visit[R][C] = 0;

		shark[index].row = moveR;
		shark[index].col = moveC;
		shark[index].now_dir = move_dir;

		if (visit[moveR][moveC] > 0)
		{
			if (visit[moveR][moveC] > index) //흐름상 없는 경우긴 함
			{
				shark[visit[moveR][moveC]].death = true;
			}
			else shark[index].death = true;

			alive_shark--;
		}
		else visit[moveR][moveC] = index;
	}
}

void Shark_smell()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (Map[i][j].second > 0)
			{
				Map[i][j].second--;
				if (Map[i][j].second == 0) Map[i][j].first = 0;
			}
		}
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (visit[i][j] > 0)
			{
				Map[i][j].first = visit[i][j];
				Map[i][j].second = K;
			}
		}
	}
}

void Simulation()
{
	Input();
	alive_shark = M;

	while (1)
	{
		Shark_move();
		Shark_smell();

		time_cnt++;

		if (alive_shark == 1) break;
		if (time_cnt >= 1000)
		{
			no_answer = true;
			break;
		}
	}

	if (no_answer) cout << -1;
	else cout << time_cnt;
}

int main()
{
	Simulation();
	return 0;
}