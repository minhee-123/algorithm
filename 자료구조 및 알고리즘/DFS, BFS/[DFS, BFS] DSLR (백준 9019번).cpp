// 문제: https://www.acmicpc.net/problem/9019
#include <iostream>
#include <string>
#include <cstring>
#include <queue>
using namespace std;

// 이전에 풀었던 문제 중에서 유사한 문제가 DFS로 풀었던 것 같아서 DFS로 접근
// BUT 최단거리를 찾는 것이기 때문에 정석은 BFS로 푸는 게 낫다고 함 (자꾸 접근을 잘못하네!)
// → 문제 푸는 감각 좀 되찾아야 할 것 같다 ★!!

/* 새삼스러운 문법 CHECK */
// 함수의 인자로 배열을 사용하면 → 원본을 그대로 가져옴 (복사해서 사용하고 싶다면 수동 복사)
// 함수의 인자로 벡터를 사용하면 → 복사해서 가져옴

int T;
bool visit[10000];

struct inform
{
	int nowA;
	string path;
};

void Solution()
{
	int A, B;
	cin >> A >> B;
	memset(visit, false, sizeof(visit)); // 탐색 경로를 단축하기 위해 방문했던 숫자 check (재방문 방지)

	queue<inform> que;
	que.push({ A, "" });
	visit[A] = true;

	string answer = "";

	while (!que.empty())
	{
		int nowA = que.front().nowA;
		string nowP = que.front().path;

		que.pop();
		if (nowA == B)
		{
			answer = nowP;
			break;
		}

		for (int k = 0; k < 4; k++)
		{
			int nextA = nowA;
			string nextP = nowP;

			if (k == 0)
			{
				nextA *= 2;
				if (nextA > 9999) nextA %= 10000;

				nextP += "D";
			}
			else if (k == 1)
			{
				// n에서 1을 뺀 결과를 레지스터에 저장
				// 이때 n는 0에서 9999까지 저장할 수 있으니까
				// 1을 뺏을 때 n이 음수가 되면 9999를 저장하라는 뜻임 (빼기 전의 값이 0이면 9999로 바꿔라)
				nextA -= 1;
				if (nextA < 0) nextA = 9999;

				nextP += "S";
			}
			else if (k == 2)
			{
				int tempA[4];
				tempA[0] = nextA / 1000; nextA = nextA % 1000;
				tempA[1] = nextA / 100; nextA = nextA % 100;
				tempA[2] = nextA / 10; nextA = nextA % 10;
				tempA[3] = nextA;

				int temp = tempA[0];
				tempA[0] = tempA[1];
				tempA[1] = tempA[2];
				tempA[2] = tempA[3];
				tempA[3] = temp;
				
				/* 굳이 배열을 안 쓰고 아래와 같이 정수 연산으로도 구할 수 있음 */
				// nextA = (nextA % 1000) * 10 + (nextA / 1000);

				nextA = (tempA[0] * 1000) + (tempA[1] * 100) + (tempA[2] * 10) + tempA[3];
				nextP += "L";
			}
			else
			{
				int tempA[4];
				tempA[0] = nextA / 1000; nextA = nextA % 1000;
				tempA[1] = nextA / 100; nextA = nextA % 100;
				tempA[2] = nextA / 10; nextA = nextA % 10;
				tempA[3] = nextA;

				int temp = tempA[3];
				tempA[3] = tempA[2];
				tempA[2] = tempA[1];
				tempA[1] = tempA[0];
				tempA[0] = temp;

				/* 굳이 배열을 안 쓰고 아래와 같이 정수 연산으로도 구할 수 있음 */
				// nextA = (nextA % 10) * 1000 + (nextA / 10);

				nextA = (tempA[0] * 1000) + (tempA[1] * 100) + (tempA[2] * 10) + tempA[3];
				nextP += "R";
			}

			if (visit[nextA]) continue; // 이미 방문한 숫자일 경우 pass
			
			visit[nextA] = true;
			que.push({ nextA, nextP });
		}
	}

	cout << answer << '\n';
}

int main()
{
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		Solution();
	}
	return 0;
}