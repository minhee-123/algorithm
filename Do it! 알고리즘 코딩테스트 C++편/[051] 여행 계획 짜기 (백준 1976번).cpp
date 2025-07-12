// 문제: https://www.acmicpc.net/problem/1976

#include <iostream>
using namespace std;

int N, M;
int city[201];
bool visit[201][201];
int trip[1001];

int Find(int c)
{
	if (city[c] == c) return c;
	else return city[c] = Find(city[c]);
}

void Union(int a, int b)
{
	a = Find(a);
	b = Find(b);

	if (a == b) return;
	else
	{
		if (a > b) swap(a, b);
		city[b] = a;
	}
}

int main()
{
	cin >> N >> M;
	
	for (int i = 1; i <= N; i++) city[i] = i;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			int cmd;
			cin >> cmd;

			if (visit[i][j] || cmd == 0) continue;
			if (cmd == 1)
			{
				Union(i, j);
				visit[i][j] = true; //중복연산 방지
				visit[j][i] = true;
			}
		}
	}

	bool connect = true;
	for (int i = 0; i < M; i++) cin >> trip[i];
	for (int i = 1; i < M; i++)
	{
		int a = Find(trip[i-1]);
		int b = Find(trip[i]);

		if (a != b)
		{
			connect = false;
			break;
		}
	}

	if (connect) cout << "YES" << '\n';
	else cout << "NO" << '\n';
	return 0;
}