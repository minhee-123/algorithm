// 문제: https://www.acmicpc.net/problem/12865
#include <iostream>
#include <vector>
using namespace std;

// N개의 물건, 각 물건의 무게 W와 가치 V
// 가치 V만큼 즐거움, 최대 K만큼의 무게만을 넣을 수 있는 배낭 → 배낭에 넣을 수 있는 물건의 가치 최대값

int N, K;
vector<pair<int, int>> thing; // 물건의 무게, 가치

int DP[101][100001];
// DP[i][j] = i번째 물건까지 고려했을 때 j이하의 무게제한에서 얻을 수 있는 최대 가치
// 전역변수로 선언했기 때문에 자동 0으로 초기화

int main()
{
	cin >> N >> K;
	thing.resize(N + 1);
	for (int i = 1; i <= N; i++) cin >> thing[i].first >> thing[i].second;
	
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= K; j++)
		{
			int now_w = thing[i].first;
			int now_v = thing[i].second;

			if (now_w > j) DP[i][j] = DP[i - 1][j]; // i번째 물건을 넣을 수 없음 (무게 초과)
			else // now_w <= j (현재 물건의 무게가 배낭의 무게제한 이하인 경우)
			{
				// (1) i번째 물건을 포함하지 않는 경우
				// (2) i번째 물건을 포함하는 경우 → DP[i-1][j-물건무게] 가치에 현재 물건 가치를 더한 값
				DP[i][j] = max(DP[i - 1][j], DP[i - 1][j - now_w] + now_v);
			}
		}
	}

	cout << DP[N][K];
	return 0;
}