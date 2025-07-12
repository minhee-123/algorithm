// 문제: https://www.acmicpc.net/problem/1405
#include <iostream>
using namespace std;
//같은 곳을 한번만 방문할 경우 → 이동경로가 단순하다

int N;
double pro[4]; //동서남북 확률

bool visit[30][30];
int dr[4] = {0, 0, -1, 1}; //동서남북
int dc[4] = {1, -1, 0, 0};

double answer = 0;
void BackTrack(int depth, int row, int col, double cum)
{
	if (depth == N)
	{
		answer += cum;
		return;
	}

	for (int i = 0; i < 4; i++)
	{
		int next_row = row + dr[i];
		int next_col = col + dc[i];
		if (next_row < 0 || next_row > 30 || next_col < 0 || next_col > 30) continue; //범위가 넘어가는 경우는 없긴 함 (발생하면 문제 오류)
		if (visit[next_row][next_col]) continue; //단순하지 않은 경우 제외

		visit[next_row][next_col] = true;
		BackTrack(depth+1, next_row, next_col, cum * pro[i]);
		visit[next_row][next_col] = false; //상태해체
	}
}

int main()
{
	cin >> N >> pro[0] >> pro[1] >> pro[2] >> pro[3];
	for (int i = 0; i < 4; i++) pro[i] *= 0.01;

	visit[15][15] = true;
	BackTrack(0, 15, 15, 1); //시작부터 동서남북 이동해야하는 것을 고려하면 중앙에서 시작해야 함 (음수 index가 생기면 안됨)

	cout.precision(16); //소수점 아래 10자리까지 고정 (10^-10까지 출력)
	cout << answer;
	return 0;
}
//시작부터 동서남북으로 이동 가능 → 중앙에서 시작해야 함 (이 부분을 놓쳐서 고치는 데 오래 걸림)