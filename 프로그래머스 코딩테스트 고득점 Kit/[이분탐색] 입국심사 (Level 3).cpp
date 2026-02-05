// ★ 감이 안 잡혀서 풀이를 좀 참고했다 → 아이디어 참고: https://jinho082008.tistory.com/203
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

long long solution(int n, vector<int> times)
{
    int inspect_cnt = times.size();
    sort(times.begin(), times.end()); // 오름차순 정렬

    // 모든 사람이 심사를 받는데 걸리는 최대 시간
    long long maxT = (long long)n * (long long)times[inspect_cnt - 1];
    long long minT = 1; // 최소 시간 (1분부터 시작)

    while (minT <= maxT)
    {
        long long T = (minT + maxT) / 2;

        long long cnt = 0; // T시간 동안 입국심사대에서 처리한 사람의 수
        for (int i = 0; i < inspect_cnt; i++) cnt += (T / (long long)times[i]);

        if (cnt >= n) maxT = T - 1; // 처리한 사람의 수가 n명 이상 (최소시간인지 알 수 없고 더 짧은 시간에도 가능할 수 있기 때문에 T-1)
        else minT = T + 1; // 처리한 사람의 수가 n명 미만 (무조건 더 긴 시간이 필요하기 때문에 T+1)
    }
    return minT;
    // maxT는 답이 될 수도 있는 후보의 최대치를 깎아 내려옴
    // minT는 답이 안되는 범위를 넘어서 답이 되는 첫 번째 지점에 도착한 채로 멈춤
    // 예시로 정답이 28일 때 minT와 maxT가 모두 28에 도착 → maxT가 27이 되면서 while이 종료됨

    /* 이분 탐색에서 min(s), max(e) 중에 뭐가 정답인지 헷갈릴 때 */
    // 마지막 순간에 조건이 만족되었을 때 누가 움직이는가를 생각하면 된다!
    // 조건이 만족된 마지막 상황(min과 max의 값이 같을 때) 움직이지 않는 쪽이 정답 
    // → 정답이 아니라서 움직이는 쪽이 정답 (다른 답이 있나 움직여보는 쪽은 정답이 아님)
}