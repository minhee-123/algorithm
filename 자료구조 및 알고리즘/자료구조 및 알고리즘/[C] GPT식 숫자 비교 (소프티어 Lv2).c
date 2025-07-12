// ★ qsort를 사용할 때 주의해야 할 것 (sort와 배치 방법이 완전히 다름!!)
// sort는 comp 함수 작성시 직관적으로 생각하면 됨 (bool이 사용되기 때문)
// But!!
// qsort에서는 양수를 반환했을 때 자리를 바꾸고, 음수를 반환했을 때 자리를 유지함
// 예시로 오름차순 정렬을 할때 
// intA > intB이면 자리를 바꿔야하므로 return 1
// intA < intB이면 자리를 유지해야하므로 return -1
// ★ 자리를 유지하려면 return -1, 자리를 바꾸려면 return 1 (상관없는 경우 return 0)

// 문제: https://softeer.ai/practice/11001
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

int N;
char str[1001][8];

int comp(const void* a, const void* b) //포인터를 가져왔으므로
{
    char* strA = (char*)a; //char형으로 바꿔줌 → 이때 포인터 변수이므로 끝 (만약 int라면 값을 가져와야 되서 *(int*) 형태가 됨)
    char* strB = (char*)b;

    char Af[8] = { 0 }, Bf[8] = { 0 };
    int indexA = 0, indexB = 0;
    int hasDotA = 0, hasDotB = 0;

    for (int i = 0; i < strlen(strA); i++)
    {
        if (strA[i] == '.')
        {
            indexA = i;
            hasDotA = 1;
            break;
        }
        Af[i] = strA[i];
    }
    for (int i = 0; i < strlen(strB); i++)
    {
        if (strB[i] == '.')
        {
            indexB = i;
            hasDotB = 1;
            break;
        }
        Bf[i] = strB[i];
    }

    //오름차순 → a > b이면 return 1 (내림차순이라면 a < b이면 return 1)
    if (atoi(Af) > atoi(Bf)) return 1; //문자열을 int형 정수로 바꿔줌 (자매품 atol, atof 등등)
    else if (atoi(Af) < atoi(Bf)) return -1;

    //소수점이 없다면 같은 정수에서 가장 작은 숫자
    //오름차순에서 a가 b보다 크면 true (내림차순에서 b가 a보다 크면 true)
    if (hasDotA == 0) return -1; //a가 b보다 작은 상황 → 오름차순 → return -1
    else if (hasDotB == 0) return 1;

    char As[8] = { 0 }, Bs[8] = { 0 };
    int cnt = 0;

    for (int i = indexA + 1; i < strlen(strA); i++) As[cnt++] = strA[i];
    cnt = 0;
    for (int i = indexB + 1; i < strlen(strB); i++) Bs[cnt++] = strB[i];

    if (atoi(As) > atoi(Bs)) return 1;
    else if (atoi(As) < atoi(Bs)) return -1;
    return 0;
}

int main()
{
    scanf("%d", &N);
    for (int i = 0; i < N; i++) scanf("%s", str[i]);

    qsort(str, N, sizeof(str[0]), comp); //qsort 작성법 (배열, 길이, 요소의 크기, 비교함수)
    for (int i = 0; i < N; i++) printf("%s\n", str[i]);

    return 0;
}