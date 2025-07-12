// 문제: https://www.acmicpc.net/problem/2251
// 그래프 + 구현 문제 (배열만 사용했을 때 더 깔끔하게 풀림, 무조건 벡터를 사용하려고 하지는 말 것)

#include <iostream>
#include <queue>
using namespace std;

bool visit[201][201]; //A용량과 B용량만 따지면 C용량은 자동으로 결정됨
bool answer[201]; //용량의 최대값은 200L
int now[3]; //A, B, C 물의 용량 저장

int departure[6] = { 0, 0, 1, 1, 2, 2 }; //A->B, A->C, B->A, B->C, C->A, C->B
int arrive[6] = { 1, 2, 0, 2, 0, 1 };

void BFS()
{
	queue<pair<int, int>> water;
	water.push({ 0,0 });

	visit[0][0] = true;
	answer[now[2]] = true;

	while (!water.empty())
	{
		pair<int, int> w = water.front();
		water.pop();

		int A = w.first;
		int B = w.second;
		int C = now[2] - A - B;

		for (int i = 0; i < 6; i++) //물이 이동하는 경우는 6가지
		{
			int dep = departure[i];
			int arr = arrive[i];
			int next[3] = { A, B, C };

			next[arr] += next[dep];
			next[dep] = 0;
			if (next[arr] > now[arr])
			{
				next[dep] = next[arr] - now[arr];
				next[arr] = now[arr];
			}

			if (visit[next[0]][next[1]]) continue;

			water.push({ next[0], next[1] });
			visit[next[0]][next[1]] = true;

			if (next[0] == 0) answer[next[2]] = true;
		}
	}
}

int main()
{
	cin >> now[0] >> now[1] >> now[2];
	BFS();

	for (int i = 0; i < 201; i++)
	{
		if (answer[i]) cout << i << '\n'; //오름차순으로 출력하는 문제는 bool 배열에 true 값을 저장해서 출력하는 식으로 구현해도 좋음
	}
	return 0;
}