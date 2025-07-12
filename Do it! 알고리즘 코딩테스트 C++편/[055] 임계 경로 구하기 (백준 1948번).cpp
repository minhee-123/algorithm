// 문제: https://www.acmicpc.net/problem/1948

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

int N, M;
int S, E;
vector<pair<int, int>> city[10001]; //{이어지는 도시, 걸리는 시간}
vector<pair<int, int>> city_reverse[10001]; //에지 뒤집기

int D[10001];
int dist[10001];

int answer1, answer2 = 0;

int main()
{
	cin >> N >> M;
	for (int i = 0; i < M; i++)
	{
		int sc, ec, sp;
		cin >> sc >> ec >> sp;

		D[ec]++;
		city[sc].push_back({ ec, sp });
		city_reverse[ec].push_back({ sc, sp });
	}
	cin >> S >> E;

	queue<int> que;
	que.push(S);
	while (!que.empty())
	{
		int now = que.front();
		que.pop();

		for (int i = 0; i < city[now].size(); i++)
		{
			int next = city[now][i].first;
			int next_distance = city[now][i].second;

			dist[next] = max(dist[next], dist[now] + next_distance);
			D[next]--;

			if (D[next] == 0) que.push(next);
		}
	}
	answer1 = dist[E];

	queue<int> que2;
	que2.push(E);
	vector<bool> visit(N + 1, false);
	while (!que2.empty())
	{
		int now = que2.front();
		que2.pop();

		for (int i = 0; i < city_reverse[now].size(); i++)
		{
			int next = city_reverse[now][i].first;
			int next_distance = city_reverse[now][i].second;

			if (dist[next] + next_distance == dist[now])
			{
				answer2++;
				if (visit[next]) continue; //큐에 두번 넣으면 안되니까 (근데 두번 같은 노드로 도착할 수는 있기 때문에 visit을 여기에 둬야 함)
				else
				{
					que2.push(next);
					visit[next] = true;
				}
			}
		}
	}

	cout << answer1 << '\n' << answer2;
	return 0;
} //솔직히 문제 이해가 너무 어렵다