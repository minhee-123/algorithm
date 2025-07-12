// 문제: https://www.acmicpc.net/problem/1516

// 위상정렬 알고리즘 → 사이클이 없는 그래프에서만 사용가능
// 사이클 → 그래프의 특정 노드에서 출발하여 방향을 따라 다시 출발한 노드로 올 수 있는 상황 (순환하는 형태를 가짐)

// 너무 어려워서 풀다가 정답풀이 보고 따라함
// 심지어 문제를 잘못 이해하고 있었음 (집중해라...)
// 입력으로 주어지는 것은 해당 건물을 짓기 위해 먼저 지어야 하는 건물의 index들
// 건물을 짓기 위해 먼저 지어야하는 건물들이 있음 → 노드 순서가 있음 → 그래서 위상정렬

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
	int N; cin >> N;

	vector<int> build[501]; //건물 인접리스트
	vector<int> indegree(N + 1, 0); //진입차수 배열
	vector<int> self_build(N + 1, 0); //건물을 짓는데 걸리는 시간

	for (int i = 1; i <= N; i++)
	{
		cin >> self_build[i];
		while (1)
		{
			int temp;
			cin >> temp;

			if (temp == -1) break;

			build[temp].push_back(i);
			indegree[i]++; //진입차수 저장 (현재 건물의 인접리스트 값들은 진입차수가 하나씩 증가함)
		}
	}

	//위상정렬 → 위상정렬의 구현은 BFS와 유사함
	queue<int> q;
	for (int i = 1; i <= N; i++)
	{
		if (indegree[i] == 0) q.push(i); //진입차수가 0인 값을 큐에 넣음
	}

	vector<int> answer(N + 1, 0);
	while (!q.empty())
	{
		int now = q.front();
		q.pop();

		for (int i = 0; i < build[now].size(); i++)
		{
			int next = build[now][i];
			indegree[next]--;

			answer[next] = max(answer[next], answer[now] + self_build[now]); //해당 건물의 선행조건 건물들을 모두 짓고 와야하기 때문에 max를 사용함 (예제의 건물 4번을 생각해보면 이해할 수 있음)
			if (indegree[next] == 0) q.push(next);
		}
	}

	for (int i = 1; i <= N; i++)
	{
		cout << answer[i] + self_build[i] << '\n';
	}
	return 0;
}