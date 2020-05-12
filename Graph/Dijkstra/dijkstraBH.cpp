#include<bits/stdc++.h>
using namespace std;
template<class T> class BinaryHeap{
	public:
		BinaryHeap(int MAXN){ tree.reserve(MAXN); }
		BinaryHeap(){}
		bool empty(){ return tree.empty(); }
		int size(){ return (int)tree.size(); }
		T top(){ return tree[0]; }
		void push(T x){
			int i=(int)tree.size();
			tree.push_back(x);
			while(i>0 && tree[(i-1)/2]>tree[i]){
				swap(tree[i],tree[(i-1)/2]);
				i=(i-1)/2;
			}
		}
		void pop(){
			if(tree.empty()) return;
			tree[0]=tree.back();
			tree.pop_back();
			if(!tree.empty()) balance(0);
		}
	private:
		vector<T> tree;
		void balance(int i){
			while(i<(int)tree.size()){
				int smallest=i, l=i*2+1, r=i*2+2;
				if(l<(int)tree.size() && tree[l]<tree[smallest])	smallest=l;
				if(r<(int)tree.size() && tree[r]<tree[smallest]) smallest=r;
				if(i==smallest) return;
				swap(tree[i],tree[smallest]);
				i=smallest;
			}
		}
};
template<typename T> T dijkstra(int N, int start, int end, vector<vector<pair<int,T>>> &graph){
	vector<T> dist(N,-1);
	BinaryHeap<pair<T,int>> pq;
	dist[start]=0;
	pq.push({0,start});
	while(!pq.empty()){
		auto [d,node]=pq.top();
		if(node==end)
			return d; 
		pq.pop();
		for(auto next:graph[node])
			if(dist[next.first]==-1 || dist[next.first]>d+next.second){
				dist[next.first]=d+next.second;
				pq.push({dist[next.first],next.first});
			}
	}
	return -1;
}
