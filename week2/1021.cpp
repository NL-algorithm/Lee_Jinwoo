#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;

    cin >> n >> m;

    deque<int> dq;

    for (int i = 1; i <= n; ++i) {
        dq.push_back(i);
    }

    vector<int> targets(m);
    for (int i = 0; i < m; ++i) {
        cin >> targets[i];
    }

    int total_moves = 0;

    for (int target : targets) {
        int target_index = 0;
        for (int i = 0; i < dq.size(); ++i) {
            if (dq[i] == target) {
                target_index = i;
                break;
            }
        }

        int left_moves = target_index;
        int right_moves = dq.size() - target_index;

        if (left_moves <= right_moves) {
            total_moves += left_moves;
            for (int i = 0; i < left_moves; ++i) {
                dq.push_back(dq.front());
                dq.pop_front();
            }
        } else {
            total_moves += right_moves;
            for (int i = 0; i < right_moves; ++i) {
                dq.push_front(dq.back());
                dq.pop_back();
            }
        }
        dq.pop_front();
    }

    cout << total_moves << endl;

    return 0;
}

/*전략
1.왼쪽으로 회전하는 횟수는 현재 인덱스와 같고, 오른쪽으로 회전하는 횟수는 전체 indexs에서 
현재 index를 뺀 크기와 같다.
2. 그리고 맨 앞에 있는 원소 빼서 제거하기*/
