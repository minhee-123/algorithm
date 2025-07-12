// ЦђБе (https://www.acmicpc.net/problem/1546)

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool comp(int a, int b) { return a > b; }

int main()
{
	int N;
	vector<int> sub;

	cin >> N;
	for (int i = 0; i < N; i++)
	{
		int temp;
		cin >> temp;
		sub.push_back(temp);
	}
	sort(sub.begin(), sub.end(), comp);

	int M = sub[0];
	float ave = 0;
	for (int i = 0; i < N; i++)
	{
		float temp = (float)sub[i] / M * 100;
		ave += temp;
	}
	ave = ave / N;

	cout << ave;
	return 0;
}