// 문제: https://www.acmicpc.net/problem/13913
// 알고리즘: 그래프 (그래프 탐색 및 역추적)
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

int N, K;
bool visit[100001];

int parent[100001];
int dist[100001];

struct NODE
{
	int num;
	int cost;

	bool operator()(NODE A, NODE B) { return A.cost > B.cost; }
};
priority_queue<NODE, vector<NODE>, NODE> pq;
// 모든 가중치가 같기 때문에 아래 풀이 상 우선순위 큐가 아니라 큐를 사용해도 문제 없음

int main()
{
	cin >> N >> K;
	for (int i = 0; i <= 100000; i++)
	{
		parent[i] = -1;
		dist[i] = 1000000; // cost의 최대값은 10^5
	}

	pq.push({ N, 0 });
	while (!pq.empty())
	{
		int now = pq.top().num;
		int cost = pq.top().cost;
		pq.pop();

		if (now == K)
		{
			cout << cost << '\n';
			break;
		}

		if (visit[now]) continue;
		visit[now] = true;

		for (int i = 0; i < 3; i++)
		{
			int next = now;

			if (i == 0) next--;
			if (i == 1) next++;
			if (i == 2) next *= 2;

			if (next < 0 || next > 100000) continue;
			if (visit[next]) continue;

			if (cost + 1 < dist[next])
			{
				parent[next] = now;
				dist[next] = cost + 1;
				pq.push({ next, cost + 1 });

				// 가중치가 모두 같아서 먼저 도착하는 숫자가 당연히 이쪽으로 옴
				// 따라서 이렇게 구성할 이유는 굳이 없음(우선순위 큐 방식) → 물론 정답에는 문제가 없다!
			}
		}
	}

	stack<int> st;
	st.push(K);

	while (st.top() != N)
	{
		int temp = parent[st.top()];
		st.push(temp);
	}

	while (!st.empty())
	{
		cout << st.top() << ' ';
		st.pop();
	}
	return 0;
}