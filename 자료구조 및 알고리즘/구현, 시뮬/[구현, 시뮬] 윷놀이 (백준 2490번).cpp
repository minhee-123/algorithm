// 윷놀이 (https://www.acmicpc.net/problem/2490)

#include <iostream>
using namespace std;

int main()
{
	int flag = 0;
	while (flag < 3)
	{
		int yut[4] = { 0 };
		int cnt_1 = 0;
		for (int i = 0; i < 4; i++)
		{
			cin >> yut[i];
			if (yut[i] == 1) cnt_1++;
		}

		if (cnt_1 == 3) cout << 'A' << '\n';
		else if (cnt_1 == 2) cout << 'B' << '\n';
		else if (cnt_1 == 1) cout << 'C' << '\n';
		else if (cnt_1 == 0) cout << 'D' << '\n';
		else cout << 'E' << '\n';

		flag++;
	}
	return 0;
}