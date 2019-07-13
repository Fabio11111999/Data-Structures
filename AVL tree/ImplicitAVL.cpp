#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
int const MAXN=11000000; 
template<typename t>
struct node{			
	int height, size;
	node *left, *right;
	t val;
	inline void calc_height(){
		if(left && right) height=max(left->height,right->height)+1;
		if(left && !right) height=left->height+1;
		if(!left && right) height=right->height+1;
		if(!left && !right) height=1; 
	}
	inline int balance(){
		if(left && right) return right->height-left->height;
		if(left && !right) return -1*left->height;
		if(!left && right) return right->height;
		if(!left && !right) return 0;
	}
	inline int calc_size(){
		if(left && right) size=left->size+right->size+1;
		if(left && !right) size=left->size+1;
		if(!left && right) size=right->size+1;
		if(!left && !right) size=1;
	}
};
node<int> disp[MAXN]; 
int ind=0;
template<class t> class ImplicitAVL{
	public:
		node<t> *root=nullptr;
		int height(){return root->height;}
		int dim=0;
		inline void insert(int position, t v) {
			if(position>dim) return;		//Wrong Position
			dim++;
			root=insert(position,v,root);
		}
		node<t> *insert(int position, t new_val, node<t> *r){		//Insert new_val in Position : position of r
			if(r==nullptr){		//Creating the new Node
				r=&disp[ind++];	
				r->height=1;
				r->size=1;
				r->val=new_val;
				r->left=r->right=nullptr;
				return r;
			}
			int left_size=0;
			if(r->left) left_size=r->left->size;
			if(position==left_size){		//This node is the Right Position
				int old=r->val;
				r->val=new_val;
				r->right=insert_min(old,r->right);		//Inserting the old value in the Next Node
				return rebalance(r);
			}
			if(position<left_size) r->left=insert(position,new_val,r->left);		//the Correct position is in the left subtree
			else r->right=insert(position-left_size-1,new_val,r->right);			//the Correct position is in the right subtree
			return rebalance(r);													//Always rebalance the tree!!!
		}
		inline node<t> *insert_min(t v, node<t> *r){		//Insert a new node like the minimum of this subtree					
			if(r==nullptr){		//New Node							
				r=&disp[ind++];
				r->height=1;
				r->size=1;
				r->val=v;
				r->left=r->right=nullptr;
				return r;
			}
			r->left=insert_min(v,r->left);		//Go to left as much as you can
			return rebalance(r);				//Always rebalance the tree!!!
		}
		inline void erase(int position) {
			if(position>dim)	return;
			root=erase(position,root);
			dim--;
		}
		inline node<t> *erase(int position, node<t> *r){		//Erase the node in Position: position from r
			int left_size=0;
			if(r->left) left_size=r->left->size;
			if(position==left_size){							//Correct position
				if(r->right && r->left){						//Node has both children 
					r->val=findMin(r->right);					//Swapping this node with the next one
					r->right=eraseMin(r->right);				//Erasing the next one
				}
				else{
					node<t> *tmp=r;
					if(!r->left && r->right) r=r->right;		//Only right Child
					else if(r->left && !r->right) r=r->left;	//Only left Child
					else{										//Leaf
						r=nullptr;
						return r;
					}
				}
			}
			else if(position<left_size) r->left=erase(position,r->left);	//The correct position is in the left subtree
			else r->right=erase(position-left_size-1,r->right);				//The correct position is in the righr subtree
			return rebalance(r);											//Always rebalance the tree!!!
		}
		inline t find(int position) {return find(position,root);}
		inline t find(int position, node<t> *r){
			int left_size=0;
			if(r->left) left_size=r->left->size;
			if(position==left_size) return r->val;					//Correct position
			if(position<left_size) return find(position,r->left);	//Left subtree
			else return find(position-left_size-1,r->right);		//Right subtree
		}
		inline t findMin(node<t> *r){
			if(!r->left) return r->val;								//Go to the left as much as you can
			return findMin(r->left);
		}
		inline node<t> *eraseMin(node<t> *r){
			if(!r->left && !r->right)	return nullptr;		//Leaf
			if(!r->left){									//Only right child
				r=r->right;
				return rebalance(r);						//Always rebalance the tree!!!
			}
			r->left=eraseMin(r->left);						//Go to the left as much as you can
			return rebalance(r);							//Always rebalance the tree!!!
		}
		inline node<t> *leftRotation(node<t> *r){
			node<t> *tmp=r->right;
			r->right=tmp->left;		/*						R				     B				*/
			tmp->left=r;			/*				      /  \					/ \				*/
			tmp->calc_height();		/*				     A    B	   ------>     R   D			*/
			tmp->calc_size();		/*				         / \			  / \				*/
			r->calc_height();		/*						C	D			 A   C				*/
			r->calc_size();			
			return tmp;
		}
		inline node<t> *rightRotation(node<t> *r){
			node<t> *tmp=r->left;	
			r->left=tmp->right;		/*						R				     A				*/
			tmp->right=r;			/*				      /  \					/ \				*/
			tmp->calc_height();		/*				     A    D	   ------>     B   R			*/
			tmp->calc_size();		/*				    / \			              / \			*/
			r->calc_height();		/*				   B   C			 A       C   D			*/
			r->calc_size();
			return tmp;
		}
		inline node<t> *rebalance(node<t> *r){
			if(r==nullptr) return r;
			r->calc_height();	
			r->calc_size();															
			int current=r->balance();
			if(current>1){
				if(r->right->balance()<0) r->right=rightRotation(r->right);
				r=leftRotation(r);
			}
			else if(current<-1){
				if(r->left->balance()>0) r->left=leftRotation(r->left);
				r=rightRotation(r);
			}
			r->calc_height();
			r->calc_size();
			return r;
		}
		inline void printNode(node<t> *r){
			if(r==nullptr) return;
			cout<<"     [ Value: "<<r->val<<" ";
			cout<<"Height: "<<r->height<<" ";
			cout<<"Size: "<<r->size<<" ";
			if(r->left) cout<<"Left Child: "<<r->left->val<<" ";
			if(r->right) cout<<"Right Child: "<<r->right->val<<" ";
			cout<<"]\n";
		}
		void printTree(){
			if(root) {cout<<"Tree:\n";printTree(root);}
			else cout<<"Tree is empty\n";
		}
		void printTree(node<t> *r){
			printNode(r);
			if(r->left) printTree(r->left);
			if(r->right) printTree(r->right);
		}
		void inOrder(){
			if(root) {cout<<"Tree:\n";inOrder(root);cout<<"\n";}
			else cout<<"Tree is empty\n";
		}
		void inOrder(node<t> *r){
			if(r->left) inOrder(r->left);
			cout<<r->val<<" ";
			if(r->right) inOrder(r->right);
		}
		inline void build(int start, int end) {//Build the tree with values from 0 to N-1 O(N)
		    dim+=end-start+1;
		    root=build(start,end,root);
		}		
		inline node<t> *build(int start, int end, node<t> *r){					//Binary search of the values
			if(start>end) return nullptr;
			int mid=(start+end)/2;
			r=&disp[ind++];
			r->val=mid;
			r->left=build(start,mid-1,r->left);
			r->right=build(mid+1,end,r->right);
			r->calc_height();
			r->calc_size();
			return r;
		}
};
