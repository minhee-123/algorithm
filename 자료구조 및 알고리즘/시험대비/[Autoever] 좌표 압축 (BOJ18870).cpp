// 문제: https://www.acmicpc.net/problem/18870
// 알고리즘: 좌표압축
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 혹시 코딩테스트 언어 제한이 C언어일 경우
// C언어로 다시 풀어봐야 함 (아이디어는 똑같은데 구현이 꽤 달라지니까)

int N;
struct NUM
{
	int origin;
	int location;
	int compression;
};
vector<NUM> number;

bool flag = true;
bool comp(NUM A, NUM B)
{
	if (flag) // origin을 기준으로 오름차순 정렬
	{
		if (A.origin != B.origin) return A.origin < B.origin;
		else return A.location < B.location;
	}
	else // location을 기준으로 오름차순 정렬
	{
		if (A.location != B.location) return A.location < B.location;
		else return A.origin < B.origin;
	}
	// 새삼스럽지만 sort는 디폴트가 오름차순 (우선순위 큐는 디폴트가 내림차순)
	// 오름차순이 작은것부터 큰것으로 올라가고, 내림차순이 큰것부터 작은것으로 내려감
}

int main()
{
	cin >> N;
	number.resize(N);

	for (int i = 0; i < N; i++)
	{
		cin >> number[i].origin;
		number[i].location = i;
	}
	sort(number.begin(), number.end(), comp); // origin을 기준으로 오름차순

	int index = 0;
	int pre_num = 0;
	for (int i = 0; i < N; i++)
	{
		if (i == 0)
		{
			number[i].compression = index;
			pre_num = number[i].origin;
		}
		else
		{
			if (pre_num == number[i].origin) // 앞선 숫자와 같은 경우
			{
				number[i].compression = index;
			}
			else
			{
				index++;
				number[i].compression = index;
				pre_num = number[i].origin;
			}
		}
	}

	flag = false;
	sort(number.begin(), number.end(), comp); // location을 기준으로 오름차순

	for (int i = 0; i < N; i++) cout << number[i].compression << ' ';
	return 0;
}