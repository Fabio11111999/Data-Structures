#include<bits/stdc++.h>
using namespace std;
/* ************************* */
/* Point Update, Range Query */
/* ************************* */
template<class t, t merge(t, t)>class SegmentTree{
	public:
		vector<t> tree;
		int N;
		SegmentTree(int N, t defaultValue){
			tree.resize(N<<2);
			this->N=N;
			buildDefault(0,N-1,0,defaultValue);
		}
		SegmentTree(int N, vector<t> &v){
			tree.resize(N<<2);
			this->N=N;
			buildTree(0,N-1,0,v);
		}
		int left(int i){
			return i<<1|1;
		}
		int right(int i){
			return (1+i)<<1;
		}
		int mid(int start, int end){
			return (start+end)>>1;
		}
		void buildDefault(int start, int end, int pos, t defValue){
			if(start^end){
				buildDefault(start,mid(start,end),left(pos),defValue);
				buildDefault(mid(start,end)+1,end,right(pos),defValue);
			}
			tree[pos]=(start^end)?merge(tree[left(pos)],tree[right(pos)]):defValue;
		}
		void buildTree(int start, int end, int pos, vector<t> &v){
			if(start^end){
				buildTree(start,mid(start,end),left(pos),v);
				buildTree(mid(start,end)+1,end,right(pos),v);
			}
			tree[pos]=(start^end)?merge(tree[left(pos)],tree[right(pos)]):v[start];
		}
		void update(int index, t newValue){
			update(0,N-1,0,index,newValue);
		}
		void update(int start, int end, int pos, int index, t newValue){
			if(start==end) 
				tree[pos]=newValue;
			else{
				if(index<=mid(start,end))
					update(start,mid(start,end),left(pos),index,newValue);
				else update(1+mid(start,end),end,right(pos),index,newValue);
				tree[pos]=merge(tree[left(pos)],tree[right(pos)]);
			}
		}
		t query(int l, int r){
			return query(0,N-1,0,l,r);
		}
		t query(int start, int end, int pos, int l, int r){
			if(l<=start && r>=end)
				return tree[pos];
			if(r<=mid(start,end))
				return query(start,mid(start,end),left(pos),l,r);
			if(l>mid(start,end))
				return query(1+mid(start,end),end,right(pos),l,r);
			else return merge(query(start,mid(start,end),left(pos),l,r),query(1+mid(start,end),end,right(pos),l,r));
		}
		void printTree(){
			printTree(0,N-1,0);
		}
    //Write a print() function for the node to use printTree()
		/*void printTree(int start, int end, int pos){
			cout<<"Range: ["<<start<<"; "<<end<<"] value: ";
			tree[pos].print();
			cout<<endl;
			if(start^end){
				printTree(start,mid(start,end),left(pos));
				printTree(1+mid(start,end),end,right(pos));
			}
		}*/
};
int merge(int a, int b){
	return min(a,b);
}
int main(){
	SegmentTree<int,merge> st(10,1e9);
}
