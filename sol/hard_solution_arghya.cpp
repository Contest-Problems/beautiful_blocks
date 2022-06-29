#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define pb push_back
#define mp make_pair

#define FOR(i,a,b) for(i=a ; i<=b ; i++)
#define DBG printf("Hi\n")
#define INF 1000000000000000000LL
#define i64 long long int
#define eps (1e-8)
#define xx first
#define yy second
#define ln 17
#define SZ(z) ((int)z.size())
#define sq(x) ((x)*(x))

#define FastIO ios_base::sync_with_stdio(false); cin.tie(NULL)

#define mod 1000000007

using namespace __gnu_pbds;
using namespace std ;

typedef tree< pair<int,int>, null_type, less<pair<int,int>>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

const double EPS = 1e-9 , PI = acos(-1.0);

#define IN freopen("/benchmark_node2/stat.txt","r",stdin)
#define OUT freopen("output.txt","w",stdout)
typedef pair<int,int> pii;

#define maxn 1000005
#define off 2500

struct data{
    i64 v[4];
    int idx;
}blocks[maxn];

bool comp1(struct data b1, struct data b2){
    return b1.v[0] < b2.v[0];
}
bool comp2(struct data b1, struct data b2){
    return b1.v[0]+b1.v[1] < b2.v[0]+b2.v[1];
}
bool comp3(struct data b1, struct data b2){
    return b1.v[0]+b1.v[1]+b1.v[2] < b2.v[0]+b2.v[1]+b2.v[2];
}
bool compIdx(struct data b1, struct data b2){
    return b1.idx < b2.idx;
}

i64 dp[5005][5005];

int main()
{
    int tc;
    scanf("%d",&tc);

    while(tc--)
    {
        int n, K=1;
        scanf("%d %d",&n,&K);
//        scanf("%d",&n);

        int m = (n*n*K)/4;
        int lenofpath = K*(n-1);
        for(int i=1; i<=m; i++)
        {
            for(int j=0; j<4; j++){
                scanf("%lld",&blocks[i].v[j]);
            }
            sort(blocks[i].v,blocks[i].v+4);
            reverse(blocks[i].v,blocks[i].v+4);
            blocks[i].idx = i;
        }

        vector<int> idx;
        sort(blocks+1, blocks+m+1, comp1);
        for(int i=m, j=1; j<=lenofpath; j++,i--) idx.pb(blocks[i].idx);
        sort(blocks+1, blocks+m+1, comp2);
        for(int i=m, j=1; j<=lenofpath; j++,i--) idx.pb(blocks[i].idx);
        sort(blocks+1, blocks+m+1, comp3);
        for(int i=m, j=1; j<=lenofpath; j++,i--) idx.pb(blocks[i].idx);

        sort(blocks+1, blocks+m+1, compIdx);


        sort(idx.begin(), idx.end());
        idx.erase(unique(idx.begin(), idx.end()), idx.end());
    //    for(auto i:idx) printf("-- %d\n",i);
    //    printf("--------------------- %d\n",idx.size());

        m = idx.size();
        for(int i=1; i<=m; i++){
            for(int j=0; j<4; j++) blocks[i].v[j] = blocks[idx[i-1]].v[j];
            blocks[i].idx = blocks[idx[i-1]].idx;
        }

        sort(blocks+1, blocks+m+1, comp2);
        reverse(blocks+1, blocks+m+1);
        for(int i=1; i<=m; i++) blocks[i].idx = i;

        for(int i=1; i<=m; i++)
        {
   //         for(int j=0; j<4; j++) printf("%d ",blocks[i].v[j]);
   //         printf("\n");
        }

        for(int i=0; i<=lenofpath; i++)
        {
            for(int j=-(lenofpath+1); j<=lenofpath+1; j++) dp[i][j+off] = -INF;
        }
        dp[0][0+off] = 0;
        for(int i=1; i<=lenofpath; i++){
            for(int j=-lenofpath; j<=lenofpath; j++){
                dp[i][j+off] = max(dp[i][j+off], dp[i-1][j-1+off] + blocks[i].v[0] + blocks[i].v[1] + blocks[i].v[2]);
                dp[i][j+off] = max(dp[i][j+off], dp[i-1][j+off] + blocks[i].v[0] + blocks[i].v[1]);
                dp[i][j+off] = max(dp[i][j+off], dp[i-1][j+1+off] + blocks[i].v[0]);
            }
        }

        i64 ans = dp[lenofpath][K+off];
        //printf("-- %lld\n",ans);

        for(int i=lenofpath; i>=1; i--){
            i64 total = 0LL;
            set<pair<i64,int>> single, singleplus2, zero;
            for(int j=i; j<=m; j++) single.insert(mp(blocks[j].v[0],j));
            while(single.size()>lenofpath-i+1){
                single.erase(single.begin());
            }

            for(int j=i; j<=m; j++){
                if(single.find(mp(blocks[j].v[0],j))!=single.end()){
                    singleplus2.insert(mp(blocks[j].v[1]+blocks[j].v[2],j));
                    total += blocks[j].v[0];
                }
                else zero.insert(mp(blocks[j].v[0]+blocks[j].v[1]+blocks[j].v[2],j));
            }

        //    printf("started - %lld\n",total);
            for(int j=0; j<=lenofpath-i+1; j++){
                if(j>=1){
                    // take one from zero block and remove one from single block
                    if(zero.size()>0 && zero.rbegin()->xx - single.begin()->xx > singleplus2.rbegin()->xx){
                        auto it1 = zero.rbegin();
                        auto it2 = single.begin();
                        int sidx = it2->yy, zidx = it1->yy;
                        total += (it1->xx - it2->xx);
                        singleplus2.erase(singleplus2.find(mp(blocks[sidx].v[1]+blocks[sidx].v[2],sidx)));
                        single.erase(it2);
                        zero.erase(zero.find(mp(it1->xx,it1->yy)));
                        zero.insert(mp(blocks[sidx].v[0]+blocks[sidx].v[1]+blocks[sidx].v[2],sidx));
                    }
                    else{
                        auto it1 = singleplus2.rbegin();
                        int sidx = it1->yy;
                        total += it1->xx;
                        single.erase(single.find(mp(blocks[sidx].v[0],sidx)));
                        singleplus2.erase(singleplus2.find(mp(it1->xx,it1->yy)));
                    }
                }
                assert( single.size() == (lenofpath-(i-1)-j) );
                if(abs(K-(j-(lenofpath-(i-1)-j))) > i-1) continue;
             //   assert(K-(j-(lenofpath-(i-1)-j)) >= -lenofpath && K-(j-(lenofpath-(i-1)-j)) >= lenofpath );
                //printf("--%d %d %d  %d\n",i,j,K-(j-(lenofpath-(i-1)-j)), (lenofpath-(i-1)-j));
                ans = max(ans, dp[i-1][K-(j-(lenofpath-(i-1)-j)) + off] + total);
      //          printf("%d %d: %lld %lld %lld %d %d\n",i,j,ans,total, dp[i-1][1-(j-(n-i-j)) + off], j, n-i-j);
            }
      //      printf("%d: %lld\n",i,ans);
        }
        printf("%lld\n",ans);
    }

    return 0;
}
