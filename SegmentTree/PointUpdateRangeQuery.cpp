#include <bits/stdc++.h>
using namespace std;
template<class T, T merge(T,T)>class SegmentTree{
	public:
		SegmentTree(int N, T def){ 
			tree.resize(N<<2);
			build_default(0,N-1,def,0);
		}
		SegmentTree(vector<T> vals){ 
			tree.resize((int)vals.size()<<2);
			build(0,(int)vals.size()-1,0,vals);
		}
		void update(int i, T value){ update(0,(int)tree.size()/4-1,i,0,value); }
		T query(int L, int R){ return query(0,(int)tree.size()/4-1,0,L,R); }
	private:
		vector<T> tree;
		void build_default(int l, int r, int pos, T def){
			if(l^r){
				build_default(l,l+r>>1,2*pos+1,def);
				build_default(2+l+r>>1,r,2*pos+2,def);
				tree[pos]=merge(tree[2*pos+1],tree[2*pos+2]);
			}
			else tree[pos]=def;			
		}
		void build(int l, int r, int pos, vector<T> &vals){
			if(l^r){
				build(l,(l+r)/2,2*pos+1,vals);
				build(1+(l+r)/2,r,2*pos+2,vals);
				tree[pos]=merge(tree[2*pos+1],tree[2*pos+2]);
			}
			else tree[pos]=vals[l];
		}
		void update(int l, int r, int i, int pos, T val){
			if(l==r)	tree[pos]=val;
			else{
				if(i<=l+r>>1)	update(l,l+r>>1,i,2*pos+1,val);
				else update(2+l+r>>1,r,i,2*pos+2,val);
				tree[pos]=merge(tree[2*pos+1],tree[2*pos+2]);	
			}
		}
		T query(int l, int r, int pos, int L, int R){
			if(L<=l && R>=r)	return tree[pos];
			if(R<=(l+r)/2)	return query(l,(l+r)/2,2*pos+1,L,R);
			if(L>(l+r)/2)	return query(1+(l+r)/2,r,2*pos+2,L,R);
			return merge(query(l,(l+r)/2,2*pos+1,L,R),query(1+(l+r)/2,r,2*pos+2,L,R));
		}
};
