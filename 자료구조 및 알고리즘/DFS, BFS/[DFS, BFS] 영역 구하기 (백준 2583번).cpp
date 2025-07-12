// 영역 구하기 (https://www.acmicpc.net/problem/2583)

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int M, N, K;
int MAP[100][100];
bool visit[100][100];

int dr[4] = { 0, 1, 0, -1 }; //상, 우, 하, 좌
int dc[4] = { 1, 0, -1, 0 };

int cnt = 0;
vector<int> dimension;

int main()
{
	cin >> M >> N >> K;
	for (int i = 0; i < K; i++)
	{
		int ld_r, ld_c, ru_r, ru_c;
		cin >> ld_r >> ld_c >> ru_r >> ru_c;

		for (int row = ld_r; row <= ru_r-1; row++)
		{
			for (int col = ld_c; col <= ru_c-1; col++)
			{
				MAP[row][col]++;
			}
		}
	}

	for (int row = 0; row < N; row++)
	{
		for (int col = 0; col < M; col++)
		{
			if (MAP[row][col] > 0) continue;
			if (visit[row][col]) continue;

			queue<pair<int, int>> q;
			q.push({ row, col });
			visit[row][col] = true;

			int Count = 1;
			while (!q.empty())
			{
				int now_r = q.front().first;
				int now_c = q.front().second;
				q.pop();

				for (int i = 0; i < 4; i++)
				{
					int new_r = now_r + dr[i];
					int new_c = now_c + dc[i];

					if (new_r < 0 || new_r >= N || new_c < 0 || new_c >= M) continue;
					if (MAP[new_r][new_c] > 0) continue;
					if (visit[new_r][new_c]) continue;

					q.push({ new_r, new_c });
					visit[new_r][new_c] = true;
					Count++;
				}
			}

			dimension.push_back(Count);
			cnt++;
		}
	}
	sort(dimension.begin(), dimension.end());

	cout << cnt << '\n';
	for (int i = 0; i < dimension.size(); i++)
	{
		cout << dimension[i] << " ";
	}
	return 0;
}