// 문제: https://www.acmicpc.net/problem/20057
#include <iostream>
#include <vector>
using namespace std;

int N, R, C; //격자 크기, 현재 행, 현재 열
vector<vector<int>> Map;

int dir = 0;
int dr[4] = {0, 1, 0, -1}; //서남동북
int dc[4] = {-1, 0, 1, 0};

float percent[10] = { 0.05, 0.1, 0.1, 0.02, 0.02, 0.07, 0.07, 0.01, 0.01, 1 }; //마지막은 알파 (남은 것을 전부 가져감)

// 이동방향에 따른 이동 위치 (y를 기준으로 함)
int pr[4][10] =
{
	{0, -1, 1, -2, 2, -1, 1, -1, 1, 0}, //서
	{2, 1, 1, 0, 0, 0, 0, -1, -1, 1},    //남
	{0, -1, 1, -2, 2, -1, 1, -1, 1, 0}, //동
	{-2, -1, -1, 0, 0, 0, 0, 1, 1, -1}   //북
};
int pc[4][10] =
{
	{-2, -1, -1, 0, 0, 0, 0, 1, 1, -1},  //서
	{0, -1, 1, -2, 2, -1, 1, -1, 1, 0}, //남
	{2, 1, 1, 0, 0, 0, 0, -1, -1, 1},    //동
	{0, -1, 1, -2, 2, -1, 1, -1, 1, 0}  //북
};

void Input()
{
	cin >> N;
	Map.resize(N);
	R = N / 2;
	C = N / 2;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			int temp;
			cin >> temp;
			Map[i].push_back(temp);
		}
	}
}

int result = 0;
int move_len = 1;
void Tornado()
{
	while (1)
	{
		for (int M = 0; M < 2; M++) //같은 길이로 두 방향씩 이동
		{
			for (int moving = 0; moving < move_len; moving++) //move_len만큼 한 방향으로 이동
			{
				R += dr[dir];
				C += dc[dir];

				int Sand = Map[R][C];
				int Sand_Leavings = Sand;
				for (int i = 0; i < 10; i++) //모래 이동
				{
					int NR = R + pr[dir][i];
					int NC = C + pc[dir][i];

					int Flow = Sand * percent[i];

					if (i == 9) Flow = Sand_Leavings;
					else Sand_Leavings -= Flow;

					if (NR < 0 || NR >= N || NC < 0 || NC >= N) result += Flow;
					else Map[NR][NC] += Flow;
				}

				if (R == 0 && C == 0) return;
			}

			dir++;
			if (dir == 4) dir = 0;
		}
		move_len++;
	}
}

int main()
{
	Input();
	Tornado();

	cout << result;
	return 0;
}

// (1)
// 문제에서 헷갈리는 부분이 있어서 그 부분을 이해하는데 시간이 걸림
// (2)
// 구현은 쉽게 했으나 같은 방향으로 move_len만큼 이동하는 것, 같은 move_len으로 두번 이동하는 것을 실수함
// (3)
// 비율과 해당 비율의 위치(row, col) 계산을 실수함 
// → 계산하기 번거로워서 다른사람 풀이의 이동값을 가져옴 (row, col 이동은 항상 꼼꼼하게 계산하자)