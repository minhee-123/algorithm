//문제: https://www.acmicpc.net/problem/1339
//백트래킹 문제인 줄 알고 시작했는데 그리디였다
//각 문자의 자릿수 합을 구하고 → 자릿수가 큰 순서대로 숫자 변환
//같은 알파벳인 건 어떻게 구분하지 → 알파벳 배열 선언해서 저장 (알파벳 배열이라는 구상이 꽤 유용한듯)
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

int N;
int ch[26]; //대문자 알파벳 (A → 0 ... Z → 25)
vector<string> voca;

bool comp(int a, int b) { return a > b; }

int main()
{
	cin >> N;
	voca.resize(N);

	for (int i = 0; i < N; i++)
	{
		cin >> voca[i];
		for (int k = voca[i].size() - 1; k >= 0; k--)
		{
			ch[voca[i][k] - 'A'] += pow(10, voca[i].size() - k - 1);
		}
	}
	sort(ch, ch + 26, comp);

	int answer = 0;
	for (int i = 0; i <= 9; i++)
	{
		answer += ch[i] * (9 - i);
	}

	cout << answer;
	return 0;
}