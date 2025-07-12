// 코드트리 삼성 SW 역량테스트 2022 상반기 오후 1번 문제
// https://www.codetree.ai/ko/frequent-problems/samsung-sw/problems/tail-catch-play/description

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int N, M, K;
int Map[20][20];

int dr[4] = {0, -1, 0, 1};
int dc[4] = {1, 0, -1, 0};

vector<pair<int, int>> head;
vector<pair<int, int>> tail;

int score = 0;

bool visitFT[20][20];
void find_tail(int index, int R, int C)
{
	visitFT[R][C] = true;
	if (Map[R][C] == 3)
	{
		tail[index] = { R, C };
		return;
	}

	for (int i = 0; i < 4; i++)
	{
		int NR = R + dr[i];
		int NC = C + dc[i];

		if (NR < 0 || NR >= N || NC < 0 || NC >= N) continue;
		if (visitFT[NR][NC]) continue;
		if (Map[NR][NC] == 2 || Map[NR][NC] == 3) find_tail(index, NR, NC);
	}
}

void Input()
{
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> Map[i][j];
			if (Map[i][j] == 1) head.push_back({ i, j });
		}
	}

	tail.resize(M);
	for (int i = 0; i < M; i++) find_tail(i, head[i].first, head[i].second);
}

void Move()
{
	for (int index = 0; index < M; index++)
	{
		bool flag = true;
		// flag true = 1과 3이 붙어있음 (이동 선에 4가 없음)
		// flag false = 1과 3이 떨어져 있음 (이동 선에 4가 있음)

		// 머리 이동
		int HR = head[index].first;
		int HC = head[index].second;

		for (int i = 0; i < 4; i++)
		{
			int NR = HR + dr[i];
			int NC = HC + dc[i];

			if (NR < 0 || NR >= N || NC < 0 || NC >= N) continue;
			if (Map[NR][NC] == 4)
			{
				HR = NR;
				HC = NC;

				flag = false;
				break;
			}
		}
		if (flag) 
		{
			// 이동 선에 4(빈칸)가 없는 경우 (1과 3이 붙어있음)
			// 머리는 2가 있는 위치로 이동함

			for (int i = 0; i < 4; i++)
			{
				int NR = HR + dr[i];
				int NC = HC + dc[i];

				if (NR < 0 || NR >= N || NC < 0 || NC >= N) continue;
				if (Map[NR][NC] == 3)
				{
					HR = NR;
					HC = NC;
					break;
				}
			}
		}

		// 꼬리 이동
		int TR = tail[index].first;
		int TC = tail[index].second;

		for (int i = 0; i < 4; i++)
		{
			int NR = TR + dr[i];
			int NC = TC + dc[i];

			if (NR < 0 || NR >= N || NC < 0 || NC >= N) continue;

			if (Map[NR][NC] == 2)
			{
				TR = NR;
				TC = NC;
				break;
			}
		}

		Map[HR][HC] = 1;
		Map[head[index].first][head[index].second] = 2;

		Map[TR][TC] = 3;
		if (!flag) Map[tail[index].first][tail[index].second] = 4; //이동선에 4가 있는 경우

		head[index].first = HR;
		head[index].second = HC;

		tail[index].first = TR;
		tail[index].second = TC;
	}
}

bool visitFG[20][20];
int findIndex;
void find_group_index(int R, int C)
{
	visitFG[R][C] = true;

	if (Map[R][C] == 1)
	{
		for (int index = 0; index < M; index++)
		{
			if (head[index].first == R && head[index].second == C)
			{
				findIndex = index;
				return;
			}
		}
	}
	if (Map[R][C] == 3)
	{
		for (int index = 0; index < M; index++)
		{
			if (tail[index].first == R && tail[index].second == C)
			{
				findIndex = index;
				return;
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		int NR = R + dr[i];
		int NC = C + dc[i];

		if (NR < 0 || NR >= N || NC < 0 || NC >= N) continue;
		if (visitFG[NR][NC]) continue;
		if (Map[NR][NC] != 0 && Map[NR][NC] != 4) find_group_index(NR, NC);
	}
}

bool visitK[20][20];
int cntK;
void find_k(int cnt, int R, int C, int targetR, int targetC)
{
	visitK[R][C] = true;

	if (R == targetR && C == targetC)
	{
		cntK = cnt;
		return;
	}

	for (int i = 0; i < 4; i++)
	{
		int NR = R + dr[i];
		int NC = C + dc[i];

		if (NR < 0 || NR >= N || NC < 0 || NC >= N) continue;
		if (visitK[NR][NC]) continue;
		
		if (Map[R][C] == 1 && Map[NR][NC] == 2) find_k(cnt + 1, NR, NC, targetR, targetC); //이동선에 4가 없는 경우 1에서 3으로 바로 이동하지 않도록 처리함
		else if (Map[R][C] != 1 && Map[NR][NC] != 0 && Map[NR][NC] != 4) find_k(cnt + 1, NR, NC, targetR, targetC);
	}
}

void Shoot(int turn)
{
	if (turn > 4 * N) turn = turn % (4 * N);
	if (turn == 0) turn = 4 * N; // ★★★ 이 부분을 못찾아서 디버깅이 오래 걸렸다

	int dir = 0;
	int SR = 0;
	int SC = 0;

	if (turn <= N) dir = 0;
	else if (turn <= 2 * N) dir = 1;
	else if (turn <= 3 * N) dir = 2;
	else if (turn <= 4 * N) dir = 3;

	if (dir == 0)
	{
		SC = 0;
		SR = turn - 1;
	}
	if (dir == 1)
	{
		SR = N - 1;
		SC = (turn - N) - 1;
	}
	if (dir == 2)
	{
		SC = N - 1;

		SR = (turn - 2 * N) - 1;
		SR = N - SR - 1; //N에서 값을 빼주면 0이랑 N-1값을 바꾸는 것과 같음
	}
	if (dir == 3)
	{
		SR = 0;

		SC = (turn - 3 * N) - 1;
		SC = N - SC - 1;
	}

	while (SR >= 0 && SR < N && SC >= 0 && SC < N)
	{
		if (Map[SR][SC] != 0 && Map[SR][SC] != 4)
		{
			memset(visitFG, false, sizeof(visitFG));
			memset(visitK, false, sizeof(visitK));

			cntK = 0;
			findIndex = 0;

			find_group_index(SR, SC);
			find_k(1, head[findIndex].first, head[findIndex].second, SR, SC);

			score += (cntK * cntK);

			swap(head[findIndex].first, tail[findIndex].first);
			swap(head[findIndex].second, tail[findIndex].second);

			Map[head[findIndex].first][head[findIndex].second] = 1;
			Map[tail[findIndex].first][tail[findIndex].second] = 3; //맵 업데이트

			break;
		}

		SR += dr[dir];
		SC += dc[dir];
	}
}

void Solution()
{
	Input();

	for (int turn = 1; turn <= K; turn++)
	{
		Move();
		Shoot(turn);
	}

	cout << score;
}

int main()
{
	Solution();
	return 0;
}

/*
푸는 데 오래 걸렸다... 치명적인 실수와 엣지케이스

(1) Map 업데이트
- 좌표 업데이트할 때 꼭 맵도 업데이트 해줘야 한다
- 맵을 업데이트 안해서 1차 문제가 발생했었다

(2) 이동 선에 4가 없는 경우가 있다
- 이동 선에 빈칸(4)이 없이 사람이 채워진 경우
- 머리(1)와 꼬리(3)가 바로 옆에 인접해 있다
- 머리는 앞으로 진행되므로 꼬리(3)가 있는 위치로 이동한다 (꼬리는 똑같이 2로 이동)
- Move뿐만 아니라 find_k에서 재귀하는 기준도 if로 처리해야 한다 (1에서 무조건 2로만 이동하도록 해야 함)

(3) turn을 1부터 받고 있기 때문에 turn이 0이 될 때 문제가 발생한다
- turn을 0부터 받는 것으로 수정하거나
- turn이 0이 될때를 따로 처리해줘야 한다 (turn은 4*N의 배수일때 0이 된다)

3번을 못찾아서 오래 걸렸다
챗지피티가 알려줬는데 대충 보고 무시했다... 챗지피티 피드백도 꼼꼼하게 보자
*/