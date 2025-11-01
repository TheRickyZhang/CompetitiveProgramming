import sys
input = sys.stdin.readline

def solve():
    x = input()
    print(int(x[0]) + int(x[1]))


def main():
    t = int(input())
    for _ in range(t):
        solve()

if __name__ == '__main__':
    main()