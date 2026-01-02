// 문제: https://www.acmicpc.net/problem/1915
#include <iostream>
#include <string>
using namespace std;

int N, M;
int Map[1000][1000];
int D[1000][1000]; 
// D[i][j] = (i, j) 위치를 우측끝으로 만들 수 있는 가장 큰 정사각형의 변 길이

int answer = 0;

int main()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		string st;
		cin >> st;
		for (int j = 0; j < M; j++)
		{
			Map[i][j] = st[j] - '0';
			if (Map[i][j] == 1) answer = 1;
		}
	}

	for (int i = 0; i < N; i++) D[i][0] = Map[i][0]; // 0행 초기화
	for (int j = 0; j < M; j++) D[0][j] = Map[0][j]; // 0열 초기화

	for (int i = 1; i < N; i++)
	{
		for (int j = 1; j < M; j++)
		{
			if (Map[i][j] == 0) D[i][j] = 0; // 해당 위치가 0이라면 정사각형을 만들 수 없음
			else
			{
				if (D[i - 1][j - 1] == 0) D[i][j] = 1; // 대각선이 0이라면 본인이 최대임 (길이 = 1)
				else if (D[i - 1][j] == 0 || D[i][j - 1] == 0) D[i][j] = 1; // 왼쪽 혹은 위쪽이 0이라면 본인이 최대임 (길이 = 1)
				else // 정사각형의 길이 확장
				{
					// 위, 왼쪽, 왼쪽위대각선의 DP테이블 값이 다를 경우
					// 최대값을 가져오는 게 아니라 최소값을 가져와야 함 (+1)
					// → 모두가 동시에 최소 길이를 확장해야 하기 때문
					// → 따라서 최소 길이를 기준으로 확장해야 함 (최소값에 +1)

					D[i][j] = min(D[i - 1][j - 1], min(D[i - 1][j], D[i][j - 1])) + 1;
				}
			}

			if (D[i][j] > answer) answer = D[i][j];
		}
	}

	cout << answer * answer;
	return 0;
}
// 정사각형의 길이 확장 조건을 잘못 설정했음
// (1) 처음에는 단순히 위, 왼쪽, 왼쪽위대각선이 같으면 +1, 아니면 최대값을 가져옴
// (2) 문제는 그럴 경우 어느 한쪽에 구멍이 있어도 큰 값이 계속 전파됨 → 오답 발생
// 해당 부분을 고쳐야함!! 그래도 DP테이블 정의는 잘 했음!!