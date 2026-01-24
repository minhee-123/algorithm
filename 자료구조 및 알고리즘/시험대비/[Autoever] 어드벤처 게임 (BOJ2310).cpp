// 문제: https://www.acmicpc.net/problem/2310
// 알고리즘: 그래프
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int N;
pair<int, int> type[1001]; // 방의 종류(0(빈방), 1(레프리콘), 2(트롤)), 방의 비용
bool visit[1001];
vector<int> door[1001];

bool escape = false;
void DFS(int num, int money)
{
	if (num == N)
	{
		escape = true;
		return;
	}

	if (type[num].first == 1) // 레프리콘이 있는 방에 들어온 경우
	{
		if (money < type[num].second) money = type[num].second;
	}

	for (int i = 0; i < door[num].size(); i++)
	{
		int next = door[num][i];
		if (visit[next]) continue;

		if (type[next].first == 2) // 트롤이 있는 방으로 향하는 경우
		{
			if (money < type[next].second) continue;
			else
			{
				visit[next] = true;
				DFS(next, money - type[next].second);
				visit[next] = false;
			}
		}
		else // 그 외의 경우
		{
			visit[next] = true;
			DFS(next, money);
			visit[next] = false;
		}
	}
}

void Solution()
{
	memset(type, 0, sizeof(type));
	memset(visit, false, sizeof(visit));
	for (int i = 0; i <= N; i++) door[i].clear();

	for (int i = 1; i <= N; i++)
	{
		char Type; cin >> Type;
		int cost; cin >> cost;

		if (Type == 'L') type[i] = { 1, cost };
		else if (Type == 'T') type[i] = { 2, cost };
		else type[i] = { 0, cost };

		int connect; cin >> connect;
		while (connect != 0)
		{
			door[i].push_back(connect);
			cin >> connect;
		}
	}

	escape = false;
	visit[1] = true;
	DFS(1, 0);

	if (escape) cout << "Yes\n";
	else cout << "No\n";
}

int main()
{
	cin >> N;
	while (N != 0)
	{
		Solution();
		cin >> N;
	}
	return 0;
}