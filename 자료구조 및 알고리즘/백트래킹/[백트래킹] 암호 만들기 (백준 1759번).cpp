//문제: https://www.acmicpc.net/problem/1759
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int L, C; // L(암호의 길이), C(문자의 종류)
vector<char> element;
vector<bool> visit;

bool aeiou(char c) //모음 여부
{
	if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') return true;
	else return false;
}

void BackTrack(int index, string code)
{
	if (code.size() == L)
	{
		int cntA = 0; //모음
		int cntB = 0; //자음

		for (int i = 0; i < L; i++)
		{
			if (aeiou(code[i])) cntA++;
			else cntB++;
		}

		if (cntA >= 1 && cntB >= 2) cout << code << '\n';
		return;
	}

	for (int i = index; i < C; i++)
	{
		if (visit[i]) continue;
		visit[i] = true;
		BackTrack(i, code + element[i]);
		visit[i] = false; //상태해체 (백트래킹, 되돌아옴)
	}
}

int main()
{
	cin >> L >> C;
	
	element.resize(C);
	visit.resize(C, false);
	
	for (int i = 0; i < C; i++) cin >> element[i];
	sort(element.begin(), element.end()); //암호는 무조건 오름차순

	BackTrack(0, "");
	return 0;
}