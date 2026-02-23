# 자료구조 및 알고리즘
> 자료구조 및 알고리즘을 공부하고 풀이한 문제를 정리한 공간입니다. 하단의 내용은 C++를 기준으로 자료구조 이해 및 STL 사용법, 알고리즘 문제풀이 팁을 정리합니다.
<br>

**🌱 이전 공부 내역 및 정리 (네이버 블로그)**
<br>[C++ 문법](https://blog.naver.com/valsgml/223540967988)
<br>[자료구조 및 라이브러리](https://blog.naver.com/valsgml/223598534580)

<br>

---

## 🧩 자료구조 및 STL
#### STL의 기본 구성
- **컨테이너 (Container)**: 임의 타입의 객체를 보관할 수 있는 보관함
- **반복자 (Iterator)**: 컨테이너 원소에 접근할 수 있는 포인터와 유사한 객체 (포인터와 비슷하게 동작하며 원소의 주소를 저장하고 역참조로 원소를 가져옴)
- **알고리즘 (Algorithm)**: 반복자들을 가지고 일련의 작업을 수행하는 알고리즘
<br>

### 📍 선형 (연속) 컨테이너
<br>

#### 1️⃣ 배열 (Array)
같은 자료형의 변수를 일렬로 저장하는 자료구조

- **Header**: `#include <iostream>`

**시간 복잡도**
- 접근: `O(1)` (랜덤 액세스 가능)
- 검색: `O(n)` (인덱스를 모를 때 하나하나 확인해야 함)
- 삽입/삭제  
  - 맨 뒤: `O(1)`  
  - 중간/앞: `O(n)`

**사용 방법**
```cpp
// 선언: 자료형 변수이름 [변수길이]
int counts[10] = {}; // 모든 요소를 0으로 초기화하여 선언

// 문자열: char 타입 배열 (마지막 문자 '\0')
// 또는 #include <string> 사용
string s = "hello";

// 동적 배열 할당: new 사용 후 delete로 해제 필수
int * psome = new int [10];
psome[0] = 0.2;
delete [] psome; 
psome = nullptr; // 오류 방지 초기화
```
<br>

#### 2️⃣ 벡터 (Vector)
자동으로 메모리가 할당(동적 할당)되는 배열 → 배열 기반 컨테이너

- **Header**: `#include <vector>`
- **특징**: 인덱스 접근 가능, 요소가 메모리 상 연속적 할당, 스택과 유사한 구조

**시간 복잡도**
- 접근: `O(1)` 
- 검색: `O(n)` 
- 삽입/삭제  
  - 맨 뒤: `O(1)` (재할당 시 O(n))  
  - 임의 위치: `O(n)`

**사용 방법**
```cpp
vector<int> v;        // 빈 벡터 생성
vector<int> v(5);     // 0으로 초기화된 5개 원소
vector<int> v(5, 2);  // 2로 초기화된 5개 원소
vector<int> v2(v1);   // v1 복사 생성
vector<int>::iterator iter; // 반복자 선언

// 주요 함수
v.begin();  // 0번째 원소 주소 반환
v.end();    // 마지막 원소 다음 위치 주소 반환
v.front();  // 0번째 원소 반환
v.back();   // 마지막 원소 반환
v.push_back(val); // 맨 뒤 삽입
v.pop_back();     // 맨 뒤 삭제
v.insert(v.begin()+1, 99); // 1번째 위치 앞에 99 삽입 (기존 원소 밀림)
v.erase(v.begin()+2);      // 2번째 원소 삭제 (뒤 원소 앞당겨짐)
v.clear();     // 모든 원소 제거 (size만 0, capacity는 유지)
v.size();      // 원소 개수 반환
v.capacity();  // 할당된 공간 크기 반환
```
<br>

#### 3️⃣ 스택 (Stack)
LIFO(Last In First Out, 후입선출) 구조의 컨테이너

- **Header**: `#include <stack>`
- **특징**: 목록 끝에서만 접근 발생, 인덱스 접근 불가, DFS 알고리즘에 주로 사용

**시간 복잡도**
- 접근: `O(1)` (맨 뒤에서만 발생)
- 삽입/삭제: `O(1)` (맨 뒤에서만 발생)

**사용 방법**
```cpp
stack<int> s;
s.push(val); // 맨 뒤 추가
s.pop();     // 맨 뒤 삭제
s.top();     // 가장 위(맨 뒤) 원소 반환
s.size();    // 원소 개수
s.empty();   // 비어있는지 확인
```
<br>

#### 4️⃣ 큐 (Queue)
FIFO(First In First Out, 선입선출) 구조의 컨테이너

- **Header**: `#include <queue>`
- **특징**: 데이터 입력 순서대로 처리 필요 시 이용, 인덱스 접근 불가, BFS 및 Flood Fill 사용

**시간 복잡도**
- 접근/삭제: `O(1)` (맨 앞에서만 발생)
- 삽입: `O(1)` (맨 뒤에서만 발생)

**사용 방법**
```cpp
queue<int> q;
q.push(val); // 맨 뒤 삽입
q.pop();     // 맨 앞 삭제
q.front();   // 맨 앞 원소 반환
q.back();    // 맨 뒤 원소 반환
```
<br>

#### 5️⃣ 덱 (Deque)
큐와 스택을 합친 형태로, 양쪽 끝에서 삽입/삭제가 가능

- **Header**: `#include <deque>`
- **특징**: 인덱스 접근 가능, 앞뒤 삽입/삭제 발생 시 벡터보다 우수하나 중간 처리는 느림

**시간 복잡도**
- 접근: `O(1)` 
- 검색: `O(n)` 
- 삽입/삭제  
  - 맨 뒤: `O(1)` (재할당 시 O(n))  
  - 임의 위치: `O(n)`

**사용 방법**
```cpp
deque<int> dq;
dq.push_front(val); // 맨 앞 삽입
dq.push_back(val);  // 맨 뒤 삽입
dq.pop_front();     // 맨 앞 삭제
dq.pop_back();      // 맨 뒤 삭제
// 그 외 insert, erase, begin, end 등은 벡터와 동일
```
<br>

#### 6️⃣ 연결 리스트 (Linked List)
C++ 리스트는 이중 연결 리스트(Doubly Linked List)

- **Header**: `#include <list>`
- **특징**: 노드 기반 컨테이너, 데이터와 포인터로 연결, 인덱스 접근 불가(한 칸씩 이동 필요)

**시간 복잡도**
- 접근: `O(n)` 
- 임의 위치 삽입/삭제: `O(n)` 

**사용 방법**
```cpp
list<int> lt;
list<int>::iterator iter; // iter+숫자 불가, iter++, iter--만 가능

lt.push_front/back(); // 앞뒤 삽입
lt.pop_front/back();  // 앞뒤 삭제
lt.insert(pos, val);  // pos 앞에 삽입
lt.erase(pos);        // 해당 위치 삭제
lt.remove(val);       // 값과 같은 모든 원소 제거
lt.unique();          // 인접한 중복 원소 삭제
lt.sort();            // 오름차순 정렬
lt.splice(pos, lt2);  // lt2를 pos 위치에 잘라붙이기
```
<br>

### 📍 비선형 (연관) 컨테이너
<br>

#### 1️⃣ 맵 (Map) & 해시맵 (Unordered Map)

- **Header**: `#include <map>` (맵) `#include <unordered_map>` (해시맵)
- **맵의 특징**
  - 각 노드가 key와 value 쌍으로 이루어진 컨테이너
  - 중복된 key 값을 사용할 수 없음, 인덱스 접근 불가능
  - 원소가 오름차순 자동 정렬
 
**맵의 시간 복잡도**
- 검색: `O(log(n))` 
- 삽입/삭제: `O(log(n))`

**맵의 사용 방법**
```cpp
map<int, int> m1;   //key-int형, value-int형
map<string, int> m2;   //key-string형, value-int형

m[key] = value;   //연산자 []를 사용해서 key, value의 추가 또는 수정이 가능함
//key를 이용해 접근(m[key])도 가능하지만 인덱스 접근은 불가능하기 때문에 반복문 등에서는 iterator 사용

map<int, int>::iterator iter;   //맵(int, int pair)의 iterator인 iter 선언

//위치
m.begin();   //맨 앞의 원소의 주소 반환 (iterator에 저장해서 사용 가능)
m.end();   //맨 마지막 원소 다음의 주소 반환 (원소의 끝부분 주소)
m.find(key);   //해당 키를 가리키는 주소를 반환 (iterator) (키가 없다면 m.end() 반환)
//iterator의 first, second를 통해 key, value에 접근 
m.lower_bound(key);   //해당 키 이상인 것들 중 가장 작은 키를 가리키는 주소 반환 (iterator)
m.upper_bound(key);   //해당 키를 초과하는 것들 중 가장 작은 키를 가리키는 주소 반환 (iterator)

//삽입과 삭제 (연산)
m.insert(make_pair(key, value));   //key와 value 삽입
m.insert({key, value});
m[key] = value;
m.erase(key);   //해당 키의 원소를 삭제
m.count(key);   //키에 해당하는 원소들의 개수 반환 (value가 저장되는 공간을 배열, 벡터 등으로 선언하면 하나의 키에 여러 개의 원소가 저장됨)

//초기화와 용량
m.clear();   //모든 원소 제거
m.empty();   //맵이 비어있는지 확인 (true, false)
m.size();   //원소들의 개수 반환
```
- **해시맵의 특징**
  - 맵과 동일한 특징을 가짐
  - **BUT** 원소가 자동으로 정렬되지 않음 (해시테이블로 구현)
 
**해시맵의 시간 복잡도**
- 검색: `O(1)` 
- 삽입/삭제: `O(1)`

**해시맵의 사용 방법**
```cpp
unordered_map<int, int> hm1;   //key-int형, value-int형
unordered_map<string, int> hm2;   //key-string형, value-int형

hm[key] = value;   //연산자 []를 사용해서 key, value의 추가 또는 수정이 가능함
//key를 이용해 접근(m[key])도 가능하지만 인덱스 접근은 불가능하기 때문에 반복문 등에서는 iterator 사용

unordered_map<int, int>::iterator iter;   //해시맵(int, int pair)의 iterator인 iter 선언

//위치
hm.begin();   //맨 앞의 원소의 주소 반환 (iterator에 저장해서 사용 가능)
hm.end();   //맨 마지막 원소 다음의 주소 반환 (원소의 끝부분 주소)
hm.find(key);   //해당 키를 가리키는 주소를 반환 (iterator) (키가 없다면 hm.end() 반환)
//iterator의 first, second를 통해 key, value에 접근 
hm.lower_bound(key);   //해당 키 이상인 것들 중 가장 작은 키를 가리키는 주소 반환 (iterator)
hm.upper_bound(key);   //해당 키를 초과하는 것들 중 가장 작은 키를 가리키는 주소 반환 (iterator)

//삽입과 삭제 (연산)
hm.insert(make_pair(key, value));   //key와 value 삽입
hm.insert({key, value});
hm[key] = value;
hm.erase(key);   //해당 키의 원소를 삭제
hm.count(key);   //키에 해당하는 원소들의 개수 반환 (value가 저장되는 공간을 배열, 벡터 등으로 선언하면 하나의 키에 여러 개의 원소가 저장됨)

//초기화와 용량
hm.clear();   //모든 원소 제거
hm.empty();   //해시맵이 비어있는지 확인 (true, false)
hm.size();   //원소들의 개수 반환
```
**(+)** 맵, 해시맵과 유사한 컨테이너로 set과 hase set이 있음 (key와 value가 동일한 맵)
<br>
<br>

#### 2️⃣ 그래프 (Graph) & 트리 (Tree)
- **그래프**: 노드와 간선으로 구성, 방향/무방향, 순환/비순환 구조 존재. 루트/부모-자식 개념 없음
- **트리**: 비순환 무방향 그래프, 하나의 루트 노드 존재, 부모-자식 계층형 모델. 간선 수 = $N-1$
<br>

#### 3️⃣ 힙 (Heap) & 우선순위 큐

- **Header**: `#include <algorithm>` (힙 정렬) `#include <queue>` (우선순위 큐)
- **힙의 특징**
  - 완전 이진 트리 기반의 자료구조
  - **최소힙**: 루트 노드에 있는 값은 모든 자식에 있는 값 중에서 최솟값, 모든 자식 노드는 부모 노드 이상의 값을 가짐 (오름차순)
  - **최대힙**: 루트 노드에 있는 값은 모든 자식에 있는 값 중에서 최대값, 모든 자식 노드는 부모 노드 이하의 값을 가짐 (내림차순)

**힙 정렬 시간복잡도**
- 힙 정렬: `O(nlog(n))` 

**힙 정렬 사용 방법**
```cpp
//힙을 구성(정렬)하는 과정은 자식 노드에서 부모 노드로 올라감 (참고: https://zoosso.tistory.com/491)
//삽입은 새로운 노드를 트리의 마지막 노드에 추가하고, 부모 노드와 크기 비교에 따라 자리를 바꾸는 방식으로 이루어짐
//삭제는 루트 노드가 빠지고 마지막 노드가 루트 노드 자리를 채움, 이후 크기 비교에 따라 자리를 바꿈
#include <algorithm>
#include <vector>
vector<int> v = {1,6,5,2,3,8,4,9,7};

make_heap(v.begin(), v.end());   //우선순위 큐 9 7 8 6 3 5 4 2 1 생성
//삽입
v.push_back(10);   //힙에 값 삽입
push_heap(v.begin(), v.end());   //재배열 (10 9 8 6 7 5 4 2 1 3)
//삭제
pop_heap(v.begin(), v.end());   //우선순위가 가장 높은 루트 노드가 맨 끝으로 이동하고 재배열 (8 7 5 6 3 1 4 2 9)
v.pop_back();   //루트 노드 삭제
```
- **우선순위 큐의 특징**
  - 최대힙(내림차순 기본) 구조의 큐
  - 설정을 추가하여 정렬 기준을 변경할 수 있음

**우선순위 큐의 시간 복잡도**
- 접근: `O(1)` 
- 삽입/삭제: `O(log(n))`

**우선순위  사용 방법**
```cpp
priority_queue<int> pq;   //우선순위 큐(최대힙) 선언
priority_queue<int, deque<int>> pq;   //내부 컨테이너 변경 (노드의 컨테이너가 deque)
priority_queue<int, vector<int>, greater<int>> pq;   //우선순위 최소값(오름차순), 내부 컨테이너 vector, 자료형 int

//삽입과 삭제
pq.push(val);   //val 원소 삽입
pq.pop();   //우선순위가 가장 높은 원소(루트 노드 값) 삭제

//접근
pq.top();   //우선순위가 가장 높은 원소(루트 노드 값) 반환

//용량
pq.size();   //원소 개수 반환
pq.empty();   //비어있는지 확인 (true, false)
```
<br>

---

## 💡 문제풀이 TIP
#### 📖 회전 관련
#include <cstring> memmove(A, B, 크기) <br/>
→ 배열의 크기만큼 B를 A로 복사 (배열 복사할 때 유용한 함수) <br/>
<br/>
**2차원 배열 회전 공식** <br/>
좌상단 (a, b) <br/>
우하단 (c, d) <br/>
c-a == d-b를 만족해야 함 <br/>
- **시계방향 90도**: rotated[ **i** ][ **j** ] = origin[ **a + (d - j)** ][ **b + (i - a)** ] <br/>
- **반시계방향 90도**: rotated[ **i** ][ **j** ] = origin[ **a + (j - b)** ][ **d - (i - a)** ] <br/>
<br>

#### 📖 MOD 연산
- (A + B) % C = ((A % C) + (B % C)) % C <br/>
- (A - B) % C = ((A % C) - (B % C) + C) % C <br/>
- (A * B) % C = ((A % C) * (B % C)) % C <br/>

계산이 누적되는 경우 중간중간 적용 <br/>
<br>

#### 📖 시간 단축
ios::sync_with_stdio(false); <br/>
cin.tie(NULL); <br/>
cout.tie(NULL); <br/>
<br>

#### 📖 문자열의 문자를 숫자로 변환
string number; <br/>
int num = number[i] - '0'; <br/>
<br>

#### 📖 우선순위 큐의 정렬기준 (디폴트 최대힙, 내림차순)
> struct comp { <br/>
bool operator()(int a, int b){ return a > b; } <br/>
}; → 우선순위 큐의 정렬기준 <br/>

> priority_queue <int, vector<int>, comp> pq; → 정렬기준을 추가하여 최소힙 선언 <br/>

우선순위 큐의 정렬기준은 struct의 bool operator 사용 <br/>
위의 예시는 최소힙, 오름차순 <br/>
bool operator의 return은 두 값 중 어떤 값이 더 우선순위가 낮은지를 반환해야 함 <br/>
(true가 우선순위가 낮음, 정렬할 때 뒤로 감) <br/>
<br>

#### 📖 sort의 비교함수와 우선순위 큐의 비교함수 비교
- **sort**: bool 함수 이용 | 어느 값이 더 작아야 하는가 | 디폴트 오름차순
- **priority queue**: struct의 bool operator()(input) 이용 | 어느 값이 우선순위가 더 낮은가 | 디폴트 내림차순 (최대힙)

sort는 true가 그대로 적용, priority queue는 true가 뒤로 밀림 (우선순위 낮음, 반대로 적용된다고 생각)

<br>

#### 📖 1차원 index를 2차원 값으로 변환 / 2차원 값을 1차원 index로 변환
1차원의 index를 2차원 값으로 변환 (M은 열의 개수(columns))
- row = index / M
- col = index % M

2차원 값을 1차원 index로 변환 (M은 열의 개수(columns))
- index = (row * M) + col
<br>
