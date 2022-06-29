#include<bits/stdc++.h>
using namespace std;

map<tuple<int, int, int>, long long> dp;

long long solve(int i, int taken, int diff, int to_take, vector<int>&candidates, vector<vector<long long>> &blocks) {
    if(i == candidates.size()) {
        if(taken != to_take or diff != 1) {
            return LLONG_MIN;
        }
        return 0;
    }
    if(dp.find(make_tuple(i, taken, diff)) != dp.end()) return dp[make_tuple(i, taken, diff)];
    long long ans = solve(i + 1, taken, diff, to_take, candidates, blocks);
    int index = candidates[i];
    ans = max(ans, solve(i + 1, taken + 1, diff + 1, to_take, candidates, blocks) + blocks[index][2]);
    ans = max(ans, solve(i + 1, taken + 1, diff, to_take, candidates, blocks) + blocks[index][1]);
    ans = max(ans, solve(i + 1, taken + 1, diff - 1, to_take, candidates, blocks) + blocks[index][0]);
    return dp[make_tuple(i, taken, diff)] = ans;
}


int main() {
    int tc;
    cin >> tc;
    while(tc--) {
        int n, board_cnt;
        cin >> n >> board_cnt;
        assert(board_cnt == 1);
        int k = n * n / 4;
        vector<vector<long long>> blocks;
        for(int i = 0; i < k; i++) {
            vector<long long> v(4);
            for(int j = 0; j < 4; j++) cin >> v[j];
            sort(v.rbegin(), v.rend());
            v.pop_back();
            for(int j = 1; j < v.size(); j++) v[j] += v[j - 1];
            blocks.push_back(v);
        }
        /*
        for(auto v : blocks) {
            for(auto x : v) {
                cout << x << " ";
            }
            cout << endl;
        }
        */
        int c = n - 1;
        vector<int> candidates;
        for(int i = 0; i < 3; i++) {
            vector<pair<long long, int>> perm(k);
            for(int j = 0; j < k; j++) {
                perm[j].first = blocks[j][i];
                perm[j].second = j;
            }
            sort(perm.rbegin(), perm.rend());
            for(int j = 0; j < c; j++) {
                candidates.push_back(perm[j].second);
            }
        }
        sort(candidates.begin(), candidates.end());
        candidates.erase(unique(candidates.begin(), candidates.end()), candidates.end());
        
        dp.clear();
        cout << solve(0, 0, 0, c, candidates, blocks) << "\n";
    }
}