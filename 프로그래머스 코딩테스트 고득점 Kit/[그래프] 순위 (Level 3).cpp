#include <vector>
#include <cstring>
using namespace std;

// 자신을 기준으로 자신에게 패배한 선수의 수 + 자신에게 이긴 선수의 수 = n-1 이면 순위를 알 수 있음
// 재귀를 이용해 해당 타임의 선수를 기준으로 패배한/이긴 선수의 수를 count (visit 배열을 통해 매타임마다 체크함)
// → DP의 메모이제이션을 이용해볼까도 했으나 cnt가 중복되서 계산되는 문제 때문에 매턴마다 다시 세는 방식을 채택 (시간도 충분)

vector<int> player_win[101]; // i가 이긴 선수들 (i한테 패배한 선수들)
vector<int> player_lose[101]; // i가 패배한 선수들 (i한테 이긴 선수들)

int answer = 0;
bool visit[101];

int check_win(int index)
{
    int cnt = 0;
    for (int i = 0; i < player_win[index].size(); i++)
    {
        int next_index = player_win[index][i];
        if (visit[next_index]) continue;
        visit[next_index] = true;

        cnt++;
        if (player_win[next_index].size() != 0) cnt += check_win(next_index);
    }
    return cnt;
}

int check_lose(int index)
{
    int cnt = 0;
    for (int i = 0; i < player_lose[index].size(); i++)
    {
        int next_index = player_lose[index][i];
        if (visit[next_index]) continue;
        visit[next_index] = true;

        cnt++;
        if (player_lose[next_index].size() != 0) cnt += check_lose(next_index);
    }
    return cnt;
}

void check_ranks(int index, int n)
{
    memset(visit, false, sizeof(visit));
    int cnt = check_win(index) + check_lose(index);
    if (cnt == n - 1) answer++;
}

int solution(int n, vector<vector<int>> results)
{
    for (int i = 0; i < results.size(); i++)
    {
        int A = results[i][0];
        int B = results[i][1];
        player_win[A].push_back(B);
        player_lose[B].push_back(A);
    }

    for (int i = 1; i <= n; i++) check_ranks(i, n);
    return answer;
}