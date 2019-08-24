#include<bits/stdc++.h>
using namespace std;
template <class t> class MergeSortTree{
	public:
		int _l, _r, _m;
		vector<t> v;
		MergeSortTree *left, *right;
		MergeSortTree(int l, int r, vector<t> &e){
			_l=l, _r=r, _m=(l+r)/2;
			v.resize(r-l+1);
			if(l==r){
				left=right=nullptr;
				v[0]=e[l];
			}
			else{
				left=new MergeSortTree(_l,_m, e);
				right=new MergeSortTree(_m+1,_r, e);
				merge(left->v.begin(), left->v.end(), right->v.begin(), right->v.end(), v.begin());
			}
		}
		inline int count(int l, int r, t a, t b){
			if(l>_r || r<_l) return 0;
			if(_l>=l && _r<=r)	return upper_bound(v.begin(), v.end(), b)-lower_bound(v.begin(), v.end(), a);
			return left->count(l,r,a,b)+right->count(l,r,a,b);
		}
};
int main(){
	vector<int> v={1,5,2,7,4,1};
	MergeSortTree<int> mt(0,v.size()-1,v);
	cout<<mt.count(0,v.size()-1,0,7);
}
