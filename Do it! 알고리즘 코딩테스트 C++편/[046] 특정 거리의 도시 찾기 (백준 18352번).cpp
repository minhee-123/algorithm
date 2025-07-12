// 문제: https://www.acmicpc.net/problem/18352

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main()
{
	int N, M, K, X;
	cin >> N >> M >> K >> X;

	vector<vector<int>> graph(N + 1);
	for (int i = 0; i < M; i++)
	{
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
	}

	vector<int> visit(N + 1, -1); // -1로 초기화하고 문제를 풀어야 함 (0으로 할 경우, K가 0일때 방문하지 않은 노드도 답이 되버림)
	vector<int> answer;

	queue<int> q;
	q.push(X);
	visit[X]++;

	while (!q.empty())
	{
		int now = q.front();
		q.pop();

		for (int i = 0; i < graph[now].size(); i++)
		{
			int next = graph[now][i];
			if (visit[next] == -1)
			{
				visit[next] = visit[now] + 1;
				q.push(next);
			}
		}
	}

	for (int i = 1; i <= N; i++)
	{
		if (visit[i] == K) answer.push_back(i);
	}

	if (answer.size() == 0) cout << -1 << '\n';
	else
	{
		for (int i = 0; i < answer.size(); i++) cout << answer[i] << '\n';
	}
	return 0;
}