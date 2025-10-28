// 문제: https://www.acmicpc.net/problem/1600
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int K, N, M; // N과 M의 범위는 200 이하, K는 30 이하
int Map[200][200];
bool visit[200][200][31]; // K는 최대 30 (말 점프는 최대 30번 사용 가능)
// visit 배열을 3차원으로 관리
// → 말 이동 횟수에 따라 visit 관리가 달라짐 (같은 루트에서 뒤돌아가는 경우를 막아야 함)

int dr[12] = { 0, 0, 1, -1, -2, -1, 1, 2, 2, 1, -1, -2};
int dc[12] = { 1, -1, 0, 0, 1, 2, 2, 1, -1, -2, -2, -1};

struct inform
{
	int R;
	int C;
	int useK;
	int moveCNT;
};

int main()
{
	cin >> K >> M >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++) cin >> Map[i][j];
	}

	queue<inform> que;
	que.push({ 0, 0, K, 0 });
	visit[0][0][K] = true;

	int answer = -1;

	if (Map[N - 1][M - 1] == 1) cout << answer; // 도착 지점에 애초에 갈 수 없는 경우를 먼저 처리
	else
	{
		while (!que.empty())
		{
			int R = que.front().R;
			int C = que.front().C;
			int useK = que.front().useK;
			int moveCNT = que.front().moveCNT;

			que.pop();

			if (R == N - 1 && C == M - 1) // 도착한 경우
			{
				answer = moveCNT;
				break;
			} // 시작 지점이 도착 지점인 경우를 고려해야 하기 때문에 도착 체크는 이쪽에 위치해야 함

			for (int i = 0; i < 12; i++)
			{
				int NR = R + dr[i];
				int NC = C + dc[i];
				int NuseK = useK;

				if (i >= 4) // 말 점프를 사용한 경우
				{
					if (NuseK == 0) continue;
					NuseK--; // 말 이동 한번 사용
				}

				if (NR < 0 || NR >= N || NC < 0 || NC >= M) continue;
				if (Map[NR][NC] == 1) continue; // 도착한 지점에 장애물이 있으면 갈 수 없음 (말 점프는 이동 중 장애물만 무시)
				if (visit[NR][NC][NuseK]) continue; // 일반 이동에서 중복해서 이동하지 않도록 주의 (3차원 이용)

				visit[NR][NC][NuseK] = true;
				que.push({ NR, NC, NuseK, moveCNT + 1 });
			}
		}
		cout << answer;
	}
	return 0;
}

/********** 오랜만에 코테 풀어서 그런지 문제가 참 많다
* (1) 메모리 초과 문제 발생
*	큐가 과도하게 커져서 발생한 문제 → visit 체크에서 문제 (말 이동을 한 경우 이동 후에 체크해야 함)
* (2) 예외 케이스 하나를 처리하지 못함
*	1x1 맵에서 장애물이 없는 경우 → 정답이 0이어야 함
*	그래서 도착 체크 부분을 pop 이후에 넣어야 함 (정답이 0인 경우도 바로 체크)
*	→ 도착한 위치에 1이 있는 경우도 따로 처리함
**********/

/********** visit을 3차원으로 관리하는 것에 대해
* ??: visit을 3차원으로 관리하게 되면 
	  1번 이동 루트에서 K를 다 쓴 경우와 
	  2번 이동 루트에서 K를 다 써서 이동을 못할 때 
	  한 루트는 탐색하지 못하는 것 아닌가
* 
* BFS는 최단 거리를 보장하는 성질이 있음 → 모든 경로를 같은 거리(이동 횟수) 기준으로 먼저 탐색
* 처음 도달한 상태가 항상 최단 거리
* 현재 3차원으로 관리하는 이유 → 같은 칸이지만 남은 K가 다를 때 (서로 다른 상태라서 막히면 안됨 → 이후 탐색 가능성이 다르기 때문)
* 
* 3차원을 이용하는 게 다른 상태를 처리하기 위함 (상태에 따른 이동을 구분)
* 같은 상태에 도달한 경우(K 사용 수가 같은 경우) 이후 탐색 가능성은 동일하기 때문에 → 늦게 도착한 케이스는 버려야 함
* 최단 거리 보장을 이용해 같은 상태는 두번 탐색하지 않도록 구성 (불필요한 연산을 줄임)
**********/