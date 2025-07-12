// 게임 맵 최단거리 (https://school.programmers.co.kr/learn/courses/30/lessons/1844)

// 최단거리 구하기 → BFS 사용
// (DFS로 풀이하게 될 경우 완전탐색을 진행하게 됨, 시간초과 문제 발생)
// (BFS의 경우 최단거리를 찾게되면 반복종료, 시간초과 문제가 발생하지 않음)
#include<vector>
#include<queue>
using namespace std;

int dr[4] = { 1, 0, -1, 0 }; //상 우 하 좌
int dc[4] = { 0, 1, 0, -1 };

bool visit[105][105]; //false;
int dist[105][105] = { 0 }; //0으로 초기화

int solution(vector<vector<int>> maps) //0은 벽이 있는 자리, 1은 벽이 없는 자리
{
    int N = maps.size();
    int M = maps[0].size();

    queue<pair<int, int>> que;
    que.push({ 0, 0 });
    visit[0][0] = true;
    dist[0][0] = 1;

    while (!que.empty())
    {
        int r = que.front().first;
        int c = que.front().second;
        que.pop();

        for (int i = 0; i < 4; i++)
        {
            int move_r = r + dr[i];
            int move_c = c + dc[i];

            if (move_r<0 || move_r>N - 1 || move_c<0 || move_c>M - 1) continue;
            if (visit[move_r][move_c]) continue;
            if (maps[move_r][move_c] == 0) continue;

            que.push({ move_r, move_c });
            visit[move_r][move_c] = true;
            dist[move_r][move_c] = dist[r][c] + 1;
        }
    }
    if (dist[N - 1][M - 1] == 0) return -1;
    else return dist[N - 1][M - 1];
}