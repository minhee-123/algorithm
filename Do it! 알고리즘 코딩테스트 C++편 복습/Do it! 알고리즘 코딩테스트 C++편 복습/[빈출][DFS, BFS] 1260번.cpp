// DFS와 BFS
// 문제: https://www.acmicpc.net/problem/1260
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

int N, M, V;

vector<vector<int>> graph;
bool visit[1001]; //default false

void DFS(int index)
{
	if (visit[index]) return;

	visit[index] = true;
	cout << index << " ";

	for (int i = 0; i < graph[index].size(); i++)
	{
		int next = graph[index][i];
		if (visit[next]) continue;

		DFS(next);
	}
}

void BFS(int index)
{
	queue<int> que;
	que.push(index);
	visit[index] = true;

	while (!que.empty())
	{
		int now = que.front();
		que.pop();

		cout << now << " ";

		for (int i = 0; i < graph[now].size(); i++)
		{
			int next = graph[now][i];
			if (visit[next]) continue;

			que.push(next);
			visit[next] = true;
		}
	}
}

int main()
{
	cin >> N >> M >> V;
	
	graph.resize(N + 1);
	for (int i = 0; i < M; i++)
	{
		int a, b;
		cin >> a >> b;

		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	for (int i = 1; i <= N; i++) sort(graph[i].begin(), graph[i].end());

	DFS(V);
	cout << '\n';

	memset(visit, false, sizeof(visit));

	BFS(V);

	return 0;
}