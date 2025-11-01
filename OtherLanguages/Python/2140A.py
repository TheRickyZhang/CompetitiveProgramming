import sys
readline = sys.stdin.readline

def solve():
    n = int(input())
    s = input()
    x = s.count("1")
    y = s.count("1", n-x, n)
    print(x-y)

def main():
    t = int(input())
    for _ in range(t):
        solve()

if __name__ == '__main__':
    main()
