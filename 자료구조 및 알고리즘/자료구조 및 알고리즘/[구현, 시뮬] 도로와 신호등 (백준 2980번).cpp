// 도로와 신호등 (https://www.acmicpc.net/problem/2980)

#include <iostream>
#include <vector>
using namespace std;

struct blinker 
{
	int D; //신호등의 위치
	int R; //신호등 빨간색이 지속되는 시간
	int G; //신호등 초록색이 지속되는 시간
};

int main()
{
	int N, L;
	vector<blinker> Blinker;
	cin >> N >> L;
	for (int i = 0; i < N; i++)
	{
		int temp_D, temp_R, temp_G;
		cin >> temp_D >> temp_R >> temp_G;
		Blinker.push_back({ temp_D, temp_R, temp_G });
	}

	int time = 0;
	int idx = 0;
	int move = 0;
	while (move != L)
	{
		if (move == Blinker[idx].D) //신호등 구간
		{
			int temp = time % (Blinker[idx].R + Blinker[idx].G);
			if (temp < Blinker[idx].R) //빨간불
			{
				//빨간불에서 초록불이 되는 시간이 애매한데 등호가 포함 안됨
				//멈춰있음
			}
			else //초록불
			{
				move++;
				if (idx < Blinker.size() - 1) idx++;
			}
		}
		else //신호등 구간 아님
		{
			move++;
		}
		time++;
	}
	cout << time;
}