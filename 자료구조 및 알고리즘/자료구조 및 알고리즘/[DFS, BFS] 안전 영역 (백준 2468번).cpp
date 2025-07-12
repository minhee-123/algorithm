// 안전 영역 (https://www.acmicpc.net/problem/2468)

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> //memset 사용
using namespace std;

int MAP[105][105] = { 0 };
bool visit[105][105];
int N;
vector<int> CNT;

int dr[4] = {-1, 0, 1, 0}; //상 우 하 좌
int dc[4] = {0, 1, 0, -1};

vector<int> check;
void Find(int row, int col)
{
	if (visit[row][col]) return;
	if (MAP[row][col] == 0) return;

	visit[row][col] = true;
	check.push_back(1);

	for (int i = 0; i < 4; i++)
	{
		int new_r = row + dr[i];
		int new_c = col + dc[i];

		if (new_r < 0 || new_r >= N || new_c < 0 || new_c >= N) continue;
		if (visit[new_r][new_c]) continue;
		if (MAP[new_r][new_c] <= 0) continue;

		Find(new_r, new_c);
	}
}

bool comp(int a, int b) { return a > b; }

int main()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> MAP[i][j];
		}
	}

	int rain = 0; //비가 정수가 아닐 수도 있음 (예시로 0.5)
	// 높이는 1이상 100 이하의 정수이므로 비가 0.5일 경우 모든 지역이 물에 잠기지 않음 (rain을 정수 0으로 시작해야 함)

	while (1)
	{
		int cnt = 0;
		memset(visit, false, sizeof(visit));

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (MAP[i][j] <= rain) MAP[i][j] = 0;
			}
		}

		for (int row = 0; row < N; row++)
		{
			for (int col = 0; col < N; col++)
			{
				check.clear();
				
				Find(row, col);
				if (check.size() > 0) cnt++;
			}
		}

		if (cnt == 0) break;
		else
		{
			CNT.push_back(cnt);
			rain++;
		}
	}

	sort(CNT.begin(), CNT.end(), comp);
	cout << CNT[0];
	return 0;
}