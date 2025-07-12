// 코드트리 삼성 SW 역량테스트 2022 하반기 오전 1번 문제
// https://www.codetree.ai/ko/frequent-problems/samsung-sw/problems/battle-ground/description

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0, 1, 0, -1 }; //상우하좌

int N, M, K;
vector<int> Map[20][20]; //범위는 0부터 N-1까지 사용함
int Player[20][20];

struct PLAYER
{
	int id;
	int R; //row
	int C; //col
	int S; //초기 능력치
	int G = 0; //가지고 있는 총
	int dir; //이동방향
};

vector<PLAYER> P;
vector<int> point;

bool comp(int A, int B) { return A > B; }

void Input()
{
	cin >> N >> M >> K;
	
	P.resize(M);
	point.resize(M, 0);

	memset(Player, -1, sizeof(Player));

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			int temp;
			cin >> temp;
			Map[i][j].push_back(temp);
		}
	}

	for (int i = 0; i < M; i++)
	{
		int R, C, dir, S;
		cin >> R >> C >> dir >> S;

		P[i].id = i;
		P[i].R = R - 1;
		P[i].C = C - 1;
		P[i].S = S;
		P[i].dir = dir;

		Player[R - 1][C - 1] = i;
	}
}

void Move()
{
	for (int idx = 0; idx < M; idx++)
	{
		// 1. 이동
		int dir = P[idx].dir;
		int NR = P[idx].R + dr[dir];
		int NC = P[idx].C + dc[dir];

		if (NR < 0 || NR >= N || NC < 0 || NC >= N)
		{
			if (dir == 0) dir = 2;
			else if (dir == 2) dir = 0;
			else if (dir == 1) dir = 3;
			else if (dir == 3) dir = 1; //격자를 벗어나는 경우 반대방향으로

			NR = P[idx].R + dr[dir];
			NC = P[idx].C + dc[dir];
		}
		Player[P[idx].R][P[idx].C] = -1; //이전 위치 비워두기

		P[idx].R = NR;
		P[idx].C = NC;
		P[idx].dir = dir;


		// 2. 이동 후 확인
		if (Player[NR][NC] == -1) //플레이어가 없는 경우
		{
			Player[NR][NC] = P[idx].id;

			sort(Map[NR][NC].begin(), Map[NR][NC].end(), comp);
			if (Map[NR][NC][0] == 0) continue; //총이 없는 경우
			else //총이 있는 경우
			{
				if (Map[NR][NC][0] > P[idx].G) swap(Map[NR][NC][0], P[idx].G);
			}
		}
		else //플레이어가 있는 경우
		{
			int idA = idx;
			int idB = Player[NR][NC];

			int winID = 0, loseID = 0;

			if (P[idA].S + P[idA].G > P[idB].S + P[idB].G)
			{
				winID = idA;
				loseID = idB;
			}
			else if (P[idA].S + P[idA].G < P[idB].S + P[idB].G)
			{
				winID = idB;
				loseID = idA;
			}
			else if (P[idA].S + P[idA].G == P[idB].S + P[idB].G)
			{
				if (P[idA].S > P[idB].S)
				{
					winID = idA;
					loseID = idB;
				}
				else
				{
					winID = idB;
					loseID = idA;
				}
			}

			point[winID] += (P[winID].S + P[winID].G) - (P[loseID].S + P[loseID].G);
			Player[NR][NC] = winID;

			Map[NR][NC].push_back(P[loseID].G);
			P[loseID].G = 0;

			// 진 플레이어 행동
			int dirL = P[loseID].dir;
			while (1)
			{
				int tempR = NR + dr[dirL];
				int tempC = NC + dc[dirL];

				if (tempR < 0 || tempR >= N || tempC < 0 || tempC >= N || Player[tempR][tempC] > -1)
				{
					dirL++;
					if (dirL == 4) dirL = 0;
				}
				else
				{
					P[loseID].dir = dirL;
					P[loseID].R = tempR;
					P[loseID].C = tempC;
					Player[tempR][tempC] = loseID;

					sort(Map[tempR][tempC].begin(), Map[tempR][tempC].end(), comp);
					if (Map[tempR][tempC][0] > 0) //총이 있다면
					{
						swap(Map[tempR][tempC][0], P[loseID].G);
					}

					break;
				}
			}

			// 이긴 플레이어 행동
			sort(Map[NR][NC].begin(), Map[NR][NC].end(), comp);
			if (Map[NR][NC][0] > P[winID].G) //자리에 있는 총의 공격력이 더 높을 경우
			{
				swap(Map[NR][NC][0], P[winID].G);
			}
		}
	}
}

void Solution()
{
	Input();

	for (int i = 0; i < K; i++)
	{
		Move();
	}

	for (int idx = 0; idx < M; idx++) cout << point[idx] << " ";
}

int main()
{
	Solution();
	return 0;
}


/*
바보같은 실수 하나 했다
실제 시험에서는 정신 똑바로 차리자...

point를 업데이트할 때 점수를 누적해야 하는데 +=가 아닌 =을 사용했다 (값을 계속해서 새로고침함)

(+) 추가로
Map을 3차원 벡터로 선언해서 사용하고 있는데
우선순위큐(최대힙)으로 구현했으면 sort 과정이 빠져서 구현이 더 간단했을 것 같다
*/