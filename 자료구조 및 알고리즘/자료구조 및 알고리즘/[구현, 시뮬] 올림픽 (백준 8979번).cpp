//올림픽 (https://www.acmicpc.net/problem/8979)

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct NA
{
	int name;
	int gold; //금메달 수
	int silver; //은메달 수
	int bronze; //동메달 수
};

bool cmp(NA A, NA B)
{
	if (A.gold > B.gold) return true;
	else if (A.gold == B.gold)
	{
		if (A.silver > B.silver) return true;
		else if (A.silver == B.silver)
		{
			if (A.bronze > B.bronze) return true;
		}
	}
	return false;
}

int main()
{
	//입력
	int N, K;
	cin >> N >> K;
	vector<NA> nation;
	for (int i = 0; i < N; i++)
	{
		int temp1, temp2, temp3, temp4;
		cin >> temp1 >> temp2 >> temp3 >> temp4;
		nation.push_back({ temp1, temp2, temp3, temp4 });
	}

	//정렬
	sort(nation.begin(), nation.end(), cmp);

	//등수 매기기
	vector<int> nation_name; //국가이름
	vector<int> rank; //등수
	nation_name.push_back(nation[0].name);
	rank.push_back(1);
	int cnt = 1;
	for (int i = 1; i < N; i++)
	{
		nation_name.push_back(nation[i].name);
		if (nation[i].gold == nation[i - 1].gold && nation[i].silver == nation[i - 1].silver && nation[i].bronze == nation[i - 1].bronze)
		{
			rank.push_back(rank[i - 1]);
			cnt++;
		}
		else
		{
			rank.push_back(rank[i - 1] + cnt); //(예시) 공동 2등이 나오면 다음은 4등
			cnt = 1;
		}
	}

	//출력
	for (int i = 0; i < N; i++)
	{
		if (nation_name[i] == K)
		{
			cout << rank[i];
		}
	}
	return 0;
}