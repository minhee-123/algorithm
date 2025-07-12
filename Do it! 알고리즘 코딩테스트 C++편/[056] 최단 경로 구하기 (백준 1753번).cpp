// 문제: https://www.acmicpc.net/problem/1753
// 다익스트라 알고리즘을 잘못 이해해서 처음에 잘못 구현함
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int V, E, S;
vector<pair<int, int>> node[20001]; //연결 노드, 가중치
bool visit[20001];
int dis[20001]; //최단거리 배열
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; //오름차순 우선순위 큐

int main()
{
	cin >> V >> E >> S;
	for (int i = 0; i < E; i++) 
	{
		int u, v, w;
		cin >> u >> v >> w;
		node[u].push_back({ v, w });
	}
	memset(dis, 5000000, sizeof(dis));

	dis[S] = 0;
	pq.push({ 0, S }); //거리, index (거리를 기준으로 우선순위 큐 수행)
	
	while (!pq.empty())
	{
		int now_index = pq.top().second;
		int now_dis = pq.top().first;
		pq.pop();

		if (visit[now_index]) continue; //이미 선택된 적이 있다면(더 작은 거리로 이미 선택된 적이 있다면) pass
		visit[now_index] = true;

		for (int i = 0; i < node[now_index].size(); i++)
		{
			int next_index = node[now_index][i].first;
			int next_val = node[now_index][i].second;

			if (visit[next_index]) continue; //이미 최단거리로 선택됨 (시작점을 기준으로 최단거리부터 처리하기 때문에)
			if (dis[next_index] > now_dis + next_val) //최단거리 업데이트
			{
				dis[next_index] = now_dis + next_val;
				pq.push({ dis[next_index], next_index }); //업데이트가 수행될 때만 pq에 삽입
			}
		}
	}

	for (int i = 1; i <= V; i++)
	{
		if (!visit[i]) cout << "INF" << '\n'; //선택되지 않은 값들은 시작점에서 도착할 수 없는 노드
		else cout << dis[i] << '\n';
	}
	return 0;
}