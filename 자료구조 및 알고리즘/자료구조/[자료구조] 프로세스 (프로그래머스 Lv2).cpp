//프로세스 (https://school.programmers.co.kr/learn/courses/30/lessons/42587)

#include <string>
#include <vector>
#include <queue>

//우선순위라는 개념이 좀 헷갈렸는데
//우선순위 값이 높은게 최우선
//우선순위 [2,1,3,2] → [0번째(2우선), 1번째(1우선), 2번째(3우선), 3번째(2우선)]
//우선순위가 동일한 애들은 앞에 있는 애들부터 실행됨

using namespace std;

int solution(vector<int> priorities, int location) 
{
    int answer = 0; //몇번째 실행되는지 count
    int flag;
    queue<pair<int, int>> q;
    priority_queue<int> pq;

    for (int i = 0; i < priorities.size(); i++)
    {
        q.push({ i, priorities[i] });
        pq.push(priorities[i]); //우선순위(최대값)가 높은 데이터가 먼저 나옴 (알아서 정렬)
    }

    while (flag != location)
    {
        if (pq.top() == q.front().second)
        {
            flag = q.front().first;
            answer++;

            q.pop();
            pq.pop();
        }
        else
        {
            pair<int, int> temp = q.front();
            q.pop();
            q.push(temp);
        }
    }

    return answer;
}
