#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

const int TOTAL = 2000;
const int N = 1000, MAX = 1e9, K = 1000;

int main(int argc, char *argv[]) {
  freopen(argv[1], "r", stdin);
  registerValidation(argc, argv);
  int tc = inf.readInt();
  inf.readEoln();
  int n_sum = 0;
  for(int t = 0; t < tc; t++) {
      int n = inf.readInt(1, N);
      assert(n % 2 == 0);
      inf.readSpace();
      int k = inf.readInt(1, K);
      n_sum += n * k;
      inf.readEoln();
      for(int i = 0; i < k * n * n / 2; i++) {
          int x = inf.readInt(0, MAX);
          inf.readSpace();
          int y = inf.readInt(0, MAX);
          inf.readEoln();
      }
  }

  assert(n_sum <= TOTAL);
  inf.readEof();

  return 0;
}