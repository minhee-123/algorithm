// 단지번호붙이기 (https://www.acmicpc.net/problem/2667)

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
using namespace std;

int dr[4] = {0, 1, 0, -1}; //하 우 상 좌
int dc[4] = {1, 0, -1, 0};

vector<int> danzi;

int len;
int MAP[30][30] = { 0 };
bool visit[30][30];

int Find(int row, int col)
{
	if (visit[row][col]) return 0;
	if (MAP[row][col] == 0) return 0;

	int cnt = 1;

	queue<pair<int, int>> q;
	q.push({ row, col });
	visit[row][col] = true;

	while (!q.empty())
	{
		int now_r = q.front().first;
		int now_c = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int new_r = now_r + dr[i];
			int new_c = now_c + dc[i];

			if (new_r < 0 || new_r > len || new_c < 0 || new_c > len) continue;

			if (MAP[new_r][new_c] == 1 && !visit[new_r][new_c])
			{
				cnt++;
				q.push({ new_r, new_c });
				visit[new_r][new_c] = true;
			}
		}
	}

	return cnt;
}

int main()
{
	cin >> len;
	for (int i = 0; i < len; i++)
	{
		string st;
		cin >> st;
		for (int j = 0; j < len; j++)
		{
			MAP[i][j] = st[j] - '0';
		}
	}

	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len; j++)
		{
			int cnt = Find(i, j);

			if (cnt > 0) danzi.push_back(cnt);
		}
	}
	sort(danzi.begin(), danzi.end());

	cout << danzi.size() << '\n';
	if (danzi.size() > 0)
	{
		for (int i = 0; i < danzi.size(); i++)
		{
			cout << danzi[i] << '\n';
		}
	}
	//else cout << 0 << '\n';
	return 0;
}