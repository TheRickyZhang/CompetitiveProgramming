
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while(T--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++) cin >> a[i];
        deque<pair<int, int>> cells;
        int levels = 1;
        while(true){
            int cur = levels * (levels + 1) / 2;
            if(cur > n) break;
            levels++;
        }
        for(int i = 0; i <= levels; i++) cells.push_back({0, i});
        deque<pair<int, int>> order;
        for(auto [i, j]: cells) {
            int x = 3 * i + 1, y = 3 * j + 1;
            while(true) {
                if(x >= 1 && y >= 1) {
                    order.push_back({x, y});
                    x += 3, y -= 3;
                } else break;
            }
            x = 3 * i + 1, y = 3 * j + 2;
            while(true) {
                if(y >= 2) {
                    order.push_back({x, y});
                    int X = x + 1, Y = y - 1;
                    if(Y - 2 >= 2) order.push_back({X, Y - 2});
                    order.push_back({X, Y});
                    x += 3, y -= 3;
                } else break;
            }
            if(order.size() >= 4 * n) break;
        }
        deque<pair<int, int>> diagonals;
        levels = 0;
        while(diagonals.size() < n) {
            int lmt = levels++;
            for(int x = 0, y = lmt; x <= lmt; x++, y--) diagonals.push_back({3 * x + 1, 3 * y + 1});
        }
        map<pair<int, int>, int> done, done2;
        for(int i = 0; i < n; i++) {
            if(a[i] == 1) {
                while(done.count(order.front()))  order.pop_front();
                auto [x, y] = order.front();
                order.pop_front();
                cout << x << " " << y << '\n';
                if((x - 1) % 3 == 0 && (y - 1) % 3 == 0) {
                    done2[{x, y}] = true;
                }
            } else {
                while(done2.count(diagonals.front())) diagonals.pop_front();
                auto [x, y] = diagonals.front();
                diagonals.pop_front();
                cout << x << " " << y << '\n';
                done[{x, y}] = true;
            }
        }
    }
}
