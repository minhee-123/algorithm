// 문제: https://www.acmicpc.net/problem/21608
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int N, N2; //N2가 학생의 수
int MAP[21][21];

vector<int> Order;
vector<vector<int>> Like;

int dr[4] = { -1, 1, 0, 0 }; //상 하 좌 우
int dc[4] = { 0, 0, -1, 1 };

void Input()
{
	cin >> N;
	N2 = N * N;

	Like.resize(N2 + 1);
	for (int i = 0; i < N2; i++)
	{
		int index;
		cin >> index;
		Order.push_back(index);

		for (int j = 0; j < 4; j++)
		{
			int value;
			cin >> value;
			Like[index].push_back(value);
		}
	}
}

void Find(int index)
{
	int R = N;
	int C = N;
	int like_person = 0;
	int empty = 0;

	for (int row = 1; row <= N; row++)
	{
		for (int col = 1; col <= N; col++)
		{
			if (MAP[row][col] > 0) continue;

			int temp_like_person = 0;
			int temp_empty = 0;

			for (int k = 0; k < 4; k++) //자리 탐색
			{
				int nr = row + dr[k];
				int nc = col + dc[k];

				if (nr <= 0 || nr > N || nc <= 0 || nc > N) continue;

				if (MAP[nr][nc] < 1) temp_empty++;
				else
				{
					for (int j = 0; j < 4; j++)
					{
						if (MAP[nr][nc] == Like[index][j])
						{
							temp_like_person++;
						}
					}
				}
			}

			bool flag = false;

			//자리 비교
			if (temp_like_person > like_person) flag = true;
			else if (temp_like_person == like_person)
			{
				if (temp_empty > empty) flag = true;
				else if (temp_empty == empty)
				{
					if (row < R) flag = true;
					else if (row == R)
					{
						if (col < C) flag = col;
					}
				}
			}

			if (flag)
			{
				R = row;
				C = col;
				like_person = temp_like_person;
				empty = temp_empty;
			}
		}
	}

	MAP[R][C] = index;
}

void Seating()
{
	for (int i = 0; i < N2; i++)
	{
		int index = Order[i];
		Find(index);
	}
}

int answer = 0;

void Score()
{
	int plus[5] = { 0, 1, 10, 100, 1000 };

	for (int row = 1; row <= N; row++)
	{
		for (int col = 1; col <= N; col++)
		{
			int num = 0;

			for (int i = 0; i < 4; i++)
			{
				int nr = row + dr[i];
				int nc = col + dc[i];
				if (nr <= 0 || nr > N || nc <= 0 || nc > N) continue;
			
				int next_person = MAP[nr][nc];
				for (int j = 0; j < 4; j++)
				{
					if (next_person == Like[MAP[row][col]][j]) num++;
				}
			}

			answer += plus[num];
		}
	}
}

int main()
{
	Input();
	Seating();
	Score();

	cout << answer;
	return 0;
}