// 외판원 순회 2 (https://www.acmicpc.net/problem/10971)
// 백트래킹 문제
// 백트래킹: 되추적 알고리즘, 결과를 찾는 도중에 제약조건에 걸릴 경우 다시 되돌아가서 다른 결과를 찾음
// (DFS와 유사하나 DFS와 달리 특정 조건을 설정해서 이 경로의 해가 안될 거라고 판단이 되면 경로를 이탈하고 다시 되돌아감 → 가지치기 (부모노드로 되돌아감))
// (백트랙 → 다시는 이 후보군을 체크하지 않을 것을 표기)

// 유의할 점
// 1. 각 행렬의 성분은 최다 1000000, 최대 도시의 개수는 10 → 최대값을 엄청 크게 설정 (1e9)
// 2. 갈 수 없는 길은 0으로 표시함 (마지막 마을에서 출발 마을로 되돌아와야 함)

// 참고 블로그
// https://astrid-dm.tistory.com/324
// https://gdlovehush.tistory.com/335


#include <iostream>
#include <algorithm>
using namespace std;

int N;
int W[15][15];
bool visit[15]; //false
int min_cost = 1e9; 
//약 10의 9승
//2e9의 경우 int 범위 내에서 무한대 값을 나타내기 위해 사용하는 경우가 많음

void Go(int start, int index, int cnt, int sum) //처음 위치, 현재 위치, 들린 도시의 개수, 비용합
{
	if (cnt == N) //N개의 도시를 모두 들린 경우
	{
		if (W[index][start] == 0) return; //처음 위치로 되돌아갈 수 없는 경우
		
		min_cost = min(min_cost, sum + W[index][start]);
		return;
	}

	for (int i = 1; i <= N; i++)
	{
		if (visit[i]) continue;
		if (W[index][i] == 0) continue;

		visit[i] = true;
		Go(start, i, cnt + 1, sum + W[index][i]); //도시 i로 이동
		visit[i] = false; //다음 경로에 영향이 가지 않도록 현재 경로가 끝나면 바로 false로 되돌려줌
	}
}

int main()
{
	cin >> N;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			cin >> W[i][j];
		}
	}

	for (int i = 1; i <= N; i++)
	{
		visit[i] = true;
		Go(i, i, 1, 0); //현재 위치한 도시도 들린 거니까 cnt는 1로 시작함
		visit[i] = false; //다음 경로에 영향이 가지 않도록 현재 경로가 끝나면 바로 false로 되돌려줌
	}
	cout << min_cost << '\n';
	return 0;
}