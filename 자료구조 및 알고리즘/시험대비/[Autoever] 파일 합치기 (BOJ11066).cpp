// 문제: https://www.acmicpc.net/problem/11066
// 알고리즘: DP
#include <iostream>
#include <cstring>
using namespace std;

int T, K;
int chapter[500];
long long sum[500]; //누적합 기록
long long DP[500][500]; // DP[i][j] = i번째 장부터 j번째 장까지 합치는 데 드는 최소 비용
// DP[i][j] = min(DP[i][k] + DP[k+1][j]) + (i부터 j까지의 합)
// i부터 j까지 구간의 최소 비용 + 마지막으로 합칠 때 비용

/* 1차원 DP 테이블은 앞에서부터 순서대로 쌓아가는 구조일 때 사용
* 현재 문제는 중간에 있는 파일들끼리 먼저 합쳐질 수도 있는 상황
* → 따라서 범위를 나타낼 수 있는 2차원 DP 테이블을 사용해야 함
* → 추가로 구간을 나누어서 계산을 하는 유형이기 때문에 구간 DP */

/* 대표적인 구간 DP 유형 문제 → DP에서 많이 보이는 유형이니까 암기 */
/* 이전에 풀었던 문제중 행렬 곱셈 순서 문제와 같은 유형 (구간 DP) */

long long calcu(int s, int e)
{
	if (DP[s][e] != -1) return DP[s][e]; // 이미 답이 있는 경우 (메모이제이션)

	if (e - s == 0) return DP[s][e] = 0; // 구간의 길이가 0인 경우(자기 자신은 합치지 않음! 합칠 수 없어서 비용이 없음!)
	if (e - s == 1) return DP[s][e] = chapter[s] + chapter[e]; // 구간의 길이가 1인 경우(원소가 두개)

	for (int k = s; k < e; k++)
	{
		long long last_cost;
		if (s == 0) last_cost = sum[e];
		else last_cost = sum[e] - sum[s - 1];

		long long temp = calcu(s, k) + calcu(k + 1, e) + last_cost;

		if (DP[s][e] == -1) DP[s][e] = temp;
		else DP[s][e] = min(DP[s][e], temp);
	}
	return DP[s][e];
}

void Solution()
{
	memset(chapter, 0, sizeof(chapter));
	memset(sum, 0, sizeof(sum));
	memset(DP, -1, sizeof(DP)); // 전체 초기화

	cin >> K;
	for (int i = 0; i < K; i++)
	{
		cin >> chapter[i];

		if (i == 0) sum[i] = chapter[i];
		else sum[i] = sum[i - 1] + chapter[i];
	}
	cout << calcu(0, K - 1) << '\n';
}

int main()
{
	cin >> T;
	for (int i = 0; i < T; i++) Solution();
	return 0;
}

// 풀다가 사소하게 실수한 부분
// → DP[s][s] = 0이다! 원소가 하나인 경우 합칠 수가 없어서 합치는 비용이 없다!