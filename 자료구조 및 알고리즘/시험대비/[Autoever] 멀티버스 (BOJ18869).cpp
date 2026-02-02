// 문제: https://www.acmicpc.net/problem/18869
// 알고리즘: 좌표압축 및 스위핑
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int M, N;
vector<int> univ[100];

int main()
{
	cin >> M >> N;
	for (int i = 0; i < M; i++)
	{
		vector<int> temp(N);
		for (int j = 0; j < N; j++) cin >> temp[j];

		vector<int> sort_temp = temp;
		sort(sort_temp.begin(), sort_temp.end());

		for (int j = 0; j < N; j++)
		{
			// temp[j]가 처음 등장하는 위치(iterator 형태이기 때문에 begin을 빼줘야 함 → 그래야 index)
			int index = lower_bound(sort_temp.begin(), sort_temp.end(), temp[j]) - sort_temp.begin();
			univ[i].push_back(index); // 원소 순위 배열
		}
	}

	int answer = 0;
	for (int i = 0; i < M - 1; i++)
	{
		for (int j = i + 1; j < M; j++)
		{
			bool flag = true;

			for (int k = 0; k < N; k++)
			{
				if (univ[i][k] != univ[j][k])
				{
					flag = false;
					break;
				}
			}

			if (flag) answer++;
		}
	}

	cout << answer;
	return 0;
}

// 처음 시도한 풀이법
// (1) vector pair로 선언한 후 첫번째 원소에는 값, 두번째 원소에는 index
// (2) 첫번째 원소를 기준으로 정렬 + index 순서가 결정되고 해당 index 순서로 쌍을 찾음
// (3) 이때 문제는 같은 원소가 있을 때 index 순서 비교가 제대로 안됨 (증감을 비교하는 것도 추가했으나 근본적으로 sort는 같은 값의 순서를 보장하지 않음(순서가 달라질 수 있음))

// 두번째로 시도한 풀이법
// 각 우주를 독립적으로 압축 → 새로운 수열로 바꿈
// 원래 수열의 각 원소가 몇번째 순위인지로 값을 치환 → 변화된 순위 수열 자체가 같은지 비교
// ★ 각 원소가 몇번째 순위인지는 이진탐색 함수(lower_bound, upper_bound)를 이용하면 쉽게 찾을 수 있음 (좌표 압축에 이진탐색 활용!)
// ★ 이진탐색 알고리즘 자체가 원하는 값을 찾아나가는 것 → 원하는 값이 몇번째인지 (참고로 오름차순 정렬이 필요함)