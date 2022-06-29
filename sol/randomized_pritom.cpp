#include<bits/stdc++.h>
using namespace std;

namespace FASTIO {
    static const int buf_size = 4096;

    /** read */
    inline int getChar() {
        static char buf[buf_size];
        static int len = 0, pos = 0;
        if (pos == len) pos = 0, len = fread(buf, 1, buf_size, stdin);
        if (pos == len) return -1;
        return buf[pos++];
    }

    inline int readChar() {
        int c = 0;
        while (c <= 32)     c = getChar();
        return c;
    }

    template <class T = long long>
    inline T readInt() {
        int s = 1, c = readChar();
        T x = 0;
        if (c == '-')       s = -1, c = getChar();
        while ('0' <= c && c <= '9')    x = x * 10 + c - '0', c = getChar();
        return s == 1 ? x : -x;
    }

    /** Write */
    static int write_pos = 0;
    static char write_buf[buf_size];
    inline void writeChar( int x ) {
        if (write_pos == buf_size)  fwrite(write_buf, 1, buf_size, stdout), write_pos = 0;
        write_buf[write_pos++] = x;
    }

    template <class T = long long>
    inline void writeInt( T x, char end = 0) {
        if (x < 0)  writeChar('-'), x = -x;
        char s[24];
        int n = 0;
        while (x || !n) s[n++] = '0' + x % 10, x /= 10;
        while (n--)     writeChar(s[n]);
        if (end)        writeChar(end);
    }

    inline void writeWord( const char *s ) {
        while (*s)  writeChar(*s++);
    }

    struct Flusher {
        ~Flusher() {
            if (write_pos)  fwrite(write_buf, 1, write_pos, stdout), write_pos = 0;
        }
    } flusher;
}


const int N = 1000, D=20;
long long dp[2][N][2*D+1];
using namespace FASTIO;
int main() {
    int t;
    t = readInt();

    while (t--) {
        int n = readInt();
        int board_cnt = readInt();
        assert(board_cnt == 1);
        int k = n*n/4;
        vector<vector<long long>> blocks(k);

        vector<int> by[3];
        for (int i=0; i<k; i++) {
            blocks[i].resize(4);
            for (int j=0; j<4; j++) {
                blocks[i][j] = readInt();
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
        shuffle(interesting.begin(), interesting.end(), rng);


        for (int id: interesting) {
            cur++;
            bool b = cur%2;
//            cout<<cur<<" "<<id<<" ----> "<<endl;
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

        cout<<dp[cur%2][n-1][D+1]<<endl;

    }
}