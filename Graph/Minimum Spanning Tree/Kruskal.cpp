#pragma GCC optimize ("O3")
#define ll long long int
#include<bits/stdc++.h>
using namespace std;
struct edge{
	int from, to;
	ll weight;
};
bool confEdge(edge const &a, edge const &b){
	if(a.weight<b.weight) return true;
	if(a.weight>b.weight) return false;
	if(a.from<b.from) return true;
	if(a.from>b.from) return false;
	if(a.to<b.to) return true;
	if(a.to>b.to) return false;
}
struct subset{
	int parent, rank;
};
vector<subset> sub;
int _find(int node){
	if(sub[node].parent!=node)
		sub[node].parent=_find(sub[node].parent);
	return sub[node].parent;
}
void _union(int n1, int n2){
	int p1=_find(n1), p2=_find(n2);
	if(sub[p1].rank>sub[p2].rank)
		sub[p2].parent=p1;
	else if(sub[p1].rank<sub[p2].rank)
		sub[p1].parent=p2;
	else{
		sub[p2].parent=p1;
		sub[p1].rank++;
	}
}
//Kruskal
vector<pair<int,int>> sol;
ll mst(vector<edge> &v, int n){
	sort(v.begin(),v.end(),confEdge);
	ll ans=0, cnt=0, idx=0;
	while(cnt<n-1 && idx<v.size()){
		if(_find(v[idx].from)!=_find(v[idx].to)){
			cnt++;
			ans+=v[idx].weight;
			_union(v[idx].from, v[idx].to);
			sol.push_back({v[idx].from, v[idx].to});
		}
		idx++;
	}
	return ans;
}
int n, m;
int main()
{
	ifstream in("input.txt");
	ofstream out("output.txt");
	in>>n>>m;
	vector<edge> v(m);
	for(int i=0;i<m;i++){
		int from, to;
		ll dist;
		in>>from>>to>>dist;
		v[i]={from-1,to-1,dist};
	}
	sub.resize(n);
	for(int i=0;i<n;i++)
		sub[i]={i,0};
	out<<mst(v,n)<<"\n";
	for(auto x:sol)
		out<<x.first+1<<" "<<x.second+1<<"\n";
}
