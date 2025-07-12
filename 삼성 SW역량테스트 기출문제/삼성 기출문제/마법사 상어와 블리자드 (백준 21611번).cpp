// 문제: https://www.acmicpc.net/problem/21611
#include <iostream>
#include <vector>
using namespace std;

int N, M;
int sharkR;
int sharkC;

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

vector<int> order;
vector<int> magic_len;

int Num[50][50];
vector<int> Map_line;

int Bomb_cnt[4]; // 정답 배열 (index 1부터 3까지 사용)

void Make_map()
{
	int R = (N + 1) / 2;
	int C = (N + 1) / 2;

	int move_len = 1;
	int move_dir = 0;
	int move_index = 0;

	int mr[4] = {0, 1, 0, -1};
	int mc[4] = {-1, 0, 1, 0};

	Num[R][C] = move_index++;
	bool flag = false;

	// N * N 행렬 각 자리의 번호 생성 (자리 번호)
	while (1)
	{
		for (int turn = 0; turn < 2; turn++)
		{
			for (int move = 0; move < move_len; move++)
			{
				R += mr[move_dir];
				C += mc[move_dir];

				Num[R][C] = move_index++;

				if (R == 1 && C == 1)
				{
					flag = true;
					break;
				}
			}
			if (flag) break;

			move_dir++;
			if (move_dir == 4) move_dir = 0;
		}
		if (flag) break;

		move_len++;
	}
}

void Input()
{
	cin >> N >> M;
	sharkR = (N + 1) / 2;
	sharkC = (N + 1) / 2;

	Make_map();

	Map_line.resize(N * N, 0);
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			int temp;
			cin >> temp;

			int idx = Num[i][j]; // 해당 자리의 번호를 찾고
			Map_line[idx] = temp; // 알맞은 자리번호에 값을 저장
		}
	}

	for (int i = 0; i < M; i++)
	{
		int O, L;
		cin >> O >> L;

		order.push_back(O - 1);
		magic_len.push_back(L);
	}
}

void Attack(int now_order, int now_magic_len)
{
	int R = sharkR;
	int C = sharkC;

	// 얼음 파편 공격
	for (int i = 0; i < now_magic_len; i++)
	{
		R += dr[now_order];
		C += dc[now_order];

		int idx = Num[R][C];
		Map_line[idx] = 0;
	}

	// 구슬을 굳이 이동시키지 않아도 처리할 수 있음
	// 구슬 사이에 있는 0은 고려하지 않고 구슬을 연결하면 됨
}

bool Bomb_flag = false;
void Bomb()
{
	int S = Map_line.size() - 1;
	int E = S;
	int connect = 1;

	// 구슬 폭발
	for (int i = Map_line.size() - 2; i >= 1; i--)
	{
		if (Map_line[i] == 0) continue;

		if (Map_line[S] == Map_line[i])
		{
			E = i;
			connect++;
		}
		else //Map_line[S] != Map_line[i]
		{
			if (connect >= 4)
			{
				int value = Map_line[S];
				for (int j = S; j >= E; j--)
				{
					if (Map_line[j] == 0) continue;

					Map_line[j] = 0;
					Bomb_cnt[value]++;
				}
				Bomb_flag = true;
			}

			S = i;
			E = S;
			connect = 1;
		}
	}

	// 구슬 connect가 1번까지 이어지는 경우 (for문에서는 마지막 부분이 누락됨 + 누락 처리)
	if (connect >= 4)
	{
		int value = Map_line[S];
		for (int j = S; j >= E; j--)
		{
			if (Map_line[j] == 0) continue;

			Map_line[j] = 0;
			Bomb_cnt[value]++;
		}
		Bomb_flag = true;
	}
}

void Run_Bomb()
{
	while (1)
	{
		Bomb_flag = false;
		Bomb();
		if (!Bomb_flag) break;
	}
}

void Change_Map()
{
	vector<pair<int, int>> record; //{A, B}
	int A = 0;
	int B = 0;

	// 구슬 기록하기 (그룹 만들어서 기록)
	for (int i = 1; i < Map_line.size(); i++)
	{
		if (Map_line[i] == 0) continue;

		if (A == 0)
		{
			A = 1;
			B = Map_line[i];
		}
		else //A!=0
		{
			if (Map_line[i] == B) A++;
			else //Map_line[i] != B
			{
				record.push_back({ A, B });

				A = 1;
				B = Map_line[i];
			}
		}
	}

	// 마지막 그룹 추가 (for문에서는 마지막 그룹이 누락됨)
	if (A != 0 && B != 0) record.push_back({ A, B });

	// 기록해둔 구슬 채우기
	int idx = 1;
	for (int i = 0; i < record.size(); i++)
	{
		Map_line[idx] = record[i].first;
		idx++;
		if (idx > N * N - 1) break;

		Map_line[idx] = record[i].second;
		idx++;
		if (idx > N * N - 1) break;
	}

	// 남는 자리 0으로 채우기
	if (idx <= N * N - 1)
	{
		for (int index = idx; index < Map_line.size(); index++) Map_line[index] = 0;
	}
}

void Solution()
{
	Input();

	for (int i = 0; i < M; i++)
	{
		Attack(order[i], magic_len[i]);
		Run_Bomb();
		Change_Map();
	}

	int answer = (1 * Bomb_cnt[1]) + (2 * Bomb_cnt[2]) + (3 * Bomb_cnt[3]);
	cout << answer;
}

int main()
{
	Solution();
	return 0;
}


/*
(1)
맨 처음에는 구슬이 제거될 때마다 전체 구슬을 이동시켜주는 방향으로 문제를 풀었음
→ 매번 구슬을 삭제하고 이동시켜주는 것은 시간복잡도 or 구현이 복잡해짐
→ 구슬을 이동시키지 않고 비어있는 자리는 0으로 처리, 0은 pass하는 것으로 내부 구현
(2)
구슬 폭발과 남은 구슬의 그룹화에서 마지막 처리를 누락함
→ for문 내부에서 마지막 반복을 저장할 수가 없음 (코드 확인)
→ 마지막 부분은 따로 처리하도록 코드 추가 (이 부분을 못 찾아서 오래 걸렸음!! ★★)
→ 문제 풀 때 for문이 마지막 or 첫번째 인덱스까지 모든 경우를 처리할 수 있는지 꼭 확인
*/

/*
Maybe... (추가 공부 내용)

vector에서 erase 기능을 사용하면 시간복잡도가 높다 (시간이 터질 확률이 매우 높아 비추천, 사용하지 않아야 함)
차라리 vector를 새롭게 선언해서 옮기는 방식으로 중간값을 제거해라

vector에서 resize를 쓰면 공간 복잡도를 낮출 수 있음
push_back은 작업을 반복할 수록 넉넉한 공간을 확보해두려고 하기 때문에 공간복잡도가 안 좋음
*/