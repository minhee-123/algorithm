// 코드트리 삼성 SW 역량테스트 2025 하반기 오후 1번 문제
// https://www.codetree.ai/ko/frequent-problems/samsung-sw/problems/ai-robot/description

/* 자잘한 디버깅이 있긴 했으나 문제없이 풀이완료 */
// (1) 대소 비교를 하는 과정에서 값 업데이트를 안함 (max_dust)
// (2) visit = true 처리를 안해줬음
// (3) 입력 부분에서 vacuum_location 처리를 안해줬음 (초기 처리가 안됐으니까 문제)


#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

// 동(오른쪽) 남(아래쪽) 서(왼쪽) 북(위쪽)
int dr[4] = { 0, 1, 0, -1 };
int dc[4] = { 1, 0, -1, 0 };

int N, K, L;
int Map[31][31]; // index 1부터 30까지 사용

struct VACUUM
{
	int row;
	int col;
};
vector<VACUUM> vacuum; // index 0부터 사용

bool visit[31][31];
bool vacuum_location[31][31];

// 입력을 받는 함수
void Input()
{
	cin >> N >> K >> L;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++) cin >> Map[i][j]; // -1은 장애물
	}

	for (int i = 0; i < K; i++)
	{
		int row, col;
		cin >> row >> col;

		vacuum.push_back({ row, col });
		vacuum_location[row][col] = true;
	}
}

struct INFORM
{
	int row;
	int col;
	int move_cnt;
};

// 청소기 하나가 이동하는 함수
void Vac_Move(int id)
{
	memset(visit, false, sizeof(visit));

	int SR = vacuum[id].row;
	int SC = vacuum[id].col;

	queue<INFORM> que;
	que.push({ SR, SC, 0 });
	visit[SR][SC] = true;

	int min_cnt = 10000;
	int answerR = 0;
	int answerC = 0;

	while (!que.empty())
	{
		int R = que.front().row;
		int C = que.front().col;
		int cnt = que.front().move_cnt;
		que.pop();

		if (Map[R][C] > 0) // 먼지가 있다면
		{
			if (cnt < min_cnt)
			{
				min_cnt = cnt;
				answerR = R;
				answerC = C;
			}
			else if (cnt == min_cnt)
			{
				if ((answerR > R) || (answerR == R && answerC > C))
				{
					answerR = R;
					answerC = C;
				}
			}
			continue;
		}
		if (cnt > min_cnt) continue;

		for (int i = 0; i < 4; i++)
		{
			int NR = R + dr[i];
			int NC = C + dc[i];

			if (NR < 1 || NR > N || NC < 1 || NC > N) continue; // 격자 밖으로 나가는 경우
			if (visit[NR][NC]) continue; // 이미 방문한 경우
			if (Map[NR][NC] == -1) continue; // 물건이 있는 경우
			if (vacuum_location[NR][NC]) continue; // 청소기가 있는 경우

			visit[NR][NC] = true;
			que.push({ NR, NC, cnt + 1 });
		}
	}

	if (answerR == 0 && answerC == 0) return; // 이동할 곳이 없는 경우

	vacuum_location[SR][SC] = false;
	vacuum_location[answerR][answerC] = true;

	vacuum[id].row = answerR;
	vacuum[id].col = answerC;
}

// 청소기 하나가 청소하는 함수
void Vac_Clean(int id)
{
	int R = vacuum[id].row;
	int C = vacuum[id].col;

	int max_dust = 0;
	int clean_dir = -1;
	vector<pair<int, int>> clean_location[4];

	for (int dir = 0; dir < 4; dir++)
	{
		int dust = 0;
		for (int i = 0; i < 4; i++)
		{
			if (i == 0)
			{
				if (Map[R][C] > 20) dust += 20;
				else dust += Map[R][C];

				clean_location[dir].push_back({ R, C });
			}
			else if (i == 1)
			{
				int NR = R + dr[dir];
				int NC = C + dc[dir];
				if (NR < 1 || NR > N || NC < 1 || NC > N) continue;
				if (Map[NR][NC] == -1) continue; // 물건이 있는 경우

				if (Map[NR][NC] > 20) dust += 20;
				else dust += Map[NR][NC];

				clean_location[dir].push_back({ NR, NC });
			}
			else if (i == 2)
			{
				int NR = R;
				int NC = C;

				if (dir == 0 || dir == 2) // 오른쪽, 왼쪽
				{
					NR += dr[1];
					NC += dc[1];
				}
				else // dir == 1 || dir == 3
				{
					NR += dr[0];
					NC += dc[0];
				}
				if (NR < 1 || NR > N || NC < 1 || NC > N) continue;
				if (Map[NR][NC] == -1) continue; // 물건이 있는 경우

				if (Map[NR][NC] > 20) dust += 20;
				else dust += Map[NR][NC];

				clean_location[dir].push_back({ NR, NC });
			}
			else // i == 3
			{
				int NR = R;
				int NC = C;

				if (dir == 0 || dir == 2) // 오른쪽, 왼쪽
				{
					NR += dr[3];
					NC += dc[3];
				}
				else // dir == 1 || dir == 3
				{
					NR += dr[2];
					NC += dc[2];
				}
				if (NR < 1 || NR > N || NC < 1 || NC > N) continue;
				if (Map[NR][NC] == -1) continue; // 물건이 있는 경우

				if (Map[NR][NC] > 20) dust += 20;
				else dust += Map[NR][NC];

				clean_location[dir].push_back({ NR, NC });
			}
		}
		if (dust == 0) continue;
		if (dust > max_dust) // 합이 같은 방향이 여럿일 경우 동남서북 방향의 우선순위
		{
			max_dust = dust;
			clean_dir = dir;
		}
	}

	if (clean_dir == -1) return; // 청소할 곳이 없음

	// 청소
	for (int i = 0; i < clean_location[clean_dir].size(); i++)
	{
		int nowR = clean_location[clean_dir][i].first;
		int nowC = clean_location[clean_dir][i].second;

		int clean_val = 20;
		if (Map[nowR][nowC] <= 20) clean_val = Map[nowR][nowC];

		Map[nowR][nowC] -= clean_val;
	}
}

// 청소기 전체 이동 후 전체 청소 함수
void Vac()
{
	// 순서대로 이동 → 전체 이동 후 순서대로 청소
	for (int i = 0; i < vacuum.size(); i++) Vac_Move(i);
	for (int i = 0; i < vacuum.size(); i++) Vac_Clean(i);
}

int copy_Map[31][31];
void Dust()
{
	memset(copy_Map, 0, sizeof(copy_Map));
	// 먼지가 있는 모든 격자에 5씩 추가하며 맵 복사
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			if (Map[i][j] > 0) Map[i][j] += 5;
			copy_Map[i][j] = Map[i][j];
		}
	}

	// 먼지 확산
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			if (Map[i][j] == 0) // 깨끗한 격자에서 확산 발생
			{
				int dust_sum = 0;
				for (int k = 0; k < 4; k++)
				{
					int NR = i + dr[k];
					int NC = j + dc[k];
					if (NR < 1 || NR > N || NC < 1 || NC > N) continue;
					if (Map[NR][NC] <= 0) continue;

					dust_sum += Map[NR][NC];
				}
				dust_sum = dust_sum / 10;

				copy_Map[i][j] = dust_sum; // 확산된 먼지는 복사 맵에 기록 (동시 확산을 위함)
			}
		}
	}

	// 모든 작업 완료 후 Map 재업데이트
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++) Map[i][j] = copy_Map[i][j];
	}
}

int Solution()
{
	Vac();
	Dust();

	int answer = 0;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			if (Map[i][j] <= 0) continue;
			answer += Map[i][j];
		}
	}
	return answer;
}

int main()
{
	Input();
	for (int T = 0; T < L; T++)
	{
		int answer = Solution();
		cout << answer << '\n';
	}
	return 0;
}