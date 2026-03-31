// 문제: https://www.acmicpc.net/problem/20055
#include <iostream>
#include <deque>
using namespace std;

int N, K;
deque<int> Line; // 컨테이너 벨트
deque<int> Robot; // 로봇 (1은 로봇이 있고, 0은 없는 것)

int main()
{
	// Input
	cin >> N >> K;
	Line.resize(2 * N); // 0번은 올리는 위치, N-1번은 내리는 위치
	Robot.resize(2 * N);
	for (int i = 0; i < 2 * N; i++) cin >> Line[i];

	// Action
	int answer = 0;
	int broken = 0;

	while (broken < K)
	{
		answer++;

		// Step 1
		int temp = Line[2 * N - 1];
		Line.pop_back();
		Line.push_front(temp);

		temp = Robot[2 * N - 1];
		Robot.pop_back();
		Robot.push_front(temp);
		if (Robot[N - 1] == 1) Robot[N - 1] = 0; // 내리는 위치에 도달한 로봇은 하차

		// Step 2
		for (int i = N - 2; i >= 0; i--) // 가장 먼저 벨트에 올라간 로봇부터 이동 (오래된 순으로 이동)
		{
			if (Robot[i] == 1 && Line[i + 1] > 0 && Robot[i + 1] != 1)
			{
				Robot[i] = 0;
				Robot[i + 1] = 1;
				Line[i + 1]--;

				if (i + 1 == N - 1) Robot[i + 1] = 0; // 내리는 위치에 도달한 로봇은 하차
				if (Line[i + 1] == 0) broken++; // 내구도가 0이 되었을 경우 broken++
			}
		}

		// Step 3
		if (Line[0] != 0)
		{
			Robot[0] = 1;
			Line[0]--;
			if (Line[0] == 0) broken++;
		}
	}

	cout << answer;
	return 0;
}

/* 난이도 자체는 쉬운데 문제 설명이 거지 같아서 풀이에 시간이 좀 걸림 */
// Step 2의 반복문 순서를 반대로 해서 디버깅 수행 → 문제를 집중해서 읽자!!