// 문제: https://www.acmicpc.net/problem/14567
// 알고리즘: 그래프
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// 걸리는 시간을 1이라고 생각하고 위상정렬 수행
int N, M;
vector<int> subj[1001];

vector<int> indegree;
vector<int> term;

int main()
{
	cin >> N >> M;
	indegree.resize(N + 1, 0);
	term.resize(N + 1, 0);

	for (int i = 0; i < M; i++)
	{
		int A, B; // A가 B의 선수과목 (A를 들어야 B를 들을 수 있음)
		cin >> A >> B;

		subj[A].push_back(B);
		indegree[B]++;
	}

	queue<int> que;
	for (int i = 1; i <= N; i++)
	{
		if (indegree[i] == 0)
		{
			que.push(i);
			term[i] = 1;
		}
	}

	while (!que.empty())
	{
		int now = que.front();
		que.pop();

		for (int i = 0; i < subj[now].size(); i++)
		{
			int next = subj[now][i];
			term[next] = max(term[next], term[now] + 1);
			indegree[next]--;

			if (indegree[next] == 0) que.push(next);
		}
	}

	for (int i = 1; i <= N; i++) cout << term[i] << ' ';
	return 0;
}
