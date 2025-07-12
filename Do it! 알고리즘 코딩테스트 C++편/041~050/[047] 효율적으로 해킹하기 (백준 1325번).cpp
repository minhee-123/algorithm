// 문제: https://www.acmicpc.net/problem/1325

// DFS로 풀었을 때 시간초과 문제 발생
// BFS로 풀고 접근법을 다르게 생각 → 모든 노드에 대해서 각 노드가 신뢰하는(방문하는) 노드의 신뢰값을 ++, 최대값이 정답
// 정답이 가장 많이 방문되는 노드임

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int N, M;
vector<vector<int>> graph;
vector<bool> visit;

vector<int> answer;
void BFS(int index)
{
	queue<int> q;
	q.push(index);
	visit[index] = true;

	while (!q.empty())
	{
		int now = q.front();
		q.pop();

		for (int i = 0; i < graph[now].size(); i++)
		{
			int next = graph[now][i];
			if (!visit[next])
			{
				visit[next] = true;
				answer[next]++;
				q.push(next);
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	graph.resize(N + 1);
	visit = vector<bool>(N + 1, false);
	answer = vector<int>(N + 1, 0);

	for (int i = 0; i < M; i++)
	{
		int A, B;
		cin >> A >> B;
		graph[A].push_back(B);
	}

	for (int i = 1; i <= N; i++)
	{
		fill(visit.begin(), visit.end(), false);
		BFS(i);
	}

	int maxVal = 0;
	for (int i = 1; i <= N; i++) maxVal = max(maxVal, answer[i]);

	for (int i = 1; i <= N; i++)
	{
		if (answer[i] == maxVal) cout << i << ' ';
	}
	return 0;
}