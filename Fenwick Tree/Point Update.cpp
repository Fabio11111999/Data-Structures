#include<bits/stdc++.h>
using namespace std;
template <class t,t op(t,t)> class fenwickTree
{
	public:
		vector <t> tree;
		int dim;
		fenwickTree(vector<t> elements, int n){
			dim=n+1;
			tree.resize(dim);
			for(int i=0;i<dim;i++) tree[i]=0;
			for(int i=0;i<dim;i++) pointUpdate(i, elements[i]);
		}
		fenwickTree(int n){
			dim=n+1;
			tree.reserve(dim);
			for(int i=0;i<dim;i++) tree[i]=0;
		}
		void pointUpdate(int index, t val){
			index++;
			while(index<dim){
				tree[index]=op(tree[index],val);
				index+=index&(-index);			
			}
		}
		t prefixQuery(int index){
			t sol=0;
			while(index>0){
				sol=op(sol,tree[index]);
				index-=index&(-index);    
			}
			return sol;
		}
};
