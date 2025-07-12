// 문제: https://www.acmicpc.net/problem/1167

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int N;
vector<int> A[100001];
vector<int> D[100001];
bool visit[100001];
int dis[100001] = { 0 };

void BFS(int index)
{
	queue<int> q;
	q.push(index);

	visit[index] = true;
	dis[index] = 0;

	while (!q.empty())
	{
		int now_index = q.front();
		q.pop();

		for (int i = 0; i < A[now_index].size(); i++)
		{
			int next_index = A[now_index][i];
			int next_dis = D[now_index][i];

			if (visit[next_index]) continue;

			q.push(next_index);
			visit[next_index] = true;
			dis[next_index] = dis[now_index] + next_dis;
		}
	}
}

int main()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		int index;
		cin >> index;

		while (1)
		{
			int E_A;
			cin >> E_A;
			if (E_A == -1) break;

			int E_D;
			cin >> E_D;

			A[index].push_back(E_A);
			D[index].push_back(E_D);
		}
	}

	BFS(1);
	
	int max_index = 1;
	int max_value = dis[1];
	for (int i = 1; i <= N; i++)
	{
		if (dis[i] > max_value)
		{
			max_index = i;
			max_value = dis[i];
		}
	}

	memset(visit, false, sizeof(visit));
	BFS(max_index);

	for (int i = 1; i <= N; i++)
	{
		if (dis[i] > max_value)
		{
			max_index = i;
			max_value = dis[i];
		}
	}
	cout << max_value << '\n';
	return 0;
}