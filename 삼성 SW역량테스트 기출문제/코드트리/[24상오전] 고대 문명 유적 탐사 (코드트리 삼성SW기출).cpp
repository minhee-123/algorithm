// 코드트리 삼성 SW 역량테스트 2024 상반기 오전 1번 문제
// https://www.codetree.ai/training-field/frequent-problems/problems/ancient-ruin-exploration/description?page=1&pageSize=5

// 구현 중 회전(하드코딩)과 BFS 부분은 다른 사람의 풀이를 일부 참고했다! (그럼에도 오래 걸렸다!)
// 반례를 고치는 것도 제법 오래 걸렸다!
// (1) 무한 루프에 빠지지 않도록 주의한다 ★ while 문을 사용할 때 특히 주의 (답이 아예 출력되지 않는 시간초과는 무한루프에 걸린 것)
// (2) 코드의 순서에 유의한다 ★ 순차적으로 실행되는 것을 유의, 코드에 위치만 바꿔줘도 반례가 해결된다 (이번에 visit을 now_rc를 부를 때 체크했더니 new_rc를 진행하며 갔던 곳을 또 가는 문제가 발생했음 (cnt가 여러번 더해져서 오답 발생했음))


#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

int K, M; //탐사 반복 횟수, 벽면에 적힌 유물 조각의 개수
queue<int> piece;
vector<vector<int>> map = { {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0} };

struct rotation_record
{
	int row;
	int col;
	int rotation; // 0(90도 회전), 1(180도 회전), 2(270도 회전)
	int value;
};
vector<rotation_record> turn_result; //(행, 열), 유물의 가치
rotation_record turn_result_final = { 0, 0, 0, 0 };

bool visit[5][5]; //자동 false
int dr[4] = { 1, 0, -1, 0 }; // 상 우 하 좌
int dc[4] = { 0, 1, 0, -1 };

int count_value = 0;
bool flag = false;


void Input()
{
	cin >> K >> M;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cin >> map[i][j];
		}
	}
	for (int i = 0; i < M; i++)
	{
		int temp;
		cin >> temp;
		piece.push(temp);
	}
}


vector<vector<int>> Rotation_90(vector<vector<int>> copy, int r, int c)
{
	// B[row][colmun] = A[N - colmun - 1][row] (NxN 격자 A를 회전한 결과 B)
	// NxM 격자를 회전하면 MxN 격자가 되는 것을 주의해서 같은 공식 (for루프 M > for루프 N > B[row][colmun] = A[M - 1 - column][row]

	// ↑ 위의 방법이 공식이긴 하지만 공식을 적용하기 어려운 상황
	// 무식하게 하드코딩하는 방법이 더 편리함

	vector<vector<int>> temp_map = copy;

	temp_map[r - 1][c + 1] = copy[r - 1][c - 1];
	temp_map[r][c + 1] = copy[r - 1][c];
	temp_map[r + 1][c + 1] = copy[r - 1][c + 1];
	temp_map[r + 1][c] = copy[r][c + 1];
	temp_map[r + 1][c - 1] = copy[r + 1][c + 1];
	temp_map[r][c - 1] = copy[r + 1][c];
	temp_map[r - 1][c - 1] = copy[r + 1][c - 1];
	temp_map[r - 1][c] = copy[r][c - 1];

	return temp_map;
}

vector<vector<int>> Rotation_180(vector<vector<int>> copy, int r, int c)
{
	vector<vector<int>> temp_map = copy;

	temp_map[r + 1][c + 1] = copy[r - 1][c - 1];
	temp_map[r + 1][c] = copy[r - 1][c];
	temp_map[r + 1][c - 1] = copy[r - 1][c + 1];
	temp_map[r][c - 1] = copy[r][c + 1];
	temp_map[r - 1][c - 1] = copy[r + 1][c + 1];
	temp_map[r - 1][c] = copy[r + 1][c];
	temp_map[r - 1][c + 1] = copy[r + 1][c - 1];
	temp_map[r][c + 1] = copy[r][c - 1];

	return temp_map;
}

vector<vector<int>> Rotation_270(vector<vector<int>> copy, int r, int c)
{
	vector<vector<int>> temp_map = copy;

	temp_map[r + 1][c - 1] = copy[r - 1][c - 1];
	temp_map[r][c - 1] = copy[r - 1][c];
	temp_map[r - 1][c - 1] = copy[r - 1][c + 1];
	temp_map[r - 1][c] = copy[r][c + 1];
	temp_map[r - 1][c + 1] = copy[r + 1][c + 1];
	temp_map[r][c + 1] = copy[r + 1][c];
	temp_map[r + 1][c + 1] = copy[r + 1][c - 1];
	temp_map[r + 1][c] = copy[r][c - 1];

	return temp_map;
}


int Find(vector<vector<int>> MAP, int r, int c)
{
	if (visit[r][c]) return 0; //이미 방문했던 곳이라면 0을 반환

	queue<pair<int, int>> q;
	queue<pair<int, int>> record;
	q.push({ r, c });
	record.push({ r, c });
	visit[r][c] = true;

	int cnt = 1;
	int val = MAP[r][c];

	while (!q.empty())
	{
		int now_r = q.front().first;
		int now_c = q.front().second;

		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int new_r = now_r + dr[i];
			int new_c = now_c + dc[i];

			if (new_r < 0 || new_r > 4 || new_c < 0 || new_c > 4) continue;
			if (visit[new_r][new_c]) continue;

			if (MAP[new_r][new_c] == val)
			{
				q.push({ new_r, new_c });
				record.push({ new_r, new_c });

				visit[new_r][new_c] = true;
				cnt++;
			}
		}
	}

	if (cnt >= 3)
	{
		for (int i = 0; i < cnt; i++)
		{
			MAP[record.front().first][record.front().second] = 0;
			record.pop();
		}
		return cnt;
	}
	else return 0;
}

int Find_final(int r, int c)
{
	if (visit[r][c]) return 0; //이미 방문했던 곳이라면 0을 반환

	queue<pair<int, int>> q;
	queue<pair<int, int>> record;
	q.push({ r, c });
	record.push({ r, c });
	visit[r][c] = true;

	int cnt = 1;
	int val = map[r][c];

	while (!q.empty())
	{
		int now_r = q.front().first;
		int now_c = q.front().second;

		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int new_r = now_r + dr[i];
			int new_c = now_c + dc[i];

			if (new_r < 0 || new_r > 4 || new_c < 0 || new_c > 4) continue;
			if (visit[new_r][new_c]) continue;

			if (map[new_r][new_c] == val)
			{
				q.push({ new_r, new_c });
				record.push({ new_r, new_c });

				visit[new_r][new_c] = true;
				cnt++;
			}
		}
	}

	if (cnt >= 3)
	{
		for (int i = 0; i < cnt; i++)
		{
			map[record.front().first][record.front().second] = 0;
			record.pop();
		}
		return cnt;
	}
	else return 0;
}


void Turn()
{
	for (int i = 1; i <= 3; i++) //행
	{
		for (int j = 1; j <= 3; j++) //열
		{
			int temp_r = i;
			int temp_c = j;

			for (int k = 0; k < 3; k++)
			{
				vector<vector<int>> temp_map = map;

				if (k == 0) temp_map = Rotation_90(temp_map, temp_r, temp_c);
				else if (k == 1) temp_map = Rotation_180(temp_map, temp_r, temp_c);
				else if (k == 2) temp_map = Rotation_270(temp_map, temp_r, temp_c);

				int cnt = 0;
				for (int ii = 0; ii < 5; ii++)
				{
					for (int jj = 0; jj < 5; jj++)
					{
						cnt += Find(temp_map, ii, jj);
					}
				}
				memset(visit, false, sizeof(visit));

				if (cnt == 0) continue;
				else turn_result.push_back({ temp_r, temp_c, k, cnt });
			}
		}
	}
}

bool comp(rotation_record A, rotation_record B)
{
	if (A.value != B.value) return A.value > B.value;
	else if (A.rotation != B.rotation) return A.rotation < B.rotation;
	else if (A.col != B.col) return A.col < B.col;
	else if (A.row != B.row) return A.row < B.row;
	else return false;
}

void Solution()
{
	if (turn_result.empty()) flag = true;
	else
	{
		sort(turn_result.begin(), turn_result.end(), comp);

		int row = turn_result[0].row;
		int col = turn_result[0].col;

		if (turn_result[0].rotation == 0) map = Rotation_90(map, row, col);
		else if (turn_result[0].rotation == 1) map = Rotation_180(map, row, col);
		else if (turn_result[0].rotation == 2) map = Rotation_270(map, row, col);

		while (1)
		{
			int count = 0;
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					count += Find_final(i, j);
				}
			}
			memset(visit, false, sizeof(visit));

			if (count == 0) break;
			else if (count > 0) count_value += count;

			for (int i = 0; i < 5; i++)
			{
				for (int j = 4; j >= 0; j--)
				{
					if (map[j][i] == 0)
					{
						map[j][i] = piece.front();
						piece.pop();
					}
				}
			}
		}
	}
}


int main()
{
	Input();
	for (int i = 0; i < K; i++)
	{
		turn_result.clear();
		Turn();

		count_value = 0;
		Solution();

		if (flag) break;
		else cout << count_value << " ";
	}
	return 0;
}