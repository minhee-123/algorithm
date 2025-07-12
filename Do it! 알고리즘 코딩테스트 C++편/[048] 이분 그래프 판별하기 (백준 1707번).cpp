// 문제: https://www.acmicpc.net/problem/1707
// 처음에 문제 이해를 잘못해서 좀 헤맴

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int K, V, E;
vector<vector<int>> graph;
vector<bool> visit;
vector<char> group;

bool flag = false;
void DFS(int index, char G)
{
	if (visit[index]) return;
	visit[index] = true;
	group[index] = G;

	for (int i = 0; i < graph[index].size(); i++)
	{
		int next = graph[index][i];
		if (visit[next]) //현재 노드와 연결되어 있는데 이미 방문한 곳
		{
			if (group[next] == G) //연결되어 있는 노드가 같은 집합 (이분 그래프 X)
			{
				flag = true;
				break;
			}
			else continue;
		}
		else
		{
			char next_c;
			if (G == 'A') next_c = 'B';
			else next_c = 'A';

			DFS(next, next_c);
		}
	}
}

void clear_all()
{
	V = 0;
	E = 0;
	graph.clear();
	visit.clear();
	group.clear();
	flag = false; //초기화 까먹으면 안됨
}

int main()
{
	cin >> K;
	for (int i = 0; i < K; i++)
	{
		clear_all();
		cin >> V;
		if (V == 1)
		{
			cout << "NO" << '\n';
			continue;
		}
		cin >> E;

		graph.resize(V + 1);
		visit = vector<bool>(V + 1, false);
		group = vector<char>(V + 1, 'N');

		for (int i = 0; i < E; i++)
		{
			int A, B;
			cin >> A >> B;
			graph[A].push_back(B);
			graph[B].push_back(A);
		}

		for (int i = 1; i <= V; i++)
		{
			DFS(i, 'A');
			if (flag) break;
		}

		if (flag) cout << "NO" << '\n'; //이분그래프X
		else cout << "YES" << '\n'; //이분그래프
	}
	return 0;
}