// 문제: https://www.acmicpc.net/problem/17298

#include <iostream>
#include <vector>
#include <stack>
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

	vector<int> NGE(N, 0); //오른쪽에 있으면서 i보다 큰 수 중 가장 왼쪽에 있는 수
	stack<int> st;

	st.push(0);
	for (int i = 1; i < N; i++)
	{
		while (!st.empty() && A[st.top()] < A[i])
		{
			int index = st.top();
			NGE[index] = A[i];
			st.pop();
		}
		st.push(i);
	}

	while (!st.empty())
	{
		int index = st.top();
		NGE[index] = -1;
		st.pop();
	}

	for (int i = 0; i < N; i++)
	{
		cout << NGE[i] << ' ';
	}
	return 0;
}