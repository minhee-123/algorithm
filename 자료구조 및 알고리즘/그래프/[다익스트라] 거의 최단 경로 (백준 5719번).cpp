// 문제: https://www.acmicpc.net/problem/5719
#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

int N, M;
int S, D;
struct INFORM
{
	int node;
	int cost;
	bool operator()(INFORM A, INFORM B) { return A.cost > B.cost; }
};

int Map[501][501]; // Map[a][b] = c : a에서 b로 이동할 때 비용 c (-1이라면 길이 없음)
int Dist[501];

bool finish = false;
void Input()
{
	cin >> N >> M;
	if (N == 0 && M == 0)
	{
		finish = true;
		return; // 종료
	}
	for (int i = 0; i <= N; i++)
	{
		Dist[i] = 100000000;
		for (int j = 0; j <= N; j++) Map[i][j] = -1;
	}

	cin >> S >> D;
	for (int i = 0; i < M; i++)
	{
		int U, V, P; cin >> U >> V >> P;
		Map[U][V] = P;
	}
}

vector<int> parent[501]; // 최단경로가 여럿일 수 있으니 vector 사용
bool visit[501];
void Find_Min_Path()
{
	for (int i = 0; i <= N; i++) parent[i].clear();
	priority_queue<INFORM, vector<INFORM>, INFORM> que;

	que.push({ S, 0 });
	Dist[S] = 0;

	while (!que.empty())
	{
		int now = que.top().node;
		int nowC = que.top().cost;
		que.pop();

		if (Dist[now] < nowC) continue;

		for (int i = 0; i <= N; i++) // 인접 행렬의 단점은 전체를 봐야한다는 점
		{
			if (Map[now][i] == -1) continue;
			int next = i;
			int nextC = Map[now][i];

			if (Dist[i] > nowC + nextC) // 더 짧은 최단경로를 발견한 경우
			{
				parent[next].clear();
				parent[next].push_back(now);
				Dist[next] = nowC + nextC;
				que.push({ next, Dist[next] });
			}
			else if (Dist[i] == nowC + nextC) parent[next].push_back(now); // 동일한 최단경로를 발견한 경우
			// parent만 업데이트하고 큐에는 넣지 않음 (이미 큐에 동일한 최단거리 조건의 next가 들어가 있음)
		}
	}

	// 역추적 및 최단경로 삭제
	memset(visit, false, sizeof(visit));
	queue<int> q; q.push(D);
	while (!q.empty())
	{
		int B = q.front(); q.pop();
		if (B == S) continue; // S는 시작점이라 이전 간선이 존재하지 않음

		for (int i = 0; i < parent[B].size(); i++)
		{
			int A = parent[B][i];
			Map[A][B] = -1; // 경로 삭제

			if (!visit[A]) // A를 큐에 넣지 않았다면
			{
				visit[A] = true; // 큐에 중복하여 A를 넣는 경우 방지
				q.push(A);
			}
		}
	}
}

void Find_Answer()
{
	for (int i = 0; i <= N; i++) Dist[i] = 100000000;

	priority_queue<INFORM, vector<INFORM>, INFORM> que;
	que.push({ S, 0 });
	Dist[S] = 0;

	while (!que.empty())
	{
		int now = que.top().node;
		int nowC = que.top().cost;
		que.pop();

		if (Dist[now] < nowC) continue;
		if (now == D) break; // S-D 거의 최단 경로를 찾음

		for (int i = 0; i <= N; i++)
		{
			if (Map[now][i] == -1) continue;
			int nextC = Map[now][i];

			if (Dist[i] > nowC + nextC)
			{
				Dist[i] = nowC + nextC;
				que.push({ i, Dist[i] });
			}
		}
	}

	if (Dist[D] != 100000000) cout << Dist[D] << '\n';
	else cout << -1 << '\n';
}

int main()
{
	while (1)
	{
		Input();
		if (finish) break;

		Find_Min_Path();
		Find_Answer();
	}
	return 0;
}

/* 디버깅 수행 */
/* 처음 시도 → 메모리 초과 발생 */
// (1) INFORM에 vector를 넣어서 큐에서 최단경로를 들고다님
// (2) 탐색 과정이 길어질 경우 모든 경로를 복사하는 비용이 커짐 → 메모리초과 발생

/* 역방향 추적용 리스트 활용 (역추적 알고리즘) */
// (1) 경로를 역추적해야 함 → 역추적 알고리즘 활용
// (2) 이때 최단거리가 여러 개 나올 수 있으므로 parent 배열을 벡터로 선언 → vector<int> parent[501];
// (3) 역추적할 때 주의할 점은 이미 처리한 노드는 다시 큐에 넣지 않도록 해야 한다 (특정 노드가 여러번 사용되었을 경우 큐에 너무 많은 양을 넣음 → 메모리 초과 가능)
// (4) 그 외에도 BFS 및 다익스트라에서 메모리초과를 방지하기 위해서는 큐에 중복한 값을 넣지 않도록 주의하자 (최단거리 찾을 때도 동일한 최단거리에서 큐에 중복해서 넣어서 메모리초과가 발생했음)
// ★ parent 배열을 사용한 경로 역추적 알고리즘을 기억해두자! (경로가 여럿이라면 벡터를 활용!)