// 문제: https://www.acmicpc.net/problem/1260

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

int N, M, V;
vector<int> A[1001];
bool visit[1001];

void DFS(int index)
{
	visit[index] = true;
	cout << index << ' ';

	for (int i = 0; i < A[index].size(); i++)
	{
		int next = A[index][i];

		if (visit[next]) continue;
		DFS(next);
	}
}

void BFS(int index)
{
	queue<int> Q;
	Q.push(index);
	visit[index] = true;
	
	while (!Q.empty())
	{
		int now = Q.front();
		Q.pop();
		cout << now << ' ';

		for (int i = 0; i < A[now].size(); i++)
		{
			int next = A[now][i];

			if (visit[next]) continue;

			Q.push(next);
			visit[next] = true; //방문체크가 이쪽에 있어야 함 → 그래야 같은 노드가 중복으로 큐에 들어가는 경우를 방지함
		}
	}
}

int main()
{
	cin >> N >> M >> V;
	for (int i = 0; i < M; i++)
	{
		int temp1, temp2;
		cin >> temp1 >> temp2;

		A[temp1].push_back(temp2);
		A[temp2].push_back(temp1);
	}

	for (int i = 1; i <= N; i++) //방문할 수 있는 노드가 여러 개일 경우, 노드 번호가 작은 것을 먼저 방문함 → 정렬해둬야 함
	{
		sort(A[i].begin(), A[i].end());
	}

	DFS(V);
	cout << '\n';
	memset(visit, false, sizeof(visit));
	BFS(V);

	return 0;
}