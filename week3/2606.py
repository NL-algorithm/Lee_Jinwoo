import sys
sys.setrecursionlimit(2000) 

def solve():
    try:
        N = int(sys.stdin.readline())
        M = int(sys.stdin.readline())
    except:
        return

    graph = [[] for _ in range(N + 1)]
    visited = set()

    for _ in range(M):
        a, b = map(int, sys.stdin.readline().split())
        graph[a].append(b)
        graph[b].append(a)

    def dfs(node):
        visited.add(node)
        for neighbor in graph[node]:
            if neighbor not in visited:
                dfs(neighbor)

    dfs(1)
    
    print(len(visited) - 1)

if __name__ == "__main__":
    solve()
