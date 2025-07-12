// 문제: https://www.acmicpc.net/problem/1916
#include <iostream>
#include <vector>
#include <queue>
#include <limits.h> // INT_MAX 사용
#include <algorithm> // fill 함수 사용 (배열에 사용할 경우 (arr, arr+N, value)로 채우면 됨)
using namespace std;

int N, M, S, E;
vector<pair<int, int>> bus[1001];
vector<bool> visit;
vector<int> money;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; //오름차순 우선순위 큐

int main()
{
	cin >> N >> M;
	for (int i = 0; i < M; i++) 
	{
		int s, e, m;
		cin >> s >> e >> m;
		bus[s].push_back({ e, m });
	}
	cin >> S >> E;

	visit.resize(N + 1); //벡터의 크기를 재조정
	money.resize(N + 1);
	fill(visit.begin(), visit.end(), false);
	fill(money.begin(), money.end(), INT_MAX); //memset은 0, 1, -1, true나 false를 채울 때만 유용한 듯 (특정값을 채우려니까 제대로 작동 안함)

	money[S] = 0;
	pq.push({ 0, S });

	while (!pq.empty())
	{
		int now_index = pq.top().second;
		int now_money = pq.top().first;
		pq.pop();

		if (visit[now_index]) continue;
		visit[now_index] = true;

		for (int i = 0; i < bus[now_index].size(); i++)
		{
			int next_index = bus[now_index][i].first;
			int next_money = bus[now_index][i].second;
			if (visit[next_index]) continue;

			if (money[next_index] > now_money + next_money)
			{
				money[next_index] = now_money + next_money;
				pq.push({ money[next_index], next_index });
			}
		}
	}

	cout << money[E];
	return 0;
}