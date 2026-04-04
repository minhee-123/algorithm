// 문제: https://www.acmicpc.net/problem/1766
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// 노드 순서를 결정할 때 같은 조건이라면 작은 수부터 가져와야 함
struct comp
{
	bool operator()(int a, int b) { return a > b; }
};

int N, M;
vector<int> indegree;
vector<int> inform[32001];

int main()
{
	cin >> N >> M;
	indegree.resize(N + 1, 0);

	for (int i = 0; i < M; i++)
	{
		int A, B; cin >> A >> B; // A를 풀고 B를 풀어야 함 (A -> B)
		inform[A].push_back(B);
		indegree[B]++;
	}

	priority_queue<int, vector<int>, comp> que;
	for (int i = 1; i <= N; i++)
	{
		if (indegree[i] == 0) que.push(i);
	}

	vector<int> answer;
	while (!que.empty())
	{
		int now = que.top();
		que.pop();
		// 위상정렬의 조건은 사이클 없음 → visit 배열을 필요로 하지 않음

		answer.push_back(now);
		for (int i = 0; i < inform[now].size(); i++)
		{
			int next = inform[now][i];
			indegree[next]--;

			if (indegree[next] == 0) que.push(next);
		}
	}

	for (int i = 0; i < answer.size(); i++) cout << answer[i] << ' ';
	return 0;
}