// 문제: https://www.acmicpc.net/problem/23289

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int N, M, K, W;

int dr[4] = { 0, 0, -1, 1 }; //우 좌 상 하
int dc[4] = { 1, -1, 0, 0 };

int moveR[4][3] =
{
	{-1, 0, 1},
	{-1, 0, 1},
	{-1, -1, -1},
	{1, 1, 1}
};
int moveC[4][3] =
{
	{1, 1, 1},
	{-1, -1, -1},
	{-1, 0, 1},
	{-1, 0, 1}
};

int move_check[4][3][2] =
{
	{{2, 0}, {0}, {3, 0}},
	{{2, 1}, {1}, {3, 1}},
	{{1, 2}, {2}, {0, 2}},
	{{1, 3}, {3}, {0, 3}},
};

vector<pair<int, int>> check_point; // {행, 열}

struct HITTER
{
	int R;
	int C;
	int dir;
};
vector<HITTER> hitter;

bool wall[21][21];
vector<HITTER> wall_list;

int Map[21][21]; //index는 0부터 N-1, 0부터 M-1

int choco = 0; //100을 넘어갈 경우 101을 출력하고 종료

void Input()
{
	cin >> N >> M >> K;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			int temp;
			cin >> temp;

			if (temp > 0)
			{
				if (temp == 5) check_point.push_back({ i, j });
				else
				{
					temp--; //방향 인덱스는 0부터 3
					hitter.push_back({ i, j, temp });
				}
			}

			Map[i][j] = 0; //맵 초기화
		}
	}

	cin >> W;
	for (int i = 0; i < W; i++)
	{
		int R, C, t;
		cin >> R >> C >> t;
		R--;
		C--;

		if (t == 0)
		{
			wall[R][C] = true;
			wall[R - 1][C] = true;

			wall_list.push_back({ R, C, 2});
			wall_list.push_back({ R - 1, C, 3 });
		}
		else if (t == 1)
		{
			wall[R][C] = true;
			wall[R][C + 1] = true;

			wall_list.push_back({ R, C, 0});
			wall_list.push_back({ R, C + 1, 1 });
		}
	}
}

bool visit_hitting[21][21];

void Do_Hitting(int R, int C, int val, int dir)
{
	if (val == 0) return;

	for (int i = 0; i < 3; i++)
	{
		int NR = R + moveR[dir][i];
		int NC = C + moveC[dir][i];

		if (NR < 0 || NR >= N || NC < 0 || NC >= M) continue;
		if (visit_hitting[NR][NC]) continue;

		//벽이 있는 경우 1
		if (wall[R][C])
		{
			bool wall_flag = false;
			for (int k = 0; k < wall_list.size(); k++)
			{
				int tempR = wall_list[k].R;
				int tempC = wall_list[k].C;
				int tempDir = wall_list[k].dir;

				if (tempR == R && tempC == C && tempDir == move_check[dir][i][0]) wall_flag = true;
			}

			if (wall_flag) continue;
		}
		//벽이 있는 경우 2
		if (i != 1 && wall[NR][NC])
		{
			int TR = R + dr[move_check[dir][i][0]];
			int TC = C + dc[move_check[dir][i][0]];

			bool wall_flag = false;
			for (int k = 0; k < wall_list.size(); k++)
			{
				int tempR = wall_list[k].R;
				int tempC = wall_list[k].C;
				int tempDir = wall_list[k].dir;

				if (tempR == TR && tempC == TC && tempDir == move_check[dir][i][1]) wall_flag = true;
			}

			if (wall_flag) continue;
		}

		//온열이 이동할 수 있는 경우
		Map[NR][NC] += val;
		visit_hitting[NR][NC] = true;

		Do_Hitting(NR, NC, val - 1, dir);
	}
}

void Hitting() //모든 온풍기에서 바람이 한 번씩 나옴
{
	for (int index = 0; index < hitter.size(); index++)
	{
		memset(visit_hitting, false, sizeof(visit_hitting));

		int R = hitter[index].R;
		int C = hitter[index].C;
		int dir = hitter[index].dir;

		//온풍기가 있는 칸과 바람이 나오는 방향에 있는 칸 사이에는 벽이 없음
		//온풍기의 바람이 나오는 방향에 있는 칸은 항상 존재
		R += dr[dir];
		C += dc[dir];

		Map[R][C] += 5;
		visit_hitting[R][C] = true;

		Do_Hitting(R, C, 4, dir);
	}
}

bool Moved_visit[21][21];

void Move_Hit() //온도가 조절됨
{
	int Moved[21][21];
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++) Moved[i][j] = Map[i][j];
	}
	memset(Moved_visit, false, sizeof(Moved_visit));

	for (int R = 0; R < N; R++)
	{
		for (int C = 0; C < M; C++)
		{
			Moved_visit[R][C] = true;
			for (int i = 0; i < 4; i++)
			{
				int NR = R + dr[i];
				int NC = C + dc[i];

				if (NR < 0 || NR >= N || NC < 0 || NC >= M) continue;
				if (Moved_visit[NR][NC]) continue;

				if (wall[R][C])
				{
					bool flag = false;
					for (int k = 0; k < wall_list.size(); k++)
					{
						int WR = wall_list[k].R;
						int WC = wall_list[k].C;
						int Wdir = wall_list[k].dir;

						if (WR == R && WC == C && Wdir == i) flag = true;
					}
					if (flag) continue; //벽이 있는 경우
				}

				int mR = 0, mC = 0;
				int MR = 0, MC = 0;

				if (Map[R][C] > Map[NR][NC])
				{
					MR = R; MC = C;
					mR = NR; mC = NC;
				}
				else
				{
					MR = NR; MC = NC;
					mR = R; mC = C;
				}

				int val = (Map[MR][MC] - Map[mR][mC]) / 4;

				Moved[MR][MC] -= val;
				Moved[mR][mC] += val;
			}
		}
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++) Map[i][j] = Moved[i][j];
	}
}

void Down_Hit() //바깥쪽 온도 감소
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (i == 0 || i == N - 1 || j == 0 || j == M - 1)
			{
				if (Map[i][j] > 0) Map[i][j]--;
			}
		}
	}
}

void Simulation()
{
	Input();

	while (1)
	{
		Hitting();
		Move_Hit();
		Down_Hit();

		choco++;

		bool finish = true;
		for (int i = 0; i < check_point.size(); i++)
		{
			int R = check_point[i].first;
			int C = check_point[i].second;

			if (Map[R][C] < K) finish = false;
		}

		if (finish) break;
		if (choco == 101) break;
	}

	cout << choco;
}

int main()
{
	Simulation();
	return 0;
}