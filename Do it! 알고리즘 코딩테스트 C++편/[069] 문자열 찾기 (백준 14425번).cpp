// 문제: https://www.acmicpc.net/problem/14425
#include <iostream>
#include <set>
#include <string>
using namespace std;
// 트라이를 구현해보는 문제
// 본 문제 자체는 set이나 map을 사용하면 간단하게 풀린다
// → 트라이를 사용하는 건 못하겠어서 일단 set이나 map으로 풀이 (트라이 구현은 교재 참고)

// 굳이 key-value를 사용할 필요는 없어서 set 사용
// set 특징
// 1. 숫자든 문자든 중복을 없앰 (중복되어서 입력되지 않음)
// 2. 삽입하는 순서에 상관없이 정렬되어서 입력됨
// 3. 이진트리의 특성상 삽입과 삭제가 용이함
// → 멤버함수는 map과 거의 동일함 (set은 key와 value가 동일한 map)

int main()
{
	int N, M;
	cin >> N >> M;

	set<string> container;
	for (int i = 0; i < N; i++)
	{
		string str;
		cin >> str;
		container.insert(str);
	}

	int answer = 0;
	for (int i = 0; i < M; i++)
	{
		string str;
		cin >> str;
		if (container.find(str) != container.end()) answer++; //str이 없으면 set의 end 위치를 반환함 (있으면 해당 키를 가리키는 주소 반환)
	}

	cout << answer;
	return 0;
}

// 참고로 value값에 접근하는 방법으로 m[key]를 사용해도 됨 (인덱스 접근은 안되는데 key 접근은 되네)
// 문자를 대표로 사용하고 싶을때 유용할 듯 (정렬이 필요없으면 unordered_map 사용하자 → 연산이 빠름)