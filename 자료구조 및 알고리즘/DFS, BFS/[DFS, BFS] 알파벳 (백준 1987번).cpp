// 문제: https://www.acmicpc.net/problem/1987

// 비트마스크 사용
// → set이나 배열을 사용할 경우 큐에 너무 많은 양이 쌓여서 메모리 터짐
// → 비트마스크 구현: https://kimtaesoo99.tistory.com/121

// 아뿔사 그런데 애초에 DFS로 구현해야 하는 것이었다
// → BFS는 최단거리에 특화
// → 해당 문제는 최대거리를 구하는 것이기 때문에 DFS + 백트래킹 적용이 필요

// ★ BFS랑 DFS 중 어떤걸 선택해야 하는지 잘 생각 (최단거리 vs 최대거리 or 완탐)

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int dr[4] = { 0, 0, 1, -1 };
int dc[4] = { 1, -1, 0, 0 };

int Map[20][20];
int N, M;

int max_cnt = 1;

void DFS(int R, int C, int visit, int cnt)
{
	if (cnt > max_cnt) max_cnt = cnt;

	for (int i = 0; i < 4; i++)
	{
		int NR = R + dr[i];
		int NC = C + dc[i];
		int value = Map[NR][NC];

		if (NR < 0 || NR >= N || NC < 0 || NC >= M) continue;
		if (visit & (1 << value)) continue; // value 위치의 비트가 켜져있는지 확인

		int Nvisit = visit;
		Nvisit |= (1 << value); // value 위치의 비트 check

		DFS(NR, NC, Nvisit, cnt + 1);
	}
}

int main()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		string temp;
		cin >> temp;
		for (int j = 0; j < M; j++) Map[i][j] = ((int)temp[j]) - 65; // 알파벳을 숫자로 치환 (0부터 25)
	}

	int temp_visit = 0;
	temp_visit |= (1 << Map[0][0]); // Map[0][0]번째 비트 check

	DFS(0, 0, temp_visit, 1);

	cout << max_cnt;
	return 0;
}