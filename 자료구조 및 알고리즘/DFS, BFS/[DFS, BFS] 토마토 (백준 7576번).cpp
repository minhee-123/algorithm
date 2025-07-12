//문제: https://www.acmicpc.net/problem/7576
#include <iostream>
#include <queue>
using namespace std;

int dr[4] = { 0, 0, 1, -1 };
int dc[4] = { 1, -1, 0, 0 };

int M, N;
int MAP[1000][1000];
bool visit[1000][1000];

int answer = 0;
queue<pair<int, int>> tomato;
queue<int> day;

int main()
{
	cin >> M >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			int val;
			cin >> val;

			MAP[i][j] = val;
			if (val == 1)
			{
				tomato.push({ i, j });
				day.push(0);
				visit[i][j] = true;
			}
			if (val == -1) visit[i][j] = true;
		}
	}

	while (!tomato.empty())
	{
		int TR = tomato.front().first;
		int TC = tomato.front().second;
		int now_day = day.front();
		
		tomato.pop();
		day.pop();

		for (int i = 0; i < 4; i++)
		{
			int nextR = TR + dr[i];
			int nextC = TC + dc[i];
			
			if (nextR < 0 || nextR >= N || nextC < 0 || nextC >= M) continue; //맵을 벗어나는 경우 제외
			if (visit[nextR][nextC]) continue; //익은 토마토 OR 토마토가 없는 경우 제외

			visit[nextR][nextC] = true;
			tomato.push({ nextR, nextC });
			day.push(now_day + 1);

			answer = now_day + 1;
		}
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (!visit[i][j])
			{
				cout << -1;
				return 0;
			}
		}
	}
	cout << answer;
	return 0;
}
// 오랜만에 풀어서 그런가 row랑 col 방향을 헷갈려서 좀 헤맸다
// row랑 col 잘 구분하기 (어디가 x고 어디가 y값인지 잘 생각해봐야 함)