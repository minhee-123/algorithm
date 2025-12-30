// 문제: https://www.acmicpc.net/problem/14501
#include <iostream>
#include <vector>
using namespace std;

int N, D[17]; // D[i] = i번째 날부터 퇴사일까지 벌 수 있는 최대 수입
vector<pair<int, int>> counsel;

int main()
{
	cin >> N;
	counsel.resize(N + 2);
	for (int i = 1; i <= N; i++)
	{
		cin >> counsel[i].first >> counsel[i].second;
	}

	D[N + 1] = 0;
	for (int i = N; i >= 1; i--)
	{
		int time = i + counsel[i].first;

		if (time > N + 1) D[i] = D[i + 1]; // i번째 날의 상담을 할 수 없음
		else // i번째 날의 상담을 할 수 있음
		{
			// i번째 상담을 하지 않고 i+1번째부터 가져올지
			// i번째 상담을 적용할지
			D[i] = max(D[i + 1], D[i + counsel[i].first] + counsel[i].second);
		}
	}

	cout << D[1];
	return 0;
}

// 사실 N이 최대 15이기 때문에 i번째 날을 무조건 포함하는 조건으로 DFS를 돌려도 됨
// 그래도 가장 최적화된 풀이 방법은 위와 같은 DP (시간이나 메모리 측면에서)