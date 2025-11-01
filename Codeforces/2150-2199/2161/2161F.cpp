#include  <bits/stdc++.h>
using namespace std;


const int M=1'000'000'007;
int add(int a,int b){a+=b; if(a>=M) a-=M; return a;}
int subm(int a,int b){a-=b; if(a<0) a+=M; return a;}
int mul(long long a,long long b){return int(a%M*b%M);}
vector<int> p2;

void ensure_p2(int n){
  if((int)p2.size()>n) return;
  if(p2.empty()) p2={1};
  while((int)p2.size()<=n) p2.push_back(add(p2.back(),p2.back()));
}

int n; vector<vector<int>> adj;

int steiner_total(){ // 2) sum_S L(S)
  vector<int> sz(n+1,0), par(n+1,-1);
  function<void(int,int)> dfs=[&](int u,int p){
    par[u]=p; sz[u]=1;
    for(int v:adj[u]) if(v!=p){ dfs(v,u); sz[u]+=sz[v]; }
  };
  dfs(1,-1);
  long long res=0;
  for(int u=1;u<=n;u++) for(int v:adj[u]) if(v==par[u]){
    int s=sz[u], t=n-s;
    int a=subm(p2[s],1), b=subm(p2[t],1);
    res+=1ll*a*b%M;
  }
  return int(res%M);
}

// collect counts per branch for center c
void collect_even_center(int c, long long &sumD){
  int m=adj[c].size(); if(m<2) return;
  // per-branch t_b(d)
  vector<vector<int>> tb; tb.reserve(m);
  int maxR=0;
  function<void(int,int,int,vector<int>&)> dfsb=[&](int u,int p,int d,vector<int>& cnt){
    if((int)cnt.size()<=d) cnt.resize(d+1,0);
    cnt[d]++; // distance d from center c
    for(int w:adj[u]) if(w!=p) dfsb(w,u,d+1,cnt);
  };
  for(int v:adj[c]){
    vector<int> cnt; dfsb(v,c,1,cnt);
    maxR=max(maxR,(int)cnt.size()-1);
    tb.push_back(move(cnt));
  }
  if(maxR==0) return;

  // sumT[d], sumPow[d]
  vector<int> sumT(maxR+1,0), sumPow(maxR+1,0);
  for(auto &cnt:tb){
    for(int d=1; d<(int)cnt.size(); d++){
      sumT[d]+=cnt[d];
    }
  }
  for(int d=1; d<=maxR; d++){
    long long s=0;
    for(auto &cnt:tb){
      int t = (d<(int)cnt.size()? cnt[d]:0);
      s += p2[t];
    }
    sumPow[d]=int(s%M);
  }

  // prefix S1 and Z
  vector<int> S1(maxR+1,0), Z(maxR+1,0);
  for(int d=1; d<=maxR; d++){
    S1[d]=S1[d-1]+sumT[d];
    Z[d]=S1[d-1];
  }

  for(int R=1; R<=maxR; R++){
    int term = subm(p2[S1[R]], mul(p2[Z[R]], subm(sumPow[R], m-1)));
    // 2*( ... ) * (2R)
    int ways = add(term, term);
    long long addD = 1LL*ways*(2LL*R % M)%M;
    sumD = (sumD + addD)%M;
  }
}

// per-edge odd centers
vector<int> side_shell(int root,int forbid){
  // T[d] for the component of root that does not go through forbid
  vector<int> T(1,0);
  function<void(int,int,int)> dfs=[&](int u,int p,int d){
    if((int)T.size()<=d) T.resize(d+1,0);
    T[d]++;
    for(int w:adj[u]) if(w!=p && w!=forbid) dfs(w,u,d+1);
  };
  dfs(root,-1,0); // includes root at d=0
  return T;
}

int solve_one(){
  cin>>n; ensure_p2(n);
  adj.assign(n+1,{});
  for(int i=0;i<n-1;i++){
    int u,v; cin>>u>>v;
    adj[u].push_back(v); adj[v].push_back(u);
  }

  // 1) sum L(S)
  int sumL = steiner_total();

  // 2a) even diam centers
  long long sumD=0;
  for(int c=1;c<=n;c++) collect_even_center(c, sumD);

  // 2b) odd diam centers
  // compute for each edge (u,v) once with sides
  vector<char> seen(n+1,0);
  for(int u=1; u<=n; u++){
    for(int v:adj[u]) if(u<v){
      auto TL = side_shell(u,v);
      auto TR = side_shell(v,u);
      int maxR=min((int)TL.size()-1,(int)TR.size()-1);
      // prefix sums S
      for(int i=1;i<(int)TL.size();i++) TL[i]+=TL[i-1];
      for(int i=1;i<(int)TR.size();i++) TR[i]+=TR[i-1];
      for(int R=0; R<=maxR; R++){
        int SL=TL[R], TLr = SL - (R?TL[R-1]:0);
        int SR=TR[R], TRr = SR - (R?TR[R-1]:0);
        int AL = subm(p2[SL], p2[SL - TLr]);
        int AR = subm(p2[SR], p2[SR - TRr]);
        long long ways = 1LL*AL*AR%M;
        sumD = (sumD + ways * ((2LL*R+1)%M))%M;
      }
    }
  }

  int ans = subm( mul(2,sumL), int(sumD%M) );
  if(ans<0) ans+=M;
  cout<<ans<<endl;
  return ans;
}

int32_t main(){
  int t; cin>>t;
  while(t--) solve_one();
}
