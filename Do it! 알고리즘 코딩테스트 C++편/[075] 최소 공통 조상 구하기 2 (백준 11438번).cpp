// 문제: https://www.acmicpc.net/problem/11438
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int N, M;
vector<vector<int>> tree;
vector<vector<int>> P; //헷갈려서 P[N][K]로 저장 (N의 2^K번째 부모) → P[N][K] = P[P[N][K-1]][K-1]
vector<int> parent;
vector<int> depth;
vector<bool> visit;

int max_depth = 0;
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
	max_depth = max(dep, max_depth);
}

void LCA(int a, int b)
{
	if (depth[a] != depth[b])
	{
		if (depth[a] < depth[b]) swap(a, b); //a의 깊이가 더 깊도록 조정
		while (depth[a] != depth[b])
		{
			int move = floor(log2(depth[a] - depth[b]));
			a = P[a][move];
		}
	}

	int k = floor(log2(max_depth));
	while (k >= 0)
	{
		if (P[a][k] != 0 && P[b][k] != 0 && P[a][k] != P[b][k]) //부모가 다를 경우 (P[a][k] or P[b][k]가 0일 경우 접근 오류 발생할 수도 있음)
		{
			a = P[a][k];
			b = P[b][k];
		}
		k--;
	}

	if (a == b) cout << a << '\n';
	else cout << P[a][0] << '\n';
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL); //이거 빼면 시간초과 문제가 발생함

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
	DFS(1, 0);

	int k = floor(log2(max_depth)); // 최대깊이 > 2^k 를 만족하는 최대값 k
	P.resize(N + 1);
	for (int i = 1; i <= N; i++)
	{
		P[i].resize(k + 1, 0);
		P[i][0] = parent[i];
	}

	for (int j = 1; j <= k; j++) //k를 순차적으로 채워줘야 함 (k=1 채우고 k=2 채우러 넘어가는 등)
	{
		for (int i = 1; i <= N; i++)
		{
			if (P[i][j - 1] != 0) //부모 노드가 있는 경우
			{
				P[i][j] = P[P[i][j - 1]][j - 1];
			}
		}
	}

	cin >> M;
	for (int i = 0; i < M; i++)
	{
		int a, b;
		cin >> a >> b;
		LCA(a, b);
	}
	return 0;
}