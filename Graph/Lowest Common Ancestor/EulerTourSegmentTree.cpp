#include<bits/stdc++.h>
using namespace std;
class LCA{
public:
	int n, dim;
	vector<int> height, first, euler, st;
	vector<bool> vis;
	LCA(vector<vector<int>> &g, int root=0){
		n=g.size();
		height.resize(n);
		first.resize(n);
		euler.resize(2*n);
		vis.resize(n);
		for(int i=0;i<n;i++)
			vis[i]=false;
		dfs(root,g);
		dim=euler.size();
		st.reserve(4*dim);
		buildSt(0,dim-1,0);

	}
	void dfs(int node, vector<vector<int>> &g, int h=0){
		vis[node]=true;
		height[node]=h;
		first[node]=euler.size();
		euler.push_back(node);
		for(auto next:g[node])
			if(!vis[next]){
				dfs(next,g,h+1);
				euler.push_back(node);
		}
	}
	void buildSt(int start, int end, int pos){
		if(start==end)
			st[pos]=euler[start];
		else{
			int mid=(start+end)/2;
			buildSt(start,mid,pos*2+1);
			buildSt(mid+1,end,pos*2+2);
			st[pos]=(height[st[pos*2+1]]<height[st[pos*2+2]])?st[pos*2+1]:st[pos*2+2];
		}
	}
	int query(int l, int r, int start, int end, int pos=0){
		if(end<l || start>r)
			return -1;
		if(l<=start && end<=r)
			return st[pos];
		int mid=(start+end)/2;
		int lq=query(l,r,start,mid,pos*2+1), rq=query(l,r,mid+1,end,pos*2+2);
		if(lq==-1)
			return rq;
		if(rq==-1)
			return lq;
		return (height[lq]<height[rq])?lq:rq;
	}
	int lca(int v1, int v2){
		int left=first[v1], right=first[v2];
		if(left>right)
			swap(left,right);
		return query(left,right,0,dim-1);
	}
};
ifstream in("input.txt");
ofstream out("output.txt");
int main(){
	int n;
	in>>n;
	vector<vector<int>> g;
	g.resize(n);
	for(int i=0;i<n-1;i++){
		int from, to;
		in>>from>>to;
		from--,to--;
		g[from].push_back(to);
	}
	LCA tree(g);
	out<<tree.lca(4,5);
}
