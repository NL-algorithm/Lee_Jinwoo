#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void solve() {
    // 입력을 위한 변수
    string str;          // 원본 문자열 (최대 1,000,000)
    string bomb;         // 폭발 문자열 (최대 36)
    
    // 결과 문자열 (스택 역할)
    string result = "";
    
    // 폭발 문자열의 길이
    int bomb_len;

    // 입력 받기
    cin >> str >> bomb;

    bomb_len = bomb.length();

    // 1. 원본 문자열을 순회하며 문자를 result에 추가
    for (char current_char : str) {
        // 문자를 결과 문자열에 추가 (push)
        result.push_back(current_char);

        // 2. 폭발 조건 확인: result의 길이가 폭발 문자열 길이 이상이고,
        //    현재 추가된 문자가 폭발 문자열의 마지막 문자와 일치할 때만 검사
        if (result.length() >= bomb_len && current_char == bomb.back()) {
            
            bool is_bomb = true;
            
            // 3. 폭발 문자열 일치 여부 검사
            // result의 끝에서 bomb_len만큼 폭발 문자열과 역순으로 비교
            for (int i = 0; i < bomb_len; ++i) {
                // result의 끝에서 (i+1)번째 문자와 bomb의 끝에서 (i+1)번째 문자를 비교
                // result[result.length() - bomb_len + i]는 비교 시작 위치
                if (result[result.length() - bomb_len + i] != bomb[i]) {
                    is_bomb = false;
                    break;
                }
            }

            // 4. 폭발 발생 시 제거 (pop)
            if (is_bomb) {
                // result에서 폭발 문자열 길이만큼 문자를 제거
                // string::pop_back()을 bomb_len 횟수만큼 호출
                for (int i = 0; i < bomb_len; ++i) {
                    result.pop_back();
                }
            }
        }
    }

    // 5. 최종 결과 출력
    if (result.empty()) {
        cout << "FRULA" << endl;
    } else {
        cout << result << endl;
    }
}

int main() {
    // 입출력 속도 향상
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}
