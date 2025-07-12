// 문제: https://www.acmicpc.net/problem/1517

#include <iostream>
#include <vector>
using namespace std;

vector<int> A;
vector<int> temp;

long cnt = 0;

void merge_sort(int s, int e)
{
	if (e - s < 1) return;
	int m = s + (e - s) / 2;

	merge_sort(s, m);
	merge_sort(m + 1, e);

	for (int i = s; i <= e; i++) temp[i] = A[i];

	int k = s;
	int index1 = s; //그룹 1의 범위는 s ~ m
	int index2 = m + 1; //그룹 2의 범위는 m+1 ~ e

	while (index1 <= m && index2 <= e)
	{
		if (temp[index1] <= temp[index2]) 
		//temp[index1] == temp[index2] 같은 숫자일 때 swap은 발생하지 않음 (굳이 이동하지 않음)
		//그러니까 앞에 있는 temp[index1]이 k에 위치하게 됨
		{
			A[k] = temp[index1];

			if (k < index1) cnt += index1 - k; //사실상 true가 될 수 없음 (k >= index1)
			k++;
			index1++;
		}
		else
		{
			A[k] = temp[index2];

			if (k < index2) cnt += index2 - k;
			k++;
			index2++;
		}
	}

	while (index1 <= m)
	{
		A[k] = temp[index1];
		k++;
		index1++;
	}
	while (index2 <= e)
	{
		A[k] = temp[index2];
		k++;
		index2++;
	}
}

int main()
{
	int N;
	cin >> N;

	A = vector<int>(N, 0);
	temp = vector<int>(N, 0);
	for (int i = 0; i < N; i++)
	{
		cin >> A[i];
	}

	merge_sort(0, N - 1);

	cout << cnt << '\n';
	return 0;
}