// 문제: https://www.acmicpc.net/problem/11758
// 전형적인 CCW 문제
#include <iostream>
using namespace std;

// P1, P2, P3를 순서대로 이은 선분이
// 반시계 방향을 나타내면 1 / 시계 방향을 나타내면 -1 / 일직선이면 0

int main()
{
	int x1, y1; // P1
	int x2, y2; // P2
	int x3, y3; // P3
	cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

	int CCW = (x1 * y2 + x2 * y3 + x3 * y1) - (x1 * y3 + x3 * y2 + x2 * y1);

	if (CCW < 0) cout << -1; // CCW 값이 음수면 시계방향
	else if (CCW > 0) cout << 1; // CCW 값이 양수면 반시계 방향
	else cout << 0; // CCW 값이 0이면 일직선 방향
	return 0;
}