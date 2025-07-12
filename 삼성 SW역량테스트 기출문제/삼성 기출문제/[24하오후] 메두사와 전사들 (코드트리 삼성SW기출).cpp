// 코드트리 삼성 SW 역량테스트 2024 하반기 오후 1번 문제
// https://www.codetree.ai/ko/frequent-problems/problems/medusa-and-warriors/description

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

// 매 턴마다 출력
int answer_distance = 0; // 해당 턴에서 전사의 이동거리 총합 
int answer_stone = 0; // 메두사로 인해 돌이 된 전사의 수
int answer_attacker = 0; // 메두사를 공격한 전사의 수

int dr[4] = {-1, 1, 0, 0}; //상 하 좌 우 (우선순위)
int dc[4] = {0, 0, -1, 1};

int dr2[4] = {0, 0, -1, 1};
int dc2[4] = {-1, 1, 0, 0}; //좌 우 상 하 (전사의 두번째 이동 우선순위)

int N, M; //마을의 크기, 전사의 수
int Map[50][50]; // 도로는 0, 도로가 아닌 곳은 1 (메두사는 도로만 이동, 전사는 상관없음)

int home_row, home_col; //메두사 출발 지점
int park_row, park_col; //메두사 도착 지점
int snake_row, snake_col; //메두사의 현재 위치

struct WARRIOR
{
	int index; //전사 번호
	int row;
	int col;
	bool stone = false; //돌이 되었는지 여부
	bool survive = true; //살아있는지 여부
};
vector<WARRIOR> warrior;
vector<int> Map_warrior[50][50]; //전사의 맵 (전사의 위치에 전사의 index를 저장함)

void Input() //입력
{
	cin >> N >> M;
	cin >> home_row >> home_col >> park_row >> park_col;

	warrior.resize(M);
	for (int i = 0; i < M; i++)
	{
		cin >> warrior[i].row >> warrior[i].col;
		warrior[i].index = i;
		Map_warrior[warrior[i].row][warrior[i].col].push_back(i);
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++) cin >> Map[i][j];
	}

	snake_row = home_row;
	snake_col = home_col;
}

int turn = 0;
vector<int> snake_move_dir;

bool Can_move_snake() //공원까지 가는 최단경로가 있는가
{
	queue<pair<int, int>> que;
	que.push({ snake_row, snake_col });

	bool visit[50][50];
	memset(visit, false, sizeof(visit));
	visit[snake_row][snake_col] = true;

	int flag = false;
	vector<int> temp_dir[50][50]; // 이동하는 방향 저장

	while (!que.empty())
	{
		int now_row = que.front().first;
		int now_col = que.front().second;
		que.pop();

		for (int i = 0; i < 4; i++)
		{
			int next_row = now_row + dr[i];
			int next_col = now_col + dc[i];

			if (next_row < 0 || next_row >= N || next_col < 0 || next_col >= N) continue;
			if (visit[next_row][next_col]) continue;
			if (Map[next_row][next_col] == 1) continue; //도로가 없는 경우

			visit[next_row][next_col] = true;
			for (int k = 0; k < temp_dir[now_row][now_col].size(); k++) temp_dir[next_row][next_col].push_back(temp_dir[now_row][now_col][k]); //now_row까지 진행한 방향 복사
			temp_dir[next_row][next_col].push_back(i); //현재 방향 추가

			if (next_row == park_row && next_col == park_col)
			{
				flag = true; //공원에 도달하는 경로가 있음
				break;
			}
			else que.push({ next_row, next_col });
		}

		if (flag) break;
	}

	if (flag)
	{
		snake_move_dir = temp_dir[park_row][park_col];
		return true;
	}
	else return false;
}

void Move_Snake() //메두사의 이동
{
	snake_row += dr[snake_move_dir[turn]];
	snake_col += dc[snake_move_dir[turn]]; //구해둔 최단경로로 이동

	if (!Map_warrior[snake_row][snake_col].empty()) //전사가 있는 경우
	{
		for (int i = 0; i < Map_warrior[snake_row][snake_col].size(); i++)
		{
			int index = Map_warrior[snake_row][snake_col][i];
			warrior[index].survive = false; //메두사에게 잡히면 사망
		}
		Map_warrior[snake_row][snake_col].clear(); //맵에서도 삭제
	}
}

int Map_see_snake[50][50]; // 메두사의 시야 (0은 관계없음, 1은 메두사의 시야, 2는 전사에 의해 보호되는 영역)
vector<int> stone_warrior; //돌로 변한 전사의 index

int Make_Stone_Straight(int row, int col, int dir)
{
	int cnt = 0;
	int move_num = 1; //이동 가중치
	while (1)
	{
		int next_row = row + dr[dir] * move_num;
		int next_col = col + dc[dir] * move_num;

		if (next_row < 0 || next_row >= N || next_col < 0 || next_col >= N) break;

		Map_see_snake[next_row][next_col] = 1;

		if (!Map_warrior[next_row][next_col].empty())
		{
			for (int i = 0; i < Map_warrior[next_row][next_col].size(); i++)
			{
				int index = Map_warrior[next_row][next_col][i];
				stone_warrior.push_back(index);
				cnt++;
			}
			break;
		}

		move_num++;
	}
	return cnt;
}

int Calculate_Diagonal(int row, int col, int dir, int nDir)
{
	int cnt = 0;
	int move_num = 1; //방향 이동 가중치
	while (1)
	{
		int next_row = row + (dr[dir] + dr[nDir]) * move_num;
		int next_col = col + (dc[dir] + dc[nDir]) * move_num;

		if (next_row < 0 || next_row >= N || next_col < 0 || next_col >= N) break;
		if (Map_see_snake[next_row][next_col] == 2) break; //전사에 의해 보호되는 영역

		Map_see_snake[next_row][next_col] = 1;

		if (!Map_warrior[next_row][next_col].empty())
		{
			for (int i = 0; i < Map_warrior[next_row][next_col].size(); i++)
			{
				int index = Map_warrior[next_row][next_col][i];
				stone_warrior.push_back(index);
				cnt++;
			}
			break; //이후 영역이 모두 보호됨
		}

		int nr = next_row;
		int nc = next_col;

		while (1) //(next_row, next_col)을 기준으로 직진 탐색
		{
			nr += dr[dir];
			nc += dc[dir];

			if (nr < 0 || nr >= N || nc < 0 || nc >= N) break;
			if (Map_see_snake[nr][nc] == 2) break; //전사에 의해 보호되는 영역

			Map_see_snake[nr][nc] = 1;

			if (!Map_warrior[nr][nc].empty())
			{
				for (int i = 0; i < Map_warrior[nr][nc].size(); i++)
				{
					int index = Map_warrior[nr][nc][i];
					stone_warrior.push_back(index);
					cnt++;
				}
				
				while (1)
				{
					nr += (dr[dir] + dr[nDir]);
					nc += (dc[dir] + dc[nDir]);
					
					if (nr < 0 || nr >= N || nc < 0 || nc >= N) break;
					Map_see_snake[nr][nc] = 2; //전사에 의해 영역이 보호됨 (탐색 불가)
				}

				break;
			}
		}

		move_num++;
	}

	return cnt;
}

int Make_Stone_Diagonal(int row, int col, int dir)
{
	//대각선의 경우 메두사의 좌표에서 해당되는 방향의 좌표를 더한 후 양 옆의 방향을 더한 좌표를 탐색함
	int nDir1, nDir2; //양 옆의 방향
	if (dir < 2) //상하
	{
		nDir1 = 2;
		nDir2 = 3; //상하의 양 옆은 좌우
	}
	else //좌우
	{
		nDir1 = 0;
		nDir2 = 1; //좌우의 양 옆은 상하
	}

	return Calculate_Diagonal(row, col, dir, nDir1) + Calculate_Diagonal(row, col, dir, nDir2);
}

int Make_Stone(int dir)
{
	memset(Map_see_snake, 0, sizeof(Map_see_snake));
	stone_warrior.clear();

	int row = snake_row;
	int col = snake_col;

	int cnt = 0;
	cnt += Make_Stone_Straight(row, col, dir);
	cnt += Make_Stone_Diagonal(row, col, dir);

	return cnt;
}

void See_Snake() //메두사의 시선
{
	int max_dir = 0;
	int max_cnt = 0;
	for (int i = 0; i < 4; i++)
	{
		int stone_cnt = Make_Stone(i);
		
		if (max_cnt < stone_cnt)
		{
			max_dir = i;
			max_cnt = stone_cnt;
		}
	}

	answer_stone = Make_Stone(max_dir); //돌로 변한 전사의 수(출력) 저장
	for (int i = 0; i < stone_warrior.size(); i++) warrior[stone_warrior[i]].stone = true; //돌로 변함
}

void Move_warrior() //전사들의 이동
{
	for (int i = 0; i < M; i++)
	{
		if (!warrior[i].survive) continue; //죽었으면 패스
		if (warrior[i].stone) continue; //돌이 된 상태면 패스

		int row = warrior[i].row;
		int col = warrior[i].col;

		int target_row = snake_row;
		int target_col = snake_col;

		int T = 1;
		while (T <= 2) //두 번 이동할 수 있음
		{
			if (!warrior[i].survive) break;
			for (int j = 0; j < 4; j++)
			{
				int next_row, next_col;
				if (T == 1)
				{
					next_row = row + dr[j];
					next_col = col + dc[j];
				}
				else if (T == 2)
				{
					next_row = row + dr2[j];
					next_col = col + dc2[j];
				} //두번째 이동의 경우에만 좌우상하 우선순위를 가짐

				if (next_row < 0 || next_row >= N || next_col < 0 || next_col >= N) continue; //범위를 벗어나면 패스
				if (Map_see_snake[next_row][next_col] == 1) continue; //메두사의 시야에 드는 곳은 패스
				if (abs(target_row - row) + abs(target_col - col) <= abs(target_row - next_row) + abs(target_col - next_col)) continue; //거리가 늘어나면 패스

				row = next_row;
				col = next_col;
				answer_distance++; //거리 이동

				if (row == target_row && col == target_col) //메두사를 공격했을 경우
				{
					answer_attacker++;
					warrior[i].survive = false; //공격하고 사망
				}

				break;
			}
			T++;
			warrior[i].row = row;
			warrior[i].col = col;
		}
	}
}

void Update_warrior()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++) Map_warrior[i][j].clear(); //전사 맵 초기화
	}

	for (int i = 0; i < M; i++)
	{
		if (!warrior[i].survive) continue; //죽었으면 패스

		warrior[i].stone = false; //돌 상태 해제
		Map_warrior[warrior[i].row][warrior[i].col].push_back(warrior[i].index); //전사 맵 업데이트
	}

	answer_distance = 0;
	answer_stone = 0;
	answer_attacker = 0; //출력 초기화
}

void Solution()
{
	Input();
	if (!Can_move_snake())
	{
		cout << -1 << '\n';
		return;
	} //공원으로 향하는 경로가 없을 경우 종료

	while (turn < snake_move_dir.size())
	{
		Move_Snake();
		if (snake_row == park_row && snake_col == park_col)
		{
			cout << 0 << '\n';
			break;
		} //공원에 도착한 경우 종료

		See_Snake();
		Move_warrior();
		cout << answer_distance << " " << answer_stone << " " << answer_attacker << '\n';
		
		Update_warrior(); //전사 정보 업데이트 및 출력값 초기화
		turn++;
	}
}

int main()
{
	Solution();
	return 0;
}

// 풀면서 들었던 생각인데 (이미 상당 부분 구현해서 고치기 애매했지만)
// 구조체를 만들어서 MAP 자체를 구조체로 선언해도 좋을 것 같음 (변수 사용이 깔끔해질 것 같음)

// 구현을 잘 못했던 부분 → 메두사의 시선 함수 (블로그를 참고했음, 다시 살펴볼 때 주의)
// 실수했던 부분
// → 전사를 이동시키고 전사의 이동 정보를 업데이트하지 않았음 (집중!)
// → 전사의 두번째 이동의 우선순위만 좌우상하 (문제를 꼼꼼하게!)