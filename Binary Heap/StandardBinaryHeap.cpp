#include<bits/stdc++.h>
using namespace std;
int const MAXN=100000;
template < class t> class binaryHeap{
	public:
		t tree[MAXN];
		int dim=0;
		t top(){
			if(dim==0) return -1;
			return tree[0];
		}
		void pop(){
			if(dim==1){
				dim=0;
				return;
			} 
			t last=tree[dim-1];
			dim--;
			tree[0]=last;
			balance(0);
		}
		void push(t val){
			int index=dim;
			tree[index]=val;
			dim++;
			while(index!=0 && tree[(index-1)/2]>tree[index]){
				swap((index-1)/2,index);
				index=(index-1)/2;
			}
			return;
		}
		void swap(int left, int right){
			t tmp=tree[left];
			tree[left]=tree[right];
			tree[right]=tmp;
		}
		void balance(int index){
			int smallest=index, left=index*2+1, 		right=index*2+2;
			if(left<dim && tree[left]<tree[smallest]) 	smallest=left;
			if(right<dim && tree[right]<tree[smallest]) smallest=right;
			if(smallest!=index)
			{
				swap(index, smallest);
				balance(smallest);
			}
		}
};
