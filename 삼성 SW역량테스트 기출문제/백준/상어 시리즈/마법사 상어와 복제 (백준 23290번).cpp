// ����: https://www.acmicpc.net/problem/23290

/* ������ϸ鼭 ���ƴ� �κ� (with ChatGPT)

(1) copy_fish ���͸� clear���� �ʰ� ��� ����� (�����Ǵ� ������ �߻�)

(2) ���� ������ �߸� ������ ���� [��, ��, ��]�� ���� ���ڸ��� ���ƿ��� �����ӵ� �� �� ����

(3) ����� ���ſ� find_cnt_map �κ� ����
	�� �� ���̰� ���ٰ� �������µ�
	�� find_cnt_map�� 0���� �ʱ�ȭ�ϰ� kill_fish���� fish deat�� true�� �ٲ���� ����
	�� 0���� �ʱ�ȭ�ϴ� �κ��� ���ְ� kill_fish���� find_cnt_map�� �����ߴ��� ��� (�������� �ؾ� fish�� map�̶� ��ġ)
	�� �������� fish.death�� ���� �����̰� �Ǿ ������ �߻��ϴ� ���̶�� �Ѵ�
	�� �Ͽ�ư ������ �߿��Ѱ���... �ڵ��� �̷��� �� �Ϸ���Ʋ�̳�
*/


#include <iostream>
#include <vector>
#include <cstring> //memset ����� �� ������ ����
#include <algorithm>
using namespace std;

int M, S;
int dr[9] = { 0, 0, -1, -1, -1, 0, 1, 1, 1 };
int dc[9] = { 0, -1, -1, 0, 1, 1, 1, 0, -1 }; //index�� 1���� 8���� ���
// ��, ��, ��, ��, ��, ��, ��, ��

int drS[5] = { 0, -1, 0, 1, 0 };
int dcS[5] = { 0, 0, -1, 0, 1  }; //index�� 1���� 4���� ���
// ��, ��, ��, ��

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

			//�̵��� ������ ���
			fish[i].R = NR;
			fish[i].C = NC;
			fish[i].dir = dir;

			fish_cnt_map[R][C]--;
			fish_cnt_map[NR][NC]++;

			break;
		} //�̵��� �Ұ����� ��� �ƹ��� ��ȭ���� ����
	}
}

vector<int> max_path;
int max_cnt;
bool visit[5][5];

void Select_shark_path(int R, int C, int cnt, vector<int> path)
{
	if (path.size() == 3)
	{
		if (cnt > max_cnt) //�켱������ ���� ������ Ž����
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
		if (dead_flag) smell_map[sharkR][sharkC] = 3; //�ٷ� 1�� ����
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