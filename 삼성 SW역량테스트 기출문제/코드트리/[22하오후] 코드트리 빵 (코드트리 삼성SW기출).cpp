// 코드트리 삼성 SW 역량테스트 2022 하반기 오후 1번 문제
// https://www.codetree.ai/ko/frequent-problems/samsung-sw/problems/codetree-mon-bread/description

#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

int dr[4] = { -1, 0, 0, 1 };
int dc[4] = { 0, -1, 1, 0 };

int Time = 0;
int N, M;

int Map[15][15]; //범위는 0에서 14까지 사용
bool No_passing[15][15]; //이동할 수 없는 구역 표시

struct PERSON
{
	int id;
	int NR;
	int NC;
	int targetR; //편의점 위치 row
	int targetC; //편의점 위치 col
	bool arrive = false;
};

vector<PERSON> P;

void Input()
{
	cin >> N >> M;
	P.resize(M);

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++) cin >> Map[i][j];
	}

	for (int i = 0; i < M; i++)
	{
		int R, C;
		cin >> R >> C;

		P[i].id = i;
		P[i].targetR = R - 1;
		P[i].targetC = C - 1;

		Map[R - 1][C - 1] = 2; //편의점이 위치해 있음
	}
}

bool visitB[15][15];
void Go_Basecamp(int idx)
// 최단거리가 같은 베이스캠프가 여러개일 경우
// 행이 가장 작은 베이스캠프 → 동일한 행이라면 열이 가장 작은 베이스캠프로 이동
{
	memset(visitB, false, sizeof(visitB));

	int TR = P[idx].targetR;
	int TC = P[idx].targetC;

	queue<pair<int, int>> Q;
	Q.push({ TR, TC });
	visitB[TR][TC] = true;

	bool flag = false;

	int distance[15][15] = { 0 };
	distance[TR][TC] = 0;

	int minD = 10000;
	vector<pair<int, int>> camp;
	// 상좌우하 이동으로는 가장 작은 행, 가장 작은 열의 최단거리 베이스캠프 도착을 보장해주지 않음

	while (!Q.empty())
	{
		int R = Q.front().first;
		int C = Q.front().second;
		Q.pop();

		for (int i = 0; i < 4; i++)
		{
			int NR = R + dr[i];
			int NC = C + dc[i];

			if (NR < 0 || NR >= N || NC < 0 || NC >= N) continue;
			if (visitB[NR][NC]) continue;
			if (No_passing[NR][NC]) continue;

			Q.push({ NR, NC });
			visitB[NR][NC] = true;
			distance[NR][NC] = distance[R][C] + 1;

			if (Map[NR][NC] == 1) //베이스캠프에 도착한 경우
			{
				if (distance[NR][NC] <= minD) //최단거리가 같은 베이스캠프 모두 저장
				{
					camp.push_back({ NR, NC });
					minD = distance[NR][NC];
				}
				else //최단거리 이상의 베이스캠프에 도착한 경우
				{
					flag = true;
					break;
				}
			}
		}

		if (flag) break;
	}

	sort(camp.begin(), camp.end());

	P[idx].NR = camp[0].first;
	P[idx].NC = camp[0].second;

	No_passing[P[idx].NR][P[idx].NC] = true;
}

bool visitM[15][15];
int Move(int index)
{
	memset(visitM, false, sizeof(visitM));

	int TR = P[index].targetR;
	int TC = P[index].targetC;

	int NowR = P[index].NR;
	int NowC = P[index].NC;

	queue<pair<int, int>> Q;
	Q.push({ NowR, NowC });
	visitM[NowR][NowC] = true;

	bool flag = false;
	vector<int> recordDIR[15][15];

	while (!Q.empty())
	{
		int R = Q.front().first;
		int C = Q.front().second;
		Q.pop();

		for (int dir = 0; dir < 4; dir++)
		{
			int NR = R + dr[dir];
			int NC = C + dc[dir];

			if (NR < 0 || NR >= N || NC < 0 || NC >= N) continue;
			if (visitM[NR][NC]) continue;
			if (No_passing[NR][NC]) continue; //지나갈 수 없는 위치

			visitM[NR][NC] = true;
			Q.push({ NR, NC });

			for (int i = 0; i < recordDIR[R][C].size(); i++) recordDIR[NR][NC].push_back(recordDIR[R][C][i]);
			recordDIR[NR][NC].push_back(dir);

			if (NR == TR && NC == TC)
			{
				flag = true;
				break;
			}
		}

		if (flag) break;
	}

	return recordDIR[TR][TC][0];
}

int arriveCNT = 0; //도착한 사람의 수
void Simulation()
{
	vector<pair<int, int>> arriveP; //도착한 사람의 좌표 저장

	for (int id = 0; id < M; id++) //M초까지
	{
		if (id > 0)
		{
			arriveP.clear();

			for (int index = 0; index < id; index++)
			{
				if (P[index].arrive) continue;

				int moveDIR = Move(index);

				P[index].NR += dr[moveDIR];
				P[index].NC += dc[moveDIR];

				if (P[index].NR == P[index].targetR && P[index].NC == P[index].targetC)
				{
					P[index].arrive = true;
					arriveCNT++;
					arriveP.push_back({ P[index].NR, P[index].NC });
				}
			}

			if (!arriveP.empty())
			{
				for (int k = 0; k < arriveP.size(); k++) No_passing[arriveP[k].first][arriveP[k].second] = true;
			} //모두 이동한 후 업데이트 (No Passing)
		}

		Go_Basecamp(id);
		Time++;
	}

	while (1) //M초 이후
	{
		if (arriveCNT == M) break;

		arriveP.clear();

		for (int index = 0; index < M; index++)
		{
			if (P[index].arrive) continue;

			int moveDIR = Move(index);

			P[index].NR += dr[moveDIR];
			P[index].NC += dc[moveDIR];

			if (P[index].NR == P[index].targetR && P[index].NC == P[index].targetC)
			{
				P[index].arrive = true;
				arriveCNT++;
				arriveP.push_back({ P[index].NR, P[index].NC });
			}
		}

		if (!arriveP.empty())
		{
			for (int k = 0; k < arriveP.size(); k++) No_passing[arriveP[k].first][arriveP[k].second] = true;
		} //모두 이동한 후 업데이트 (No Passing)

		Time++;
	}
}

int main()
{
	Input();
	Simulation();

	cout << Time;
	return 0;
}


/*
해당 문제는 꽤 빠르게 풀었다

구현하다가 실수한 부분 
→ BFS 구현에서 Q 삽입을 안했음 (당연히 오류 발생)

100번째 테스트케이스에서 틀린 부분
→ 베이스캠프 이동은 최단거리가 같은 베이스캠프가 여러가지일 경우 가장 작은 행, 다음으로 가장 작은 열의 캠프로 이동함
→ 이때 단순히 상좌우하 이동은 최단거리의 가장 작은 행과 열 베이스캠프를 보장해주지 않음
→ ★ 그래서 최단거리 베이스캠프를 모두 저장 후 정렬해서 이동시킴
*/