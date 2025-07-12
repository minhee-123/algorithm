// 문제: https://www.acmicpc.net/problem/1197
#include <iostream>
#include <queue>
using namespace std;

struct EDGE
{
	int A;
	int B;
	int C;
};

struct comp
{
	bool operator()(EDGE num1, EDGE num2)
	{
		return num1.C > num2.C;
		//우선순위 큐의 비교함수는 두 값 중 어떤 값이 더 우선순위가 낮은가를 반환 (위 경우는 오름차순)(num1.C가 더 크다면 num1이 우선순위가 더 낮음)
		//C언어의 qsort와 유사하게 생각해도 됨 (양수값 true(자리를 바꿔야함), 음수값 false(자리를 유지함))
	}
};

int V, E, UF[10001];
priority_queue<EDGE, vector<EDGE>, comp> edges;

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
	cin >> V >> E;
	for (int i = 1; i <= V; i++) UF[i] = i; //Union-Find 배열 초기화
	for (int i = 0; i < E; i++) //에지가 기준 (에지를 중심으로 알고리즘 전개)
	{
		EDGE temp;
		cin >> temp.A >> temp.B >> temp.C;
		edges.push(temp);
	}

	int connect = 0;
	int answer = 0;
	while (connect < V - 1) //connect가 V-1이 되는 순간 break (간선의 수가 N-1이 될때까지 반복)
	{
		EDGE temp = edges.top();
		edges.pop();

		if (Find(temp.A) == Find(temp.B)) continue; //사이클 형성 주의
		else //같은 집합에 속해있지 않음
		{
			Union(temp.A, temp.B); //현재 선택한 노드 연결
			answer += temp.C;
			connect++;
		}
	}

	cout << answer;
	return 0;
}