// 문제: https://www.acmicpc.net/problem/13398
#include <iostream>
#include <vector>
using namespace std;

int N;
vector<long long> num;

vector<long long> L; // L[n] = 0에서 n까지 수에서 n을 포함하여 연속 최대값 (왼쪽에서 오른쪽으로 더함)
vector<long long> R; // R[n] = N에서 n까지 수에서 n을 포함하여 연속 최대값 (오른쪽에서 왼쪽으로 더함)

int main()
{
	cin >> N;
	num.resize(N);
	for (int i = 0; i < N; i++) cin >> num[i];

	L.resize(N);
	R.resize(N);

	L[0] = num[0];
	R[N - 1] = num[N - 1];

	// L
	for (int i = 1; i < N; i++) L[i] = max(num[i], L[i - 1] + num[i]);

	// R
	for (int i = N - 2; i >= 0; i--) R[i] = max(num[i], R[i + 1] + num[i]);

	// 최대값 찾기
	int answer = L[0];
	for (int i = 0; i < N; i++)
	{
		if (L[i] > answer) answer = L[i]; // L중에서 최대값
		if (R[i] > answer) answer = R[i]; // R중에서 최대값
		if (i != 0 && i != N - 1) // i를 삭제하는 경우에서 최대값
		{
			// L이랑 R은 각각 i를 포함해서 최대인 연속값이기 때문에 아래 공식이 성립
			if (L[i - 1] + R[i + 1] > answer) answer = L[i - 1] + R[i + 1];
		}
	}

	cout << answer;
	return 0;
}
// 좀 어렵긴 하다 결국 풀이를 참고했음