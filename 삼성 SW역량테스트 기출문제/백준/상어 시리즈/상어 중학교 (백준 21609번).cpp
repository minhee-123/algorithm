// ����: https://www.acmicpc.net/problem/21609

/* ������� ���� �ɷȴ�! */
/*
(1) sort�� ���� comp �Լ��� �ۼ��� �� return�� �����ϰų� �� ������ �̻��ϰ� �ۼ���
(2) ���� ������ ������
	�� ũ�Ⱑ ���� ū ��� �׷��� �����̶�� ������ ����� ���� ���� ���� �׷��� ���� ã�´� (��� ���� ������ �־���)
(3) ���� ��ġ �Ǽ�
	�� location�� ����� �ϴ� ��ġ�� row�� �ۼ���
(4) visit�̶� visit_rainbow ȥ�� ���
	�� ���������� �׷�ȭ�� �� �ٸ� �׷�� �ߺ��ؼ� �����ϰ� ��
	�� �׷��� visit�� ���� ó������� �� (�̰� �� ȥ���ؼ� ����߾���)
	�� �ٵ� ���� ������ ����� 3�� �Ǽ� ������ Ʋ�ȴ� ���� ���� ���� (3���̶� 4���� ���ÿ� ��ħ)
*/

#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

// ������ ĭ �� �����¿�
// ������ ��� -1 / ������ ��� 0 / �Ϲ� ��� 1~M

int score = 0;

int N, M;
int Map[20][20];

int dr[4] = { 1, -1, 0, 0 };
int dc[4] = { 0, 0, 1, -1 };

void Input()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++) cin >> Map[i][j];
	}
}

vector<vector<pair<int, int>>> group;
vector<pair<int, int>> temp_group;
bool visit[20][20];
bool visit_rainbow[20][20];

void make_group(int R, int C, int value)
{
	if (Map[R][C] == 0) visit_rainbow[R][C] = true;
	else visit[R][C] = true;

	temp_group.push_back({ R, C });

	for (int i = 0; i < 4; i++)
	{
		int NR = R + dr[i];
		int NC = C + dc[i];

		if (NR < 0 || NR >= N || NC < 0 || NC >= N) continue;
		if (Map[NR][NC] == value && visit[NR][NC]) continue;
		if (Map[NR][NC] == 0 && visit_rainbow[NR][NC]) continue;
		
		if (Map[NR][NC] == 0 || Map[NR][NC] == value)
		{
			make_group(NR, NC, value);
		}
	}
}

void find_group()
{
	memset(visit, false, sizeof(visit));
	group.clear();

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (Map[i][j] <= 0 || visit[i][j]) continue;
			memset(visit_rainbow, false, sizeof(visit_rainbow));

			temp_group.clear();
			make_group(i, j, Map[i][j]);

			if (temp_group.size() >= 2) group.push_back(temp_group);
		}
	}
}

bool game_finish = false;

bool comp_mini(pair<int, int> A, pair<int, int> B)
{
	bool rainbow_A = false;
	bool rainbow_B = false;

	if (Map[A.first][A.second] == 0) rainbow_A = true;
	if (Map[B.first][B.second] == 0) rainbow_B = true;

	if (rainbow_A != rainbow_B)
	{
		if (rainbow_A) return false;
		else return true;
	}
	else
	{
		if (A.first != B.first) return A.first < B.first;
		else return A.second < B.second;
	}
}

bool comp_All(vector<pair<int, int>> A, vector<pair<int, int>> B)
{
	if (A.size() != B.size()) return A.size() > B.size(); //����� ū �׷��� �켱
	else
	{
		int cntA = 0;
		int cntB = 0;

		for (int i = 0; i < A.size(); i++)
		{
			if (Map[A[i].first][A[i].second] == 0) cntA++;
			if (Map[B[i].first][B[i].second] == 0) cntB++;
		}

		if (cntA != cntB) return cntA > cntB; //������ ����� ���� ���� �׷��� �켱
		else
		{
			if (A[0].first != B[0].first) return A[0].first > B[0].first; //���� ū �׷��� �켱
			else return A[0].second > B[0].second; //���� ū �׷��� �켱
		}
	}
}

void select_group()
{
	find_group();

	if (group.empty()) game_finish = true;
	else
	{
		for (int i = 0; i < group.size(); i++) sort(group[i].begin(), group[i].end(), comp_mini);
		sort(group.begin(), group.end(), comp_All);

		vector<pair<int, int>> max_group = group[0];

		int num = max_group.size();
		score += (num * num);

		for (int i = 0; i < max_group.size(); i++)
		{
			int R = max_group[i].first;
			int C = max_group[i].second;

			Map[R][C] = -10; //����� ���� ������ -10���� ����
		}
	}
}

void gravity()
{
	for (int col = 0; col < N; col++)
	{
		for (int row = N - 1; row >= 0; row--)
		{
			if (Map[row][col] == -1) continue;

			int value = Map[row][col];
			int location = row;

			while (location < N - 1)
			{
				if (Map[location + 1][col] == -10)
				{
					Map[location][col] = -10;
					location++;
					Map[location][col] = value;
				}
				else break;
			}
		}
	}
}

void rotation()
{
	int rotated[20][20];

	for (int i = 0; i <= N - 1; i++)
	{
		for (int j = 0; j <= N - 1; j++)
		{
			rotated[i][j] = Map[j][(N - 1) - i]; //�ݽð� ���� ȸ��
		}
	}

	for (int i = 0; i < N; i++) 
	{
		for (int j = 0; j < N; j++) Map[i][j] = rotated[i][j]; //ȸ���� �� ī��
	}
}

void AutoPlay()
{
	Input();

	while (1)
	{
		select_group();
		if (game_finish) break;

		gravity();
		rotation();
		gravity();
	}
}

int main()
{
	AutoPlay();

	cout << score;
	return 0;
}