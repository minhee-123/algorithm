//다리를 지나는 트럭 (https://school.programmers.co.kr/learn/courses/30/lessons/42583)

#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(int bridge_length, int weight, vector<int> truck_weights)
{
	int answer = 0;
	int idx = 0;
	int b_w = 0;
	queue<int> bridge;

	for (int i = 0; i < bridge_length; i++)
	{
		bridge.push(0);
	}

	while (1)
	{
		if (bridge.empty()) break;
		else
		{
			if (idx == truck_weights.size())
			{
				bridge.pop();
			}
			else
			{
				int truck = truck_weights[idx];
				b_w -= bridge.front();
				bridge.pop(); //먼저 다리 맨 앞에 있는 트럭 나가고

				if (b_w + truck <= weight) //이후에 다리에 들어올지
				{
					b_w += truck;
					bridge.push(truck);
					idx++;
				}
				else bridge.push(0); //무게 초과로 못들어올지 결정
			}
		}
		answer++;
	}

	return answer;
}