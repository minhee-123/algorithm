// 문제: https://www.acmicpc.net/problem/6087
// 알고리즘: 그래프
#include <iostream>
#include <queue>
#include <string>
using namespace std;

// 두 지점을 연결하는데 90도 회전을 최소한 사용
int N, M;
int Map[100][100]; // 0은 빈 길, 1은 벽, 2는 도착 지점, 3은 출발 지점
bool visit[100][100];

int SR = -1;
int SC = -1;

int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0, 1, 0, -1 }; // 북 동 남 서

struct Q
{
	int R;
	int C;
	int turn;
	int dir;

	bool operator()(Q a, Q b) { return a.turn > b.turn; } // 우선순위 낮은 쪽이 true (turn 기준 최소힙, 오름차순)
};
priority_queue<Q, vector<Q>, Q> que;

int check_turn(int now_dir, int next_dir)
{
	if (now_dir == -1) return 0;
	
	int check = abs(next_dir - now_dir);
	if (check == 0 || check == 2) return 0;
	else if (check == 1 || check == 3) return 1;
}

int main()
{
	cin >> M >> N;
	for (int i = 0; i < N; i++)
	{
		string st;
		cin >> st;
		for (int j = 0; j < M; j++)
		{
			if (st[j] == '.') Map[i][j] = 0;
			else if (st[j] == '*') Map[i][j] = 1;
			else
			{
				if (SR == -1 && SC == -1)
				{
					SR = i;
					SC = j;
					Map[i][j] = 3;
				}
				else Map[i][j] = 2;
			}
		}
	} // Map 입력 및 시작점 초기화

	que.push({ SR, SC, 0, -1 }); // 시작점은 방향이 없음 (dir == -1)
	int answer = -1;
	while (!que.empty())
	{
		int R = que.top().R;
		int C = que.top().C;
		int turn = que.top().turn;
		int ing_dir = que.top().dir;
		que.pop();

		if (Map[R][C] == 2)
		{
			answer = turn;
			break;
		}
		visit[R][C] = true; // turn을 최소로 갖기 위해 visit은 여기에 위치해야 함
		// 최소 turn을 보장하기 위함 (우선순위 큐를 사용하는 것도 같은 맥락)

		for (int i = 0; i < 4; i++)
		{
			int NR = R + dr[i];
			int NC = C + dc[i];
			
			if (NR < 0 || NR >= N || NC < 0 || NC >= M) continue;
			if (visit[NR][NC]) continue;
			if (Map[NR][NC] == 1) continue;

			int Nturn = turn + check_turn(ing_dir, i);
			que.push({ NR, NC, Nturn, i });
		}
	}

	cout << answer;
	return 0;
}