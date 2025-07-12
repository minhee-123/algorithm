// 문제: https://www.acmicpc.net/problem/11725
#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> tree;
vector<bool> visit;
vector<int> answer;

void DFS(int index)
{
	if (visit[index]) return; //순환이 없는 트리 구조라서 return 되는 일은 없을 것임
	visit[index] = true;

	for (int i = 0; i < tree[index].size(); i++)
	{
		int next = tree[index][i];
		if (visit[next]) continue; //순환이 없는 트리 구조라서 return 되는 일은 없을 것임

		answer[next] = index;
		DFS(next);
	}
}

int main()
{
	int N;
	cin >> N;

	tree.resize(N + 1);
	visit.resize(N + 1);
	answer.resize(N + 1);

	for (int i = 0; i < N - 1; i++)
	{
		int a, b;
		cin >> a >> b;
		tree[a].push_back(b);
		tree[b].push_back(a);
	}

	DFS(1);

	for (int i = 2; i <= N; i++) cout << answer[i] << '\n';
	return 0;
}