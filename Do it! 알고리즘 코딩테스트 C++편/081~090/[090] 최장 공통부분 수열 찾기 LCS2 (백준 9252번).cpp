// 문제: https://www.acmicpc.net/problem/9252
#include <iostream>
#include <string>
using namespace std;

// 부분 수열은 순서가 중요 + 연속일 필요는 없음
// 가장 긴 부분 수열을 구함

string A, B; // A가 i행, B가 j열
int D[1001][1001]; // i행까지의 문자열과 j열까지의 문자열로 만들 수 있는 최장 공통 수열의 길이

int main()
{
	cin >> A >> B;

	// i행 0열 초기화
	for (int i = 0; i < A.length(); i++)
	{
		if (A[i] == B[0]) D[i][0] = 1;
		else if (i == 0) D[i][0] = 0;
		else D[i][0] = D[i - 1][0]; // B가 하나이기 때문에 이전 경우를 반영해옴
	}
	// 0행 j열 초기화
	for (int j = 0; j < B.length(); j++)
	{
		if (A[0] == B[j]) D[0][j] = 1;
		else if (j == 0) D[0][j] = 0;
		else D[0][j] = D[0][j - 1]; // A가 하나이기 때문에 이전 경우를 반영해옴
	}

	// 점화식 채우기 (i번째 A까지의 문자열과 j번째 B까지 문자열에서 최장 공통 수열의 길이)
	for (int i = 1; i < A.length(); i++)
	{
		for (int j = 1; j < B.length(); j++)
		{
			if (A[i] == B[j]) // 현재 위치에서 문자가 같을 때
			{
				D[i][j] = D[i - 1][j - 1] + 1; // 이전 경우에 +1 (수열에 문자 추가)
			}
			else // 현재 위치에서 문자가 다를 때
			{
				D[i][j] = max(D[i][j - 1], D[i - 1][j]); // 왼쪽 혹은 위쪽 경우를 따라감 (최대인 경우를 따라감)
			}
		}
	}

	cout << D[A.length() - 1][B.length() - 1] << '\n';
	string answer = "";

	// LCS 만들기
	int i = A.length() - 1;
	int j = B.length() - 1;
	while (1)
	{
		if (A[i] == B[j])
		{
			answer = A[i] + answer;
			i--;
			j--;
		}
		else
		{
			if (i == 0 || j == 0)
			{
				if (i == 0 && j == 0) break;
				else if (i == 0) j--;
				else i--;
			}
			else
			{
				if (D[i - 1][j] > D[i][j - 1]) i--;
				else j--;
			}
		}

		if (answer.length() == D[A.length() - 1][B.length() - 1]) break;
	}

	cout << answer;
	return 0;
}
// 이것도 진짜 모르겠다 바로 풀이 참고했음 (아직 DP 감각이 없다)

// 처음에 좀 틀려서 디버깅을 진행했는데
// LCS 만들기 부분에 오류가 좀 있었음 → while 조건을 잘못 사용함 (i==0, j==0인 경우는 따로 처리)