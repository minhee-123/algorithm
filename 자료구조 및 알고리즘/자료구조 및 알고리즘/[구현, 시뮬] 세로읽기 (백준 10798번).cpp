// 세로읽기 (https://www.acmicpc.net/problem/10798)
// 무조건 string을 쓰려고 하지는 말 것 (char로 해야 풀리는 것도 있음)

#include <iostream>
using namespace std;

int main()
{
	char word[5][15] = { }; //배열 초기화 (그래야 NULL값을 가지게 됨)
	for (int i = 0; i < 5; i++)
	{
		cin >> word[i]; //문자를 하나씩 받아옴 (엔터로 행 구분됨)
	}

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (word[j][i] == NULL) continue;
			else cout << word[j][i];
		}
	}
	return 0;
}