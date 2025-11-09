#include <iostream>
#include <vector>
#include <algorithm>
#include <set> 

using namespace std;

// 전역 변수 설정
int N, M;
vector<int> unique_input; // 중복을 제거하고 정렬된 고유한 숫자들
vector<int> sequence; // 현재 만들어지고 있는 길이가 M인 수열

// 백트래킹 함수
// start_index: 현재 깊이에서 숫자를 선택할 때, unique_input 배열에서 탐색을 시작할 인덱스
void solve(int start_index) {
    // 1. 종료 조건: 길이가 M인 수열이 완성된 경우
    if (sequence.size() == M) {
        for (int i = 0; i < M; ++i) {
            cout << sequence[i] << (i == M - 1 ? "" : " ");
        }
        cout << "\n";
        return;
    }

    // 2. 재귀 호출 (다음 숫자 선택)
    for (int i = start_index; i < unique_input.size(); ++i) {
        
        // 1. 숫자 선택
        sequence.push_back(unique_input[i]);
        
        // 2. 다음 깊이로 이동
        solve(i);

        // 3. 선택 취소 (백트래킹)
        sequence.pop_back();
    }
}

int main() {
    // 입출력 속도 향상
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 입력 받기
    cin >> N >> M;
    vector<int> input(N); // N개의 모든 자연수를 저장할 임시 벡터
    
    for (int i = 0; i < N; ++i) {
        cin >> input[i];
    }

    // 1. 입력 배열 정렬
    sort(input.begin(), input.end());

    // 2. 고유한 숫자들만 추출하여 unique_input 구성
    for (int num : input) {
        if (unique_input.empty() || unique_input.back() != num) {
            unique_input.push_back(num);
        }
    }

    // 3. 백트래킹 시작: 항상 인덱스 0부터 시작
    solve(0);

    return 0;
}
