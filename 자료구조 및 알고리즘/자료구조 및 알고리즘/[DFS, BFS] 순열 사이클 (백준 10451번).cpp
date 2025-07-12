// 순열 사이클 (https://www.acmicpc.net/problem/10451)

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int T;
int N;
vector<int> permu[1005];
int cnt = 0;
bool visit[1005]; //자동 false

void Count_permu()
{
	for (int num = 1; num <= N; num++)
	{
		if (visit[num]) continue;

		queue<int> q;
		q.push(num);

		while (!q.empty())
		{
			int now = q.front();
			visit[now] = true;
			q.pop();

			for (int i = 0; i < permu[now].size(); i++)
			{
				if (visit[permu[now][i]]) continue;
				else
				{
					q.push(permu[now][i]);
					visit[permu[now][i]] = true;
				}
			}
		}

		cnt++;
	}
}

int main()
{
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		cin >> N;
		for (int i = 1; i <= N; i++)
		{
			permu[i].clear(); //2차원일 경우 하나씩 초기화해줘야 함 (조심!)
		}

		for (int i = 1; i <= N; i++)
		{
			int temp;
			cin >> temp;
			permu[i].push_back(temp);
			permu[temp].push_back(i);
		}

		cnt = 0;
		memset(visit, false, sizeof(visit));
		Count_permu();
		cout << cnt << '\n';
	}
	return 0;
}