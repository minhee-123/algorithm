//가장 큰 수 (https://school.programmers.co.kr/learn/courses/30/lessons/42746)
//참고: https://school.programmers.co.kr/questions/79918
//sort 사용할 때 정렬기준을 사용자가 원하는대로 설정할 수 있음 ★연습필요

#include <string> //숫자를 문자열로 to_string(숫자) / 문자열을 숫자로 stoi(문자열) → 정수형 반환
#include <vector>
#include <algorithm>
using namespace std;

bool compare(string a, string b) { return a + b > b + a; }
// (ex) "10" "8"이 있다고 하면
// "108" < "810" 이므로 "8" "10" 순서로 정렬함

string solution(vector<int> numbers) 
{
    string answer = "";
    vector<string> Numbers;

    for (int i = 0; i < numbers.size(); i++)
    {
        Numbers.push_back(to_string(numbers[i]));
    }
    sort(Numbers.begin(), Numbers.end(), compare);

    for (int i = 0; i < Numbers.size(); i++)
    {
        answer += Numbers[i];
    }

    if (answer[0] == '0') return answer = "0";
    else return answer;
}