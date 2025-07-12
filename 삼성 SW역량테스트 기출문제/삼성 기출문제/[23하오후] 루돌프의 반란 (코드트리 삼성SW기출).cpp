// 코드트리 삼성 SW 역량테스트 2023 하반기 오후 1번 문제
// https://www.codetree.ai/training-field/frequent-problems/problems/rudolph-rebellion/description?page=2&pageSize=5

// 구현도 오래 걸렸고 반례를 고치는 것도 오래 걸렸다! (문제에서 조건이 상당히 까다로웠다!)
// (1) 변수를 잘못 작성하는 실수를 꼭 주의하자 ★ 다른 기출에서도 동일한 실수를 했다 (이번에는 A를 B로 가져와서 찾는데 오래 걸림)
// (2) 문제의 조건을 잘 파악하자 ★ 빡구현 문제인만큼 조건이 까다롭다 (이번에는 기절이 반복되는 경우 계속해서 기절 시간이 초기화되는 것을 깜빡했음)


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//최상단 (1,1) 아래로 갈수록 r증가, 오른쪽으로 갈수록 c증가
//위, 오른쪽 대각선 위, 오른쪽, 오른쪽 대각선 아래, 아래, 왼쪽 대각선 아래, 왼쪽, 왼쪽 대각선 위
int dr[8] = { -1, -1, 0, 1, 1, 1, 0, -1 }; //위 오른쪽 아래 왼쪽 (0 2 4 6)
int dc[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };

int N, M, P, C, D; //게임판 크기, 턴 수, 산타의 수, 루돌프의 힘, 산타의 힘

pair<int, int> RU;
struct Santa
{
	int idx;
	int row;
	int col;
	int state; //0(일반 상태), 1(기절), 2(탈락)
	int state1_time;
	int score; //점수
};
vector<Santa> SA;


/////////////// 입력, 충돌, 상호작용
bool Input_comp(Santa A, Santa B) { return A.idx < B.idx; }

void Input()
{
	cin >> N >> M >> P >> C >> D;
	cin >> RU.first >> RU.second;

	for (int i = 0; i < P; i++)
	{
		int idx, row, col;
		cin >> idx >> row >> col;
		SA.push_back({ idx - 1, row, col, 0, 0, 0 });
	}
	sort(SA.begin(), SA.end(), Input_comp); //산타의 숫자는 0부터 시작
}

int Distance(int r1, int c1, int r2, int c2) { return (r1 - r2) * (r1 - r2) + (c1 - c2) * (c1 - c2); }

bool Fail(Santa A)
{
	if (A.row >= 1 && A.row <= N && A.col >= 1 && A.col <= N) return false;
	else return true;
}

void Interaction(int dir, int idx) //상호작용
{
	for (int i = 0; i < P; i++)
	{
		if (idx == i) continue;
		if (SA[idx].state == 2) continue;

		if (SA[idx].row == SA[i].row && SA[idx].col == SA[i].col)
		{
			SA[i].row += dr[dir];
			SA[i].col += dc[dir];

			if (Fail(SA[i])) //탈락
			{
				SA[i].state = 2;
				SA[i].row = -1;
				SA[i].col = -1;
				break;
			}
			else Interaction(dir, i);
		}
	}
	return;
}

void Crash(int dir, int idx, int type)
{
	if (type == 0) //루돌프가 산타를 잡은 경우
	{
		SA[idx].score += C;
		SA[idx].row += dr[dir] * C;
		SA[idx].col += dc[dir] * C;

		if (Fail(SA[idx])) //탈락
		{
			SA[idx].state = 2;
			SA[idx].row = -1;
			SA[idx].col = -1;
		}
		else
		{
			SA[idx].state = 1; //기절
			SA[idx].state1_time = 0; //또 기절하면 기절 시간이 초기화됨
			Interaction(dir, idx);
		}
	}
	else if (type == 1) //산타가 루돌프를 잡은 경우
	{
		SA[idx].score += D;
		SA[idx].row += dr[dir] * D;
		SA[idx].col += dc[dir] * D;

		if (Fail(SA[idx])) //탈락
		{
			SA[idx].state = 2;
			SA[idx].row = -1;
			SA[idx].col = -1;
		}
		else
		{
			SA[idx].state = 1; //기절
			SA[idx].state1_time = 0;
			if (D > 1) Interaction(dir, idx);
		}
	}
}


/////////////// (1) 루돌프 움직임
struct RU_distance
{
	int idx;
	int row;
	int col;
	int distance;
};

bool Comp_RU(RU_distance A, RU_distance B)
{
	if (A.distance != B.distance) return A.distance < B.distance;
	else if (A.row != B.row) return A.row > B.row;
	else if (A.col != B.col) return A.col > B.col;
	else return false;
}

int RU_dir(int r_d, int c_d)
{
	if (r_d > 0 && c_d == 0) return 0;
	else if (r_d > 0 && c_d < 0) return 1;
	else if (r_d == 0 && c_d < 0) return 2;
	else if (r_d < 0 && c_d < 0) return 3;
	else if (r_d < 0 && c_d == 0) return 4;
	else if (r_d < 0 && c_d > 0) return 5;
	else if (r_d == 0 && c_d > 0) return 6;
	else if (r_d > 0 && c_d > 0) return 7;
}

void RU_move()
{
	vector<RU_distance> RU_D;

	for (int i = 0; i < P; i++)
	{
		if (SA[i].state == 2) continue;

		int D = Distance(SA[i].row, SA[i].col, RU.first, RU.second);
		RU_D.push_back({ i, SA[i].row, SA[i].col, D });
	}
	sort(RU_D.begin(), RU_D.end(), Comp_RU);

	Santa RU_near = SA[RU_D[0].idx];
	int dir = RU_dir(RU.first - RU_near.row, RU.second - RU_near.col);

	RU.first += dr[dir];
	RU.second += dc[dir];

	//충돌발생
	if (RU.first == RU_near.row && RU.second == RU_near.col)
	{
		int idx = RU_near.idx;
		Crash(dir, idx, 0);
	}
}


/////////////// (2) 산타의 움직임
bool SA_comp1(pair<int, int> A, pair<int, int> B)
{
	if (A.first != B.first) return A.first < B.first;
	else if (A.second != B.second) return A.second < B.second;
	else return false;
}

vector<int> SA_dir(int ru_r, int ru_c, int sa_r, int sa_c)
{
	int comp_distance = (ru_r - sa_r) * (ru_r - sa_r) + (ru_c - sa_c) * (ru_c - sa_c);

	vector<pair<int, int>> distance;
	for (int i = 0; i <= 6; i = i + 2)
	{
		int sa_r_new = sa_r + dr[i];
		int sa_c_new = sa_c + dc[i];
		int distance_new = (ru_r - sa_r_new) * (ru_r - sa_r_new) + (ru_c - sa_c_new) * (ru_c - sa_c_new);

		if (distance_new < comp_distance)
		{
			distance.push_back({ distance_new, i });
		}
	}
	sort(distance.begin(), distance.end(), SA_comp1);

	vector<int> answer;
	for (int i = 0; i < distance.size(); i++)
	{
		answer.push_back(distance[i].second);
	}
	return answer;
}

void SA_move()
{
	for (int i = 0; i < P; i++)
	{
		if (SA[i].state > 0) continue; //기절했거나 탈락한 산타는 움직일 수 없음

		vector<int> dir_total = SA_dir(RU.first, RU.second, SA[i].row, SA[i].col);

		for (int k = 0; k < dir_total.size(); k++)
		{
			int new_r = SA[i].row + dr[dir_total[k]];
			int new_c = SA[i].col + dc[dir_total[k]];

			if (new_r < 1 || new_r > N || new_c < 1 || new_c > N) continue;
			bool flag = false;
			for (int j = 0; j < P; j++)
			{
				if (j == i) continue;
				if (new_r == SA[j].row && new_c == SA[j].col)
				{
					flag = true;
					break;
				}
			}
			if (flag) continue;

			SA[i].row = new_r;
			SA[i].col = new_c;

			//충돌발생
			if (SA[i].row == RU.first && SA[i].col == RU.second)
			{
				int dir = 0; //산타가 움직인 방향의 반대방향으로 밀려남
				if (dir_total[k] == 0) dir = 4;
				else if (dir_total[k] == 2) dir = 6;
				else if (dir_total[k] == 4) dir = 0;
				else if (dir_total[k] == 6) dir = 2;

				int idx = SA[i].idx;
				Crash(dir, idx, 1);
			}

			break; //위에를 스킵없이 모두 수행했다면 break
		}
	}
}

int main()
{
	Input();

	for (int i = 0; i < M; i++)
	{
		RU_move();
		SA_move();

		int cnt = 0;
		for (int i = 0; i < P; i++)
		{
			if (SA[i].state == 1 && SA[i].state1_time == 0)
			{
				SA[i].state1_time++;
				SA[i].score++;
			}
			else if (SA[i].state == 1 && SA[i].state1_time == 1)
			{
				SA[i].state = 0;
				SA[i].state1_time = 0;
				SA[i].score++;
			}
			else if (SA[i].state == 2)
			{
				cnt++;
			}
			else if (SA[i].state == 0)
			{
				SA[i].score++;
			}
		}
		if (cnt == P) break; //모든 산타가 탈락함
	}

	for (int i = 0; i < P; i++)
	{
		cout << SA[i].score << " ";
	}
	return 0;
}