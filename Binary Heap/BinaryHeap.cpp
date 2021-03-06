#include<bits/stdc++.h>
using namespace std;
template<class T> class BinaryHeap{
	public:
		BinaryHeap(int MAXN){ tree.reserve(MAXN); }
		BinaryHeap() {}
		bool empty(){ return tree.empty(); }
		T top(){ return tree[0]; }
		int size(){ return (int)tree.size(); }
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
