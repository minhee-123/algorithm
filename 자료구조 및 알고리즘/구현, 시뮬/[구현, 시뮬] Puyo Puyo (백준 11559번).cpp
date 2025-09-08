// 문제: https://www.acmicpc.net/problem/11559

/* 정신 차리고 문제 풀자 등호 빼먹고 변수 실수하고 그럼 안된다 진짜 */

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

int color2int(char c)
{
	if (c == '.') return 0; //빈칸
	else if (c == 'R') return 1;
	else if (c == 'G') return 2;
	else if (c == 'B') return 3;
	else if (c == 'P') return 4;
	else if (c == 'Y') return 5;
	else return -1; //에러케이스
}

int Map[12][6]; //12개의 줄, 각 줄에는 6개의 문자

void Input()
{
	for (int i = 0; i < 12; i++)
	{
		string temp;
		cin >> temp;

		for (int j = 0; j < 6; j++)
		{
			char ch = temp[j];
			int num = color2int(ch);

			Map[i][j] = num;
		}
	}
}

bool visit[12][6];
int bomb_cnt = 0;

vector<vector<pair<int, int>>> bomb_group;
vector<pair<int, int>> temp_group;

int dr[4] = { 0, 0, 1, -1 };
int dc[4] = { 1, -1, 0, 0 };

void find_bomb(int R, int C, int value)
{
	visit[R][C] = true;
	temp_group.push_back({ R, C });

	for (int i = 0; i < 4; i++)
	{
		int NR = R + dr[i];
		int NC = C + dc[i];

		if (NR < 0 || NR >= 12 || NC < 0 || NC >= 6) continue;
		if (visit[NR][NC]) continue;

		if (Map[NR][NC] == value) find_bomb(NR, NC, value);
	}
}

void gravity()
{
	for (int col = 0; col < 6; col++)
	{
		for (int row = 11; row >= 0; row--)
		{
			if (Map[row][col] == 0) continue;

			int r = row;
			int value = Map[row][col];

			while (r < 11)
			{
				if (Map[r + 1][col] == 0)
				{
					Map[r][col] = 0;
					r++;
					Map[r][col] = value;
				}
				else break;
			}
		}
	}
}

void Solution()
{
	Input();

	while (1)
	{
		memset(visit, false, sizeof(visit));
		bomb_group.clear();

		for (int i = 0; i < 12; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				if (Map[i][j] == 0 || visit[i][j]) continue;

				temp_group.clear();
				find_bomb(i, j, Map[i][j]);

				if (temp_group.size() >= 4) bomb_group.push_back(temp_group);
			}
		}

		if (bomb_group.empty()) break;
		bomb_cnt++;

		for (int i = 0; i < bomb_group.size(); i++)
		{
			for (int j = 0; j < bomb_group[i].size(); j++)
			{
				Map[bomb_group[i][j].first][bomb_group[i][j].second] = 0;
			}
		}

		gravity();
	}
}

int main()
{
	Solution();

	cout << bomb_cnt;
	return 0;
}