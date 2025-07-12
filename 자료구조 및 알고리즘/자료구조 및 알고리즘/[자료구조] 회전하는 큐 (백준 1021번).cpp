// 회전하는 큐 (https://www.acmicpc.net/problem/1021)
// 주어진 원소가 front에 가까운지 back에 가까운지 찾아서 2번 혹은 3번 연산의 최소 횟수를 구하면 됨

#include <iostream>
#include <deque>
using namespace std;

int main()
{
	int N, M;
	cin >> N >> M;

	deque<int> dq;
	for (int i = 1; i <= N; i++)
	{
		dq.push_back(i);
	}

	int idx = 0;
	int num;
	int cnt = 0;
	while (M--) //M번 반복하면 0이 되어서 false로 반복중단
	{
		cin >> num; //처음 dq에서 위치 (그 값)
		for (int i = 0; i < dq.size(); i++)
		{
			if (num == dq[i]) idx = i; //현재 dq에서 위치 기록 (연산 때문에 처음의 위치가 이동함)
		}

		if (idx <= dq.size() / 2) //2번연산 (왼쪽으로 한칸 이동)
		{
			while (1)
			{
				if (dq.front() == num)
				{
					dq.pop_front();
					break;
				}
				cnt++;
				dq.push_back(dq.front());
				dq.pop_front();
			}
		}
		else //3번연산 (오른쪽으로 한칸 이동)
		{
			while (1)
			{
				if (dq.front() == num)
				{
					dq.pop_front();
					break;
				}
				cnt++;
				dq.push_front(dq.back());
				dq.pop_back();
			}
		}
	}

	cout << cnt;
	return 0;
}