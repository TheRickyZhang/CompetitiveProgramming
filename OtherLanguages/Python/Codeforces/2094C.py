import sys
input = sys.stdin.readline

def solve():
    n = int(input())
    seen = [False] * (2*n+1)

    a = list(map(int, input().split()))
    for i in range(n-1):
        nums = list(map(int, input().split()))
        x = nums[-1]
        a.append(x)
    for x in a:
        seen[x] = True

    missing = None
    for x in range(1, 2*n+1):
        if not seen[x]:
            missing = x
            break
    # print the singular missing number, then the list in a single line
    print(" ".join(map(str, [missing] + a)))

def main():
    t = int(input())
    for _ in range(t):
        solve()

if __name__ == '__main__':
    main()