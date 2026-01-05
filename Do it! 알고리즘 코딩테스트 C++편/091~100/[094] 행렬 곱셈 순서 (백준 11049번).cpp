// 문제: https://www.acmicpc.net/problem/11049
// 톱다운 방식의 재귀를 적용하는 DP
// 아이디어가 좀 어려워서 풀이를 먼저 참고 → 재귀로 푸는 DP도 익혀야 함
#include <iostream>
#include <vector>
using namespace std;

int N;
pair<int, int> matrix[501];
long long D[501][501];
// D[i][j] = i번째에서 j번째 행렬을 합치는 데 필요한 최소 연산
// 1에서 N까지의 최소 연산을 구하기 위해서는 (1, N-1)(N, N) / (1, N-2)(N-1, N) ... 등등 다 비교해야 함

long long calcu(int s, int e)
{
	if (D[s][e] != -1) return D[s][e]; // 계산한 적이 있으면 가져와서 사용(메모제이션)

	if (e - s == 0) return D[s][e] = 0; // 행렬이 1개인 경우
	if (e - s == 1) return D[s][e] = matrix[s].first * matrix[e].first * matrix[e].second; // 행렬이 2개인 경우

	// 행렬이 3개 이상인 경우
	for (int i = s; i < e; i++)
	{
		long long temp = calcu(s, i) + calcu(i + 1, e) + (matrix[s].first * matrix[i + 1].first * matrix[e].second);
		// 예시로 D[1][3] = D[1][1] + D[2][3] + (A1[row] * A2[row] * A3[col])
		// 두 행렬의 최소 연산 횟수를 더하고 + 마지막 두 행렬을 합치는 곱셈 횟수를 더함

		if (D[s][e] == -1) D[s][e] = temp;
		else D[s][e] = min(D[s][e], temp);
	}
	return D[s][e];
}

int main()
{
	cin >> N;
	for (int i = 1; i <= N; i++) cin >> matrix[i].first >> matrix[i].second;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++) D[i][j] = -1;
	}

	cout << calcu(1, N);
	return 0;
}