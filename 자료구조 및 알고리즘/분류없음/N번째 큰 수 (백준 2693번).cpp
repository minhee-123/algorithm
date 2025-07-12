// N번째 큰 수 (https://www.acmicpc.net/problem/2693)

#include <iostream>
#include <algorithm>
using namespace std;

int T, N = 3;

bool desc(int a, int b) { return a > b; }
void output()
{
	int arr[10] = {};
	for (int i = 0; i < 10; i++)
	{
		cin >> arr[i];
	}
	sort(arr, arr + 10, desc);
	cout << arr[N - 1] << '\n';
}

int main()
{
	cin >> T;
	for (int i = 0; i < T; i++) output();
	return 0;
}