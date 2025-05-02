import sys
input = sys.stdin.readline

def solve():
    a, b, c, d = map(int, input().split())
    if b < a:
        a, b = b, a
    if d < c:
        c, d = d, c
    if a > d:
        print(4)
    elif a > c and b > d:
        print(2)
    else:
        print(0)

def main():
    t = int(input())
    for _ in range(t):
        solve()

if __name__ == '__main__':
    main()