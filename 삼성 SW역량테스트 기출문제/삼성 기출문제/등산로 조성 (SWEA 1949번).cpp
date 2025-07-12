// SWEA 1949번 등산로 조성
// https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5PoOKKAPIDFAUq&categoryId=AV5PoOKKAPIDFAUq&categoryType=CODE&problemTitle=%EB%AA%A8%EC%9D%98+SW+%EC%97%AD%EB%9F%89%ED%85%8C%EC%8A%A4%ED%8A%B8&orderBy=INQUERY_COUNT&selectCodeLang=ALL&select-1=&pageSize=10&pageIndex=1

#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int T, N, K;
int Map[8][8];

vector<pair<int, int>> highest;
int maxV = 0;
int answer = 0;

void Input()
{
	memset(Map, 0, sizeof(Map));
	highest.clear();
	maxV = 0;
	answer = 0;

	cin >> N >> K;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> Map[i][j];
			maxV = max(maxV, Map[i][j]);
		}
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (Map[i][j] == maxV) highest.push_back({ i, j });
		}
	}
}

int dr[4] = { 0, 0, 1, -1 };
int dc[4] = { 1, -1, 0, 0 };
bool visit[8][8];

void DFS(int cnt, int nowV, int R, int C, bool useK)
{
	answer = max(answer, cnt);

	for (int dir = 0; dir < 4; dir++)
	{
		int NR = R + dr[dir];
		int NC = C + dc[dir];

		if (NR < 0 || NR >= N || NC < 0 || NC >= N) continue;
		if (visit[NR][NC]) continue;

		int nextV = Map[NR][NC];

		if (nextV < nowV)
		{
			visit[NR][NC] = true;
			DFS(cnt + 1, nextV, NR, NC, useK);
			visit[NR][NC] = false; //모든 경우를 탐색할 수 있도록 백트래킹
		}
		else //nextV >= nowV
		{
			if (!useK)
			{				
				int num = nextV - (nowV - 1);
				if (num <= K)
				{
					useK = true;
					visit[NR][NC] = true;

					DFS(cnt + 1, nowV - 1, NR, NC, useK); //K는 사용한 상태가 됨

					useK = false; //★ 백트래킹할 때 변하는 상태 (분기에 영향을 미치는 상태)를 되돌려야 함 (오래 걸린 부분!!)
					visit[NR][NC] = false;
				}
			}
		}
	}
}

void Solution()
{
	Input();

	for (int index = 0; index < highest.size(); index++)
	{
		int R = highest[index].first;
		int C = highest[index].second;

		visit[R][C] = true;
		DFS(1, maxV, R, C, false);
		visit[R][C] = false;
	}
}

int main()
{
	cin >> T;
	for (int Test = 1; Test <= T; Test++)
	{
		Solution();
		cout << "#" << Test << " " << answer << '\n';
	}
	return 0;
}

/*
첫번째로는 머리가 아파서 잔실수를 좀 했다

두번째로는 백트래킹을 구현할 때 자주 하는 실수
- 백트래킹을 할 때는 분기점의 모든 상태를 복구해줘야 한다
- useK의 상태가 분기점에서 변하고 있기 때문에 복구(false)시켜줘야 했음
*/