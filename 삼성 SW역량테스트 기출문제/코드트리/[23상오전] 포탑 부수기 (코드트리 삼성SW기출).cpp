// 코드트리 삼성 SW 역량테스트 2023 상반기 오전 1번 문제
// https://www.codetree.ai/ko/frequent-problems/problems/destroy-the-turret/description

#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

int N, M, K;
int MAP[11][11];

struct TURRENT
{
	int index;
	int row;
	int col;
	int power;
};

int turrent_cnt = 0;
vector<TURRENT> turrent;

int K_index = 0; //현재 턴 수 (공격 횟수)
vector<int> attack_record;

int dr[8] = { 0, 1, 0, -1, 1, 1, -1, -1 }; //우 하 좌 상 (이후는 대각선 방향)
int dc[8] = { 1, 0, -1, 0, 1, -1, 1, -1 };

void Input()
{
	cin >> N >> M >> K;

	int index = 0;
	turrent.resize(N * M);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> MAP[i][j];
			if (MAP[i][j] != 0) turrent_cnt++;

			turrent[index].row = i;
			turrent[index].col = j;
			turrent[index].power = MAP[i][j];
			turrent[index].index = index;

			index++;
		}
	}

	attack_record.resize(K + 1);
	attack_record[K_index] = -1; //시점 0에서 모두 공격한 경험이 있다고 가정함
}

void update_turrent()
{
	turrent_cnt = 0;
	int index = 0;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (MAP[i][j] != 0) turrent_cnt++;

			turrent[index].row = i;
			turrent[index].col = j;
			turrent[index].power = MAP[i][j];
			turrent[index].index = index;

			index++;
		}
	}
} //포탑 정보 업데이트

bool comp_attacker(TURRENT A, TURRENT B)
{
	if (MAP[A.row][A.col] == 0) return false;
	else if (MAP[B.row][B.col] == 0) return true;
	else //A와 B 포탑이 모두 생존한 경우
	{
		if (A.power != B.power) return A.power < B.power; //공격력이 낮은 포탑으로 선정
		else //공격력이 같을 경우
		{
			int index = K_index;
			while (index >= 0) //최근에 공격한 포탑으로 선정
			{
				if (A.index == attack_record[index]) return true;
				if (B.index == attack_record[index]) return false;
				index--;
			}

			//최근 공격한 포탑이 없다면
			if (A.row + A.col != B.row + B.col) return A.row + A.col > B.row + B.col; //행과 열의 합이 큰 포탑으로 선정
			else return A.col > B.col; //열 값이 가장 큰 포탑으로 선정
		}
	}
}

bool comp_victim(TURRENT A, TURRENT B)
{
	if (A.power != B.power) return A.power > B.power; //공격력이 강한 포탑으로 선정
	else //공격력이 같을 경우
	{
		int index = K_index;
		while (index >= 0) //공격한지 가장 오래된 포탑으로 선정 (시점 0에서 모두 1회의 공격 이력을 가지고 있다고 전제함 → 회차에서 공격 이력이 전혀 없다면 우선 선발)
		{
			if (A.index == attack_record[index]) return false;
			if (B.index == attack_record[index]) return true;
			index--;
		}

		//둘다 회차에서 공격한 이력이 없다면
		if (A.row + A.col != B.row + B.col) return A.row + A.col < B.row + B.col; //행과 열의 합이 작은 포탑으로 선정
		else return A.col < B.col; //열 값이 가장 작은 포탑으로 선정
	}
}

void Attack()
{
	sort(turrent.begin(), turrent.end(), comp_attacker); //공격자 선정
	TURRENT attacker = turrent[0];
	sort(turrent.begin(), turrent.end(), comp_victim); //피해자 선정
	TURRENT victim;
	if (turrent[0].index == attacker.index) victim = turrent[1]; //피해자로 자기 자신을 설정하는 경우 제외
	else victim = turrent[0];

	K_index++;
	attack_record[K_index] = attacker.index; //공격자 기록

	attacker.power += N + M; //공격자의 공격력 증가
	MAP[attacker.row][attacker.col] += N + M;

	int attack_power = attacker.power;
	int row = attacker.row;
	int col = attacker.col;

	int target_row = victim.row;
	int target_col = victim.col;

	queue<pair<int, int>> q;
	q.push({ row, col });

	bool target_flag = false; //target에 도착했는지 여부
	bool visit[11][11];
	memset(visit, false, sizeof(visit));

	visit[row][col] = true; //출발점 visit
	vector<pair<int, int>> road_record[11][11]; //지나온 길 check

	//레이저 공격 시도
	while (!q.empty())
	{
		int now_row = q.front().first;
		int now_col = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int next_row = now_row + dr[i];
			if (next_row == -1) next_row = N - 1;
			if (next_row == N) next_row = 0;

			int next_col = now_col + dc[i];
			if (next_col == -1) next_col = M - 1;
			if (next_col == M) next_col = 0;

			if (MAP[next_row][next_col] == 0) continue;
			if (visit[next_row][next_col]) continue;

			visit[next_row][next_col] = true;
			for (int i = 0; i < road_record[now_row][now_col].size(); i++) road_record[next_row][next_col].push_back(road_record[now_row][now_col][i]);
			road_record[next_row][next_col].push_back({ next_row, next_col });

			if (next_row == target_row && next_col == target_col)
			{
				target_flag = true;
				break;
			}
			else q.push({ next_row, next_col });
		}

		if (target_flag) break;
	}

	int attack_visit[11][11];
	memset(attack_visit, false, sizeof(attack_visit));

	attack_visit[row][col] = true;
	attack_visit[target_row][target_col] = true;

	if (target_flag) //레이저 공격
	{
		MAP[target_row][target_col] -= attack_power;
		if (MAP[target_row][target_col] < 0) MAP[target_row][target_col] = 0;

		for (int i = road_record[target_row][target_col].size() - 1; i >= 0; i--)
		{
			if (i == road_record[target_row][target_col].size() - 1) continue;

			int r = road_record[target_row][target_col][i].first;
			int c = road_record[target_row][target_col][i].second;

			MAP[r][c] -= attack_power / 2;
			if (MAP[r][c] < 0) MAP[r][c] = 0;
			attack_visit[r][c] = true;
		}
	}
	else //레이저 공격 불가
	{
		//포탄 공격
		MAP[target_row][target_col] -= attack_power;
		if (MAP[target_row][target_col] < 0) MAP[target_row][target_col] = 0;

		for (int i = 0; i < 8; i++)
		{
			int r = target_row + dr[i];
			if (r == -1) r = N - 1;
			if (r == N) r = 0;

			int c = target_col + dc[i];
			if (c == -1) c = M - 1;
			if (c == M) c = 0;

			if (r == row && c == col) continue;
			MAP[r][c] -= attack_power / 2;

			if (MAP[r][c] < 0) MAP[r][c] = 0;
			attack_visit[r][c] = true;
		}
	}

	//포탑 정비
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (!attack_visit[i][j] && MAP[i][j] != 0) MAP[i][j] += 1;
		}
	}

	update_turrent(); //포탑 정보 업데이트
}

void Solution()
{
	Input();

	for (int i = 0; i < K; i++)
	{
		Attack();
		if (turrent_cnt == 1) break;
	}

	int max_power = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++) max_power = max(max_power, MAP[i][j]);
	}
	cout << max_power;
}

int main()
{
	Solution();
	return 0;
}

// 문제의 상세 조건을 지키지 않아서 디버깅 수행
// 앞으로 문제를 풀 때 한 줄의 조건을 놓치지 않도록 주의함
// → 공격자를 선정할 때 MAP[row][col] == 0 예외 조건 잘 처리해줘야 함
// → 피해자를 선정할 때 '공격한지 가장 오래된 포탑'은 공격을 한 적 없는 포탑(시점 0에서 모두 1회씩 공격)이 최우선
// → 포탄 공격에서 공격자는 영향을 받지 않음