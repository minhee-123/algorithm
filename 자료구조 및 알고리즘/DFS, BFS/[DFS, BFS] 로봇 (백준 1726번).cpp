// 문제: https://www.acmicpc.net/workbook/view/1833

// BFS로 풀 수 있는 것 같긴 한데 최적화하고 싶어서
// 다익스트라 적용해봄 (중간에 실수를 많이 해서 오래 걸림)

/* 디버깅이 오래 걸렸다! */
/*
(1) visit 배열을 3차원으로 다루어야 한다
    → 방향에 따라 cnt가 달라짐
	→ 이후 루트가 같을 수 있는데 갖고있는 cnt가 달라져서 방향도 visit 처리해야 함
(2) 근데 애초에 visit이 좋지 않다
	→ 다익스트라 알고리즘에서 visit 배열을 사용하지 않는다
	→ dist 배열을 사용해야 함 (모든 값을 INF로 초기화 / push하려는 값이 더 작은지 체크)
(3) 정답을 잘못 초기화했다
	→ answer를 처음에 200으로 초기화했는데 최대값이 200이 아니다...
	→ 최소/최대를 찾을 때 초기화는 극단적으로 하자
*/

#include <iostream>
#include <queue>
using namespace std;

int N, M;
int dr[4] = { 0, 0, 1, -1 }; // 동 서 남 북
int dc[4] = { 1, -1, 0, 0 };
int Map[100][100]; 

int startR, startC, startDir;
int targetR, targetC, targetDir;

void Input()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++) cin >> Map[i][j];
	}

	int tempR, tempC, tempDir;

	cin >> tempR >> tempC >> tempDir;
	startR = tempR - 1;
	startC = tempC - 1;
	startDir = tempDir - 1;

	cin >> tempR >> tempC >> tempDir;
	targetR = tempR - 1;
	targetC = tempC - 1;
	targetDir = tempDir - 1;
}

// 현재 방향에서 타겟 방향으로 바꾸는 데 필요한 명령의 수
int turn_cnt(int now_dir, int target_dir)
{
	if (now_dir == target_dir) return 0;
	else
	{
		// 동(0), 서(1), 남(2), 북(3)
		if (now_dir == 0)
		{
			if (target_dir >= 2) return 1;
			else return 2;
		}
		else if (now_dir == 1)
		{
			if (target_dir >= 2) return 1;
			else return 2;
		}
		else if (now_dir == 2)
		{
			if (target_dir <= 1) return 1;
			else return 2;
		}
		else // now_dir == 3
		{
			if (target_dir <= 1) return 1;
			else return 2;
		}
	}
}

struct inform
{
	int R;
	int C;
	int dir;
	int cnt;

	bool operator()(inform A, inform B)
	{
		// cnt가 작은 순으로 나옴
		return A.cnt > B.cnt; // A.cnt가 클 경우 더 낮은 우선순위를 가짐 (오름차순)
	}
};
int answer = 1000000;
int dist[100][100][4];
// 어떤 방향으로 도착했는지도 중요
// → dist을 3차원으로 관리해야 함
// → 어떤 방향을 보며 도착했는지에 따라 cnt가 달라지기 때문 (이후 루트는 같을 수도 있지만 보유한 cnt가 달라짐!!)

void Solution()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			for (int k = 0; k < 4; k++) dist[i][j][k] = 1000000;
		}
	}

	priority_queue<inform, vector<inform>, inform> pq;
	pq.push({ startR, startC, startDir, 0 });

	dist[startR][startC][startDir] = 0;

	/* 최단거리를 확실히 보장하기 위해서 */
	// → 우선순위 큐 적용
	// → cnt가 작은 것부터 꺼내서 움직임 (다익스트라 적용)
	while (!pq.empty())
	{
		int R = pq.top().R;
		int C = pq.top().C;
		int dir = pq.top().dir;
		int cnt = pq.top().cnt;

		pq.pop();

		if (R == targetR && C == targetC)
		{
			int temp_answer = cnt + turn_cnt(dir, targetDir);
			if (temp_answer < answer) answer = temp_answer;
		}
		if (cnt > dist[R][C][dir]) continue; // 이미 더 작은 cnt로 처리했다면 pass

		for (int i = 0; i < 4; i++) // 해당 방향으로 2칸, 3칸 이동하는 것도 고려
		{
			int NR = R + dr[i];
			int NC = C + dc[i];
			
			if (NR < 0 || NR >= N || NC < 0 || NC >= M) continue;
			if (Map[NR][NC] == 1) continue;
			int Ncnt = cnt + 1 + turn_cnt(dir, i);
			if (Ncnt < dist[NR][NC][i])
			{
				dist[NR][NC][i] = Ncnt;
				pq.push({ NR, NC, i, Ncnt });
			}

			// 2칸 이동하는 경우
			NR += dr[i];
			NC += dc[i];
			if (NR < 0 || NR >= N || NC < 0 || NC >= M) continue;
			if (Map[NR][NC] == 1) continue;
			if (Ncnt < dist[NR][NC][i])
			{
				dist[NR][NC][i] = Ncnt;
				pq.push({ NR, NC, i, Ncnt });
			}

			// 3칸 이동하는 경우
			NR += dr[i];
			NC += dc[i];
			if (NR < 0 || NR >= N || NC < 0 || NC >= M) continue;
			if (Map[NR][NC] == 1) continue;
			if (Ncnt < dist[NR][NC][i])
			{
				dist[NR][NC][i] = Ncnt;
				pq.push({ NR, NC, i, Ncnt });
			}
		}
	}
	cout << answer;
}

int main()
{
	Input();
	Solution();
	return 0;
}