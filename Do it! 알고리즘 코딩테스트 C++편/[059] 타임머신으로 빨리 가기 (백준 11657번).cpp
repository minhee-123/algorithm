// 문제: https://www.acmicpc.net/problem/11657
// 어떤 도시로 가는 과정에서 시간을 무한히 오래전으로 되돌릴 수 있다면 → 음수 사이클이 존재한다면
#include <iostream>
#include <vector>
#include <limits.h>
#include <algorithm>
using namespace std;

struct edge
{
	int A;
	int B;
	int C;
};

int N, M;
vector<long> dis; //최단거리 배열
vector<edge> E; //edge 정보

int main()
{
	cin >> N >> M;
	dis.resize(N + 1);
	fill(dis.begin(), dis.end(), LONG_MAX);

	for (int i = 0; i < M; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		E.push_back({ a, b, c });
	}

	dis[1] = 0;
	bool flag = false; //음수 사이클의 유(true)무(false)

	for (int i = 1; i <= N; i++) //에지들을 N-1번 사용, N번째는 음수사이클 확인 (음수사이클이 없다면 N번째에 업데이트가 발생하지 않음)
	{
		for (int j = 0; j < M; j++) //에지는 총 M개 있음 (0번부터 M-1번)
		{
			int start = E[j].A;
			int end = E[j].B;
			int weight = E[j].C;

			if (dis[start] == LONG_MAX) continue; //출발 노드의 값이 무한대라면 업데이트를 수행하지 않음 (아직 출발노드까지 탐색한 정보가 없음)
			if (dis[end] > dis[start] + weight)
			{
				dis[end] = dis[start] + weight;
				if (i == N) flag = true; //N번째에 업데이트가 발생했다면 음수사이클 존재
			}
		}
	}

	if (flag) cout << -1 << '\n';
	else
	{
		for (int i = 2; i <= N; i++)
		{
			if (dis[i] == LONG_MAX) cout << -1 << '\n';
			else cout << dis[i] << '\n';
		}
	}
	return 0;
}