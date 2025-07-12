// 알람 시계 (https://www.acmicpc.net/problem/2884)

#include <iostream>
using namespace std;

int main()
{
	int H, M;
	cin >> H >> M;

	int new_H, new_M;
	if (M >= 45)
	{
		new_H = H;
		new_M = M - 45;
	}
	else
	{
		new_M = 60 - (45 - M);
		if (H == 0) new_H = 23;
		else new_H = H - 1;
	}

	cout << new_H << " " << new_M;
	return 0;
}