// 코드트리 삼성 SW 역량테스트 2025 하반기 오전 1번 문제
// https://www.codetree.ai/ko/frequent-problems/samsung-sw/problems/delivery-service/description

/* 1회차 시도했을 때 도저히 디버깅이 되지 않음(틀린 부분을 못 찾음)
 문제에서 요구한 사항을 바꾸지 않고 그대로 수행하는 방향으로 재풀이 */

/* 크게 달라진 부분이 없는데 재풀이 성공(수정 내용은 아래와 같음)
 (1) 맨위를 1, 맨 아래를 N → 중력이 작용하면 N으로 떨어지도록 풀이
 (2) 하차 택배를 찾는 로직을 수정 → 박스 별로 검토 + 박스의 좌측과 우측을 확인

 기존 풀이 결과와 비교해보니까
 기존 풀이는 Input()이 잘못되었던 것 같음 → (1) 수정이 결정적인 듯 */

/* 최대한 문제에서 제시하는 방향대로 풀어야할 것 같음(내 편의대로 풀지 말고!!) */


#include<iomanip>
#include <iostream>
#include <vector>
using namespace std;

int N, M;
int Map[51][51]; // 1부터 50까지 사용

struct BOX
{
	int row1; // 윗쪽 (작은쪽)
	int row2; // 아랫쪽 (큰쪽)
	int col1; // 왼쪽
	int col2; // 오른쪽
	bool dead = false;
};
BOX Box[101];
vector<int> record_id;

// 입력을 받아오는 함수
void Input()
{
	cin >> N >> M;
	for (int i = 0; i < M; i++)
	{
		int k, h, w, c;
		cin >> k >> h >> w >> c;

		record_id.push_back(k);

		int row1 = 1;
		while(1)
		{
			if (row1 + h - 1 == N + 1) break;

			bool flag = false;
			for (int R = row1; R < row1 + h; R++)
			{
				for (int C = c; C < c + w; C++)
				{
					if (Map[R][C] != 0) flag = true; // 현재 위치는 불가능 (내려갈 수 없음)
				}
			}
			if (flag) break;
			row1++;
		}
		row1--; // 무조건 +1 하기 때문에 나와서 -1해야 함

		Box[k] = { row1, row1 + h - 1, c, c + w - 1, false };
		for (int i = Box[k].row1; i <= Box[k].row2; i++)
		{
			for (int j = Box[k].col1; j <= Box[k].col2; j++) Map[i][j] = k;
		}
	}
}

// 택배를 하차하는(삭제하는) 함수
void Delete_Box(int id)
{
	int row1 = Box[id].row1;
	int row2 = Box[id].row2;
	int col1 = Box[id].col1;
	int col2 = Box[id].col2;
	
	for (int i = row1; i <= row2; i++)
	{
		for (int j = col1; j <= col2; j++) Map[i][j] = 0;
	}
}

// 택배를 새로운 위치에 삽입하는 함수
void Add_Box(int id, int row1, int row2)
{
	Box[id].row1 = row1;
	Box[id].row2 = row2;
	int col1 = Box[id].col1;
	int col2 = Box[id].col2;

	for (int i = row1; i <= row2; i++)
	{
		for (int j = col1; j <= col2; j++) Map[i][j] = id;
	}
}

// 택배에 중력을 작용하는 함수
void Down_Box(int id)
{
	int row1 = Box[id].row1;
	int row2 = Box[id].row2;
	int col1 = Box[id].col1;
	int col2 = Box[id].col2;

	if (row2 == N) return; // 더 내려갈 수 없음

	int DR1 = row1;
	int DR2 = row2;
	bool can_move = false;

	while (DR2 <= N)
	{
		DR1++;
		DR2++;
		if (DR2 > N) break;

		bool flag = false;
		for (int i = col1; i <= col2; i++)
		{
			if (Map[DR2][i] != 0)
			{
				flag = true;
				break;
			}
		}
		if (flag) break;
		can_move = true;
	}

	if (!can_move) return; // 내려갈 수 없음
	DR1--;
	DR2--; // 무조건 +1 하기 때문에 나와서 -1해야 함

	Delete_Box(id);
	Add_Box(id, DR1, DR2);
}

// 전체 박스에 중력을 적용하는 함수
void Down()
{
	int visit[101] = { 0 };
	for (int i = N; i >= 1; i--)
	{
		for (int j = 1; j <= N; j++)
		{
			if (Map[i][j] != 0)
			{
				int temp_id = Map[i][j];
				if (visit[temp_id] == 1) continue;

				visit[temp_id] = 1;
				Down_Box(temp_id);
			}
		}
	}
}

// 택배 하차 (왼쪽 오른쪽)
int answer_cnt = 0;
void GetOff(int order)
{
	int min_id = 1000;

	for (int i = 0; i < record_id.size(); i++)
	{
		int temp_id = record_id[i];
		if (Box[temp_id].dead) continue; // 이미 하차한 택배일 경우 pass

		int row1 = Box[temp_id].row1;
		int row2 = Box[temp_id].row2;
		int col1 = Box[temp_id].col1;
		int col2 = Box[temp_id].col2;
		
		bool can_getoff = true;
		for (int R = row1; R <= row2; R++)
		{
			if (order == 0) // 좌측 하차
			{
				if (col1 == 1) break;
				for (int C = col1 - 1; C >= 1; C--)
				{
					if (Map[R][C] != 0)
					{
						can_getoff = false;
						break;
					}
				}
			}
			else // 우측 하차
			{
				if (col2 == N) break;
				for (int C = col2 + 1; C <= N; C++)
				{
					if (Map[R][C] != 0)
					{
						can_getoff = false;
						break;
					}
				}
			}
			if (!can_getoff) break;
		}
		if (can_getoff) min_id = min(min_id, temp_id);
	}
	answer_cnt++;
	cout << min_id << '\n';

	if (min_id == 1000) return; // 오류가 있을 경우에 대비 (문제에서 주어진 조건 상 min_id가 없는 경우는 없음)
	Delete_Box(min_id);
	Box[min_id].dead = true;
}

void Solution()
{
	Input();
	while (answer_cnt < M)
	{
		//*****************************************************디버깅
		
		cout << "\n우측 하차 이후\n";
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++) cout << setw(2) << Map[i][j] << " ";
			cout << '\n';
		}
		cout << '\n';
		
		//*****************************************************디버깅

		GetOff(0);
		if (answer_cnt == M) break;
		Down();

		//*****************************************************디버깅
		
		cout << "\n좌측 하차 이후\n";
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++) cout << setw(2) << Map[i][j] << " ";
			cout << '\n';
		}
		cout << '\n';
		
		//*****************************************************디버깅

		GetOff(1);
		if (answer_cnt == M) break;
		Down();
	}
}

int main()
{
	Solution();
	return 0;
}