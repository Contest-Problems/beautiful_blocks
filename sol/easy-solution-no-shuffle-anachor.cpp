#include<bits/stdc++.h>
using namespace std;

const int N = 3010, D=18;
long long dp[2][N][2*D+1];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin>>t;

    while (t--) {
        int n, x;
        cin>>n>>x;

        int k = n*n/4;
        vector<vector<long long>> blocks(k);

        vector<int> by[3];
        for (int i=0; i<k; i++) {
            blocks[i].resize(4);
            for (int j=0; j<4; j++) {
                cin>>blocks[i][j];
            }
            sort(blocks[i].rbegin(), blocks[i].rend());
            for (int j=1; j<4; j++) {
                blocks[i][j] += blocks[i][j-1];
            }
            by[0].push_back(i);
        }

        by[1] = by[2] = by[0];
        set<int> st;

        for (int i=0; i<3; i++) {
            auto comp = [&blocks, i] (int x, int y) {
                return blocks[x][i] > blocks[y][i];
            };
            sort(by[i].begin(), by[i].end(), comp);
            int zz = min(k, n-1);
            if (by[i].size() > zz) by[i].resize(zz);
            for (int x: by[i])  st.insert(x);
        }

        int kk = st.size(), cur = 0;


        for (int i=0; i<=kk+1; i++) {
            for (int j=max(-D, -kk/2-2); j<=min(kk/2+2, D); j++) {
                dp[0][i][D+j] = dp[1][i][D+j] = -1;
            }
        }

        dp[0][0][D] = 0;

        vector<int> interesting(st.begin(), st.end());
        mt19937 rng(23423423);
//        shuffle(interesting.begin(), interesting.end(), rng);


        for (int id: interesting) {
            cur++;
            bool b = cur%2;
            for (int taken=0; taken <= cur; taken++) {
                    for (int pd = max({-taken, -kk/2-1, -D+1}); pd <= min({taken, kk/2+1, D-1}); pd++) {
                    ///Notake
                    dp[b][taken][D+pd] = dp[!b][taken][D+pd];

                    if (taken) {
                        ///Take 1
                        if (dp[!b][taken-1][D+pd+1] != -1) dp[b][taken][D+pd] = max(dp[b][taken][D+pd], dp[!b][taken-1][D+pd+1] + blocks[id][0]);

                        ///Take 2
                        if (dp[!b][taken-1][D+pd] != -1) dp[b][taken][D+pd] = max(dp[b][taken][D+pd], dp[!b][taken-1][D+pd] + blocks[id][1]);

                        ///Take 3
                        if (dp[!b][taken-1][D+pd-1] != -1) dp[b][taken][D+pd] = max(dp[b][taken][D+pd], dp[!b][taken-1][D+pd-1] + blocks[id][2]);
                    }
//                    if (dp[b][MX+pd][taken] != -1) cout<<cur<<" "<<taken<<" "<<pd<<" "<<dp[b][MX+pd][taken]<<endl;
                }
            }
        }

        cout<<dp[cur%2][n-1][D+x]<<endl;

    }
}
