// 문제: https://www.acmicpc.net/problem/2751

#include <iostream>
#include <vector>
using namespace std;

vector<int> A; //전역변수로 선언
vector<int> tmp;

void merge_sort(int s, int e) //start, end
{
	if (e - s < 1) return; //start와 end index의 차이가 1보다 작다면 (start와 end가 같거나 start가 더 큰 경우)

	int m = s + (e - s) / 2; //중간 지점 (index가 0~3이라면 m이 1이 되어서 0,1이랑 2,3으로 나누어짐)

	merge_sort(s, m); //분할 (최대한 분할한 후 정렬 > 병합 > 정렬 > 병합 ... 반복함)
	merge_sort(m + 1, e);

	for (int i = s; i <= e; i++)
	{
		tmp[i] = A[i];
	}

	int k = s;
	int index1 = s; //그룹 1은 s~m
	int index2 = m + 1; //그룹 2는 m+1~e

	while (index1 <= m && index2 <= e) //두개의 그룹 병합
	{
		if (tmp[index1] < tmp[index2])
		{
			A[k] = tmp[index1];
			k++;
			index1++;
		}
		else
		{
			A[k] = tmp[index2];
			k++;
			index2++;
		}
	}

	while (index1 <= m) //index1이 남은 경우
	{
		A[k] = tmp[index1];
		k++;
		index1++;
	}
	while (index2 <= e) //index2가 남은 경우
	{
		A[k] = tmp[index2];
		k++;
		index2++;
	}
}

int main()
{
	int N;
	cin >> N;

	A = vector<int> (N, 0); //내용은 여기서 채움
	tmp = vector<int> (N, 0); 
	for (int i = 0; i < N; i++)
	{
		cin >> A[i];
	}

	merge_sort(0, N - 1);

	for (int i = 0; i < N; i++)
	{
		cout << A[i] << '\n';
	}
	return 0;
}