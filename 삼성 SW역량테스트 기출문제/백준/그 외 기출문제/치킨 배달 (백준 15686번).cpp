//문제: https://www.acmicpc.net/problem/15686
//도시의 치킨 거리를 최소화해야 함 (치킨거리 → 집과 가장 가까운 치킨집 사이의 거리)
//N의 최대값이 50이고 M의 최대값이 13이니까 시간복잡도 영향이 크지 않음
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

// (1) M개의 치킨집을 고르는 모든 조합을 구하고
// (2) 각 조합(선택된 치킨집)에 대해 치킨 거리를 구함
// (3) 2번에서 최소 치킨 거리를 구해서 정답으로 출력

int N, M;
int MAP[51][51]; // 0(빈칸), 1(집), 2(치킨집)
vector<pair<int, int>> chicken; //치킨 집의 위치
vector<pair<int, int>> home; //집의 위치

vector<int> num;
vector<vector<int>> selec; //M개의 치킨집을 선택한 조합의 정보를 저장
int disSum = 0; //각 조합에 대해 모든 집의 치킨 거리
int minSum = 1000000; //최소 치킨 거리

void combination() //next_permutation은 bool 배열이 오름차순으로 정렬되어 있어야 함 (permutation 자체가 오름차순 정렬 필요)
{
	vector<bool> temp(num.size(), true);
	for (int i = 0; i < num.size() - M; i++) temp[i] = false;
	//flase가 앞에 전체개수-M, 그 뒤로 true가 M만큼 채워짐 (오름차순 정렬 -> flase가 true보다 앞에 있어야함 -> true의 개수가 곧 조합 요소의 수)

	do 
	{
		vector<int> contain;
		for (int i = 0; i < num.size(); i++)
		{
			if (temp[i]) contain.push_back(i);
		}
		selec.push_back(contain);

	} while (next_permutation(temp.begin(), temp.end()));
} // 조합 생성 함수

void distance(int order)
{
	for (int i = 0; i < home.size(); i++)
	{
		int HR = home[i].first;
		int HC = home[i].second;

		int dis = 1000000;
		for (int j = 0; j < selec[order].size(); j++)
		{
			int chicken_index = selec[order][j];
			int CR = chicken[chicken_index].first;
			int CC = chicken[chicken_index].second;

			int now_dis = abs(HR - CR) + abs(HC - CC);
			if (now_dis < dis) dis = now_dis;
		}

		disSum += dis;
	}
}

int main()
{
	cin >> N >> M;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			int val;
			cin >> val;
			
			MAP[i][j] = val;
			if (val == 1) home.push_back({ i, j });
			if (val == 2) chicken.push_back({ i, j });
		}
	}
	for (int i = 0; i < chicken.size(); i++) num.push_back(i);

	combination(); //치킨집 조합 생성

	for (int i = 0; i < selec.size(); i++)
	{
		disSum = 0;
		distance(i);

		if (disSum < minSum) minSum = disSum;
	}

	cout << minSum;
	return 0;
}
// 너무 오랜만에 코테 문제를 풀어서 감이 안 잡혔을 뿐이지 어려운 문제는 아니다
// 데이터의 범위가 작으니까 브루트포스 (이때 조합을 구현 → 조합을 구현하는 방법만 기억해두자)