// 문제: https://www.acmicpc.net/problem/1043

#include <iostream>
using namespace std;

int N, M;
int liar_party = 0;

int true_num;
int true_person;
int party_person[51];
int person[51];

int Find(int c)
{
	if (person[c] == c) return c;
	else return person[c] = Find(person[c]);
}

void Union(int a, int b)
{
	a = Find(a);
	b = Find(b);
	if (a != b) person[b] = a; //굳이 가장 작은 값이 대표값이 되어야하는 건 아님
}

int main()
{
	cin >> N >> M;
	for (int i = 1; i <= N; i++) person[i] = i;

	cin >> true_num;
	if (true_num != 0)
	{
		cin >> true_person;
		for (int i = 1; i < true_num; i++)
		{
			int tp; 
			cin >> tp;

			Union(true_person, tp);
		}
	}

	for (int i = 0; i < M; i++)
	{
		int num; 
		cin >> num;
		int pp; 
		cin >> pp;

		party_person[i] = pp;
		for (int j = 1; j < num; j++)
		{
			int pp2; cin >> pp2;
			Union(pp, pp2);
		}
	}

	int value = Find(true_person);
	for (int i = 0; i < M; i++)
	{
		int comp = Find(party_person[i]);
		if (value != comp) liar_party++;
	}

	cout << liar_party;
	return 0;
}