// 네 수 (https://www.acmicpc.net/problem/10824)

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

//stoi를 쓰면 굉장히 간단한 문제이지만 수의 범위가 매우 커서 런타임에러 발생

long long int string_to_int(string st)
{
	int st_len = st.length();
	long long int answer = 0;
	for (int i = 0; i < st_len; i++)
	{
		int temp = st[i] - '0';
		answer += temp * pow(10, st_len - (i+1));
	}
	return answer;
}

int main()
{
	string A, B, C, D;
	cin >> A >> B >> C >> D;

	string AB = A + B;
	string CD = C + D;

	long long int AB_int = string_to_int(AB);
	long long int CD_int = string_to_int(CD);
	
	cout << AB_int + CD_int;
	return 0;
}