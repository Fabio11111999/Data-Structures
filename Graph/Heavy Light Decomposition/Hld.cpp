#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000
#define MAXM 100000
int pesi[MAXN], a[MAXN] , b[MAXN], qA[MAXM], qB[MAXM], sol[MAXM];
int n;
vector<int> parent, depth, heavy, head, pos, ele, tree, order;
int dfs(vector<vector<int>> &g, int node=0){
	int dim=1, max_dim=0;
	for(auto next: g[node])
		if(parent[node]!=next){
			parent[next]=node;
			depth[next]=depth[node]+1;
			int current=dfs(g,next);
			dim+=current;
			if(current>max_dim){
				max_dim=current;
				heavy[node]=next;
			}
		}
	return dim;
}
int cur_pos=0;
void decompose(int node, int inizioCantena, vector<vector<int>> &g){
	head[node]=inizioCantena;
	pos[node]=cur_pos++;
	if(heavy[node]!=-1) //Continuo la catena
		decompose(heavy[node], inizioCantena, g);
	//Altre catene
	for(auto x:g[node])
		if(x!=parent[node] && x!=heavy[node])
			decompose(x,x,g);
}
void buildST(int start, int end, int pos){
	if(start==end)
		tree[pos]=order[start];
	else{
		int mid=(start+end)/2;
		buildST(start,mid,pos*2+1);
		buildST(mid+1,end,pos*2+2);
		tree[pos]=max(tree[pos*2+1], tree[pos*2+2]);
	}
}
int queryST(int start, int end, int pos, int l, int r){
	if(start>r || end<l)
		return 0;
	if(start>=l && end<=r)
		return tree[pos];
	int mid=(start+end)/2;
	return max(queryST(start,mid,pos*2+1,l,r), queryST(mid+1,end,pos*2+2,l,r));
}
void init(vector<vector<int>> &g){
	n=g.size();
	parent.resize(n);
	depth.resize(n);
	depth[0]=0;
	heavy.resize(n);
	for(int i=0;i<n;i++)
		heavy[i]=-1;
	head.resize(n);
	pos.resize(n);
	dfs(g);
	decompose(0,0,g);
	tree.resize(4*n);
	order.resize(n);
	for(int i=0;i<n;i++)
		order[pos[i]]=ele[i];
	buildST(0,n-1,0);
	parent[0]=-1;
}
int query(int a, int b){
	int res=0;
	for(;head[a]!=head[b];b=parent[head[b]]){
		if(depth[head[a]]>depth[head[b]])
			swap(a,b);
		res=max(res, queryST(0,n-1,0,pos[head[b]], pos[b]));
	}
	if(depth[a]>depth[b])
			swap(a,b);
	res=max(res,queryST(0,n-1,0,pos[a],pos[b]));
	return res;
}
void printSt(int start=0, int end=n-1,int pos=0){
	cout<<start<<" "<<end<<" "<<tree[pos]<<"\n";
	if(start!=end){
		int mid=(start+end)/2;
		printSt(start,mid,pos*2+1);
		printSt(mid+1,end,pos*2+2);
	}
}
void solve(int N, int Q, int *briganti, int *A, int *B, int *start, int *end, int *sol){
	vector<vector<int>> g;
	g.resize(N);
	for(int i=0;i<N-1;i++){
		g[A[i]].push_back(B[i]);
		g[B[i]].push_back(A[i]);
	}
	for(int i=0;i<N;i++)
		ele.push_back(briganti[i]);
	init(g);
	for(int i=0;i<Q;i++)
		sol[i]=query(start[i],end[i]);
}
int main(){
	ifstream in("input.txt");
	ofstream out("output.txt");
	int n, q;
	in>>n>>q;
	for(int i=0;i<n;i++) in>>pesi[i];
	for(int i=0;i<n-1;i++) in>>a[i]>>b[i];
	for(int i=0;i<q;i++) in>>qA[i]>>qB[i];
    solve(n,q,pesi,a,b,qA,qB,sol);
    for(int i=0;i<q;i++) out<<sol[i]<<" ";	

}
