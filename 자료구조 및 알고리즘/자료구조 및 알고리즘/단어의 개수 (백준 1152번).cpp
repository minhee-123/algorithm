// 단어의 개수 (https://www.acmicpc.net/problem/1152)

#include <iostream>
#include <string>
using namespace std;

int main()
{
	int cnt = 0;
	bool flag = true;
	string st;
	getline(cin, st);

	for (int i = 0; i < st.length(); i++) //시작과 끝이 공백일 수도 있으니 생략
	{
		if (st[i] != ' ' && flag)
		{
			cnt++;
			flag = false;
		}

		if (st[i] == ' ' && i != 0 && i != st.length() - 1)
		{
			if (st[i + 1] != ' ' || st[i - 1] != ' ') cnt++;
		}
	}
	cout << cnt;
	return 0;
}