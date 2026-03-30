// 문제: https://www.acmicpc.net/problem/17144
#include <iostream>
#include <vector>
using namespace std;

int R, C, T, AP_T, AP_B; // 행, 열, 시간, 윗쪽 공기청정기 행, 아랫쪽 공기청정기 행
vector<int> Map[51];
vector<int> temp_Map[51];

void Input() // 입력
{
	cin >> R >> C >> T;
	for (int i = 1; i <= R; i++)
	{
		Map[i].resize(C + 1);
		temp_Map[i].resize(C + 1);
	}

	for (int i = 1; i <= R; i++)
	{
		for (int j = 1; j <= C; j++)
		{
			cin >> Map[i][j];

			if (Map[i][j] == -1)
			{
				if (Map[i - 1][j] == -1) AP_B = i;
				else AP_T = i;
			}
		}
	}
}

int dr[4] = { 0, 0, 1, -1 }; // 우 좌 하 상
int dc[4] = { 1, -1, 0, 0 };

void Diffusion() // 미세먼지 확산
{
	for (int i = 1; i <= R; i++) // 임시 맵 초기화
	{
		for (int j = 1; j <= C; j++) temp_Map[i][j] = 0;
	}
	temp_Map[AP_T][1] = -1;
	temp_Map[AP_B][1] = -1;

	for (int i = 1; i <= R; i++) // 미세먼지 확산
	{
		for (int j = 1; j <= C; j++)
		{
			int dust = Map[i][j];
			if (dust <= 0) continue; // 공기청정기 위치도 패스

			int diffusion_cnt = 0;
			for (int k = 0; k < 4; k++)
			{
				int NR = i + dr[k];
				int NC = j + dc[k];

				if (NR < 1 || NR > R || NC < 1 || NC > C) continue;
				if (Map[NR][NC] == -1) continue;

				diffusion_cnt++;
				temp_Map[NR][NC] += dust / 5; // 임시맵에 확산 저장
			}

			dust -= (dust / 5) * diffusion_cnt;
			temp_Map[i][j] += dust; // 임시맵에 남은 먼지양 저장
		}
	}

	for (int i = 1; i <= R; i++) // 임시맵을 맵으로 복사
	{
		for (int j = 1; j <= C; j++) Map[i][j] = temp_Map[i][j];
	}
}

void Action_AP(bool is_T) // 공기청정기 동작
{
	int dir[4] = { 2, 0, 3, 1 }; // 아래 공기청정기 (시계방향)
	if (is_T) // 위 공기청정기 (반시계 방향)
	{
		dir[0] = 3;
		dir[2] = 2;
	}

	int NC = 1, NR = AP_B;
	if (is_T) NR = AP_T;

	// 공기청정기의 바람 움직임 반대로 탐색
	// 탐색하며 다음 위치의 먼지를 현재 위치로 가져오면 됨
	// 첫 시작의 경우(공기청정기) 다음 위치의 먼지를 소멸 (현재 위치로 가져오면 소멸)
	int dir_idx = 0;
	while (1)
	{
		int NextR = NR + dr[dir[dir_idx]];
		int NextC = NC + dc[dir[dir_idx]];
		if ((NextR < 1 || NextR > R || NextC < 1 || NextC > C) || (is_T && NextR > AP_T) || (!is_T && NextR < AP_B))
		{
			// 반대로 탐색하기 때문에 (is_T && NextR > AP_T) || (!is_T && NextR < AP_B) 조건 추가
			// 정방향대로 탐색하면 격자를 넘어갈 때 방향을 변경하면 되는데
			// 반대로 탐색하고 있어 3번째 방향을 바꿀 때 문제 → 공기청정기 행을 넘어가지 않도록 조건 추가
			dir_idx++;
			NextR = NR + dr[dir[dir_idx]];
			NextC = NC + dc[dir[dir_idx]];
		}

		if (Map[NextR][NextC] == -1) break;

		Map[NR][NC] = Map[NextR][NextC];
		Map[NextR][NextC] = 0; // 다음 위치 먼지를 현재 위치로 가져왔으므로 0으로 만들어둠
		if ((NR == AP_B || NR == AP_T) && NC == 1) Map[NR][NC] = -1; // 첫 시작인 경우

		NR = NextR;
		NC = NextC;
	}
}

void Solution()
{
	Input();
	for (int i = 0; i < T; i++)
	{
		Diffusion(); // 먼지 확산
		Action_AP(true); // 위 공기청정기 동작
		Action_AP(false); // 아래 공기청정기 동작
	}

	int answer = 0;
	for (int i = 1; i <= R; i++)
	{
		for (int j = 1; j <= C; j++)
		{
			if (Map[i][j] == -1) continue;
			answer += Map[i][j];
		}
	}
	cout << answer;
}

int main()
{
	Solution();
	return 0;
}