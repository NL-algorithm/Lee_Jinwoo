def solve():
    import sys
    try:
        A, B = map(int, sys.stdin.readline().split())
    except:
        return
    count = 1

    while B > A:
        if B % 10 == 1:
            B = (B - 1) // 10
            count += 1
            
        elif B % 2 == 0:
            B = B // 2
            count += 1
            
        else:
            print(-1)
            return

    if B == A:
        print(count)
    else:
        print(-1)

if __name__ == "__main__":
    solve()
