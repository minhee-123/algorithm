// 코드트리 삼성 SW 역량테스트 2022 상반기 오전 1번 문제
// https://www.codetree.ai/ko/frequent-problems/samsung-sw/problems/hide-and-seek/description

#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

int N, M, H, K;

struct RUNNER
{
	int id;
	int R;
	int C;
	int dir;
	int dead = false;
};

vector<RUNNER> runner;
int Map[100][100]; //빈칸은 0, 나무는 1

int tagR = 0;
int tagC = 0;

int score = 0;

int dr[4] = { 1, -1, 0, 0 };
int dc[4] = { 0, 0, 1, -1 };

void Input()
{
	cin >> N >> M >> H >> K;
	runner.resize(M);

	for (int i = 0; i < M; i++) //도망자 정보 저장
	{
		int R, C, dir;
		cin >> R >> C >> dir;

		if (dir == 1) dir = 2; //좌우로 움직이는 유형
		else if (dir == 2) dir = 0; //상하로 움직이는 유형

		runner[i].id = i;
		runner[i].R = R - 1;
		runner[i].C = C - 1;
		runner[i].dir = dir;
	}

	for (int i = 0; i < H; i++) //나무 정보 저장
	{
		int R, C;
		cin >> R >> C;

		Map[R - 1][C - 1] = 1;
	}

	tagR = N / 2;
	tagC = N / 2;
}

int calD(int R1, int C1, int R2, int C2)
{
	return abs(R1 - R2) + abs(C1 - C2);
}

void moveR()
{
	for (int idx = 0; idx < M; idx++)
	{
		if (runner[idx].dead) continue; //잡힌 러너는 제외

		int NR = runner[idx].R;
		int NC = runner[idx].C;
		int dir = runner[idx].dir;

		int D = calD(tagR, tagC, NR, NC);
		if (D > 3) continue; //술래와의 거리가 3보다 크면 이동하지 않음

		NR += dr[dir];
		NC += dc[dir];

		if (NR < 0 || NR >= N || NC < 0 || NC >= N) //격자를 벗어나는 경우
		{
			if (dir == 0) dir = 1;
			else if (dir == 1) dir = 0;
			else if (dir == 2) dir = 3;
			else if (dir == 3) dir = 2;

			NR = runner[idx].R + dr[dir];
			NC = runner[idx].C + dc[dir];

			runner[idx].dir = dir; //방향 업데이트
		}

		if (NR == tagR && NC == tagC) continue; //술래가 있는 경우 움직이지 않음
		else //술래가 없는 경우
		{
			runner[idx].R = NR;
			runner[idx].C = NC; //도망자 위치 업데이트
		}
	}
}

int drT[4] = { -1, 0, 1, 0 };
int dcT[4] = { 0, 1, 0, -1 };

int move_len = 1;
int move_cnt = 0;
int move_dir = 0;
bool UP = true;
bool Down_first = true;

void moveT()
{
	if (UP) //중심에서 (0,0)으로 나감
	{
		tagR += drT[move_dir];
		tagC += dcT[move_dir];
		move_cnt++;

		if (move_cnt == move_len)
		{
			move_dir++;
			if (move_dir == 4) move_dir = 0;

			move_cnt = 0;
			if (move_dir == 0 || move_dir == 2) move_len++;
		}

		if (tagR == 0 && tagC == 0) //(0,0)에 도착한 경우
		{
			UP = false;
			move_len--;
			move_cnt = 0;
			move_dir = 2;
		}
	}
	else //(0,0)에서 중심으로 들어감
	{
		tagR += drT[move_dir];
		tagC += dcT[move_dir];
		move_cnt++;

		if (Down_first && move_cnt == move_len) //0열로 처음 내려오는 경우
		{
			move_cnt = 0;
			move_dir = 1;
			//move_len은 유지함 (첫 이동에는 유지해야 함)

			Down_first = false;
		}
		else
		{
			if (move_cnt == move_len)
			{
				move_dir--;
				if (move_dir == -1) move_dir = 3;

				move_cnt = 0;
				if (move_dir == 1 || move_dir == 3) move_len--;
			}

			if (tagR == N / 2 && tagC == N / 2) //중심에 도착한 경우
			{
				UP = true;
				Down_first = true;

				move_len = 1;
				move_cnt = 0;
				move_dir = 0;
			}
		}
	}
}

void Solution()
{
	Input();

	for (int k = 1; k <= K; k++)
	{
		moveR(); //도망자 이동
		moveT(); //술래 이동

		int NR = tagR;
		int NC = tagC;
		
		int cnt = 0;
		
		for (int i = 0; i < 3; i++)
		{
			if (NR < 0 || NR >= N || NC < 0 || NC >= N) break; //격자 바깥을 나가는 경우 종료

			if (Map[NR][NC] == 0) //자리에 나무가 없을 경우
			{
				for (int idx = 0; idx < M; idx++)
				{
					if (runner[idx].dead) continue;

					if (NR == runner[idx].R && NC == runner[idx].C) //술래에게 잡힘
					{
						cnt++;
						runner[idx].dead = true;
					}
				}
			}

			NR += drT[move_dir];
			NC += dcT[move_dir];
		}

		score += (k * cnt);
	}

	cout << score;
}

int main()
{
	Solution();
	return 0;
}

/*
이번 문제는 금방 풀었다!

다만 r과 c를 잘못 쓰는 실수를 해서 몇번 디버깅을 진행했다
실제로 시험 볼 때는 집중해서 실수하지 말자!
*/