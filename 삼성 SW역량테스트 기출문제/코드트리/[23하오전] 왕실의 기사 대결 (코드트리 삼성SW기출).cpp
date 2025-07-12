// 코드트리 삼성 SW 역량테스트 2023 하반기 오전 1번 문제
// https://www.codetree.ai/training-field/frequent-problems/problems/royal-knight-duel/description?page=2&pageSize=5

#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int dr[4] = {-1, 0, 1, 0}; //위쪽, 오른쪽, 아래쪽, 왼쪽
int dc[4] = {0, 1, 0, -1};

int MAP[44][44]; // 0 (빈칸) / 1 (함정) / 2 (벽)
int MAP_Night[44][44]; //기사들의 위치 정보
int L, N, Q; //체스판 크기, 초기 기사들의 정보 수, 명령 정보의 수

struct NIGHT
{
	int row; //맨 왼쪽 위의 좌표 (row)
	int col; //맨 오른쪽 위의 좌표 (col)
	int h; //세로 길이
	int w; //가로 길이
	int hp; //체력
	int hp_initial; //초기 체력
	bool survive = true; //생존여부
};

struct ORDER
{
	int num; //명령을 받은 기사 번호
	int dir; //이동 방향
};

vector<NIGHT> Night;
vector<ORDER> Order;

void Input()
{
	cin >> L >> N >> Q;
	for (int i = 1; i <= L; i++)
	{
		for (int j = 1; j <= L; j++) cin >> MAP[i][j];
	} //맵 정보

	Night.resize(N + 1);
	Order.resize(Q + 1);

	for (int i = 1; i <= N; i++)
	{
		cin >> Night[i].row >> Night[i].col >> Night[i].h >> Night[i].w >> Night[i].hp;
		Night[i].hp_initial = Night[i].hp;

		for (int j = Night[i].row; j < Night[i].row + Night[i].h; j++)
		{
			for (int k = Night[i].col; k < Night[i].col + Night[i].w; k++) MAP_Night[j][k] = i;
		}
	} //기사 정보

	for (int i = 1; i <= Q; i++)
	{
		cin >> Order[i].num >> Order[i].dir;
	} //명령 정보
}

bool visit[31];
bool flag = true; //이동을 못할 경우 false
vector<int> night_move; //이동하는 기사 기록

void Move_flag(int num, int dir) //이동이 가능한지 check
{
	night_move.push_back(num);

	if (dir == 0 || dir == 2) //위쪽 아래쪽
	{
		int row;
		if (dir == 0) row = Night[num].row;
		if (dir == 2) row = Night[num].row + Night[num].h - 1;

		for (int col = Night[num].col; col < Night[num].col + Night[num].w; col++)
		{
			int nextR = row + dr[dir];
			int nextC = col + dc[dir];

			if (nextR <= 0 || nextR > L || nextC <= 0 || nextC > L)
			{
				flag = false;
				return;
			}
			if (MAP[nextR][nextC] == 2)
			{
				flag = false;
				return;
			}

			if (MAP_Night[nextR][nextC] != 0)
			{
				int next = MAP_Night[nextR][nextC];
				if (visit[next]) continue;

				visit[next] = true;
				Move_flag(next, dir);
			}
		}
	}
	else if (dir == 1 || dir == 3) //오른쪽 왼쪽
	{
		int col;
		if (dir == 1) col = Night[num].col + Night[num].w - 1;
		if (dir == 3) col = Night[num].col;

		for (int row = Night[num].row; row < Night[num].row + Night[num].h; row++)
		{
			int nextR = row + dr[dir];
			int nextC = col + dc[dir];

			if (nextR <= 0 || nextR > L || nextC <= 0 || nextC > L)
			{
				flag = false;
				return;
			}
			if (MAP[nextR][nextC] == 2)
			{
				flag = false;
				return;
			}

			if (MAP_Night[nextR][nextC] != 0)
			{
				int next = MAP_Night[nextR][nextC];
				if (visit[next]) continue;

				visit[next] = true;
				Move_flag(next, dir);
			}
		}
	}
}

void Move(int num, int dir) //이동 수행
{
	flag = true;
	night_move.clear();
	memset(visit, false, sizeof(visit));
	Move_flag(num, dir);

	if (flag) //이동이 가능할 경우
	{
		int move_index = night_move.size() - 1;
		int attacker = num;

		while (move_index >= 0)
		{
			int num = night_move[move_index];

			if (dir == 0) Night[num].row = Night[num].row - 1; //위로 이동
			if (dir == 2) Night[num].row = Night[num].row + 1; //아래로 이동
			if (dir == 1) Night[num].col = Night[num].col + 1; //오른쪽으로 이동
			if (dir == 3) Night[num].col = Night[num].col - 1; //왼쪽으로 이동

			if (num != attacker) //밀려난 기사
			{
				for (int j = Night[num].row; j < Night[num].row + Night[num].h; j++)
				{
					for (int k = Night[num].col; k < Night[num].col + Night[num].w; k++)
					{
						if (MAP[j][k] == 1) Night[num].hp--;
					}
				}
			} //체력 감소를 check

			move_index--;
		}
	}
}

void Solution(int num, int dir)
{
	Move(num, dir);

	memset(MAP_Night, 0, sizeof(MAP_Night)); //위치 초기화
	for (int i = 1; i <= N; i++)
	{
		if (Night[i].hp <= 0) Night[i].survive = false;
		if (Night[i].survive)
		{
			for (int j = Night[i].row; j < Night[i].row + Night[i].h; j++)
			{
				for (int k = Night[i].col; k < Night[i].col + Night[i].w; k++) MAP_Night[j][k] = i;
			}
		} //살아있으면 MAP_Night 업데이트
	}
}

int answer = 0;
void Solve()
{
	Input();
	
	for (int i = 1; i <= Q; i++)
	{
		int num = Order[i].num;
		int dir = Order[i].dir;

		if (Night[num].survive) Solution(num, dir); //살아있는 기사의 명령일 경우에만 실행
	} //명령을 모두 시행

	for (int i = 1; i <= N; i++)
	{
		if (Night[i].survive) answer += Night[i].hp_initial - Night[i].hp;
	} //정답 도출
}

int main()
{
	Solve();
	cout << answer;
	return 0;
}

// 재귀(DFS) + 시뮬레이션으로 풀었음
// 이동이 가능한지 여부랑 실제 이동이랑 분리했음 → 양쪽 로직 다 조금 헤매서 오래 걸림