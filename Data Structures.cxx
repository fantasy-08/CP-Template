#include <bits/stdc++.h>
using namespace std;

#define watch(x) cout<<(#x)<<"="<<(x)<<endl
#define mset(d,val) memset(d,val,sizeof(d))
#define setp(x) cout<<fixed<<setprecision(x)
#define forn(i,a,b) for(int i=a;i<b;i++)
#define fore(i,a,b) for(int i=a;i<=b;i++)
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define PI 3.14159265358979323846264338327
#define INF 0x3f3f3f3f
#define MOD 998244353
#define pqueue priority_queue
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef unsigned long long ull;

#define MAXN 100005

//DSU start
struct DSU{
	struct node{ int p; ll sum; };
	vector<node> dsu;
	DSU(int n){ dsu.resize(n);
		forn(i,0,n){ dsu[n].p=i; }
	}
	int rt(int u){ return (dsu[u].p==u) ? u : dsu[u].p=rt(u); }
	bool sameset(int u, int v){ return rt(u)==rt(v); }
	void merge(int u, int v){
		u = rt(u); v = rt(v);
		if(u == v) return;
		if(rand()&1) swap(u,v);
		dsu[v].p = u;
	}
	//ll getstat(int u){ return dsu[rt(u)].sum; }
	//void setstat(int u,ll val){ dsu[rt(u)].sum = val; }
};
//DSU end

//Kruskal start
int n,m;
vector<pair<ll,ii>> edge;
vector<pair<ii,ll>> mst;
ll totw=0;

void kruskal(){
	DSU dsu(n);
	sort(edge.begin(),edge.end());
	
	forn(i,0,m){
		int u=edge[i].S.F, v=edge[i].S.S; ll w=edge[i].F;
		if(dsu.sameset(u,v)) continue;
		dsu.merge(u,v);
		mst.pb({{u,v},w});
		totw+=w;
		if(mst.size()>=n-1) break;
	}
}
//Kruskal end

//Dijkstra start
vii adj[MAXN];
ll dist[MAXN];

int n;

void dijkstra(int src){
	pqueue<ii,vii,greater<ii>> q;
	forn(i,0,n)	dist[i]=INF;
	dist[src]=0;
	q.push({0,src});
	
	while(!q.empty()){
		int u=q.top().S; q.pop();
		for(auto tmp: adj[u]){
			int v=tmp.F; ll w=tmp.S;
			if(dist[v]>dist[u]+w){
				dist[v]=dist[u]+w;
				q.push({d[v],v});
			}
		}
	}
}
//Dijkstra end

//Prim start

//Prim end

//Lazy Recursive ST start
class LazySegmentTree{
private:
	int size_;
	vector<ll> v,lazy;
	
	void update(int s, int e, ll val, int k, int l, int r){
		push(k,l,r);
		if(r < s || e < l) return;
		if(s <= l && r <= e){
			lazy[k] = val;
			push(k, l, r);
		}
		else{
			update(s, e, val, k*2, l, (l+r)>>1);
			update(s, e, val, k*2+1, ((l+r)>>1)+1, r);
			v[k] = merge(v[k*2], v[k*2+1]);
		}
	}
	
	ll query(int s, int e, int k, int l, int r){
		push(k,l,r);
		if(r < s || e < l) return 0;
		if(s <= l && r <= e) return v[k];
		ll lc = query(s, e, k*2, l, (l+r)>>1);
		ll rc = query(s, e, k*2+1, ((l+r)>>1)+1, r);
		return merge(lc, rc);
	}
 
public:
	LazySegmentTree(): v(vector<ll>()), lazy(vector<ll>()) {};
	LazySegmentTree(int n){
		for(size_=1;size_< n;) size_<<=1;
		v.resize(size_*4);
		lazy.resize(size_*4);
	}
	inline void push(int k, int l, int r){
		if(lazy[k]!=0){
			v[k]=lazy[k];
			if(l!=r){
				lazy[k*2]+=lazy[k];
				lazy[k*2+1]+=lazy[k];
			}
			lazy[k]=0;
		}
	}
	inline ll merge(ll x, ll y){
		return x+y;
	}
	inline void update(int l, int r, ll val){
		update(l, r, val, 1, 0, size_-1);
	}
	inline ll query(int l, int r){
		return query(l, r, 1, 0, size_-1);
	}
};

ll a[MAXN],xr[MAXN];
LazySegmentTree st(n);

//Lazy recursive ST end

//Euler path start
int in[MAXN],out[MAXN];
int tmr=-1;

void dfs(int u, int p)
{
	in[u]=++tmr;
	for(int v:adj[u])
	{
		if(v==p) continue;
		dfs(v,u);
	}
	out[u]=tmr;
}
//Euler path end

//LCA start
#define LG 18

int depth[MAXN],prt[LG+1][MAXN];
mset(prt,-1);

void dfs(int u, int p)
{
	prt[0][u]=p;
	for(int v:adj[u])
	{
		if(v==p) continue;
		depth[v]=depth[u]+1;
		dfs(v,u);
	}
}

int lca(int u, int v)
{
	if(depth[u]>depth[v]) swap(u,v);
	for(int i=LG-1;i>=0;i--)
	{
		if(prt[i][v]!=-1&&depth[prt[i][v]]>=depth[u])
		{
			v=prt[i][v];
		}
	}
	if(u==v) return u;
	for(int i=LG-1;i>=0;i--)
	{
		if(prt[i][v]!=-1&&prt[i][v]!=prt[i][u])
		{
			v=prt[i][v]; u=prt[i][u];
		}
	}
	return prt[0][u];
}
//LCA end

//Iterative ST start
ll t[2*MAXN];

void build(){
	for(int i=n-1;i>0;i--) 	t[i]=t[2*i]+t[2*i+1];	
}

void update(int p,int val){
	for(t[p+=n]=val;p>1;p/=2)	t[p/2]=t[p]+t[p^1];
}

ll query(int l,int r){
	r++;
	ll sum=0;
	for(l+=n,r+=n;l<r;l/=2,r/=2){
		if(l&1)	sum+=t[l++];
		if(r&1)	sum+=t[--r];
	}
	return sum;
}
//Iterative ST end

int in[MAXN],out[MAXN],prt[MAXN];
ll sz[MAXN];

//HLD start
void dfs_sz(int u=0,int p=-1){
	sz[u]=1;
	prt[u]=p;
	depth[u]=0;
	if(adj[u][0]==p && adj[u].size()>1) swap(adj[u][0],adj[u][1]);
	for(auto &v: adj[u]){
		if(v==p) continue;
		depth[v]=depth[u]+1;
		dfs_sz(v,u);
		sz[u]+=sz[v];
		if(sz[v]>sz[adj[u][0]]) swap(v,adj[u][0]);
	}
}

int timer=0;
void dfs_hld(int u=0,int p=-1){
	in[u]=timer++;
	pos[in[u]]=arr[u];
	for(auto v:adj[u]){
		if(v==p) continue;
		head[v] = (v==adj[u][0]) ? head[u] : v;
		dfs_hld(v,u);
	}
	out[u]=timer;
}
//HLD end

//Sparse Table start: O(1) Min Query example
struct SparseTable{
	ll spt[MAXN][LG];
	
	int lg[MAXN+1];
	lg[1]=0;
	fore(i,2,MAXN)	lg[i]=lg[i/2]+1;
	
	ll merge(ll x,ll y){
		return min(x,y);
	}
	
	SparseTable(int n){
		forn(i,0,n) spt[i][0] = spt[i];
		fore(j,1,LG)
			for(int i=0; i+(1<<j)<=n; i++)
				spt[i][j] = merge(spt[i][j-1], spt[i+(1<<(j-1))][j-1]);
	}
	
	ll query(int l,int r){
		int j=lg[r-l+1];		
		return min(spt[i][j],spt[r-(1<<j)+1][j]);
	}
}

#define LG 25
//Sparse Table end

