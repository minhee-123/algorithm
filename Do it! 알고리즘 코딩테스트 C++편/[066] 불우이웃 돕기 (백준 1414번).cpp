// 문제: https://www.acmicpc.net/problem/1414
#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

struct line
{
	int A;
	int B;
	int len;
};

struct comp
{
	bool operator()(line num1, line num2)
	{
		return num1.len > num2.len; //가중치를 기준으로 오름차순 정렬
	}
};

int N, total_len = 0;
vector<int> UF;
priority_queue<line, vector<line>, comp> edges;

int Find(int c)
{
	if (UF[c] == c) return c;
	else return UF[c] = Find(UF[c]);
}

void Union(int a, int b)
{
	a = Find(a);
	b = Find(b);
	if (a != b) UF[b] = a;
}

int main()
{
	cin >> N;
	for (int i = 1; i <= N; i++)
	{
		string temp;
		cin >> temp;

		for (int j = 1; j <= N; j++)
		{
			char ch = temp[j - 1];
			if (ch == '0') continue;

			int len = 0;
			if (ch >= 'a' && ch <= 'z') len = ch - 'a' + 1; //소문자인 경우
			else len = ch - 'A' + 27; //대문자인 경우
			
			total_len += len;
			if (i != j) edges.push({ i, j, len });
		}
	}

	UF.resize(N + 1);
	for (int i = 1; i <= N; i++) UF[i] = i;

	int answer = 0;
	int connect = 0;
	while (connect < N - 1)
	{
		if (edges.empty()) break;

		line temp = edges.top();
		edges.pop();

		if (Find(temp.A) == Find(temp.B)) continue;
		else
		{
			Union(temp.A, temp.B);
			answer += temp.len;
			connect++;
		}
	}

	if (connect < N - 1) cout << -1; //컴퓨터 연결되지 않은 경우
	else cout << total_len - answer;
	return 0;
}