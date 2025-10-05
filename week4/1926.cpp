#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 도화지의 크기
int N, M;
// 그림 정보 (1: 색칠됨, 0: 색칠 안 됨)
vector<vector<int>> board;
// 방문 여부 확인 배열
vector<vector<bool>> visited;

// 상하좌우 이동을 위한 배열 (row, col)
int dr[] = {-1, 1, 0, 0}; // 상, 하, 좌, 우
int dc[] = {0, 0, -1, 1};

/**
 * @brief 깊이 우선 탐색(DFS)을 통해 현재 좌표 (r, c)와 연결된 그림의 넓이를 계산한다.
 * * @param r 현재 행 인덱스
 * @param c 현재 열 인덱스
 * @return int 현재 그림의 총 넓이
 */
int dfs(int r, int c) {
    // 1. 현재 칸 방문 처리
    visited[r][c] = true;
    int area = 1; // 현재 칸의 넓이 (1)

    // 2. 상하좌우 인접 칸 탐색
    for (int i = 0; i < 4; ++i) {
        int nr = r + dr[i]; // next row
        int nc = c + dc[i]; // next col

        // 3. 미로 경계 확인
        if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
            // 4. 이동 가능한 조건 확인: 색칠된 칸('1')이면서 아직 방문하지 않은 칸
            if (board[nr][nc] == 1 && !visited[nr][nc]) {
                // 재귀적으로 탐색하여 넓이를 합산
                area += dfs(nr, nc); 
            }
        }
    }

    return area;
}

void solve() {
    // 입력: N (세로), M (가로)
    if (!(cin >> N >> M)) return;

    // 도화지 및 방문 배열 크기 설정
    board.resize(N, vector<int>(M));
    visited.resize(N, vector<bool>(M, false));

    // 그림 정보 입력
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> board[i][j];
        }
    }

    int picture_count = 0; // 그림의 총 개수
    int max_area = 0;      // 가장 넓은 그림의 넓이

    // 전체 도화지 탐색
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            // 아직 방문하지 않은 색칠된 칸('1')을 발견하면 새로운 그림의 시작점임
            if (board[i][j] == 1 && !visited[i][j]) {
                picture_count++; // 그림 개수 증가

                // DFS를 시작하여 이 그림의 전체 넓이를 계산
                int current_area = dfs(i, j); 
                
                // 최대 넓이 업데이트
                max_area = max(max_area, current_area); 
            }
        }
    }

    // 출력: 그림의 개수와 가장 넓은 그림의 넓이
    cout << picture_count << "\n";
    cout << max_area << "\n";
}

int main() {
    // 입출력 속도 향상
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}
