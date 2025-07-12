// 문제: https://www.acmicpc.net/problem/12891

#include <iostream>
#include <string>
using namespace std;

int S, P;
string DNA;
int ACGT[4] = { 0 };
int check_ACGT[4] = { 0 };

int cnt = 0;

void Add(char c)
{
	if (c == 'A') check_ACGT[0]++;
	else if (c == 'C') check_ACGT[1]++;
	else if (c == 'G') check_ACGT[2]++;
	else if (c == 'T') check_ACGT[3]++;
}

void Remove(char c)
{
	if (c == 'A') check_ACGT[0]--;
	else if (c == 'C') check_ACGT[1]--;
	else if (c == 'G') check_ACGT[2]--;
	else if (c == 'T') check_ACGT[3]--;
}

bool check()
{
	for (int i = 0; i < 4; i++)
	{
		if (check_ACGT[i] < ACGT[i]) return false;
	}
	return true;
}

int main()
{
	cin >> S >> P >> DNA;
	for (int i = 0; i < 4; i++)
	{
		cin >> ACGT[i];
	}

	for (int i = 0; i < P; i++) //첫번째 부분 문자열 (윈도우)
	{
		Add(DNA[i]);
	}
	if (check()) cnt++;

	for (int end = P; end < S; end++) //end는 이동한 후 맨뒤
	{
		int start = end - P; //이동하기 전 맨앞

		Add(DNA[end]);
		Remove(DNA[start]);

		if (check()) cnt++;
	}

	cout << cnt << '\n';
	return 0;
}