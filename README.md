### 💻 자료구조 및 알고리즘 문제풀이 백업 <br/><br/>
#### 문제풀이 TIP
---

##### 📖 회전 관련
#include <cstring> memmove(A, B, 크기) <br/>
→ 배열의 크기만큼 B를 A로 복사 (배열 복사할 때 유용한 함수) <br/>
<br/>
**2차원 배열 회전 공식** <br/>
좌상단 (a, b) <br/>
우하단 (c, d) <br/>
c-a == d-b를 만족해야 함 <br/>
- **시계방향 90도**: rotated[ **i** ][ **j** ] = origin[ **a + (d - j)** ][ **b + (i - a)** ] <br/>
- **반시계방향 90도**: rotated[ **i** ][ **j** ] = origin[ **a + (j - b)** ][ **d - (i - a)** ] <br/>

---

##### 📖 MOD 연산
- (A + B) % C = ((A % C) + (B % C)) % C <br/>
- (A - B) % C = ((A % C) - (B % C) + C) % C <br/>
- (A * B) % C = ((A % C) * (B % C)) % C <br/>

계산이 누적되는 경우 중간중간 적용 <br/>

---

##### 📖 시간 단축
ios::sync_with_stdio(false); <br/>
cin.tie(NULL); <br/>
cout.tie(NULL); <br/>

---

##### 📖 문자열의 문자를 숫자로 변환
string number; <br/>
int num = number[i] - '0'; <br/>

---

##### 📖 우선순위 큐의 정렬기준 (디폴트 최대힙, 내림차순)
> struct comp { <br/>
bool operator()(int a, int b){ return a > b; } <br/>
}; → 우선순위 큐의 정렬기준 <br/>

> priority_queue <int, vector<int>, comp> pq; → 정렬기준을 추가하여 최소힙 선언 <br/>

우선순위 큐의 정렬기준은 struct의 bool operator 사용 <br/>
위의 예시는 최소힙, 오름차순 <br/>
bool operator의 return은 두 값 중 어떤 값이 더 우선순위가 낮은지를 반환해야 함 <br/>
(true가 우선순위가 낮음, 정렬할 때 뒤로 감) <br/>

---

##### 📖 sort의 비교함수와 우선순위 큐의 비교함수 비교
- **sort**: bool 함수 이용 | 어느 값이 더 작아야 하는가 | 디폴트 오름차순
- **priority queue**: struct의 bool operator()(input) 이용 | 어느 값이 우선순위가 더 낮은가 | 디폴트 내림차순 (최대힙)

sort는 true가 그대로 적용, priority queue는 true가 뒤로 밀림 (우선순위 낮음, 반대로 적용된다고 생각)

---
