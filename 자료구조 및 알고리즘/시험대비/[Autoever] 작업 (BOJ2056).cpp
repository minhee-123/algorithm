// 문제: https://www.acmicpc.net/problem/2056
// 알고리즘: 그래프? 트리? + DP? (위상정렬)
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int N;
vector<int> map[10001];
vector<int> indegree;
vector<int> time_cnt;
vector<int> time_origin;

bool comp(int a, int b) { return a > b; }

int main()
{
	cin >> N;
	indegree.resize(N + 1, 0);
	time_cnt.resize(N + 1, 0);
	time_origin.resize(N + 1, 0);

	for (int i = 1; i <= N; i++)
	{
		int T, M;
		cin >> T >> M;

		time_origin[i] = T;
		for (int j = 0; j < M; j++)
		{
			int temp;
			cin >> temp;

			map[temp].push_back(i);
			indegree[i]++; // temp랑 i 자리를 바꿔도 문제가 없다 (결국 찾는 과정은 같기 때문)
		}
	}

	queue<int> que;
	for (int i = 1; i <= N; i++)
	{
		if (indegree[i] == 0)
		{
			que.push(i);
			time_cnt[i] = time_origin[i];
		}
	}

	while (!que.empty())
	{
		int now = que.front();
		que.pop();

		for (int i = 0; i < map[now].size(); i++)
		{
			int next = map[now][i];
			time_cnt[next] = max(time_cnt[next], time_cnt[now] + time_origin[next]);
			indegree[next]--;

			if (indegree[next] == 0) que.push(next);
		}
	}

	sort(time_cnt.begin(), time_cnt.end(), comp);
	cout << time_cnt[0];
	return 0;
}
