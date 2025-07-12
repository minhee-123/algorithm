// 문제: https://www.acmicpc.net/problem/11437
#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> tree;
vector<int> parent;
vector<int> depth;
vector<bool> visit;

void DFS(int idx, int dep)
{
	if (visit[idx]) return;
	visit[idx] = true;
	depth[idx] = dep;

	for (int i = 0; i < tree[idx].size(); i++)
	{
		int next = tree[idx][i];
		if (visit[next]) continue;

		parent[next] = idx;
		DFS(next, dep + 1);
	}
} //부모배열, 깊이배열 생성

void LCA(int a, int b) //최소 공통 조상
{
	if (depth[a] != depth[b]) //깊이가 다를 경우 (깊이를 같게 맞춰야 함)
	{
		if (depth[a] > depth[b]) LCA(parent[a], b); //a가 더 깊다면 a를 이동
		else LCA(a, parent[b]); //b가 더 깊다면 b를 이동
	}
	else //깊이가 같을 경우
	{
		while (a != b)
		{
			a = parent[a];
			b = parent[b];
		} //한층씩 같이 이동
		cout << a << '\n';
	}
}

int main()
{
	int N;
	cin >> N;

	tree.resize(N + 1);
	parent.resize(N + 1);
	depth.resize(N + 1);
	visit = vector<bool>(N + 1, false);

	for (int i = 0; i < N - 1; i++)
	{
		int a, b;
		cin >> a >> b;
		tree[a].push_back(b);
		tree[b].push_back(a);
	}
	DFS(1, 0); //부모노드랑 깊이 정보 저장

	int M;
	cin >> M;

	for (int i = 0; i < M; i++)
	{
		int a, b;
		cin >> a >> b;
		LCA(a, b);
	}
	return 0;
}