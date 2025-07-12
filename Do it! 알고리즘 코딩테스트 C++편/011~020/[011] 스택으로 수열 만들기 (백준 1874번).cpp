// 문제: https://www.acmicpc.net/problem/1874

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int main()
{
	int len;
	cin >> len;

	vector<int> A(len, 0);
	for (int i = 0; i < len; i++)
	{
		cin >> A[i];
	}

	vector<char> result;
	bool flag = true; //NO를 출력했는지 확인 (출력했으면 false로 바꿈)
	
	stack<int> st;
	int number = 1; //스택에 넣는 숫자 1부터 시작

	for (int i = 0; i < len; i++)
	{
		if (A[i] >= number) //현재 수열이 스택에 넣을 숫자보다 크다면
		{
			while (A[i] >= number) 
			{
				st.push(number);
				number++;
				result.push_back('+');
			}
			st.pop();
			result.push_back('-');
		}
		else // A[i] < number //현재 수열이 스택에 넣을 숫자보다 작다면 (스택에 넣어둔 수로 해결해야지)
		{
			if (st.top() != A[i]) //맨 위에 있는게 현재 수열과 다르다면
			{
				cout << "NO" << '\n';
				flag = false;
				break;
			}
			else
			{
				st.pop();
				result.push_back('-');
			}
		}
	}

	if (flag)
	{
		for (int i = 0; i < result.size(); i++)
		{
			cout << result[i] << '\n';
		}
	}
	return 0;
}