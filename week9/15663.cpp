#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

// 전역 변수 설정
int N, M;
vector<int> input; // N개의 자연수를 저장할 벡터
vector<int> sequence; // 현재 만들어지고 있는 길이가 M인 수열
vector<bool> used; // 각 숫자의 사용 여부를 체크할 벡터

// 백트래킹 함수
void solve() {
    // 1. 종료 조건: 길이가 M인 수열이 완성된 경우
    if (sequence.size() == M) {
        for (int i = 0; i < M; ++i) {
            cout << sequence[i] << (i == M - 1 ? "" : " ");
        }
        cout << "\n";
        return;
    }

    // 2. 재귀 호출 (다음 숫자 선택)
    int last_num = 0; // 이전에 선택했던 숫자 (이번 깊이에서 중복을 피하기 위함)
    for (int i = 0; i < N; ++i) {
        // 이미 사용된 숫자이면 건너뜀
        if (used[i]) {
            continue;
        }


        if (input[i] == last_num) {
            continue;
        }

        // 숫자 선택
        used[i] = true;
        sequence.push_back(input[i]);
        
        // 다음 깊이로 이동
        solve();

        // 선택 취소 (백트래킹)
        sequence.pop_back();
        used[i] = false;
        
        // 이번 깊이에서 마지막으로 사용한 숫자를 기록
        // 이렇게 하면 다음 반복에서 같은 숫자를 다시 선택하지 않아 중복 수열 생성을 막음
        last_num = input[i]; 
    }
}

int main() {
    // 입출력 속도 향상
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 입력 받기
    cin >> N >> M;
    input.resize(N);
    used.resize(N, false);
    
    for (int i = 0; i < N; ++i) {
        cin >> input[i];
    }

    // 1. 사전 순 출력을 위해 입력 배열 정렬
    sort(input.begin(), input.end());

    // 2. 백트래킹 시작
    solve();

    return 0;
}
