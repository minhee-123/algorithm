// 문제: https://www.acmicpc.net/problem/2151
// 알고리즘: 그래프
#include <iostream>
#include <queue>
#include <string>
using namespace std;

int N;
int Map[50][50]; 
// 0: 빈공간(빛 통과)
// 1: 거울을 설치할 수 있는 위치(90도 회전 가능)
// 2: 빛이 통과할 수 없는 벽(갈 수 없음)
// 3: 출발 지점
// 4: 도착 지점
bool visit[50][50][4];

int SR = -1, SC = -1, Sdir;

struct DATA
{
	int R;
	int C;
	int cnt;
	int dir;

	bool operator()(DATA A, DATA B) { return A.cnt > B.cnt; } // 오름차순 정렬
};
priority_queue<DATA, vector<DATA>, DATA> pq;

int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0, 1, 0, -1 }; // 북 동 남 서

int main()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		string st;
		cin >> st;
		for (int j = 0; j < N; j++)
		{
			if (st[j] == '.') Map[i][j] = 0;
			else if (st[j] == '!') Map[i][j] = 1;
			else if (st[j] == '*') Map[i][j] = 2;
			else
			{
				if (SR == -1 && SC == -1)
				{
					Map[i][j] = 3;
					SR = i;
					SC = j;
				}
				else Map[i][j] = 4;
			}
		}
	}

	pq.push({ SR, SC, 0, 0 });
	pq.push({ SR, SC, 0, 1 });
	pq.push({ SR, SC, 0, 2 });
	pq.push({ SR, SC, 0, 3 });
	while (!pq.empty())
	{
		int R = pq.top().R;
		int C = pq.top().C;
		int cnt = pq.top().cnt;
		int dir = pq.top().dir;
		pq.pop();

		if (Map[R][C] == 4)
		{
			cout << cnt;
			break;
		}
		visit[R][C][dir] = true;

		int NR = R + dr[dir];
		int NC = C + dc[dir];

		if (NR < 0 || NR >= N || NC < 0 || NC >= N) continue;
		if (Map[NR][NC] == 2) continue;
		if (visit[NR][NC][dir]) continue;

		pq.push({ NR, NC, cnt, dir });

		if (Map[NR][NC] == 1)
		{
			int dir1 = dir + 1;
			if (dir1 == 4) dir1 = 0;
			int dir2 = dir - 1;
			if (dir2 == -1) dir2 = 3;

			pq.push({ NR, NC, cnt + 1, dir1 });
			pq.push({ NR, NC, cnt + 1, dir2 });
		} // 도착한 곳이 거울 설치가 가능한 지점일 경우
	}
	return 0;
}

// 현재 상태를 결정짓는 요소를 잘 생각할 것
// (1) 어떤 방향으로 들어왔는지가 다음 행동에 영향을 미침
// (2) 똑같은 cnt로 특정 지점에 도착했더라도 방향이 다르면 이후 갈 수 있는 조건이 달라짐
// (3) 그렇기 때문에 방향 또한 상태의 핵심이 됨(현재 지점에 도착한 방향도 visit에 추가)

// 레이저 통신에서 문제가 없었던 것은 상대적으로 제약이 덜했고 + 큐에 넣는 순서 덕분에 운좋게 통과한 것일 수도 있음
// → 레이저 통신도 엄밀히 따지면 현재 상태에 도착한 방향이 이후 상태에 영향을 끼치기 때문에(turn 수에 영향)
// → 3차원 visit 배열을 사용하는 게 정석 풀이임

// 현재 지점에 도착한 방향, 특정 조건 사용 횟수 등등
// 이후 결과에 영향을 미칠 수 있는 조건이라면 visit 배열에 포함해야 함!