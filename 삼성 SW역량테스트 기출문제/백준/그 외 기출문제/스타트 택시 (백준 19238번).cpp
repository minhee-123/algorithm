// 문제: https://www.acmicpc.net/problem/19238
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int dr[4] = { -1, 0, 0, 1 };
int dc[4] = { 0, -1, 1, 0 };

struct comp
{
	int R;
	int C;
	int cnt;

	bool operator()(comp A, comp B)
	{
		if (A.cnt != B.cnt) return A.cnt > B.cnt;
		else if (A.R != B.R) return A.R > B.R;
		else return A.C > B.C;
	}
};

int TR, TC; // 택시의 위치
int N, M, oil;
bool can_move = true;

int Map[21][21]; // 0dms 빈칸, -1은 벽, 1 이상은 승객
bool visit[21][21];
vector<pair<int, int>> target_loca; // 승객의 도착 위치

/* Input */
void Input()
{
	cin >> N >> M >> oil;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			cin >> Map[i][j];
			if (Map[i][j] == 1) Map[i][j] = -1; // 벽은 -1로 저장
		}
	}
	cin >> TR >> TC;

	target_loca.resize(M + 1);
	for (int i = 1; i <= M; i++)
	{
		int R, C, LR, LC;
		cin >> R >> C >> LR >> LC;
		
		Map[R][C] = i;
		target_loca[i].first = LR;
		target_loca[i].second = LC;
	}
}

/* Find Passenger */
int Pidx = 0; // 현재 태우고 있는 승객의 번호
void Find_P()
{
	memset(visit, false, sizeof(visit));
	priority_queue<comp, vector<comp>, comp> que;

	que.push({ TR, TC, 0 });
	visit[TR][TC] = true;

	bool flag = false;

	while (!que.empty())
	{
		int R = que.top().R;
		int C = que.top().C;
		int cnt = que.top().cnt;
		que.pop();

		if (Map[R][C] > 0) // 승객 발견
		{
			TR = R;
			TC = C;
			Pidx = Map[TR][TC];
			Map[TR][TC] = 0;

			oil -= cnt;
			if (oil <= 0) can_move = false;
			flag = true;
			break;
		}

		for (int i = 0; i < 4; i++)
		{
			int NR = R + dr[i];
			int NC = C + dc[i];

			if (NR < 1 || NR > N || NC < 1 || NC > N) continue;
			if (visit[NR][NC]) continue;
			if (Map[NR][NC] == -1) continue;

			visit[NR][NC] = true;
			que.push({ NR, NC, cnt + 1 });
		}
	}

	if (!flag) can_move = false; // 어떤 승객도 태울 수 없는 경우
}

/* Move Passenger */
void Move_P()
{
	memset(visit, false, sizeof(visit));
	priority_queue<comp, vector<comp>, comp> que;

	que.push({ TR, TC, 0 });
	visit[TR][TC] = true;

	int targetR = target_loca[Pidx].first;
	int targetC = target_loca[Pidx].second;
	bool flag_target = false;

	while (!que.empty())
	{
		int R = que.top().R;
		int C = que.top().C;
		int cnt = que.top().cnt;
		que.pop();

		if (R == targetR && C == targetC)
		{
			TR = R;
			TC = C;
			oil -= cnt;
			if (oil < 0) can_move = false; // 이동 중 연료 고갈
			else oil += (cnt * 2); // 무사히 도착한 경우 연료 두배 충전

			flag_target = true; // 승객이 도착했음
			break;
		}

		for (int i = 0; i < 4; i++)
		{
			int NR = R + dr[i];
			int NC = C + dc[i];

			if (NR < 1 || NR > N || NC < 1 || NC > N) continue;
			if (visit[NR][NC]) continue;
			if (Map[NR][NC] == -1) continue;

			visit[NR][NC] = true;
			que.push({ NR, NC, cnt + 1 });
		}
	}

	if (!flag_target) can_move = false; // 승객을 도착지에 보낼 수 없는 경우
}

/* Total Solution */
void Solution()
{
	Input();
	for (int i = 0; i < M; i++) // 모든 승객을 이동시켜야 함
	{
		Find_P();
		if (!can_move) break;

		Move_P();
		if (!can_move) break;
	}

	if (!can_move) cout << -1;
	else cout << oil;
}

int main()
{
	Solution();
	return 0;
}

/* 디버깅이 조금 걸렸다 */
/*****
(1) 연료가 고갈되는 경우 외에 승객을 태우지 못하거나 태운 승객을 이동시키지 못하는 경우도 있다
	→ 해당 케이스를 생각하지 못해 뒤늦게 반영함
(2) 같은 최단거리일 경우 가장 작은 행, 행이 같을 경우 가장 작은 열을 선택해야 했는데
	→ dr, dc 설정만으로는 충족되지 않은 것 같음 (우선순위 큐를 적용해서 해결)
*****/