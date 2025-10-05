#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <tuple> 

using namespace std;

// 미로 탐색 함수
int solve() {
    // 입력: N, M (미로의 크기)
    int N, M;
    if (!(cin >> N >> M)) return 0;

    // 미로 정보 저장 (1은 이동 가능, 0은 이동 불가능)
    // 인덱스를 0부터 시작하기 위해 vector<string> 대신 vector<vector<int>>를 사용하고, 
    // 입력 시 '0' 또는 '1' 문자를 정수 0 또는 1로 변환하여 저장함
    vector<vector<int>> maze(N, vector<int>(M));
    for (int i = 0; i < N; ++i) {
        string row;
        cin >> row;
        for (int j = 0; j < M; ++j) {
            maze[i][j] = row[j] - '0'; // 문자 '1'/'0'을 정수 1/0으로 변환
        }
    }

    // 거리 저장 배열 (시작점으로부터의 최소 칸 수)
    // 0으로 초기화되며, 방문 여부도 겸함 (거리가 0이 아니면 방문한 것).
    vector<vector<int>> dist(N, vector<int>(M, 0));

    // BFS를 위한 큐 (좌표를 저장)
    queue<pair<int, int>> q;

    // 시작점 (1, 1) -> (0, 0)
    q.push({0, 0});
    dist[0][0] = 1; // 시작 칸도 칸 수에 포함하므로 거리는 1부터 시작

    // 상하좌우 이동을 위한 배열 (dx: 열 변화, dy: 행 변화)
    int dx[] = {0, 0, 1, -1}; // 좌, 우, 하, 상
    int dy[] = {1, -1, 0, 0}; // 좌, 우, 하, 상

    while (!q.empty()) {
        pair<int, int> current = q.front();
        q.pop();

        int x = current.first;  // 현재 칸의 행 인덱스
        int y = current.second; // 현재 칸의 열 인덱스

        // 목표 지점에 도착했으면 현재 거리를 반환하고 종료
        if (x == N - 1 && y == M - 1) {
            return dist[x][y];
        }

        // 4가지 방향으로 이동 시도
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i]; // 이동할 다음 칸의 행 인덱스
            int ny = y + dy[i]; // 이동할 다음 칸의 열 인덱스

            // 1. 미로 경계 확인
            if (nx >= 0 && nx < N && ny >= 0 && ny < M) {
                // 2. 이동 가능 여부 (1) 및 방문 여부 (dist[nx][ny] == 0) 확인
                if (maze[nx][ny] == 1 && dist[nx][ny] == 0) {
                    // 방문 표시 및 거리 업데이트
                    dist[nx][ny] = dist[x][y] + 1;
                    // 다음 탐색을 위해 큐에 추가
                    q.push({nx, ny});
                }
            }
        }
    }

    // 항상 도착 위치로 이동할 수 있는 경우만 주어진다고 했으므로 여기에 도달할 일은 없지만, 
    // 만약을 위해 0 또는 -1 반환
    return 0; 
}

int main() {
    // 입출력 속도 향상
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << solve() << "\n";

    return 0;
}
