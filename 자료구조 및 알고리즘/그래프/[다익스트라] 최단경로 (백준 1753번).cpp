// 문제: https://www.acmicpc.net/problem/1753

// 다익스트라 알고리즘 
// → 그래프에서 최단 거리를 구하는 알고리즘
// → 특정 노드에서 다른 노드들의 최단 거리를 구하는 문제가 주어졌을 때 사용

// 최단거리 배열에서 값이 가장 작은 노드를 골라서 배열 업데이트를 수행해야 함 → 우선순위 큐(오름차순) 사용
// 우선순위 큐는 조건에 맞춰 우선순위가 가장 높은 애를 top에 올려둠
// 이때 주의할 것은 최단거리가 가장 작은 값을 기준으로 해야하기 때문에 우선순위 큐를 pair로 선언하고 첫번째 값을 거리로 해야 함

// 우선순위든 정렬이든 만약 pair라면 pair의 첫번째 값을 먼저 판별함 (같을 경우 두번째 값)

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define max_value 2147483647

int N, M, start;
vector<pair<int, int>> V[20001];
vector<int> D;
bool visit[20001];
priority_queue < pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;

void BFS(int index)
{
	pq.push(make_pair(D[index], index));

	while (!pq.empty())
	{
		pair<int, int> now = pq.top();
		pq.pop();

		int now_index = now.second;
		int now_value = now.first;

		if (visit[now_index]) continue; //visit을 여기서 처리해야 함 또한 주의 (최단거리 배열에서 가장 작은 노드로 선택했을 때 처리하는 것임)
		visit[now_index] = true;

		for (int i = 0; i < V[now_index].size(); i++)
		{
			int next_index = V[now_index][i].second;
			int move_value = V[now_index][i].first;

			if (visit[next_index]) continue;

			if (D[next_index] > now_value + move_value)
			{
				D[next_index] = now_value + move_value;
				pq.push(make_pair(D[next_index], next_index));
			}
		}
	}
}

int main()
{
	cin >> N >> M >> start;
	for (int i = 0; i < M; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;

		V[u].push_back({ w, v });
	}

	D = vector<int>(N + 1, max_value);
	D[start] = 0;
	BFS(start);

	for (int i = 1; i <= N; i++)
	{
		if (visit[i]) cout << D[i] << '\n';
		else cout << "INF" << '\n';
	}
	return 0;
}