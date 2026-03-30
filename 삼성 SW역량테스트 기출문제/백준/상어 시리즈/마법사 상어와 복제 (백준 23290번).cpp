// 문제: https://www.acmicpc.net/problem/23290

/* 디버깅하면서 놓쳤던 부분 (with ChatGPT)

(1) copy_fish 벡터를 clear하지 않고 계속 사용함 (누적되는 문제가 발생)

(2) 문제 조건을 잘못 이해함 상어는 [상, 상, 하]와 같이 제자리로 돌아오는 움직임도 할 수 있음

(3) 물고기 제거와 find_cnt_map 부분 오류
	→ 난 차이가 없다고 느껴지는데
	→ find_cnt_map을 0으로 초기화하고 kill_fish에서 fish deat만 true로 바꿨더니 오류
	→ 0으로 초기화하는 부분을 없애고 kill_fish에서 find_cnt_map을 감소했더니 통과 (이쪽으로 해야 fish랑 map이랑 일치)
	→ 논리적으로 fish.death와 따로 움직이게 되어서 문제가 발생하는 것이라고 한다
	→ 하여튼 순서가 중요한거지... 코딩이 이러는 게 하루이틀이냐
*/


#include <iostream>
#include <vector>
#include <cstring> //memset 사용할 때 빼먹지 말자
#include <algorithm>
using namespace std;

int M, S;
int dr[9] = { 0, 0, -1, -1, -1, 0, 1, 1, 1 };
int dc[9] = { 0, -1, -1, 0, 1, 1, 1, 0, -1 }; //index는 1부터 8까지 사용
// ←, ↖, ↑, ↗, →, ↘, ↓, ↙

int drS[5] = { 0, -1, 0, 1, 0 };
int dcS[5] = { 0, 0, -1, 0, 1  }; //index는 1부터 4까지 사용
// ↑, ←, ↓, →

int sharkR, sharkC;

struct FISH_INFORM
{
	int R;
	int C;
	int dir;
	bool death = false;
};
vector<FISH_INFORM> fish;

int smell_map[5][5];
int fish_cnt_map[5][5];

void Input()
{
	cin >> M >> S;
	for (int i = 0; i < M; i++)
	{
		int R, C, dir;
		cin >> R >> C >> dir;

		fish.push_back({ R, C, dir, false });
		fish_cnt_map[R][C]++;
	}
	cin >> sharkR >> sharkC;
}

vector<FISH_INFORM> copy_fish;
void Copy()
{
	copy_fish.clear();

	for (int i = 0; i < fish.size(); i++)
	{
		copy_fish.push_back({ fish[i].R, fish[i].C, fish[i].dir, fish[i].death });
	}
}

void Move_fish()
{
	for (int i = 0; i < fish.size(); i++)
	{
		if (fish[i].death) continue;

		int R = fish[i].R;
		int C = fish[i].C;
		int dir = fish[i].dir;

		int cnt = 0;

		while (cnt <= 8)
		{
			cnt++;

			int NR = R + dr[dir];
			int NC = C + dc[dir];

			if (NR <= 0 || NR > 4 || NC <= 0 || NC > 4)
			{
				dir--;
				if (dir == 0) dir = 8;
				continue;
			}
			if (smell_map[NR][NC] > 0)
			{
				dir--;
				if (dir == 0) dir = 8;
				continue;
			}
			if (NR == sharkR && NC == sharkC)
			{
				dir--;
				if (dir == 0) dir = 8;
				continue;
			}

			//이동이 가능한 경우
			fish[i].R = NR;
			fish[i].C = NC;
			fish[i].dir = dir;

			fish_cnt_map[R][C]--;
			fish_cnt_map[NR][NC]++;

			break;
		} //이동이 불가능한 경우 아무런 변화없이 종료
	}
}

vector<int> max_path;
int max_cnt;
bool visit[5][5];

void Select_shark_path(int R, int C, int cnt, vector<int> path)
{
	if (path.size() == 3)
	{
		if (cnt > max_cnt) //우선순위가 높은 순으로 탐색함
		{
			max_cnt = cnt;

			max_path.clear();
			for (int i = 0; i < path.size(); i++) max_path.push_back(path[i]);
		}
		return;
	}

	for (int i = 1; i <= 4; i++)
	{
		int NR = R + drS[i];
		int NC = C + dcS[i];

		if (NR <= 0 || NR > 4 || NC <= 0 || NC > 4) continue;

		int add = 0;
		if (!visit[NR][NC])
		{
			visit[NR][NC] = true;
			add = fish_cnt_map[NR][NC];
		}

		path.push_back(i);
		Select_shark_path(NR, NC, cnt + add, path);

		path.pop_back();
		if (add > 0) visit[NR][NC] = false;
	}
}

bool dead_flag = false;
void Kill_fish(int R, int C)
{
	for (int i = 0; i < fish.size(); i++)
	{
		if (!fish[i].death && fish[i].R == R && fish[i].C == C)
		{
			fish[i].death = true;
			fish_cnt_map[R][C]--;

			dead_flag = true;
		}
	}
}

void Down_smell()
{
	for (int i = 1; i <= 4; i++)
	{
		for (int j = 1; j <= 4; j++)
		{
			if (smell_map[i][j] > 0) smell_map[i][j]--;
		}
	}
}

void Move_shark()
{
	memset(visit, false, sizeof(visit));
	max_path.clear();
	max_cnt = -1;

	vector<int> temp;
	Select_shark_path(sharkR, sharkC, 0, temp);

	for (int i = 0; i < max_path.size(); i++)
	{
		dead_flag = false;

		sharkR += drS[max_path[i]];
		sharkC += dcS[max_path[i]];

		Kill_fish(sharkR, sharkC);		
		if (dead_flag) smell_map[sharkR][sharkC] = 3; //바로 1을 깎음
	}
}

void Copy_magic()
{
	for (int i = 0; i < copy_fish.size(); i++)
	{
		if (copy_fish[i].death) continue;

		fish.push_back({ copy_fish[i].R, copy_fish[i].C, copy_fish[i].dir, copy_fish[i].death });
		fish_cnt_map[copy_fish[i].R][copy_fish[i].C]++;
	}
}

void Simulation()
{
	Input();

	for (int T = 0; T < S; T++)
	{
		Copy();
		Move_fish();
		Move_shark();
		Down_smell();
		Copy_magic();
	}

	int answer = 0;
	for (int i = 0; i < fish.size(); i++)
	{
		if (!fish[i].death) answer++;
	}

	cout << answer;
}

int main()
{
	Simulation();
	return 0;
}