// 문제: https://www.acmicpc.net/problem/1854
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits.h>
using namespace std;

int N, M, K;
int node[1001][1001]; //가중치를 중점적으로 다루기 때문에 인접리스트보다는 인접행렬이 더 편리함 (대신 인접행렬은 데이터 수가 커지면 메모리가 너무 커짐을 주의)
priority_queue<int, vector<int>> dis[1001]; //최단거리 배열 (내림차순, 데이터를 넣을 때마다 자동정렬)
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; //(오름차순)

int main()
{
	cin >> N >> M >> K;
	for (int i = 0; i < M; i++)
	{
		int s, e, d;
		cin >> s >> e >> d;
		node[s][e] = d;
	}

	dis[1].push(0);
	pq.push({ 0, 1 });

	while (!pq.empty())
	{
		int now_index = pq.top().second;
		int now_dis = pq.top().first;
		pq.pop(); //K번째 최단거리를 찾기 위해 방문했던 노드를 재방문해야 되기 때문에 visit을 사용하지 않음

		for (int i = 1; i <= N; i++)
		{
			if (node[now_index][i] == 0) continue;
			int next_dis = now_dis + node[now_index][i];

			if (dis[i].size() < K) //K개보다 적게 저장한 상태라면 push
			{
				dis[i].push(next_dis);
				pq.push({ next_dis, i });
			}
			else //dis[i].size() >= K (K개가 저장되어 있는 상태라면)
			{
				if (dis[i].top() > next_dis) //가장 큰값보다 작을 경우 push
				{
					dis[i].pop();
					dis[i].push(next_dis);
					pq.push({ next_dis, i });
				}
			}
		}
	}

	for (int i = 1; i <= N; i++)
	{
		if (dis[i].size() < K) cout << -1 << '\n';
		else cout << dis[i].top() << '\n';
	}
	return 0;
}