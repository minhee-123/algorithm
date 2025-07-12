// 문제: https://www.acmicpc.net/problem/1931

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct meeting
{
	int start;
	int end;
};

bool comp(meeting a, meeting b)
{
	if (a.end != b.end) return a.end < b.end;
	else return a.start < b.start;
}

int main()
{
	int N; cin >> N;
	vector<meeting> meet(N, { 0, 0 });
	for (int i = 0; i < N; i++) cin >> meet[i].start >> meet[i].end;

	sort(meet.begin(), meet.end(), comp);

	int start = meet[0].start;
	int end = meet[0].end;
	int cnt = 1;
	for (int i = 1; i < N; i++)
	{
		if (meet[i].start >= end)
		{
			cnt++;
			start = meet[i].start;
			end = meet[i].end;
		}
	}

	cout << cnt;
	return 0;
}