// 문제: https://www.acmicpc.net/problem/21610
#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

int dr[9] = {0, 0, -1, -1, -1, 0, 1, 1, 1};
int dc[9] = {0, -1, -1, 0, 1, 1, 1, 0, -1}; //1부터 8까지 명령

int N;
int A[51][51]; //물을 받는 바구니

int M;
vector<pair<int, int>> order; //방향, 순서

bool cloud_record[51][51]; //구름이 생성된 곳을 기록함
vector<pair<int, int>> cloud;

void Magic(int d, int s)
{
	vector<pair<int, int>> water;

	for (int i = 0; i < cloud.size(); i++) //비내림
	{
		int row = cloud[i].first;
		int col = cloud[i].second;

		int num = s;
		while (num--)
		{
			row = row + dr[d];
			col = col + dc[d];

			if (row == 0) row = N;
			if (row == N + 1) row = 1;
			if (col == 0) col = N;
			if (col == N + 1) col = 1;
		} //s만큼 이동

		A[row][col]++;
		cloud_record[row][col] = true; //구름이 이동한 곳 기록
		water.push_back({ row, col });
	}
	cloud.clear(); //구름이 모두 사라짐 (초기화)

	for (int i = 0; i < water.size(); i++) //물복사버그마법
	{
		int row = water[i].first;
		int col = water[i].second;

		int cnt = 0;
		for (int j = 2; j <= 8; j += 2)
		{
			int nr = row + dr[j];
			int nc = col + dc[j];

			if (nr <= 0 || nr > N || nc <= 0 || nc > N) continue;
			if (A[nr][nc] > 0) cnt++;
		}

		A[row][col] += cnt;
	}

	for (int i = 1; i <= N; i++) //구름 재생성
	{
		for (int j = 1; j <= N; j++)
		{
			if (cloud_record[i][j]) continue; //구름이 사라졌던 칸에는 생성되지 않음
			if (A[i][j] < 2) continue; //물의 양이 2보다 작으면 구름이 생기지 않음

			cloud.push_back({ i, j });
			A[i][j] -= 2;
		}
	}
	
	memset(cloud_record, false, sizeof(cloud_record)); //구름이 이동하기 전 (초기화)
}

int main()
{
	// 입력
	cin >> N >> M;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++) cin >> A[i][j];
	}
	order.resize(M);
	for (int i = 0; i < M; i++) cin >> order[i].first >> order[i].second;

	// 비바라기
	cloud.push_back({ N, 1 });
	cloud.push_back({ N, 2 });
	cloud.push_back({ N - 1, 1 });
	cloud.push_back({ N - 1, 2 }); //시작 구름

	for (int i = 0; i < M; i++)
	{
		int d = order[i].first;
		int s = order[i].second;

		Magic(d, s);
	}

	// 출력
	int cnt = 0;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++) cnt += A[i][j];
	}
	cout << cnt;
	return 0;
}