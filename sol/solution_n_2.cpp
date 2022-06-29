#include<bits/stdc++.h>
using namespace std;

int main() {
    int tc;
    cin >> tc;
    while(tc--) {
        int n, board_cnt;
        cin >> n >> board_cnt;
        assert(board_cnt == 1);
        assert(n == 2);
        vector<int> a(4);
        for(int i = 0; i < 4; i++) cin >> a[i];
        long long ans = 0;
        sort(a.rbegin(), a.rend());
        a.pop_back();
        for(int x : a) ans += x;
        cout << ans << "\n";
    }
}