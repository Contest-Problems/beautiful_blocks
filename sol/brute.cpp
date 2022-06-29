#include<bits/stdc++.h>
using namespace std;

long long dp[100][100];

long long solve_board(vector<vector<int>> &board) {
    int n = board.size();
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            dp[i][j] = max(i > 0 ? dp[i - 1][j] : 0, j > 0 ? dp[i][j - 1] : 0) + board[i][j];
        }
    }
    return dp[n - 1][n - 1];
}

void backtrack(int n, int idx, vector<vector<int>> &blocks, vector<vector<int>> &board, long long &ans)  {
    if(idx == blocks.size()) {
        /*
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        cout << "---------------------------" << endl;
        */
        ans = max(ans, solve_board(board));
        return;
    }
    vector<int> block = blocks[idx];
    int r = idx / (n / 2);
    int c = idx % (n / 2);

    do {
        board[2 * r][2 * c] = block[0];
        board[2 * r + 1][2 * c] = block[1];
        board[2 * r][2 * c + 1] = block[2];
        board[2 * r + 1][2 * c + 1] = block[3];
        backtrack(n, idx + 1, blocks, board, ans);
    }while(next_permutation(block.begin(), block.end()));
}

int main() {

    int tc;
    cin >> tc;
    while(tc--) {
        int n;
        cin >> n;
        int k = n * n / 4;
        vector<vector<int>> blocks;
        for(int i = 0; i < k; i++) {
            vector<int> block(4);
            for(int &x : block) cin >> x;
            sort(block.begin(), block.end());
            blocks.push_back(block);
        }
        sort(blocks.begin(), blocks.end());
        long long ans = 0;

        do {
            vector<vector<int>> board(n, vector<int>(n));
            backtrack(n, 0, blocks, board, ans);
        }while(next_permutation(blocks.begin(), blocks.end()));

        cout << ans << endl;
    }
}