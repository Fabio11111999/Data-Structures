#include<bits/stdc++.h>
using namespace std;
template<class T> class BinaryHeap{
	public:
		BinaryHeap(int MAXN){
			tree.reserve(MAXN);
			id.reserve(MAXN);
			freek.reserve(MAXN);
		}
		BinaryHeap(){}
		int size(){ return (int)tree.size(); }
		T top(){ return tree[0].first; }
		bool empty(){ return tree.empty(); }
		int push(T x){
			int key;
			if(!freek.empty()){
				key=freek.back();
				freek.pop_back();
			} else key=next_key++;
			tree.push_back({x,key});
			id[key]=(int)tree.size();
			int i=(int)tree.size()-1;
			while(i>0 && tree[(i-1)/2].first>tree[i].first){
				myswap((i-1)/2,i);
				i=(i-1)/2;
			}
			return key;
		}
		void pop(){
			if(tree.empty()) return;
			freek.push_back(tree[0].second);
			myswap(0,(int)tree.size()-1);
			tree.pop_back();
			balance(0);
		}
	private:
		vector<pair<T,int>> tree;
		vector<int> id, freek;
		int next_key=0;
		void myswap(int i, int j){
			swap(id[tree[i].second],id[tree[j].second]);
			swap(tree[i],tree[j]);
		}
		void balance(int i){
			while(i<(int)tree.size()){				
				int smallest=i, l=i*2, r=i*2+1;
				if(l<(int)tree.size() && tree[l].first<tree[smallest].first) smallest=l;
				if(r<(int)tree.size() && tree[r].first<tree[smallest].first) smallest=r;
				if(i==smallest) return;
				myswap(i,smallest);
				i=smallest;
			}
		}
};
