// 문제: https://www.acmicpc.net/problem/2166
#include <iostream>
#include <cmath>
using namespace std;

int N;
long long sum = 0;
int main()
{
	cin >> N;
	long long sx, sy;
	long long x1, y1, x2, y2;
	cin >> x1 >> y1;
	
	sx = x1;
	sy = y1;

	for (int i = 2; i <= N; i++)
	{
		cin >> x2 >> y2;
		sum += x1 * y2 - x2 * y1; 
		// (0,0), (x1,y1), (x2,y2)의 CCW를 누적하여 더함
		// 그림을 그려보면 왜 되는지 알 수 있음 (원점과 이은 두점(삼각형)들의 합과 차로 구할 수 있음)

		x1 = x2;
		y1 = y2;
	}
	sum += x1 * sy - sx * y1; // 순서도 꽤 중요하다

	cout << fixed;
	cout.precision(1);
	cout << abs(sum) / 2.0;
}