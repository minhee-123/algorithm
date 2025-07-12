// 문제: https://www.acmicpc.net/problem/11004

// 퀵 정렬 구현 → 내용이 좀 이해가 안가서 교재풀이를 따라함
// 정렬을 전부 구현하기 보다는 K번째까지만 확실히 정렬하는 느낌
// 나중에 복습할 때 다시 보자 (코테에서 퀵 정렬을 굳이 쓰지는 않을 것 같음)

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int partition(vector<int>& A, int start, int end)
{
	if (start + 1 == end)
	{
		if (A[start] > A[end]) swap(A[start], A[end]);
		return end;
	}

	int M = (start + end) / 2;
	swap(A[start], A[M]);
	
	int pivot = A[start];
	int i = start + 1;
	int j = end;

	while (i <= j)
	{
		while (j >= start + 1 && pivot < A[j])
		{
			j--;
		}
		while (i <= end && pivot > A[i])
		{
			i++;
		}

		if (i < j)
		{
			swap(A[i], A[j]);
			i++; j--;
		}
		else break;
	}

	A[start] = A[j];
	A[j] = pivot;
	return j;
}

void quickSort(vector<int>& A, int start, int end, int K)
{
	int pivot = partition(A, start, end);

	if (pivot == K) return;
	else if (K < pivot) quickSort(A, start, pivot - 1, K);
	else quickSort(A, pivot + 1, end, K);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N, K;
	cin >> N >> K;
	K = K - 1; //오름차순 정렬 후 index로 사용함

	vector<int> A(N, 0);
	for (int i = 0; i < N; i++)
	{
		cin >> A[i];
	}

	quickSort(A, 0, N - 1, K);
	cout << A[K];

	return 0;
}