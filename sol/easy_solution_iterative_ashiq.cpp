#include<bits/stdc++.h>
using namespace std;


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
        int sz = candidates.size();
        int offset = c; 
        
        vector<vector<long long>> dp1(c + 1, vector<long long>(2 * c + 1, LLONG_MIN));
        dp1[0][offset] = 0;
        for(int i = 0; i < sz; i++) {
            vector<vector<long long>> dp2 = dp1;
            int index = candidates[i];
            for(int taken = 1; taken <= c; taken++) {
                for(int diff = 0; diff <= 2 * c; diff++) {
                    // take as two-cell
                    if(dp1[taken - 1][diff] != LLONG_MIN) 
                        dp2[taken][diff] = max(dp2[taken][diff], dp1[taken - 1][diff] + blocks[index][1]);
                    
                    // take as one-cell
                    if(diff + 1 <= 2 * c)
                        dp2[taken][diff] = max(dp2[taken][diff], dp1[taken - 1][diff + 1] + blocks[index][0]);

                    // take as three-cell
                    if(diff > 0)
                        dp2[taken][diff] = max(dp2[taken][diff], dp1[taken - 1][diff - 1] + blocks[index][2]);

                }
            }
            dp1 = dp2;
        }
        cout << dp1[c][offset + 1] << "\n";
    }
}