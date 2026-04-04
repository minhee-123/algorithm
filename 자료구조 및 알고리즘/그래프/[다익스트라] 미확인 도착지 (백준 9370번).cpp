// 문제: https://www.acmicpc.net/problem/9370
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int T;
int n, m, t; // 노드, 간선, 목적지 후보의 개수
int s, g, h; // 출발지, 지나야 하는 간선의 노드들 (g에서 h로든, h에서 g로든)

struct INFORM
{
	int node;
	int cost;
	bool pass;
	bool operator()(INFORM A, INFORM B) { return A.cost > B.cost; }
};
vector<INFORM> Map[2001];

vector<bool> target;
vector<int> answer;
int Dist[2001][2]; // Dist[i][j] = i번째 노드의 g-h 간선을 지난/안 지난 경우에서 최단거리

void Input()
{
	target.clear();
	answer.clear();
	for (int i = 0; i <= 2000; i++) Map[i].clear();

	cin >> n >> m >> t;
	cin >> s >> g >> h;
	target.resize(n + 1, false);
	for (int i = 0; i <= n; i++)
	{
		Dist[i][0] = 100000000;
		Dist[i][1] = 100000000;
	} // 최단거리 배열 초기화

	for (int i = 0; i < m; i++)
	{
		int a, b, d; cin >> a >> b >> d;
		Map[a].push_back({ b, d, false });
		Map[b].push_back({ a, d, false });
	}
	for (int i = 0; i < t; i++)
	{
		int x; cin >> x;
		target[x] = true; // 목적지 후보
	}
}

void Solution()
{
	Input();
	priority_queue<INFORM, vector<INFORM>, INFORM> que;
	que.push({ s, 0, false});
	Dist[s][0] = 0;

	while (!que.empty())
	{
		int now = que.top().node;
		int nowCost = que.top().cost;
		bool pass = que.top().pass;
		que.pop();

		if (Dist[now][pass] < nowCost) continue;
		if (pass && Dist[now][pass] <= Dist[now][0] && target[now]) answer.push_back(now);
		// g-h 간선을 통과한 경우 && 해당 노드로 가는 최단거리 && 후보 중 하나

		for (int i = 0; i < Map[now].size(); i++)
		{
			int next = Map[now][i].node;
			int nextCost = Map[now][i].cost;

			bool nextPass = pass;
			if ((now == g && next == h) || (now == h && next == g)) nextPass = true;
			
			if (Dist[next][nextPass] > nowCost + nextCost)
			{
				Dist[next][nextPass] = nowCost + nextCost;
				que.push({ next, Dist[next][nextPass], nextPass });
			}
		}
	}

	sort(answer.begin(), answer.end());
	for (int i = 0; i < answer.size(); i++) cout << answer[i] << ' ';
	cout << '\n';
}

int main()
{
	cin >> T;
	for (int i = 0; i < T; i++) Solution();
	return 0;
}

/* 디버깅을 수행했다! */
// (1) g-h 간선 지남 여부를 따로 pass라는 변수로 관리했는데
// → Dist 최단거리 판단을 통한 큐 삽입에서 동일한 최단거리의 루트가 여러개 있을 경우 정답을 보장하지 않음
// (2) g-h 간선 지남 여부 또한 최단거리처럼 하나의 조건! → Dist 배열을 2차원으로 선언해서 사용
// (3) BFS에서도 그랬듯이 특정 조건에 따라 결과가 달라진다면 visit이나 Dist 배열의 차원을 하나 늘려야 함 (다른 경우로 취급)