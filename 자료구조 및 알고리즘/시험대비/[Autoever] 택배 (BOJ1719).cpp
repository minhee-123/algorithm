// 문제: https://www.acmicpc.net/problem/1719
// 알고리즘: 그래프 (그래프 탐색 및 역추적)
#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

int N, M;
int Map[201][201];

vector<pair<int, int>> load[201];
bool visit[201];

struct INFORM
{
	int now_index;
	int cost;
	int first_index; // 시작지점에서 처음 방문한 곳

	bool operator()(INFORM A, INFORM B) { return A.cost > B.cost; }
};

void find_answer(int start) // 시작점에서 모든 노드까지 최단경로(다익스트라)
{
	memset(visit, false, sizeof(visit));
	priority_queue<INFORM, vector<INFORM>, INFORM> pq;
	pq.push({ start, 0, 0 });

	while (!pq.empty())
	{
		int now = pq.top().now_index;
		int cost = pq.top().cost;
		int first = pq.top().first_index;
		pq.pop();

		if (visit[now]) continue; // cost를 기준으로 순서대로 나옴
		visit[now] = true;
		Map[start][now] = first;

		for (int i = 0; i < load[now].size(); i++)
		{
			int next = load[now][i].first;
			int next_cost = load[now][i].second;
			int next_first = first;
			if (first == 0) next_first = next;

			if (visit[next]) continue;
			pq.push({ next, cost + next_cost, next_first });
		}
	}
}

int main()
{
	cin >> N >> M;
	for (int i = 0; i < M; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;

		load[a].push_back({ b, c });
		load[b].push_back({ a, c });
	}

	for (int i = 1; i <= N; i++) find_answer(i);
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			if (i == j) cout << "- ";
			else cout << Map[i][j] << ' ';
		}
		cout << '\n';
	}
	return 0;
}