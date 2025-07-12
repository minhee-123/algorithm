// 문제: https://www.acmicpc.net/problem/11724
// 연결요소 → 간선으로 연결된 노드 집합

#include <iostream>
#include <vector>
using namespace std;

int N, M;
vector<int> graph[1001];
//이차원 벡터는 vector <vector<int>> A 와 같은 방식으로 선언할 수 있음

bool visit[1001]; //전역변수로 선언하면 디폴트 false
int cnt = 0;

void DFS(int index)
{
	if (visit[index]) return;
	visit[index] = true;
	cnt++;

	for (int i = 0; i < graph[index].size(); i++)
	{
		int next = graph[index][i];

		if (visit[next]) continue;
		DFS(next);
	}
}

int main()
{
	cin >> N >> M;
	for (int i = 0; i < M; i++)
	{
		int temp1, temp2;
		cin >> temp1 >> temp2;

		graph[temp1].push_back(temp2);
		graph[temp2].push_back(temp1);
	}

	int answer = 0;
	for (int i = 1; i <= N; i++)
	{
		cnt = 0;
		DFS(i);

		if (cnt > 0) answer++;
	}
	cout << answer << '\n';
	return 0;
}