// 최대공약수와 최소공배수 (https://www.acmicpc.net/problem/2609)

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int A, B, maxD, minM = 1, flag = 0;
vector<int> divA;
vector<int> divB;

void divisorA()
{
	for (int i = A; i > 0; i--)
	{
		if (A % i == 0) divA.push_back(i);
	}
}
void divisorB()
{
	for (int i = B; i > 0; i--)
	{
		if (B % i == 0) divB.push_back(i);
	}
}

int main()
{

	cin >> A >> B;
	divisorA();
	divisorB();

	for (int i = 0; i < divA.size(); i++)
	{
		for (int j = 0; j < divB.size(); j++)
		{
			if (divA[i] == divB[j])
			{
				maxD = divA[i];
				flag = 1;
				break;
			}
		}
		if (flag == 1) break;
	}
	minM = A * B / maxD; //최소공배수 = 두 자연수의 곱 / 최대공약수

	cout << maxD << '\n' << minM;
	return 0;
}


//유클리드 호제법을 적용하면 간단한 알고리즘으로 문제를 풀 수 있음
//유클리드 호제법 설명: https://blogshine.tistory.com/112

//int main()
//{
//	int A, B, maxD = 1;
//	cin >> A >> B;
//	if (A < B)
//	{
//		int temp = A;
//		A = B;
//		B = A;
//	}
//	int minM = A * B;
//
//	int temp;
//	while (B != 0) //함수 빼기 싫어서 안 뺐는데 함수 빼면 더 간단해짐
//	{
//		temp = A % B;
//		A = B;
//		B = temp;
//	}
//	maxD = A;
//	minM = minM / maxD;
//	
//	cout << maxD << '\n' << minM;
//	return 0;
//}