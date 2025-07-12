// 바이러스 (https://www.acmicpc.net/problem/2606)

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int cnt = 0;
int num;
int connect;
vector<int> computer[105];
bool visit[105]; //전역으로 선언했으니 false

int main()
{
	cin >> num;
	cin >> connect;
	for (int i = 0; i < connect; i++)
	{
		int temp1, temp2;
		cin >> temp1 >> temp2;
		computer[temp1].push_back(temp2);
		computer[temp2].push_back(temp1); //무방향 그래프
	}

	queue<int> vir;
	vir.push(1);
	visit[1] = true;

	while (!vir.empty())
	{
		int now = vir.front();
		vir.pop();

		for (int i = 0; i < computer[now].size(); i++)
		{
			int next = computer[now][i];

			if (!visit[next]) //들리지 않은 곳이면
			{
				vir.push(next);
				visit[next] = true;
				cnt++;
			}
		}
	}

	cout << cnt;
	return 0;
}