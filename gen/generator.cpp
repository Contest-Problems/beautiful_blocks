#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

const int TOTAL_EASY = 600;
const int N_EASY = 300;

const int TOTAL_HARD = 2000;
const int N_HARD = 1000;

const int MAX = 1e9;

void print(vector<vector<int>> lines) {
    for(auto v : lines) {
        for(int i = 0; i < v.size(); i++) {
            cout << v[i];
            if(i + 1 != v.size()) cout << " ";
            else cout << "\n";
        }
    }
}

void print_random_grid(int n, int k = 1) {
    cout << n << " " << k << "\n";
    assert(n > 0 && n % 2 == 0);
    for(int i = 0; i < k * n * n / 2; i++) {
        int x = rnd.next(MAX);
        int y = rnd.next(MAX);
        cout << x << " " << y << "\n";
    }
}

void split_cases(int n, int total, int k = 1) {
    int tc = total / n * k;
    cout << tc << "\n";
    for(int t = 0; t < tc; t++) print_random_grid(n, k);
}

void generate_same(int each, int total, int k = 1) {
    split_cases(each, total);
}

void generate_random(int total, bool large_k = false) {
    vector<int> sizes;
    vector<int> ks;
    while(total >= 2) {
        int cur = 2 * (rnd.next(min(total / 2, 20)) + 1);
        int K = large_k ? rnd.next(1, min(10, total / cur)) : 1;
        total -= cur * K;
        sizes.push_back(cur);
        ks.push_back(K);
    }
    cout << sizes.size() << "\n";
    for(int i = 0; i < sizes.size(); i++) {
        print_random_grid(sizes[i], ks[i]);
    }
}

void generate_use_only_1_3_breaks_n_by_2(int n, int k, vector<vector<int>> &lines) {
    lines.push_back({n, k});
    int total_blocks = k * n * n / 4;
    int three = (n/2) * k;
    for(int i = 0; i < three; i++) {
        lines.push_back({rnd.next(MAX/10, MAX), rnd.next(MAX/10, MAX)});
        lines.push_back({0, rnd.next(MAX/10, MAX)});
    }
    int one = three - k;
    for(int i = 0; i < one; i++) {
        lines.push_back({rnd.next(1500, 1600), rnd.next(0, 600)});
        lines.push_back({rnd.next(0, 0), rnd.next(0, 0)});
    }
    int other = total_blocks - one - three;
    for(int i = 0; i < other; i++) {
        lines.push_back({rnd.next(900, 1000), rnd.next(900, 1000)});
        lines.push_back({rnd.next(900, 1000), rnd.next(900, 1000)});
    }
}


void generate_use_only_1_3(int n, int k, vector<vector<int>> &lines) {
    lines.push_back({n, k});
    int total_blocks = k * n * n / 4;
    int three = (n/2) * k;
    int one = three - k;
    int other = total_blocks - one - three;
    int extra_three = rnd.next(0, min(other, 5));
    other -= extra_three;

    for(int i = 0; i < three; i++) {
        lines.push_back({rnd.next(MAX/10, MAX), rnd.next(MAX/10, MAX)});
        lines.push_back({rnd.next(MAX/100, MAX/10), rnd.next(MAX/10, MAX)});
    }
    for(int i = 0; i < one; i++) {
        lines.push_back({rnd.next(MAX/10, MAX), rnd.next(MAX/100, MAX/10)});
        lines.push_back({rnd.next(MAX/100, MAX/10), rnd.next(MAX/100, MAX/10)});
    }

    for(int i = 0; i < other; i++) {
        lines.push_back({rnd.next(MAX/100, MAX/10), rnd.next(MAX/100, MAX/10)});
        lines.push_back({rnd.next(MAX/100, MAX/10), rnd.next(MAX/100, MAX/10)});
    }
    for(int i = 0; i < extra_three; i++) {
        lines.push_back({rnd.next(MAX/10, MAX), rnd.next(MAX/10, MAX)});
        lines.push_back({rnd.next(MAX/100, MAX/10), rnd.next(MAX/10, MAX)});
    }
}

void generate_use_only_2(int n, int k, vector<vector<int>> &lines) {
    lines.push_back({n, k});
    int total_blocks = k * n * n / 4;
    for(int i = 0; i < total_blocks; i++) {
        lines.push_back({rnd.next(MAX/10, MAX), rnd.next(MAX/10, MAX)});
        lines.push_back({rnd.next(MAX/100, MAX/10), rnd.next(MAX/100, MAX/10)});
    }
}

void generate_easy_use_only_1_3_large() {

    int tc = 0;
    vector<vector<int>> lines;
    generate_use_only_1_3(300, 1, lines);
    tc++;
    generate_use_only_1_3_breaks_n_by_2(300, 1, lines);
    tc++;
    lines.insert(lines.begin(), {tc});
    print(lines);
}

void generate_easy_use_only_1_3_or_2_small() {
    int tc = 0;
    vector<vector<int>> lines;
    // small N, all_1_3
    int n_sum = 300; 
    while(n_sum >= 2) {
        int n = rnd.next(2, min(n_sum, 10));
        if(n % 2 == 1) n--;
        n_sum -= n;
        if(rnd.next(0, 5) <= 4) generate_use_only_1_3(n, 1, lines);
        else generate_use_only_1_3_breaks_n_by_2(n, 1, lines);
        tc++;
    }
    n_sum = 300;
    while(n_sum >= 2) {
        int n = rnd.next(2, min(n_sum, 10));
        if(n % 2 == 1) n--;
        n_sum -= n;
        generate_use_only_2(n, 1, lines);
        tc++;
    }

    lines.insert(lines.begin(), {tc});
    print(lines);
}

void generate_hard_use_only_1_3_large() {

    int tc = 0;
    vector<vector<int>> lines;
    generate_use_only_1_3(4, 500, lines);
    tc++;
    lines.insert(lines.begin(), {tc});
    print(lines);
}

void generate_hard_use_only_1_3_or_2_small() {
    int tc = 0;
    vector<vector<int>> lines;
    // small N, all_1_3
    int n_sum = 1000; 
    while(n_sum >= 2) {
        int n = rnd.next(2, min(n_sum, 10));
        if(n % 2 == 1) n--;
        int k = rnd.next(1, min(5, n_sum / n));
        n_sum -= n * k;
        generate_use_only_1_3(n, k, lines);
        tc++;
    }
    n_sum = 1000;
    while(n_sum >= 2) {
        int n = rnd.next(2, min(n_sum, 10));
        if(n % 2 == 1) n--;
        int k = rnd.next(1, min(5, n_sum / n));
        n_sum -= n * k;
        generate_use_only_2(n, k, lines);
        tc++;
    }

    lines.insert(lines.begin(), {tc});
    print(lines);
}


void generate_large_k() {
    int tc = 1;
    cout << tc << "\n";
    print_random_grid(4, 500);
}

void generate_large_n_small_k() {
    int tc = 1;
    cout << tc << "\n";
    print_random_grid(1000, 2);
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    if(strcmp("easy", argv[1]) == 0) {
        if(strcmp("same", argv[2]) == 0) {
            int each_sz = atoi(argv[3]);
            generate_same(each_sz, TOTAL_EASY);
        }
        else if(strcmp("random", argv[2]) == 0) {
            generate_random(TOTAL_EASY);
        }
        else if(strcmp("use_only_1_3", argv[2]) == 0) {
            if(strcmp("large", argv[3]) == 0) {
                generate_easy_use_only_1_3_large();
            }
            else {
                throw new exception();
            }
        }
        else if(strcmp("use_only_1_3_or_2", argv[2]) == 0) {
            if(strcmp("small", argv[3]) == 0) {
                generate_easy_use_only_1_3_or_2_small();
            }
        }
        else {
            throw new exception();
        }
    }
    else if(strcmp("hard", argv[1]) == 0) {
        if(strcmp("same", argv[2]) == 0) {
            int each_sz = atoi(argv[3]);
            if(each_sz == 4)
                generate_same(each_sz, TOTAL_HARD, 10);
            else 
                generate_same(each_sz, TOTAL_HARD);
        }
        else if(strcmp("random", argv[2]) == 0) {
            generate_random(TOTAL_HARD);
        }
        else if(strcmp("use_only_1_3", argv[2]) == 0) {
            if(strcmp("large", argv[3]) == 0) {
                generate_hard_use_only_1_3_large();
            }
            else {
                throw new exception();
            }
        }
        else if(strcmp("use_only_1_3_or_2", argv[2]) == 0) {
            if(strcmp("small", argv[3]) == 0) {
                generate_hard_use_only_1_3_or_2_small();
            }
            else {
                throw new exception();
            }
        }
        else if(strcmp("large_k", argv[2]) == 0) {
            generate_large_k();
        }
        else if(strcmp("large_n_small_k", argv[2]) == 0) {
            generate_large_n_small_k();
        }
        else {
            throw new exception();
        }
    }
    else {
        throw new exception();
    }
}