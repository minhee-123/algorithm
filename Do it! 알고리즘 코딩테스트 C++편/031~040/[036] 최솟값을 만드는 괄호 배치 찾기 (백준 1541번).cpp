// 문제: https://www.acmicpc.net/problem/1541

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
	string st;
	cin >> st;

	int answer = 0;
	bool minus_flag = false;

	string temp = "";
	for (int i = 0; i < st.size(); i++)
	{
		char ch = st[i];
		if (ch != '+' && ch != '-')
		{
			temp += ch;
			if (i != st.size() - 1) continue;
		}

		int num = stoi(temp);
		temp = "";

		if (minus_flag) answer -= num;
		else answer += num;

		if (ch == '-') minus_flag = true;
	}

	cout << answer;
	return 0;
}