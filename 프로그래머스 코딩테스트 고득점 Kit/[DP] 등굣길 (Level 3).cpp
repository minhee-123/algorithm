#include <vector>
#include <queue>
using namespace std;
#define num 1000000007
// 오른쪽과 아래쪽으로만 움직여 집에서 학교까지 갈 수 있는 최단 경로의 개수
// BFS로 처음 시도했으나 시간초과 발생(중복방문으로 큐 터짐) → 무조건 DP를 적용해야 함
/* 전체 경로의 수를 생각해보면 (최대 100x100)
* 가로 이동 횟수: 100 - 1 = 99번
* 세로 이동 횟수: 100 - 1 = 99번
* 전체 이동 횟수: 198번
* 따라서 경로의 수는 198번 중 언제 오른쪽으로 갈지 99번을 고르면 됨 (198C99 = 198!/(99!99!) = 약 2x10^58)
*/

int Map[101][101]; // 0(빈공간), 1(물에 잠긴 곳), 2(집), 3(학교)
int DP[101][101]; // DP[i][j] = (i, j) 위치에 도착하는 최단 경로의 개수

int solution(int m, int n, vector<vector<int>> puddles) // n행 m열
{
    Map[1][1] = 2;
    Map[n][m] = 3;
    for (int i = 0; i < puddles.size(); i++)
    {
        int R = puddles[i][1];
        int C = puddles[i][0];
        Map[R][C] = 1; // 물에 잠긴 곳
    } // 맵 초기화

    for (int i = 1; i <= m; i++)
    {
        if (Map[1][i] == 1) break; // 물 웅덩이가 있다면 더이상 갈 수 없음 (이후는 0)
        DP[1][i] = 1;
    } // 1행 DP 초기화 (물 웅덩이가 없다면 최단 경로의 개수는 모두 1)
    for (int i = 1; i <= n; i++)
    {
        if (Map[i][1] == 1) break; // 물 웅덩이가 있다면 더이상 갈 수 없음 (이후는 0)
        DP[i][1] = 1;
    } // 1열 DP 초기화 (물 웅덩이가 없다면 최단 경로의 개수는 모두 1)

    for (int i = 2; i <= n; i++)
    {
        for (int j = 2; j <= m; j++)
        {
            if (Map[i][j] == 1) DP[i][j] = 0; // 물 웅덩이가 있다면 최단경로 X
            // 현재 최단경로의 수 = 좌측에서 오던 경로 수 + 위쪽에서 오던 경로 수
            else DP[i][j] = (DP[i - 1][j] + DP[i][j - 1]) % num;
        }
    }
    return DP[n][m];
}