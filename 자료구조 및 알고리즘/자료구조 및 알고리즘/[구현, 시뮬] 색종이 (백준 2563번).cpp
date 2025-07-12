// 색종이 (https://www.acmicpc.net/problem/2563)

#include <iostream>
using namespace std;

//정말 간단하게 풀 수 있는 문제인데 생각을 못 했다!
//간단한 문제들은 배열만 써서 풀도록 연습 (풀이 간단)

int main()
{
	//100x100 배열에서 0이면 공백, 1이면 색종이 부분이라고 판단해 카운트
	int MAP[100][100] = { 0 };
	int N;
	cin >> N;

	int cnt = 0;
	while (N--)
	{
		int x, y;
		cin >> x >> y;
		for (int i = x; i < x + 10; i++)
		{
			for (int j = y; j < y + 10; j++)
			{
				if (MAP[i][j] == 0)
				{
					cnt++;
					MAP[i][j] = 1;
				}
			}
		}
	}
	cout << cnt;
	return 0;
}