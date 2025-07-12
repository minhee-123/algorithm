// 요세푸스 문제 0 (https://www.acmicpc.net/problem/11866)

#include <iostream>
#include <list>
#include <vector>
using namespace std;

int main()
{
	int N, K;
	cin >> N >> K;

	list<int> cir;
	for (int i = 1; i <= N; i++)
	{
		cir.push_back(i);
	}
	list<int>::iterator c_iter = cir.begin();

	int cnt = 1;
	vector<int> yose;
	while (!cir.empty())
	{
		if (c_iter == cir.end()) c_iter = cir.begin(); //end()가 가리키는 곳은 마지막 원소의 "다음" 위치

		if (cnt == K) //K번째라면
		{
			yose.push_back(*c_iter);
			c_iter = cir.erase(c_iter);
			cnt = 1;
		}
		else
		{
			c_iter++;
			cnt++;
		}
	}

	//출력
	cout << "<" << yose[0];
	for (int i = 1; i < yose.size(); i++)
	{
		cout << ", " << yose[i];
	}
	cout << ">";
	return 0;
}

//자료구조 큐를 사용하면 더 간단하게 풀 수 있음 (풀이법은 조금 달라짐)
//참고: https://baehoon.tistory.com/6