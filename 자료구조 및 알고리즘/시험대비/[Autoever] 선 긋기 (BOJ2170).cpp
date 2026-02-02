// 문제: https://www.acmicpc.net/problem/2170
// 알고리즘: 스위핑
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;
vector<pair<int, int>> location;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	location.resize(N);
	for (int i = 0; i < N; i++) cin >> location[i].first >> location[i].second;

	sort(location.begin(), location.end()); // 첫번째(시작점) 원소를 기준으로 정렬

	int s = location[0].first;
	int e = location[0].second;
	long long answer = 0;

	for (int i = 1; i < N; i++)
	{
		if (location[i].first <= e) // 다음 시작점이 범위 내에 있는 경우 (선 연장)
		{
			e = max(e, location[i].second);
		}
		else if (location[i].first > e) // 다음 시작점이 범위 다음에 있는 경우 (새로운 선 등장)
		{
			answer += e - s; // 현재 선 길이 계산
			s = location[i].first; // 다음 선 시작점
			e = location[i].second; // 다음 선 종료점
		}
	}
	answer += e - s; // 마지막 선 길이 계산

	cout << answer;
	return 0;
}

// 처음에 map을 사용한 좌표 압축을 시도했으나
// BUT map을 사용한 좌표 압축은 O(logN)의 시간복잡도로 시간의 많은 부분을 소요 (시간초과 발생)

// 좌표 압축은 구간의 중첩 횟수 혹은 특정 좌표의 값을 계속 참조해야 할 때만 강력
// BUT 해당 문제는 단순히 선들의 총 길이를 구하면 됨 (정렬을 이용)

// ★ 좌표 압축 문제가 아니라 단순히 스위핑(한번씩 스쳐가듯 확인) 문제 → 어렵게 생각할 것 없이 단순히 정렬해서 더해나가면 됨