// ★ 풀이가 바로 이해가 되긴 했는데 스스로 생각해내지는 못했다! DP 연습 더 필요!
#include <vector>
#include <set>
#include <string>
using namespace std;
// 생각한 방식 + AI의 도움을 받은 방식: 연산 가능성을 다 늘어놓고 그 중 최소값을 취하는 방식
// 다만! 값을 기준으로 DP를 짜는 게 아니라 N의 사용 횟수를 기준으로 판을 짜야 함
// (역으로 생각해야 함 → 숫자에서 최소 N의 개수를 찾는게 아니라 N의 개수로 숫자를 만들어두고 찾기)

int answer = -1;
set<int> DP[9];
// DP[i] = N을 i번 사용하여 만들 수 있는 모든 수의 집합 (i의 최대값은 8, 8을 초과할 경우 정답은 -1)
// DP[n]은 DP[j]와 DP[n-j]의 결과들을 사칙연산 + N이 n번 나오는 수

int solution(int N, int number)
{
    DP[1].insert(N); // N을 1번 사용하여 만들 수 있는 수는 N밖에 없음
    if (N == number) return 1;

    int num = N;
    for (int i = 2; i <= 8; i++) // (1) N이 n번 나오는 수
    {
        num = (num * 10) + N;
        DP[i].insert(num);
        if (num == number) return i;
    }

    for (int i = 2; i <= 8; i++) // N을 사용하는 횟수
    {
        // (2) DP[j]와 DP[i-j]를 사칙연산한 결과
        for (int j = 1; j < i; j++)
        {
            set<int>::iterator iter1;
            set<int>::iterator iter2;

            for (iter1 = DP[j].begin(); iter1 != DP[j].end(); iter1++)
            {
                for (iter2 = DP[i - j].begin(); iter2 != DP[i - j].end(); iter2++)
                {
                    int num = 0;

                    // 더하기
                    num = *iter1 + *iter2;
                    if (num == number) return i;
                    if (num != 0) DP[i].insert(num); // 0을 저장할 경우 DP[i+a]에서 DP[i]의 숫자가 나올 수 있음

                    // 빼기
                    num = *iter1 - *iter2;
                    if (num == number) return i;
                    if (num != 0) DP[i].insert(num);

                    // 빼기 (순서 변경)
                    num = *iter2 - *iter1;
                    if (num == number) return i;
                    if (num != 0) DP[i].insert(num);

                    // 곱하기
                    num = *iter1 * *iter2;
                    if (num == number) return i;
                    if (num != 0) DP[i].insert(num);

                    // 나누기
                    num = *iter1 / *iter2;
                    if (num == number) return i;
                    if (num != 0) DP[i].insert(num);

                    // 나누기 (순서 변경)
                    num = *iter2 / *iter1;
                    if (num == number) return i;
                    if (num != 0) DP[i].insert(num);
                }
            }
        }
    }
    return answer;
}