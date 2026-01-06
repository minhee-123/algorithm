// 문제: https://www.acmicpc.net/problem/14003
// 그래프에 이진탐색도 추가
// N의 범위가 10^6으로 시간복잡도를 줄이면 좋음 
// → 아래의 B배열은 오름차순으로 저장되기 때문에 이분탐색을 적용할 수 있음

// 이분탐색 함수 (binary_search() / lower_bound() / upper_bound())
// 참고(binary_search): https://m42-orion.tistory.com/69
// 참고(lower, upper bound): https://iridescent-zeal.tistory.com/179
// → 근데 지금은 이걸 못쓴다 (최초로 등장하는 이하의 index를 찾아야 해서) + 직접구현
#include <iostream>
#include <vector>
using namespace std;

int N;
vector<int> D; // D[i] = i번째 원소를 포함하는 가장 긴 증가 부분 수열
vector<int> A; // 수열
vector<int> B; // B[i] = 증가 부분 수열의 길이가 i인 수열의 마지막 원소 (길이가 같은 애들이 여럿 있다면 가장 최근 원소)

int answer_len = 1;
vector<int> answer;

// B[index] < now인 index의 최대값 + 1을 찾음 → now을 저장해야 하는 B의 index를 찾음
// 아래 함수는 B[answer_len] > now일 때 적용됨 (만약 B[answer_len] < now라면 now를 저장해야 하는 index는 answer_len + 1이 되기 때문)
int find_Bindex(int s, int e, int now)
{
	while (s < e)
	{
		int mid = (s + e) / 2;
		if (B[mid] < now) s = mid + 1; // now보다 작은 B값의 다음 index를 s에 저장
		else e = mid;
	} // s랑 e가 차이가 1밖에 나지 않는 경우 → mid == s가 됨 (숫자를 대입해보면 알 수 있음)
	return s;
}
// 이게 결국 lower_bound와 같아짐 
// 크거나 같은 값이 처음 나오는 위치를 찾음(lower_bound) → now보다 작은 인덱스의 + 1

int main()
{
	cin >> N;
	D.resize(N + 1);
	A.resize(N + 1);
	B.resize(N + 1); // index는 모두 1부터 사용

	for (int i = 1; i <= N; i++) cin >> A[i];
	D[1] = 1;
	B[1] = A[1]; // 부분 수열 길이가 1인 수열의 마지막 원소는 A[1] → 시작 값(초기화)

	// DP테이블 채우기
	for (int index = 2; index <= N; index++)
	{
		// D[index] = max(D[k]) + 1 → k = 1에서 index-1까지
		// 이때 A[k] < A[index] 조건을 만족해야 함 (그래야 증가 부분 순열이 됨)
		int now = A[index]; // 현재 원소 값

		if (B[answer_len] < now)
		{
			answer_len++;
			D[index] = answer_len;
			B[answer_len] = now;
		}
		else if (B[answer_len] == now)
		{
			D[index] = answer_len;
		}
		else // B[answer_len] > now
		{
			int len = find_Bindex(1, answer_len, now);
			D[index] = len;
			B[len] = now;
		}
	}

	// 정답 수열 찾기 및 출력
	cout << answer_len << '\n';
	int index = N;
	int find_len = answer_len;
	while (index >= 1)
	{
		if (D[index] == find_len)
		{
			answer.push_back(A[index]);
			find_len--;
		}
		index--;
	}
	for (int i = answer.size() - 1; i >= 0; i--) cout << answer[i] << ' ';
	return 0;
}
// 와 진짜 너무너무 어렵다
// DP 식을 찾아내는 것도 너무 까다롭고 B 배열을 활용하는 것도 머리아픔
// 여기에 시간초과를 방지하기 위해 이분탐색을 적용해야 함
// 나중에 차근차근 한번 더 풀어보자... 지금 100% 습득하기에는 스트레스 받아서 울 것 같다

// lower_bound의 개념이 좀 머리에 안 잡혀서 직접 구현해버렸다 (구현한 이분탐색 함수가 결국 lower_bound랑 같은 역할)
// lower_bound = 찾으려는 값 이상의 숫자가 처음 나타나는 위치 (다르게 생각하면 찾으려는 값보다 작은 숫자가 마지막으로 나타나는 위치 + 1)
// upper_bound = 찾으려는 값 초과의 숫자가 처음 나타나는 위치
// 
// 만약 lower_bound랑 upper_bound의 조건에 맞는 숫자가 없다면 탐색 범위의 끝을 반환함 (vec.end()를 반환, 배열 기준으로 범위를 하나 벗어난 인덱스)
// → 찾는 조건에 없으니 배열 맨 끝에 새롭게 추가하라는 의미
//
// upper_bound - lower_bound를 하면 배열 내에 존재하는 특정 값의 개수를 바로 구할 수 있음 (upper은 초과, lower은 이상이라서)
// upper_bound - 1은 특정값보다 같거나 작은 값들이 있는 영역의 마지막 위치와 같음