// 문제: https://www.acmicpc.net/problem/1546
// 계산 과정을 나누지 말고 한번에 계산하는 방법을 채택하면 간결함

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int cnt;
	cin >> cnt;

	vector<int> score;
	for (int i = 0; i < cnt; i++)
	{
		int temp;
		cin >> temp;
		score.push_back(temp);
	}

	int total = 0;
	int max_score = score[0];
	for (int i = 0; i < cnt; i++)
	{
		total += score[i];
		if (max_score < score[i]) max_score = score[i];
	}

	double answer = total * 100.0 / max_score / cnt; //계산 부분을 실수형으로 변환해야 되는 것 주의
	cout << answer;
	return 0;
}