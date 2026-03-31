// 문제: https://www.acmicpc.net/problem/5972
#include <iostream>
#include <queue>
using namespace std;

int N, M;
vector<pair<int, int>> Map[50001];

vector<int> MinDist;
vector<bool> visit;

int main()
{
	cin >> N >> M;
	for (int i = 0; i < M; i++)
	{
		int A, B, C;
		cin >> A >> B >> C;

		Map[A].push_back({ C, B });
		Map[B].push_back({ C, A });
	}

	visit.resize(N + 1, false);
	MinDist.resize(N + 1);
	for (int i = 0; i <= N; i++) MinDist[i] = 100000000;
	MinDist[1] = 0;

	priority_queue < pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> que;
	que.push({ 0, 1 }); // 현재까지 비용, 위치

	while (!que.empty())
	{
		int now = que.top().second;
		int cost = que.top().first;
		que.pop();

		if (visit[now]) continue;
		visit[now] = true;
		if (now == N) break;

		for (int i = 0; i < Map[now].size(); i++)
		{
			int next = Map[now][i].second;
			int next_cost = Map[now][i].first;

			if (visit[next]) continue;
			if (cost + next_cost < MinDist[next])
			{
				que.push({ cost + next_cost, next });
				MinDist[next] = cost + next_cost;
			}
		}
	}

	cout << MinDist[N];
	return 0;
}