// 문제: https://www.acmicpc.net/problem/14003
// 알고리즘: DP 및 이진탐색
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

int N;
vector<int> A; // 문제에서 주어지는 수열
vector<int> B; // B[i] = i 길이 부분 수열의 마지막 원소
vector<int> DP; // DP[i] = i번째 원소를 포함하는 가장 긴 증가하는 부분 수열의 길이

int main()
{
	cin >> N;
	A.resize(N + 1);
	B.resize(N + 1);
	DP.resize(N + 1);
	for (int i = 1; i <= N; i++) cin >> A[i];

	B[1] = A[1]; // 시작값
	DP[1] = 1; // 시작값

	int answer_len = 1; // 정답

	// 가장 긴 증가하는 부분 수열의 길이 찾기
	for (int i = 2; i <= N; i++)
	{
		int now = A[i];

		if (now > B[answer_len])
		{
			answer_len++;
			B[answer_len] = now;
			DP[i] = answer_len;
		}
		else if (now == B[answer_len]) DP[i] = answer_len;
		else // now < B[answer_len]
		{
			// now와 같은, 혹은 보다 큰 값이 처음 나오는 위치(길이)
			int len = lower_bound(B.begin() + 1, B.begin() + answer_len + 1, now) - B.begin();
			// ★ 디버깅한 부분!! 이진 탐색은 정렬되어 있다는 조건 하에서만 사용할 수 있다!!
			// → 처음에는 lower_bound를 전체 범위에서 돌려버렸는데 이러면 정렬되어 있지 않은 뒷 부분까지 포함하게 됨 (결과가 보장되지 않음)
			// → 의미있는 구간만 탐색하도록 정의를 바꿔야 함
			// → 참고로 마지막 범위가 answer_len + 1인데 모든 STL 알고리즘의 범위는 [first, last), first 포함 last 미포함이기 때문

			B[len] = now;
			DP[i] = len;
		}
	}
	cout << answer_len << '\n';

	// 가장 긴 증가하는 부분 수열 찾기
	stack<int> box;
	int len = answer_len;

	for (int i = N; i >= 1; i--)
	{
		if (DP[i] == len)
		{
			box.push(A[i]);
			len--;
		}

		if (len == 0) break;
	}

	while (!box.empty())
	{
		cout << box.top() << ' ';
		box.pop();
	}
	return 0;
}