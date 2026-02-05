#include <vector>
using namespace std;

int DP[501][501];
// DP[i][j] = 높이 i에서 j번째 위치가 가지는 거쳐간 숫자의 최대값
// i와 j의 범위가 작아 완탐 → 꼭대기와 가장 왼쪽을 0으로 생각 (DP보다는 메모이제이션 활용 문제)

int solution(vector<vector<int>> triangle)
{
    int maxH = triangle.size();
    DP[0][0] = triangle[0][0];

    for (int H = 1; H < maxH; H++)
    {
        for (int W = 0; W < triangle[H].size(); W++)
        {
            if (W == 0) DP[H][W] = DP[H - 1][W] + triangle[H][W];
            else if (W == triangle[H].size() - 1) DP[H][W] = DP[H - 1][W - 1] + triangle[H][W];
            else DP[H][W] = max(DP[H - 1][W - 1] + triangle[H][W], DP[H - 1][W] + triangle[H][W]);
        }
    }

    int answer = 0;
    for (int W = 0; W < triangle[maxH - 1].size(); W++) answer = max(answer, DP[maxH - 1][W]);

    return answer;
}