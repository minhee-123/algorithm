// 타겟넘버 (https://school.programmers.co.kr/learn/courses/30/lessons/43165)

#include <vector>
using namespace std;

int answer = 0;

//재귀를 너무 어렵게 생각하지 말고 잘 응용해보자 (DFS가 유용함)
void calculation(vector<int> numbers, int target, int sum, int index)
{
    if (index == numbers.size())
    {
        if (sum == target) answer++;
        return;
    }

    calculation(numbers, target, sum + numbers[index], index + 1);
    calculation(numbers, target, sum - numbers[index], index + 1);
}

int solution(vector<int> numbers, int target)
{
    calculation(numbers, target, 0, 0); //sum 0, index 0에서 시작
    return answer;
}