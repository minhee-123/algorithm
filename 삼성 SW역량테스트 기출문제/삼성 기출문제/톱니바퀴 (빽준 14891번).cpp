// 문제: https://www.acmicpc.net/problem/14891
#include <iostream>
#include <deque>
#include <string>
#include <cmath>
using namespace std;

deque<int> wheel[4];

void turn (int index, int dir)
{
	if (dir == 1) //시계방향 회전
	{
		int num = wheel[index].back();
		wheel[index].pop_back();
		wheel[index].push_front(num);
	}
	else if (dir == -1) //반시계방향 회전
	{
		int num = wheel[index].front();
		wheel[index].pop_front();
		wheel[index].push_back(num);
	}
}

int main()
{
	for (int i = 0; i < 4; i++)
	{
		string temp;
		cin >> temp;
		for (int j = 0; j < 8; j++) wheel[i].push_back(temp[j] - '0'); //i랑 j랑 잘못 쓰는 것 주의 (j를 i로 써서 디버깅하고 있었음)
	}

	int K;
	cin >> K;
	
	for (int i = 0; i < K; i++)
	{
		int index, dir;
		cin >> index >> dir;
		index--; //실제 사용은 0번에서 3번 바퀴

		//오른쪽 2번과 왼쪽 6번이 맞닿아 있음
		int R = wheel[index][2];
		int L = wheel[index][6];
		turn(index, dir);

		int Front = index - 1;
		int Back = index + 1;

		int direction = dir;
		int tempL = L;
		while (Front >= 0) //index의 왼쪽 바퀴
		{
			if (wheel[Front][2] == tempL) break;
			tempL = wheel[Front][6];

			if (direction == 1) direction = -1;
			else direction = 1;

			turn(Front, direction);
			Front--;
		}

		direction = dir;
		int tempR = R;
		while (Back <= 3) //index의 오른쪽 바퀴
		{
			if (wheel[Back][6] == tempR) break;
			tempR = wheel[Back][2];

			if (direction == 1) direction = -1;
			else direction = 1;

			turn(Back, direction);
			Back++;
		}
	}

	int answer = 0;
	for (int i = 0; i < 4; i++)
	{
		if (wheel[i][0] == 1) //S극이면
		{
			answer += pow(2, i);
		}
	}
	cout << answer;
	return 0;
}