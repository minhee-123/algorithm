// 문제: https://www.acmicpc.net/problem/1516

#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int build_time[501] = { 0 }; //건물 생산 시간
int indegree[501] = { 0 }; //진입 차수 배열
int answer_time[501] = { 0 }; //정답 배열
vector<int> building[501];

int main()
{
	int N; cin >> N;
	for (int i = 1; i <= N; i++)
	{
		cin >> build_time[i];

		int b; cin >> b;
		while (b != -1)
		{
			building[b].push_back(i);
			indegree[i]++;
			cin >> b;
		}
	}

	queue<int> que;
	for (int i = 1; i <= N; i++)
	{
		if (indegree[i] == 0) que.push(i);
	}

	while (!que.empty())
	{
		int now = que.front();
		que.pop();

		for (int i = 0; i < building[now].size(); i++)
		{
			int next = building[now][i];
			//max(next 건물에 저장된 최대 시간, now 건물에 저장된 최대 시간 + now 건물의 생산 시간)
			answer_time[next] = max(answer_time[next], answer_time[now] + build_time[now]); //이 부분을 생각해내는 게 좀 어려움

			indegree[next]--;
			if (indegree[next] == 0) que.push(next);
		}
	}

	for (int i = 1; i <= N; i++) cout << answer_time[i] + build_time[i] << '\n'; //본인 건물 짓는 시간 포함
	return 0;
}