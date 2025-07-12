// 문제: https://www.acmicpc.net/problem/14889
// 수가 작기 때문에 브루트포스로 풀어도 풀리긴 함 (next_permutation)
// 문제에서 의도한 것은 백트래킹 알고리즘 활용
// 풀이참고: https://cocoon1787.tistory.com/170

// 1. 팀을 어떻게 구성하는가 (중복 고려) → 한 팀을 뽑으면 다른 팀은 알아서 구성
// 2. 구성한 팀에서 능력치를 구해 상대팀과 비교 (절댓값이 최소가 되는 값)

// 아래 풀이가 왜 백트래킹인지는 모르겠음
// 풀이가 좀 이해가 안되긴 함 (혼자 떠올리기는 힘들 것 같음)

#include<iostream>
using namespace std;

int stats[21][21];
bool check[22];
int N;
int ans = 1000000000; // 10억

void DFS(int x, int pos) // x는 카운트 수, pos는 다음 값
{
	if (x == N / 2) // 카운트수가 정원의 1/2이 됐을 때 능력치합 계산
	{
		int start, link;
		start = 0;
		link = 0;

		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				if (check[i] == true && check[j] == true) start += stats[i][j];
				if (check[i] == false && check[j] == false) link += stats[i][j];
			}
		}

		int temp = abs(start - link);
		if (ans > temp) ans = temp;

		return;
	}

	for (int i = pos; i < N; i++)
	// pos부터 시작하고 N-1까지만 계산해야 중복을 피함
	// 123, 456과 456, 123은 같은 결과 값을 가짐 (중복) → N은 무조건 link 팀에 속함
	// 1234 예시로 생각해보면 이해가 됨
	{
		check[i] = true;
		DFS(x + 1, i + 1);
		check[i] = false;
	}
}

int main()
{
	cin >> N;

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			cin >> stats[i][j];
		}
	}

	DFS(0, 1); // 카운트 0회부터 숫자는 1부터 시작

	cout << ans;
	return 0;
}
// 억울하다 위에 풀이랑 똑같이 쳤는데 왜 시간초과가 발생한거지
// 어쨌든 이런 풀이 (백트래킹 이용)