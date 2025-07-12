// 문제: https://www.acmicpc.net/problem/11399

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int N;
	cin >> N;

	vector<int> A(N, 0);
	for (int i = 0; i < N; i++)
	{
		cin >> A[i];
	}

	for (int i = 1; i < N; i++) //삽입정렬 - 오름차순
	{
		int index = i;
		int value = A[i];

		for (int j = 0; j < i; j++)
		{
			if (A[j] > value)
			{
				index = j;
				break; //현재 index 앞부분은 모두 정렬이 되어있음 (삽입 정렬을 하면서 index++ 하니까)
			}
		}

		if (index == i) continue; //이동없음
		else
		{
			for (int k = i; k > index; k--)
			{
				A[k] = A[k - 1]; //index+1 부터 i-1까지 오른쪽으로 한칸씩 shift
			}
			
			A[index] = value;
		}
	}

	vector<int> S(N, 0);
	S[0] = A[0];
	for (int i = 1; i < N; i++)
	{
		S[i] = A[i] + S[i - 1];
	}

	int answer = 0;
	for (int i = 0; i < N; i++)
	{
		answer += S[i];
	}
	cout << answer << '\n';
	return 0;
}