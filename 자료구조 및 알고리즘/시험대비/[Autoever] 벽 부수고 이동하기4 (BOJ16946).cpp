// 문제: https://www.acmicpc.net/problem/16946
// 알고리즘: 그래프
#include <iostream>
#include <string>
using namespace std;

// 첫번째 시도 → 단순 DFS로 시도했으나 시간초과 (N*M의 최대값이 10^6, 최악의 경우 시간복잡도가 10^12)
// 두번째 시도 → 그래프를 이용한 메모이제이션

// 벽(1)을 기준으로 생각하지 말고 빈공간(0)을 기준으로 생각
// 빈공간을 탐색하면서 연결된 빈공간을 그룹화(ID 부여, 각 ID 당 소속된 빈공간의 개수 기록)
// 벽이랑 연결된 빈공간의 ID로 바로 개수를 가져와서 사용 → 메모이제이션
// ★ 예전에 비슷한 문제를 풀어본 적 있다! 한번 탐색한 결과를 재활용하는 기법! (보통 그룹화로 많이 이용되는 듯)

int N, M;
int Map[1000][1000];

int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0, 1, 0, -1 };

int Group[1000][1000];
int Group_cnt[1000001]; // N*M = 1000000

bool visit[1000][1000];
void Make_Group(int R, int C, int index) // 빈공간 그룹화
{
	if (visit[R][C]) return;
	visit[R][C] = true;
	
	Group[R][C] = index;
	Group_cnt[index]++;

	for (int i = 0; i < 4; i++)
	{
		int NR = R + dr[i];
		int NC = C + dc[i];

		if (NR < 0 || NR >= N || NC < 0 || NC >= M) continue;
		if (visit[NR][NC]) continue;
		if (Map[NR][NC] == 1) continue;

		Make_Group(NR, NC, index);
	}
}

int main()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		string st;
		cin >> st;
		for (int j = 0; j < M; j++) Map[i][j] = st[j] - '0';
	}

	// 빈공간 그룹화
	int index = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (Map[i][j] == 1) continue;
			if (visit[i][j]) continue;

			index++;
			Make_Group(i, j, index);
		}
	}

	// 벽에 대한 이동 수 구하기
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (Map[i][j] == 0) cout << 0;
			else
			{
				int answer = 1; // 자기자신
				int visit_group[4] = { 0, 0, 0, 0 };

				for (int k = 0; k < 4; k++)
				{
					int NR = i + dr[k];
					int NC = j + dc[k];

					if (NR < 0 || NR >= N || NC < 0 || NC >= M) continue;
					int idx = Group[NR][NC];

					bool can_sum = true;
					for (int h = 0; h < k; h++)
					{
						if (visit_group[h] == idx)
						{
							can_sum = false;
							break;
						}
					}

					if (can_sum)
					{
						answer += Group_cnt[idx];
						visit_group[k] = idx;
					}
				}
				cout << answer % 10;
			}
		}
		cout << '\n';
	}
	return 0;
}

// ★ 자잘한 실수
// (1) 가능한 그룹의 수는 최대 N*M이다 (정황상 N*M/2가 최대지만 혹시 모르니까)
// (2) 시간초과 → 이동 수를 구할 때 Group(1000001) 크기의 visit 배열을 초기화했는데, 이러면 시간이 너무 오래 걸림
//			    → 크기 4의 visit 배열을 선언해서 사용 (memset의 시간복잡도는 O(N))