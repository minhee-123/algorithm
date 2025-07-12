// ★ 풀이 실패 (전체에서 4가지 테스트케이스에 대해 오답 발생 → 이전 코드에서는 동일한 테스트케이스에 대해 런타임에러가 발생함)
// ★ 다음에 풀 때는 C++로 시도해보고, 안되면 중간 이동을 구현해보는 것을 고려
// 문제: https://softeer.ai/practice/7726
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#pragma warning(disable:4996)
// 문제의 핵심은 중간에 고스트를 만나서 실패하는 것을 따지는 것보다는 (고려해야하는 경우의 수가 많고 구현이 까다로움)
// 결과만 봤을 때 어차피 고스트가 거리가 더 짧다면 탈주실패 (고스트가 먼저 출구에 도착하기 때문에 무조건 실패함)

// 만약 구현하게 된다면 queue 활용 
// (BFS와 queue를 이용해 매턴마다 유령이 이동 가능한 곳을 기록 → 배열로 index는 위치, 배열값은 턴값 저장)
// (남우 이동을 수행할 때, 기록해둔 매턴마다의 유령 위치를 활용 → 벽과 유령위치(직전턴과 현재턴)에 따라 이동 수행)
int main(void)
{
    //비쥬얼 스튜디오에서는 스택 오버플로우 발생중 → 전부 main 함수에서 처리해서 그런듯
    int map[1005][1005] = { 0 };
    int SR, SC;
    int ER, EC;
    int G_count = 0;
    int GR[1005] = { 0 };
    int GC[1005] = { 0 };

    int N, M; scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        char temp[1005];
        scanf("%s", temp);
        for (int j = 0; j < M; j++) {
            char ch = temp[j];

            if (ch == '.') continue;
            else if (ch == '#') map[i][j] = 1;
            else if (ch == 'N') {
                SR = i;
                SC = j;
            }
            else if (ch == 'D') {
                ER = i;
                EC = j;
            }
            else {
                GR[G_count] = i;
                GC[G_count] = j;
                G_count++;
            }
        }
    }

    //유령 이동
    int ghost_distance = 2005;
    for (int i = 0; i < G_count; i++) {
        int distance = abs(ER - GR[i]) + abs(EC - GC[i]);
        if (distance < ghost_distance) ghost_distance = distance;
    }

    //남우 이동(BFS)
    int human_distance[1005][1005];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) human_distance[i][j] = -1; //memset은 에러가 발생할 확률이 좀 높은가봄 (안전하게 for loop)
    }

    int* queueR = (int*)malloc(sizeof(int) * (N * M));
    int* queueC = (int*)malloc(sizeof(int) * (N * M));

    long front = 0;
    long rear = 0;

    queueR[rear] = SR;
    queueC[rear] = SC;
    rear++;
    human_distance[SR][SC] = 0;

    int dr[4] = { 0, 0, 1, -1 };
    int dc[4] = { 1, -1, 0, 0 };
    int arrive_flag = 0;

    while (front < rear) {
        int popR = queueR[front];
        int popC = queueC[front];
        front++;

        for (int i = 0; i < 4; i++) {
            int nextR = popR + dr[i];
            int nextC = popC + dc[i];

            if (nextR >= 0 && nextR < N && nextC >= 0 && nextC < M && map[nextR][nextC] == 0 && human_distance[nextR][nextC] == -1) {
                human_distance[nextR][nextC] = human_distance[popR][popC] + 1;
                queueR[rear] = nextR;
                queueC[rear] = nextC;
                rear++;
            }

            if (nextR == ER && nextC == EC) {
                arrive_flag = 1;
                break;
            }
        }

        if (arrive_flag == 1) break;
    }
    int namou_distance = human_distance[ER][EC];

    //결과
    if (arrive_flag == 0) printf("No"); //남우가 이동하지 못할 경우
    else if (namou_distance >= ghost_distance) printf("No"); //남우의 이동거리가 유령보다 클 경우
    else printf("Yes"); //남우가 먼저 도착하는 경우 (유령이 없는 경우 포함)

    free(queueR);
    free(queueC);
    return 0;
}