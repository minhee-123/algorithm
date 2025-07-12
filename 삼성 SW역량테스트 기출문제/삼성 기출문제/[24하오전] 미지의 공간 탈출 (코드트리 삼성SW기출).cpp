// 코드트리 삼성 SW 역량테스트 2024 하반기 오전 1번 문제
// https://www.codetree.ai/ko/frequent-problems/problems/escape-unknown-space/description

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

int dr[4] = {0, 0, 1, -1};
int dc[4] = {1, -1, 0, 0}; // 동(우) 서(좌) 남(하) 북(상)

int Time = 0;
int N, M, F; //공간의 길이, 정육각형 한변의 길이, 불의 개수

int MAP[20][20]; //전체 공간, 빈공간(0), 장애물(1), 불(2), 정육각형 위치(3), 탈출구(4)
int TOP[5][10][10]; //육각형, 첫번째 인덱스: 동(0), 서(1), 남(2), 북(3), 윗면(4)

struct FIRE
{
	int row;
	int col;
	int dir;
	int num; //확산 상수 (Time이 num의 배수일 때 확산진행)
};
vector<FIRE> fire;

int startR, startC;
int targetR, targetC;

int mapR, mapC;
int topR, topC, topSide;

void Input()
{
	cin >> N >> M >> F;
	fire.resize(F);

	int firstR, firstC;
	bool firstFlag = true;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> MAP[i][j];
			if (MAP[i][j] == 4)
			{
				targetR = i;
				targetC = j;
			}

			if (firstFlag && MAP[i][j] == 3)
			{
				firstR = i;
				firstC = j;
				firstFlag = false;
			}
		}
	} //맵 정보 (최종 출구 정보)

	for (int index = 0; index < 5; index++)
	{
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < M; j++)
			{
				cin >> TOP[index][i][j];
				if (TOP[index][i][j] == 2)
				{
					startR = i;
					startC = j;
				}
			}
		}
	} //정육각형 정보 (맨 윗면에서 출발 지점 정보)

	for (int i = 0; i < F; i++)
	{
		cin >> fire[i].row >> fire[i].col >> fire[i].dir >> fire[i].num;
		MAP[fire[i].row][fire[i].col] = 2;
	} //불 정보

	for (int i = firstR - 1; i <= firstR + M; i++)
	{
		for (int j = firstC - 1; j <= firstC + M; j++)
		{
			if (MAP[i][j] != 1 && MAP[i][j] != 3)
			{
				mapR = i;
				mapC = j;

				if (MAP[i][j - 1] == 3) topSide = 0;
				else if (MAP[i][j + 1] == 3) topSide = 1;
				else if (MAP[i - 1][j] == 3) topSide = 2;
				else if (MAP[i + 1][j] == 3) topSide = 3;

				topR = M;
				if (topSide == 0) topC = firstR + M - 1 - mapR;
				else if (topSide == 1) topC = mapR - firstR;
				else if (topSide == 2) topC = mapC - firstC;
				else if (topSide == 3) topC = firstC + M - 1 - mapC;
			}
		}
	} //정육각형 탈출 정보 (맵에서 좌표, 정육각형 어떤 면, 정육각형 어떤 위치)
}

void BFS_TOP()
{
	struct information_top
	{
		int row;
		int col;
		int side; //현재 어떤 면에 있는지
	};

	queue<information_top> que;
	que.push({ startR, startC, 4 });

	bool visit[5][10][10];
	memset(visit, false, sizeof(visit));
	visit[4][startR][startC] = true;

	int times[5][10][10];
	memset(times, 0, sizeof(times));
	times[4][startR][startC] = 0;

	while (!que.empty())
	{
		int nowR = que.front().row;
		int nowC = que.front().col;
		int nowSide = que.front().side;
		que.pop();

		for (int i = 0; i < 4; i++)
		{
			int nextR = nowR + dr[i];
			int nextC = nowC + dc[i];
			int nextSide = nowSide;

			if (nextSide == topSide && nextR == topR && nextC == topC) //now값이 육각형 입구 앞일 경우
			{
				Time = times[nowSide][nowR][nowC]; //육각형 입구에 도착한 시간 (맵으로 나가기 전)
				break;
			}

			if (nowSide == 4) //윗면
			{
				if (nextR < 0) //위로 이동
				{
					nextSide = 3; //북쪽으로
					nextR = 0;
					nextC = (M - 1) - nextC;
				}
				else if (nextR >= M) //아래로 이동
				{
					nextSide = 2; //남쪽으로
					nextR = 0;
					//nextC = nextC;
				}
				else if (nextC < 0) //왼쪽으로 이동
				{
					nextSide = 1; //서쪽으로
					nextC = nextR;
					nextR = 0;
				}
				else if (nextC >= M) //오른쪽으로 이동
				{
					nextSide = 0; //동쪽으로
					nextC = (M - 1) - nextR;
					nextR = 0;
				}
			}
			else if (nowSide == 0) //동
			{
				if (nextR < 0) //위로 이동
				{
					nextSide = 4; //윗면으로
					nextR = nextC;
					nextC = M - 1;
				}
				else if (nextR >= M) //아래로 이동
				{
					continue;
				}
				else if (nextC < 0) //왼쪽으로 이동
				{
					nextSide = 2; //남쪽으로
					//nextR = nextR;
					nextC = M - 1;
				}
				else if (nextC >= M) //오른쪽으로 이동
				{
					nextSide = 3; //북쪽으로
					//nextR = nextR;
					nextC = 0;
				}
			}
			else if (nowSide == 1) //서
			{
				if (nextR < 0) //위로 이동
				{
					nextSide = 4; //윗면으로
					nextR = nextC;
					nextC = 0;
				}
				else if (nextR >= M) //아래로 이동
				{
					continue;
				}
				else if (nextC < 0) //왼쪽으로 이동
				{
					nextSide = 3; //북쪽으로
					//nextR = nextR;
					nextC = M - 1;
				}
				else if (nextC >= M) //오른쪽으로 이동
				{
					nextSide = 2; //남쪽으로
					//nextR = nextR;
					nextC = 0;
				}
			}
			else if (nowSide == 2) //남
			{
				if (nextR < 0) //위로 이동
				{
					nextSide = 4; //윗면으로
					nextR = M - 1;
					//nextC = nextC;
				}
				else if (nextR >= M) //아래로 이동
				{
					continue;
				}
				else if (nextC < 0) //왼쪽으로 이동
				{
					nextSide = 1; //서쪽으로
					//nextR = nextR;
					nextC = M - 1;
				}
				else if (nextC >= M) //오른쪽으로 이동
				{
					nextSide = 0; //동쪽으로
					//nextR = nextR;
					nextC = 0;
				}
			}
			else if (nowSide == 3) //북
			{
				if (nextR < 0) //위로 이동
				{
					nextSide = 4; //윗면으로
					nextR = 0;
					nextC = (M - 1) - nextC;
				}
				else if (nextR >= M) //아래로 이동
				{
					continue;
				}
				else if (nextC < 0) //왼쪽으로 이동
				{
					nextSide = 0; //동쪽으로
					//nextR = nextR;
					nextC = M - 1;
				}
				else if (nextC >= M) //오른쪽으로 이동
				{
					nextSide = 1; //서쪽으로
					//nextR = nextR;
					nextC = 0;
				}
			}

			if (visit[nextSide][nextR][nextC]) continue;
			if (TOP[nextSide][nextR][nextC] == 1) continue;

			visit[nextSide][nextR][nextC] = true;
			times[nextSide][nextR][nextC] = times[nowSide][nowR][nowC] + 1;
			que.push({ nextR, nextC, nextSide });
		}
	}
} //육각형 입구에 도착한 시간 업데이트 (맵으로 나가기 직전의 시간)

void Update_Fire()
{
	Time++; //불이 번지고 → 사람 이동
	for (int turn = 1; turn <= Time; turn++)
	{
		for (int index = 0; index < fire.size(); index++)
		{
			if (turn % fire[index].num == 0)
			{
				int row = fire[index].row + dr[fire[index].dir];
				int col = fire[index].col + dc[fire[index].dir];

				if (row < 0 || row >= N || col < 0 || col >= N) continue; //범위를 벗어나는 경우
				if (MAP[row][col] == 0 || MAP[row][col] == 2) //동시에 독립적으로 확산 → 불이 겹칠 수 있는 점을 고려해야 할듯
				{
					MAP[row][col] = 2;
					fire[index].row = row;
					fire[index].col = col; //확산 업데이트 (계속해서 확산하기 위함)
				}
			}
		}
	}
} //육각형 입구에 도착하고, 그 직후까지의 불번짐

void Firing(int turn)
{
	for (int index = 0; index < fire.size(); index++)
	{
		if (turn % fire[index].num == 0)
		{
			int row = fire[index].row + dr[fire[index].dir];
			int col = fire[index].col + dc[fire[index].dir];

			if (row < 0 || row >= N || col < 0 || col >= N) continue; //범위를 벗어나는 경우
			if (MAP[row][col] == 0 || MAP[row][col] == 2) //동시에 독립적으로 확산 → 불이 겹칠 수 있는 점을 고려해야 할듯
			{
				MAP[row][col] = 2;
				fire[index].row = row;
				fire[index].col = col; //확산 업데이트 (계속해서 확산하기 위함)
			}
		}
	}
} //이후 시간때 불번짐

void BFS_MAP()
{
	int row = mapR;
	int col = mapC;

	if (row == targetR && col == targetC) return; //바로 출구가 있는 경우 종료
	if (MAP[row][col] == 2) //이미 불이 번진 경우
	{
		Time = -1;
		return;
	} //이미 불이 번진 경우

	queue<pair<int, int>> que;
	que.push({ row, col });

	bool visit[20][20];
	memset(visit, false, sizeof(visit));
	visit[row][col] = true;

	int Turn[20][20];
	memset(Turn, 0, sizeof(Turn));
	Turn[row][col] = Time;

	bool arrive = false;

	while (!que.empty())
	{
		int nowR = que.front().first;
		int nowC = que.front().second;
		que.pop();

		Firing(Turn[nowR][nowC] + 1); //불번짐이 먼저 발생

		for (int i = 0; i < 4; i++)
		{
			int nextR = nowR + dr[i];
			int nextC = nowC + dc[i];

			if (nextR < 0 || nextR >= N || nextC < 0 || nextC >= N) continue;
			if (visit[nextR][nextC]) continue;
			if (MAP[nextR][nextC] == 1 || MAP[nextR][nextC] == 2 || MAP[nextR][nextC] == 3) continue;

			visit[nextR][nextC] = true;
			Turn[nextR][nextC] = Turn[nowR][nowC] + 1;

			if (nextR == targetR && nextC == targetC)
			{
				arrive = true;
				break;
			}
			else que.push({ nextR, nextC });
		}

		if (arrive) break;
	}

	if (arrive) Time = Turn[targetR][targetC];
	else Time = -1;
}

void Solution()
{
	Input();
	BFS_TOP();
	Update_Fire();
	BFS_MAP();
	cout << Time;
}

int main()
{
	Solution();
	return 0;
}