import sys
readline = sys.stdin.readline

def solve():
    n = input()
    print(str(int(n) * 2))

def main():
    t = int(input())
    for _ in range(t):
        solve()

if __name__ == '__main__':
    main()
