// 문제: https://www.acmicpc.net/problem/1504
// 알고리즘: 그래프 (그래프 탐색 및 역추적)
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, E;
int A, B; // 꼭 방문해야 하는 노드 두개
int answer = -1;
vector<pair<int, int>> node[801];

struct NODE
{
	int now; // 현재 노드
	int visitA;
	int visitB;
	long long cost;

	bool operator()(NODE A, NODE B) { return A.cost > B.cost; }
};
priority_queue<NODE, vector<NODE>, NODE> pq;

bool visit[801][2][2]; // 노드 번호, A 방문여부(0, 1), B 방문여부(0, 1)
// A와 B의 방문 여부에 따라 이후 가능한 경로가 달라지기 때문에
// 따로따로 visit을 체크해줘야 한다!

int main()
{
	cin >> N >> E;
	for (int i = 0; i < E; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;

		node[a].push_back({ b, c });
		node[b].push_back({ a, c });
	}
	cin >> A >> B;

	int visitA = 0;
	int visitB = 0;
	if (A == 1) visitA = 1;

	pq.push({ 1, visitA, visitB, 0 });
	while (!pq.empty())
	{
		int now = pq.top().now;
		int visitA = pq.top().visitA;
		int visitB = pq.top().visitB;
		int cost = pq.top().cost;
		pq.pop();

		if (now == A) visitA = true;
		if (now == B) visitB = true;

		if (visitA == 1 && visitB == 1 && now == N)
		{
			answer = cost;
			break;
		}

		if (visit[now][visitA][visitB]) continue;
		else visit[now][visitA][visitB] = true;

		for (int i = 0; i < node[now].size(); i++)
		{
			int next = node[now][i].first;
			int next_cost = node[now][i].second;

			if (visit[next][visitA][visitB]) continue;
			pq.push({ next, visitA, visitB, cost + next_cost });
		}
	}

	cout << answer;
	return 0;
}