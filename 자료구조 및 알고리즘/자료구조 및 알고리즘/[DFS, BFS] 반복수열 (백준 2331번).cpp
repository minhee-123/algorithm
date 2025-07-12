// 반복수열 (https://www.acmicpc.net/problem/2331)

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int A, P;
int dupli = 0;
vector<int> total;
bool visit[300000]; //최대값이 상당히 크니까 넉넉하게 30만까지 고려해야 함

void Solution(int A, int P)
{
	if (visit[A])
	{
		dupli = A; //중복되는 수 기록
		return;
	}

	visit[A] = true;
	total.push_back(A);

	int sum = 0;
	while (A != 0)
	{
		sum += pow(A % 10, P);
		A = A / 10;
	}

	Solution(sum, P);
}

int main()
{
	cin >> A >> P;
	Solution(A, P);

	int answer = 0;
	for (int i = 0; i < total.size(); i++)
	{
		if (total[i] == dupli) //중복되는 수가 나오기 전까지의 개수가 정답 (idx가 정답)
		{
			answer = i;
			break;
		}
	}

	cout << answer << '\n';
	return 0;
}