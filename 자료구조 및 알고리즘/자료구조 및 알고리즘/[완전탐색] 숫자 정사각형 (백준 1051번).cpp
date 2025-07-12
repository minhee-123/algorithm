//브루트포스 알고리즘 → 완전탐색 방법 (모든 경우를 살펴봄으로써 답을 구하는 알고리즘)
//모든 경우를 살펴보기 때문에 100% 정답 도출 (다만 효율이 떨어지며 제한시간에 걸릴 수도 있음)
// 숫자 정사각형 (https://www.acmicpc.net/problem/1051)

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool comp(int a, int b) { return a > b; }

int main()
{
	int MAP[50][50];
	int N, M;
	cin >> N >> M;

	for (int i = 0; i < N; i++)
	{
		string temp;
		cin >> temp;
		for (int j = 0; j < M; j++)
		{
			MAP[i][j] = temp[j] - '0'; //string을 이렇게 이용하면 연속된 숫자를 하나씩 받을 수 있음
		}
	}

	int NM_small = N < M ? N : M;
	vector<int> size;
	size.push_back(1);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			for (int k = 1; k < NM_small; k++)
			{
				if (i + k < N && j + k < M)
				{
					if (MAP[i][j] == MAP[i + k][j] && MAP[i][j] == MAP[i + k][j + k] && MAP[i][j] == MAP[i][j + k])
					{
						size.push_back((k + 1) * (k + 1));
					}
				}
			}
		}
	}
	sort(size.begin(), size.end(), comp);
	cout << size[0];
	return 0;
}