// 코드트리 삼성 SW 역량테스트 2025 상반기 오후 1번 문제
// https://www.codetree.ai/ko/frequent-problems/samsung-sw/problems/microbial-research/description

/*
풀어보던 느낌의 문제가 아니어서 다른사람의 풀이를 참고했다
https://bloodstrawberry.tistory.com/1575

어떻게 모양 그대로 옮겨야 할까?
→ 직사각형 범위로 다루고 현재 자리가 비어있는지 or 다른 미생물이 있는지 check 후 continue로 처리하면 됨
→ 너무 꼬아서 생각하지 말고 결국 단순 구현임을 잊지말자
*/


#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int N, Q;
int Map[15][15]; //칸의 개념으로 접근 → 0부터 N-1까지 범위

struct MICRO
{
    int id;
    int minR;
    int minC;
    int maxR;
    int maxC;
    int mcnt; //미생물 개수 (넓이)
};

int recent_id;
vector<MICRO> micro; //index는 1부터 사용함
bool dead[51]; //디폴트 false

int dr[4] = { 0, 0, 1, -1 };
int dc[4] = { 1, -1, 0, 0 };


// 1. 미생물 투입
void Input()
{
    int r1, c1, r2, c2;
    cin >> c1 >> r1 >> c2 >> r2;
    r2--;
    c2--; //칸의 개념으로 접근 → 우측상단은 -1

    for (int i = r1; i <= r2; i++)
    {
        for (int j = c1; j <= c2; j++) Map[i][j] = recent_id;
    }
    micro.push_back({ recent_id, r1, c1, r2, c2, 0 }); //개수는 생존여부에서 업데이트
}


// 2. 미생물 생존여부 확인
bool check_S[51]; //DFS를 돌릴때 check가 두번되는 구간이 있다면 영역이 둘 이상으로 나누어진 것 (미생물 사망)
bool visit[15][15];

int check_cnt = 0;
void DFS(int index, int id, int R, int C)
{
    if (visit[R][C]) return;
    visit[R][C] = true;
    check_cnt++;

    if (R < micro[index].minR) micro[index].minR = R;
    if (R > micro[index].maxR) micro[index].maxR = R;
    if (C < micro[index].minC) micro[index].minC = C;
    if (C > micro[index].maxC) micro[index].maxC = C; //minRC, maxRC 업데이트

    for (int i = 0; i < 4; i++)
    {
        int nextR = R + dr[i];
        int nextC = C + dc[i];

        if (nextR < 0 || nextR >= N || nextC < 0 || nextC >= N) continue;
        if (visit[nextR][nextC] || Map[nextR][nextC] != id) continue;

        DFS(index, id, nextR, nextC);
    }
}

void check_survive()
{
    memset(visit, false, sizeof(visit));
    memset(check_S, false, sizeof(check_S));

    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            int id = Map[r][c];

            // 빈공간 + 죽어있는 미생물 + 방문한 위치인 경우 continue
            if (id == 0 || dead[id] || visit[r][c]) continue;

            int index = 0;
            for (int i = 0; i < micro.size(); i++)
            {
                if (micro[i].id == id) index = i;
            }

            //★★★ 디버깅이 정말 오래 걸린 구간 (실수한 부분)
            swap(micro[index].minR, micro[index].maxR);
            swap(micro[index].minC, micro[index].maxC);
            /*  새로운 미생물이 투입되었을 때 몸체 일부가 삭제되나 생존하는 미생물에서
                삭제되는 부분이 minR, minC, maxR, maxC에 해당할 경우 문제가 발생함
                → 실제 미생물이 차지하는 직사각형보다 더 큰 직사각형 범위를 잡아버려서 이동위치를 잘못 잡아버림
                → 더 왼쪽에 위치할 수 있는데 min이 업데이트 되지 않아 오른쪽으로 이동한다거나 등등 */
            /*  그래서 min 좌표랑 max 좌표를 바꿔버려서 DFS에서 무조건 업데이트가 되도록 수정함
                → 무조건 업데이트가 수행됨 */

            check_cnt = 0;
            DFS(index, id, r, c);

            if (check_S[id]) //두번 이상 DFS를 수행한 경우
            {
                dead[id] = true;
                continue;
            }
            else
            {
                micro[index].mcnt = check_cnt;
                check_S[id] = true;
            }
        }
    }
}


// 3. 배양용기 이동
bool comp(MICRO A, MICRO B)
{
    if (A.mcnt != B.mcnt) return A.mcnt > B.mcnt;
    else return A.id < B.id;
}

int new_Map[15][15];

bool can_move(MICRO M, int R, int C)
{
    int minR = M.minR;
    int minC = M.minC;
    int maxR = M.maxR;
    int maxC = M.maxC;

    int moveR = R - minR;
    int moveC = C - minC;

    for (int r = minR; r <= maxR; r++)
    {
        for (int c = minC; c <= maxC; c++)
        {
            int row = r + moveR;
            int col = c + moveC;
            if (Map[r][c] != M.id) continue; //범위 내에 미생물이 없는 경우 (다른 미생물에 의해 침범당한 자리 등등)

            if (row < 0 || row >= N || col < 0 || col >= N) return false;
            if (new_Map[row][col] > 0) return false; //이미 다른 값이 있는 경우
        }
    }
    return true;
}

MICRO real_move(MICRO M, int R, int C)
{
    int minR = M.minR;
    int minC = M.minC;
    int maxR = M.maxR;
    int maxC = M.maxC;

    int moveR = R - minR;
    int moveC = C - minC;

    int mcnt = 0;
    for (int r = minR; r <= maxR; r++)
    {
        for (int c = minC; c <= maxC; c++)
        {
            int row = r + moveR;
            int col = c + moveC;
            if (Map[r][c] != M.id) continue; //범위 내에 미생물이 없는 경우 (다른 미생물에 의해 침범당한 자리 등등)
            
            new_Map[row][col] = M.id;
            mcnt++;
        }
    }

    M.minR = minR + moveR;
    M.minC = minC + moveC;
    M.maxR = maxR + moveR;
    M.maxC = maxC + moveC;
    M.mcnt = mcnt;

    return M;
}

void Create_new()
{
    sort(micro.begin(), micro.end(), comp); //배양용기 정렬
    memset(new_Map, 0, sizeof(new_Map));

    for (int i = 0; i < micro.size(); i++)
    {
        int id = micro[i].id;
        if (dead[id]) continue; //죽어있는 미생물은 continue

        bool flag = false;

        for (int c = 0; c < N; c++)
        {
            for (int r = 0; r < N; r++)
            {
                if (can_move(micro[i], r, c) == true) //이동할 수 있는 경우
                {
                    micro[i] = real_move(micro[i], r, c);
                    flag = true;
                    break;
                }
            }

            if (flag) break;
        }

        if (!flag) dead[micro[i].id] = true; //이동하지 못하고 삭제
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++) Map[i][j] = new_Map[i][j];
    }
}


// 4. 점수 계산
int score = 0;
bool attached[51][51];

void Result()
{
    memset(attached, false, sizeof(attached));

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            int A = Map[i][j];
            for (int dir = 0; dir < 4; dir++)
            {
                int R = i + dr[dir];
                int C = j + dc[dir];

                if (R < 0 || R >= N || C < 0 || C >= N) continue;
                int B = Map[R][C];

                if (A == 0 || B == 0) continue;
                if (dead[A] || dead[B]) continue;
                if (A == B) continue;

                attached[A][B] = true;
                attached[B][A] = true;
            }
        }
    }

    score = 0;

    for (int i = 0; i < micro.size() - 1; i++)
    {
        if (dead[micro[i].id]) continue;
        for (int j = i + 1; j < micro.size(); j++)
        {
            if (dead[micro[j].id]) continue;
            if (attached[micro[i].id][micro[j].id])
            {
                score += micro[i].mcnt * micro[j].mcnt;
            }
        }
    }

    cout << score << '\n';
}


int main()
{
    cin >> N >> Q;

    for (int i = 1; i <= Q; i++)
    {
        recent_id = i;
        Input();

        check_survive();
        Create_new();

        Result();
    }
    return 0;
}


/*
오랜만에 풀고 이런 유형은 안풀어봐서 풀이를 스스로 생각 못함
(1) flag 위치, 변수 잘못 씀, 변수 중복선언 등등 어이없는 실수 주의
(2) 미생물의 크기가 변할 때 좌표 업데이트를 주의해야 함 (미생물의 크기가 변하는 데 좌표를 업데이트하지 않아 디버깅이 정말 오래 걸림)
*/