#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> cable;
int k, n;

bool solve(int x) {
    if (x == 0) return true; 
    int cnt = 0;
    for (int i = 0; i < k; ++i) {
        cnt += cable[i] / x; // 각 랜선에서 만들 수 있는 랜선의 개수를 더하기
    }
    // 총 개수가 필요한 개수(n)보다 많거나 같으면 true 반환
    return cnt >= n;
}

void binary_search() {
    long long left = 1;
    long long right = cable[k - 1];
    long long result = 0;

    while (left <= right) {
        long long mid = left + (right - left) / 2;

        if (solve(mid)) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    cout << result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> k >> n;

    cable.assign(k, 0); //vector 0으로 초기화
    for (int i = 0; i < k; i++) {
        cin >> cable[i];
    }
    
    // 이진 탐색을 위해 랜선 길이를 오름차순으로 정렬
    sort(cable.begin(), cable.end());

    // 최대 랜선 길이를 찾는 함수 호출
    binary_search();
}
/*
전략
1.이진탐색으로 랜선길이 찾기
2.그냥 STL binary_search로는 안됨. 매개변수 탐색으로 풀기
*/