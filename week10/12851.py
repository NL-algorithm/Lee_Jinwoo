from collections import deque
import sys

# N: 수빈이 위치, K: 동생 위치
N, K = map(int, sys.stdin.readline().split())

# 최대 위치
MAX = 100001

# dist[i]: N에서 i까지 가는 최단 시간. -1은 미방문.
dist = [-1] * MAX
# count[i]: N에서 i까지 최단 시간으로 가는 방법의 수.
count = [0] * MAX

# 시작 지점 처리
dist[N] = 0
count[N] = 1

# BFS 큐 초기화
queue = deque([N])

# N과 K가 같은 경우 (예외 처리)
if N == K:
    print(0)
    print(1)
    # 프로그램 종료
    exit()

# BFS 시작
while queue:
    # 현재 위치 X
    X = queue.popleft()
    
    # X에서 이동 가능한 다음 위치들 (X-1, X+1, 2*X)
    for next_X in [X - 1, X + 1, X * 2]:
        
        # 1. 이동 가능한 범위인지 확인 (0 <= next_X < MAX)
        if 0 <= next_X < MAX:
            
            # 2. 처음 방문하는 경우 (최단 경로 발견)
            if dist[next_X] == -1:
                dist[next_X] = dist[X] + 1
                count[next_X] = count[X]
                queue.append(next_X)
                
            # 3. 이미 방문했지만, 현재 경로가 최단 시간과 같은 경우 (최단 경로 개수 증가)
            elif dist[next_X] == dist[X] + 1:
                # 새로운 최단 경로가 발견되었으므로, 이전 경로의 수에 현재 경로의 수를 더함
                count[next_X] += count[X]

# 결과 출력
# 최단 시간은 dist[K]
print(dist[K])
# 최단 시간으로 가는 방법의 수는 count[K]
print(count[K])
