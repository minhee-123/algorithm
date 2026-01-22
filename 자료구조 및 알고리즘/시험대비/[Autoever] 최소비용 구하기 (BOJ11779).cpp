// 문제: https://www.acmicpc.net/problem/11779
// 알고리즘: 그래프 (그래프 탐색 및 역추적)
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, M;
vector<pair<int, int>> bus[1001];
int A, B;

struct NODE
{
	int now;
	long cost;
	vector<int> path;

	bool operator()(NODE A, NODE B) { return A.cost > B.cost; }
};
priority_queue<NODE, vector<NODE>, NODE> pq;
bool visit[1001];

int main()
{
	cin >> N >> M;
	for (int i = 0; i < M; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		bus[a].push_back({ b, c });
	}
	cin >> A >> B;

	pq.push({ A, 0, {A} });
	while (!pq.empty())
	{
		int now = pq.top().now;
		int cost = pq.top().cost;
		vector<int> path = pq.top().path;
		pq.pop();

		if (now == B)
		{
			cout << cost << '\n' << path.size() << '\n';
			for (int i = 0; i < path.size(); i++) cout << path[i] << ' ';
			break;
		}

		if (visit[now]) continue;
		else visit[now] = true;

		for (int i = 0; i < bus[now].size(); i++)
		{
			int next = bus[now][i].first;
			int next_cost = cost + bus[now][i].second;

			vector<int> next_path = path;
			next_path.push_back(next);

			if (visit[next]) continue;
			pq.push({ next, next_cost, next_path });
		}
	}
	return 0;
}

// 해당 방법(vector를 큐의 인자로 가져옴)은 데이터의 크기가 작을 때만 가능함 → 데이터의 크기가 커질 경우 오버플로우가 발생할 수 있음
// 문제에서 의도한 방법은 → 부모 노드 기록 및 역추적

/* 부모 노드 기록 및 역추적 */
// (1) parent 배열 하나를 더 만들어서 관리 (int parent[1001])
// (2) dist[next] > dist[now] + cost 일때 parent[next] = now로 저장
// → 현재 풀이에서 dist 배열을 안 쓰고 있는데 원래는 dist 배열을 써야 함 (원래 다익스트라에서 사용, 효율성 향상)
// → 무한대로 초기화한 dist 배열을 통해 현재 경로가 이전에 찾은 경로보다 비용이 낮을 때만 큐에 넣음 (탐색 횟수 및 메모리 줄임)
// (3) 목적지 B에 도착하면 parent[B]를 타고 A가 나올 때까지 계속 올라감
// (4) 역추적의 경우 역추적 결과를 stack에 집어넣었다가 빼내면 편함 (후입선출)