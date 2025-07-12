// 최단경로 구하기
// 문제: https://www.acmicpc.net/problem/1753

// 다익스트라 알고리즘: 양수인 에지 가중치가 있을때 출발 노드에서 모든 노드까지의 최단 거리를 구함
// 최단거리 배열 + 우선순위 큐를 이용해서 구현

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int V, E;
int S; //출발 노드
vector<vector<pair<int, int>>> graph;

vector<int> minD; //최단거리 배열
priority_queue < pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq; //값이 가장 작은 노드를 선택하기 위함 (우선순위 큐로 관리, 오름차순으로 설정)
vector<bool> visit; //방문여부 배열

int main()
{
	cin >> V >> E >> S;

	graph.resize(V + 1);
	minD.resize(V + 1, 3000001);
	visit.resize(V + 1, false);

	for (int i = 0; i < E; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		graph[u].push_back({ v, w }); //(노드번호, 가중치) 순으로 정리
	}

	minD[S] = 0;
	pq.push({ minD[S], S }); //(거리, 노드번호) 순으로 저장

	while (!pq.empty())
	{
		int now_index = pq.top().second;
		int now_distance = pq.top().first;
		pq.pop();

		if (visit[now_index]) continue;
		visit[now_index] = true;


		for (int i = 0; i < graph[now_index].size(); i++)
		{
			int next_index = graph[now_index][i].first;
			int next_weight = graph[now_index][i].second;

			if (minD[next_index] > now_distance + next_weight)
			{
				minD[next_index] = now_distance + next_weight;
				pq.push({ minD[next_index], next_index });
			}
		}
	}

	for (int i = 1; i <= V; i++)
	{
		if (minD[i] == 3000001) cout << "INF" << '\n';
		else cout << minD[i] << '\n';
	}
	return 0;
}