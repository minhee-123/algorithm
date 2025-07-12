//개미 (https://www.acmicpc.net/problem/3048)

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
	int N1, N2, T;
	string ant1, ant2;
	cin >> N1 >> N2;
	cin >> ant1;
	cin >> ant2;
	cin >> T;

	string ANT = "";
	vector<int> ANT_dir;
	for (int i = N1 - 1; i >= 0; i--)
	{
		ANT += ant1[i];
		ANT_dir.push_back(1); //왼쪽에서 오른쪽 이동 1
	}
	for (int i = 0; i < N2; i++)
	{
		ANT += ant2[i];
		ANT_dir.push_back(2); //오른쪽에서 왼쪽 이동 2
	}

	bool flag = false;
	while (T--)
	{
		for (int i = 0; i < N1 + N2 - 1; i++)
		{
			if (flag) //이전 i에서 위치바꾸기를 했다면 i+1 반복문은 생략 (1초에 한 개미당 위치 바꾸기는 한번 발생함)
			{
				flag = false;
				continue;
			}
			else
			{
				if (ANT_dir[i] == 1 && ANT_dir[i + 1] == 2)
				{
					char temp = ANT[i];
					ANT[i] = ANT[i + 1];
					ANT[i + 1] = temp;

					int temp2 = ANT_dir[i];
					ANT_dir[i] = ANT_dir[i + 1];
					ANT_dir[i + 1] = temp2;

					flag = true;
				}
			}
		}
	}
	cout << ANT;
	return 0;
}