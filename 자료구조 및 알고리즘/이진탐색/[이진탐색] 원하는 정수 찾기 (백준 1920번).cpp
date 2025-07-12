// 문제: https://www.acmicpc.net/problem/1920

// 이진 탐색은 중간 지점을 잡아서 영역을 좁혀나가는 탐색법으로 속도가 매우 빠름(logn)
// ★ 단 이진탐색은 정렬된 배열에서만 사용할 수 있는 방법
// 투포인터 알고리즘을 이용한 탐색법

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N;
	cin >> N;

	vector<int> A(N, 0);
	for (int i = 0; i < N; i++) cin >> A[i];
	sort(A.begin(), A.end());

	int M;
	cin >> M;

	for (int i = 0; i < M; i++)
	{
		int target;
		cin >> target;

		int start = 0;
		int end = N - 1;

		bool flag = true;
		while (start <= end)
		{
			int mid = (start + end) / 2;

			if (A[mid] == target)
			{
				flag = false;
				break;
			}
			else if (A[mid] > target) end = mid - 1;
			else start = mid + 1;
		}

		if (flag) cout << 0 << '\n'; //이걸 위에 if문 안에 넣으면 시간초과가 발생함 (왜지)
		else cout << 1 << '\n';
	}
	return 0;
}