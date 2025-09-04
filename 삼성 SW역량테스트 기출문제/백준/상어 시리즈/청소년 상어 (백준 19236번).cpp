// 문제: https://www.acmicpc.net/problem/19236

/*
문제 접근을 잘못했다!!

처음 풀었던 풀이: 상어가 항상 이동할 수 있는 방향의 최대값만 먹으며 이동함
→ 해당 풀이는 상어가 한 가지 루트로만 이동 + 그리디 방법

BUT 상어가 총 먹은 물고기의 합이 최대가 되어야 함
→ 몇 번은 작은 값을 먹으며 이동해야 최대값이 될 수도 있음
→ 완전탐색이 필요 (백트래킹 수행)

처음 풀었던 풀이를 고치기가 너무 힘들어서 처음부터 다시 풀었다 인생
*/

/*
다시 풀 때 디버깅한 부분
(1) 맵이랑 fish 배열까지 백트래킹 대상이기 때문에 애네를 함수의 인자로 계속 사용해야 함 (지역변수로 이용)
	→ 함수의 인자로 빼먹거나 실수로 전역변수를 가져왔음
(2) 문제의 조건을 잘못 사용함
	→ 상어는 빈칸에 있을 수 없으나 지나갈 수는 있음
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int dr[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dc[8] = {0, -1, -1, -1, 0, 1, 1, 1};
// 방향: ↑, ↖, ←, ↙, ↓, ↘, →, ↗

struct FISH
{
	int value;
	int dir;

	int R;
	int C;

	bool death = false; //true가 될 경우 빈자리
};
vector<FISH> fish;
vector<vector<FISH>> Map;

bool comp(FISH A, FISH B) { return A.value < B.value; }

int find_fish_index(int R, int C, vector<FISH> Fish) //위치에 따른 물고기의 index 검출
{
	for (int i = 0; i < Fish.size(); i++)
	{
		if (Fish[i].R == R && Fish[i].C == C) return i;
	}
	return -1;
}

void Input()
{
	Map.resize(4);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int a, b;
			cin >> a >> b;
			b = b - 1; //방향 인덱스는 0부터 7까지

			Map[i].push_back({ a, b, i, j, false });
			fish.push_back({ a, b, i, j, false });
		}
	}
	sort(fish.begin(), fish.end(), comp);
}

struct Fish_and_MAP
{
	vector<FISH> Fish;
	vector<vector<FISH>> MAP;
}; // move_fish 결과 저장

Fish_and_MAP move_fish(int sharkR, int sharkC, vector<FISH> Fish, vector<vector<FISH>> MAP)
{
	for (int idx = 0; idx < Fish.size(); idx++)
	{
		if (Fish[idx].death) continue; //죽었을 경우(빈칸) 생략

		int R = Fish[idx].R;
		int C = Fish[idx].C;
		int dir = Fish[idx].dir;

		int cnt = 0;

		while (1)
		{
			int NR = R + dr[dir];
			int NC = C + dc[dir];

			if (NR < 0 || NR >= 4 || NC < 0 || NC >= 4 || (NR == sharkR && NC == sharkC)) //이동할 수 없는 경우
			{
				cnt++;
				dir++;
				if (dir == 8) dir = 0;
				continue;
			}
			else //이동할 수 있는 경우
			{
				// 물고기 이동
				Fish[idx].dir = dir;
				MAP[R][C].dir = dir;

				int change_idx = find_fish_index(NR, NC, Fish);

				Fish[idx].R = NR;
				Fish[idx].C = NC;
				Fish[change_idx].R = R;
				Fish[change_idx].C = C; //물고기 정보 변경

				swap(MAP[R][C], MAP[NR][NC]); //맵 정보 변경
				break;
			}

			if (cnt >= 8) break; //물고기가 움직일 수 없는 경우 (이동할 수 있는 방향이 없음)
		}
	}

	return { Fish, MAP };
}

int max_eating = 0;
void Simulation(int sharkR, int sharkC, int sharkD, int eating, vector<FISH> Fish, vector<vector<FISH>> MAP)
{
	Fish_and_MAP temp = move_fish(sharkR, sharkC, Fish, MAP);

	vector<vector<FISH>> temp_MAP = temp.MAP;
	vector<FISH> temp_Fish = temp.Fish; //현재 물고기 위치 정보

	int moveR = sharkR;
	int moveC = sharkC;

	while (1)
	{
		moveR += dr[sharkD];
		moveC += dc[sharkD];

		if (moveR < 0 || moveR >= 4 || moveC < 0 || moveC >= 4) break; //상어가 이동할 수 없는 경우
		if (temp_MAP[moveR][moveC].death) continue; //상어는 빈칸을 지나갈 수 있음 (빈칸으로 이동은 불가능)
	
		int idx = find_fish_index(moveR, moveC, temp_Fish);
		temp_Fish[idx].death = true;
		temp_MAP[moveR][moveC].death = true;

		Simulation(moveR, moveC, temp_MAP[moveR][moveC].dir, eating + temp_MAP[moveR][moveC].value, temp_Fish, temp_MAP);

		temp_Fish[idx].death = false;
		temp_MAP[moveR][moveC].death = false; // 백트래킹 수행
	}

	max_eating = max(eating, max_eating);
}

void Answer()
{
	Input();

	int idx = find_fish_index(0, 0, fish);
	fish[idx].death = true;
	Map[0][0].death = true;

	Simulation(0, 0, Map[0][0].dir, Map[0][0].value, fish, Map);
}

int main()
{
	Answer();
	cout << max_eating;
	return 0;
}