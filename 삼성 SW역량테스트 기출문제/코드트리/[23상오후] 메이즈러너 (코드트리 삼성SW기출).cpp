// 코드트리 삼성 SW 역량테스트 2023 상반기 오후 1번 문제
// https://www.codetree.ai/ko/frequent-problems/problems/maze-runner/description

// 90도 회전 공식 (암기해두자, 매우 중요함!!)
// → 따로 종이로 정리해둠 (암기해두자, 매우 중요함!!)

// 배열 복사 함수 → memmove (cstring 헤더에 있음)
// memmove(배열 A, 배열 B, 크기); (크기만큼 B를 A로 복사)

#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

int N, M, K; //미로 크기, 참가자 수, 게임 시간
int MAP[11][11]; //좌표는 (1,1)부터 시작

struct RUNNER
{
	int row;
	int col;
	bool outside = false; //탈출했는지 여부 (true: 탈출)
};
vector<RUNNER> runner;
int outside_cnt = 0;
int distance_cnt = 0;

int exit_row;
int exit_col;

int dr[4] = {-1, 1, 0, 0}; //상하우좌
int dc[4] = {0, 0, 1, -1};

void Input()
{
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++) cin >> MAP[i][j];
	} //맵에 정보 입력

	runner.resize(M + 1); //러너도 1번부터 관리
	for (int i = 1; i <= M; i++) cin >> runner[i].row >> runner[i].col;

	cin >> exit_row >> exit_col;
}

void Move_Runner()
{
	for (int run = 1; run <= M; run++)
	{
		if (runner[run].outside) continue; //러너가 이미 탈출함

		int row = runner[run].row;
		int col = runner[run].col;

		for (int dir = 0; dir < 4; dir++) //상하가 우선순위를 가짐
		{
			int next_row = row + dr[dir];
			int next_col = col + dc[dir];

			if (next_row <= 0 || next_row > N || next_col <= 0 || next_col > N) continue; //범위를 벗어나는 경우
			if (MAP[next_row][next_col] > 0) continue; //벽이 있는 경우
			if (abs(exit_row - row) + abs(exit_col - col) <= abs(exit_row - next_row) + abs(exit_col - next_col)) continue; //출구까지 거리가 가까워지지 않는 경우

			runner[run].row = next_row;
			runner[run].col = next_col;
			distance_cnt++;
			break;
		}

		if (runner[run].row == exit_row && runner[run].col == exit_col)
		{
			runner[run].outside = true;
			outside_cnt++;
		}
	}
}

int move_miro_row;
int move_miro_col;
int length;

void Find_Length()
{
	length = 1;
	int flag_length = false;
	while (length < N) // 무한루프 예방 (원래 N까지도 못감)
	{
		for (int row = exit_row - length; row <= exit_row; row++)
		{
			for (int col = exit_col - length; col <= exit_col; col++)
			{
				if (row <= 0 || row > N || col <= 0 || col > N) continue;
				if (row + length > N || col + length > N) continue; //범위를 넘어가는 경우

				for (int i = row; i <= row + length; i++)
				{
					for (int j = col; j <= col + length; j++)
					{
						for (int k = 1; k <= M; k++)
						{
							if (!runner[k].outside && runner[k].row == i && runner[k].col == j)
							{
								move_miro_row = row;
								move_miro_col = col;
								flag_length = true;
								break;
							}
							if (flag_length) break;
						}
						if (flag_length) break;
					}
					if (flag_length) break;
				}
				if (flag_length) break;
			}
			if (flag_length) break;
		}
		if (flag_length) break;
		else length++;
	}
}

void Move_Miro()
{
	Find_Length();
	int row = move_miro_row;
	int col = move_miro_col;
	int len = length;

	int copy[11][11];
	memset(copy, 0, sizeof(copy));

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++) copy[i][j] = MAP[i][j];
	}

	bool visit_runner[11];
	memset(visit_runner, false, sizeof(visit_runner));
	bool visit_exit = false;

	for (int i = row; i <= row + len; i++)
	{
		for (int j = col; j <= col + len; j++)
		{
			int orig_i = row + (col + len - j);
			int orig_j = col + (i - row);

			copy[i][j] = MAP[orig_i][orig_j]; 
			if (MAP[orig_i][orig_j] > 0) copy[i][j]--; //회전된 벽은 내구도 1씩 깎임

			for (int k = 1; k <= M; k++) //정사각형에 포함된 사람도 좌표 업데이트
			{
				if (!visit_runner[k] && !runner[k].outside && runner[k].row == orig_i && runner[k].col == orig_j)
				{
					runner[k].row = i;
					runner[k].col = j;
					visit_runner[k] = true;
				}
			}

			if (!visit_exit && exit_row == orig_i && exit_col == orig_j) //출구도 업데이트
			{
				exit_row = i;
				exit_col = j;
				visit_exit = true;
			}
		}
	}

	memmove(MAP, copy, sizeof(MAP)); //MAP 업데이트 완료
}

void Solution()
{
	Input();

	for (int i = 1; i <= K; i++)
	{
		Move_Runner();
		if (outside_cnt == M) break;
		Move_Miro();
	}

	cout << distance_cnt << '\n';
	cout << exit_row << " " << exit_col;
}

int main()
{
	Solution();
	return 0;
}

// 출구와 러너를 포함하는 최소 정사각형 선정에서 실수했음 → 정사각형의 종류와 우선순위를 잘못 구현함 (정사각형 크기 > row 작은 순 > col 작은 순)
// 90도 회전 공식을 몰라서 검색해서 적용했음
// 회전 공식은 종이로 따로 공부 && 문제 한 줄의 실수는 앞으로 꼭 조심할 것