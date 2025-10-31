#include <iostream>
#include <vector>

using namespace std;

// 최대 크기 N <= 16
const int MAX = 17;
int N;
int board[MAX][MAX];
// dp[r][c][dir]: (r, c)에 끝이 위치하고 방향이 dir일 때의 방법의 수
// dir: 0=가로, 1=세로, 2=대각선
long long dp[MAX][MAX][3];

// (r, c)를 파이프의 끝으로 하여 dir 방향으로 놓을 수 있는지 확인
// r, c: 1-based index
bool is_valid(int r, int c, int dir) {
    // 1. 격자 경계 확인
    if (r > N || c > N) {
        return false;
    }

    // 2. 벽(1) 확인
    if (dir == 0) { // 가로: (r, c)만 확인
        if (board[r][c] == 1) return false;
    } else if (dir == 1) { // 세로: (r, c)만 확인
        if (board[r][c] == 1) return false;
    } else if (dir == 2) { // 대각선: (r, c), (r-1, c), (r, c-1) 모두 확인
        if (board[r][c] == 1 || board[r - 1][c] == 1 || board[r][c - 1] == 1) {
            return false;
        }
    }
    
    return true;
}

void solve() {
    // 입력
    cin >> N;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            cin >> board[i][j];
        }
    }

    // 초기 상태: (1, 1)과 (1, 2)를 차지, 방향은 가로
    // 파이프의 끝은 (1, 2), 방향은 0 (가로)
    dp[1][2][0] = 1;

    // DP 진행: (1, 3)부터 시작 (1, 2)는 이미 초기값 설정됨
    for (int r = 1; r <= N; ++r) {
        for (int c = 3; c <= N; ++c) {
            
            // 1. 가로 (dir=0)로 (r, c)에 도착하는 경우
            // 이전 위치: (r, c-1). 이전 방향: 가로(0) or 대각선(2)
            if (is_valid(r, c, 0)) {
                dp[r][c][0] = dp[r][c - 1][0] + dp[r][c - 1][2];
            }
            
            // 2. 세로 (dir=1)로 (r, c)에 도착하는 경우
            // r이 1이면 이전 위치 (r-1, c)가 존재하지 않음
            if (r > 1 && is_valid(r, c, 1)) {
                // 이전 위치: (r-1, c). 이전 방향: 세로(1) or 대각선(2)
                dp[r][c][1] = dp[r - 1][c][1] + dp[r - 1][c][2];
            }

            // 3. 대각선 (dir=2)로 (r, c)에 도착하는 경우
            // r, c가 1이면 이전 위치 (r-1, c-1)가 존재하지 않음
            if (r > 1 && is_valid(r, c, 2)) {
                // 이전 위치: (r-1, c-1). 이전 방향: 가로(0), 세로(1), 대각선(2)
                dp[r][c][2] = dp[r - 1][c - 1][0] + dp[r - 1][c - 1][1] + dp[r - 1][c - 1][2];
            }
        }
        // r > 1 일 때, (r, 2)는 가로 이동이 불가능하고, 세로/대각선만 가능하다.
        // 세로 이동은 r=2부터 가능하다.
        if (r > 1) {
            int c = 2; // 열이 2일 때
             // 1. 세로 (dir=1)로 (r, 2)에 도착하는 경우 (r-1, 2)에서 이동
            if (is_valid(r, c, 1)) {
                // 이전 위치: (r-1, 2). 이전 방향: 세로(1) or 대각선(2)
                dp[r][c][1] = dp[r - 1][c][1] + dp[r - 1][c][2];
            }
            // 2. 대각선 (dir=2)로 (r, 2)에 도착하는 경우 (r-1, 1)에서 이동
            // 대각선 이동 시 (r, 2), (r-1, 2), (r, 1) 모두 비어있어야 함
            if (r > 1 && is_valid(r, c, 2)) {
                // 이전 위치: (r-1, c-1). 이전 방향: 가로(0), 세로(1), 대각선(2)
                dp[r][c][2] = dp[r - 1][c - 1][0] + dp[r - 1][c - 1][1] + dp[r - 1][c - 1][2];
            }
        }
    }

    // 최종 답: (N, N)에 끝이 위치하는 모든 경우의 수 합산
    long long answer = dp[N][N][0] + dp[N][N][1] + dp[N][N][2];
    
    // 출력
    cout << answer << endl;
}

int main() {
    // 입출력 속도 향상
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}
