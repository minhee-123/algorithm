// 문제: https://www.acmicpc.net/problem/4195

// 문제가 좀 헷갈리는데 분석하면
// → 입력으로 받은 두 사람을 같은 그룹으로 묶고(네트워크)
// → 두 사람이 속한 그룹(네트워크)의 크기를 출력

#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

int T; //테스트 케이스의 수
int F; //친구 관계의 수

int index = 0;
vector<int> group;
vector<int> sizes;
map<string, int> m;

int Find(int c)
{
	if (group[c] == c) return c;
	else return group[c] = Find(group[c]);
}

int Union(int a, int b)
{
	a = Find(a);
	b = Find(b);

	if (a == b) return sizes[a];

	if (a > b) swap(a, b);
	group[b] = a; //대표노드로 작은 값을 사용
	sizes[a] += sizes[b]; //대표노드의 크기 증가 (그룹으로 묶였으니까)
	return sizes[a];
}

void Network()
{
	cin >> F;
	for (int i = 0; i < F; i++)
	{
		string a, b;
		cin >> a >> b;

		int A, B; //string 값을 정수로 사용

		if (m.find(a) != m.end()) A = m[a]; //map에 넣어둔 이름일 경우
		else //새로 나온 이름일 경우
		{
			m[a] = index;
			A = index;
			sizes.push_back(1); //본인만 포함하기 때문에 초기값은 1
			group.push_back(index++); //대표노드로 본인 index
		}

		if (m.find(b) != m.end()) B = m[b]; //map에 넣어둔 이름일 경우
		else //새로 나온 이름일 경우
		{
			m[b] = index;
			B = index;
			sizes.push_back(1);
			group.push_back(index++);
		}

		int result = Union(A, B); //A와 B를 묶고 두 사람이 속한 그룹의 크기를 출력함
		cout << result << '\n';
	}
}

int main()
{
	ios::sync_with_stdio;
	cin.tie(NULL);
	cout.tie(NULL); //시간초과 대비

	cin >> T;
	for (int i = 0; i < T; i++)
	{
		m.clear();
		group.clear();
		sizes.clear();
		index = 0;

		Network();
	}
	return 0;
}

// 시간초과 문제가 발생했었음 
// → 원래는 매 쌍마다 전체 그룹을 순회하며 네트워크 크기를 계산 (시간복잡도가 O(N^2), F가 최대 10^5이므로 시간터짐)
// → Union 함수에 size 배열을 추가해서 각 대표 노드가 포함하는 집합의 크기를 관리