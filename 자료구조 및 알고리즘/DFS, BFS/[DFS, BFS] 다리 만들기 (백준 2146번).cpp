// 문제: https://www.acmicpc.net/problem/2146
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int N;
int Map[100][100];
bool visit[100][100];
vector<vector<pair<int, int>>> island;

int dr[4] = { 0, 0, 1, -1 };
int dc[4] = { 1, -1, 0, 0 };

vector<pair<int, int>> temp;
void DFS(int R, int C, int num)
{
	if (visit[R][C]) return;

	visit[R][C] = true;
	Map[R][C] = num;
	temp.push_back({ R, C });

	for (int i = 0; i < 4; i++)
	{
		int NR = R + dr[i];
		int NC = C + dc[i];

		if (NR < 0 || NR >= N || NC < 0 || NC >= N) continue;
		if (Map[NR][NC] == 0) continue;
		if (visit[NR][NC]) continue;

		DFS(NR, NC, num);
	}
}

void Input()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++) cin >> Map[i][j];
	}

	int num = 1;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			temp.clear();
			
			if (Map[i][j] == 0) continue;
			DFS(i, j, num);

			if (temp.size() > 0) // 무언가 담겨있다면
			{
				island.push_back(temp);
				num++;
			}
		}
	}
}

struct inform
{
	int R;
	int C;
	int cnt;
};
int answer = 200; // answer은 무조건 100 이하

void Solution()
{
	for (int i = 0; i < island.size(); i++)
	{
		for (int k = 0; k < island[i].size(); k++)
		{
			int nowR = island[i][k].first;
			int nowC = island[i][k].second;
			int index = Map[nowR][nowC]; // 섬 번호

			memset(visit, false, sizeof(visit));
			queue<inform> que;
			que.push({ nowR, nowC, 0 });
			visit[nowR][nowC] = true;

			while (!que.empty())
			{
				int R = que.front().R;
				int C = que.front().C;
				int cnt = que.front().cnt;
				que.pop();

				if (cnt > answer) break; // 최소값 이상 수행할 경우
				if (Map[R][C] != 0 && Map[R][C] != index)
				{
					answer = cnt - 1; // 다음 섬을 count한 것은 제외
					break;
				}

				for (int i = 0; i < 4; i++)
				{
					int NR = R + dr[i];
					int NC = C + dc[i];
					
					if (NR < 0 || NR >= N || NC < 0 || NC >= N) continue;
					if (Map[NR][NC] == index) continue; // 섬의 내부 이동을 막음
					if (visit[NR][NC]) continue;

					visit[NR][NC] = true;
					que.push({ NR, NC, cnt + 1 });
				}
			}
		}
	}
}

int main()
{
	Input();
	Solution();

	cout << answer;
	return 0;
}