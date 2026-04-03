// 문제: https://www.acmicpc.net/problem/1238
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// 전체 노드 중에서 최단거리로 오고 가는데 가장 오래 걸리는 사람 찾기
// A 지점에서 X 지점까지 최단거리 + X 지점에서 A 지점까지 최단거리 (모든 최단거리를 구하게 될 듯)

int N, M, X;
int Dist[1001][1001]; // Dist[A][B] = A 지점 출발, B 지점 도착

struct INFORM
{
	int node;
	int cost;
	bool operator()(INFORM A, INFORM B) { return A.cost > B.cost; }
};
vector<INFORM> road[1001];

void Find_Min(int S) // S에서 출발하여 모든 지점까지 최단 거리를 계산
{
	priority_queue<INFORM, vector<INFORM>, INFORM> que;
	que.push({ S, 0 });
	Dist[S][S] = 0;

	while (!que.empty())
	{
		int now = que.top().node;
		int cost = que.top().cost;
		que.pop();

		if (Dist[S][now] < cost) continue;

		for (int i = 0; i < road[now].size(); i++)
		{
			int next = road[now][i].node;
			int nextCost = road[now][i].cost;

			if (Dist[S][next] > cost + nextCost)
			{
				Dist[S][next] = cost + nextCost;
				que.push({ next, Dist[S][next] });
			}
		}
	}
}

int main()
{
	cin >> N >> M >> X;
	for (int i = 0; i < M; i++)
	{
		int A, B, T;
		cin >> A >> B >> T;
		road[A].push_back({ B, T });
	}

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++) Dist[i][j] = 100000000;
	}

	for (int i = 1; i <= N; i++) Find_Min(i);
	int answer = 0;
	for (int i = 1; i <= N; i++) answer = max(answer, Dist[i][X] + Dist[X][i]);

	cout << answer;
	return 0;
}