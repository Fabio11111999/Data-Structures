template < class t > class AVL{
	public:
		struct node{
			node(){height=0;left=right=nullptr;}
			node(t v, int h, node *l, node *r){val=v; height=h;left=l; right=r;} 
			t val;
			int height, _size=0;
			node *left, *right;
			void calc_height(){
				if(!right && !left) height=1;
				else if(!right && left) height=left->height+1;
				else if(right && !left) height=right->height+1;
				else height=max(left->height,right->height)+1;
			}
			int balance(){
				if(!right && !left) return 0;
				else if(!right && left) return left->height*(-1);
				else if(right && !left) return right->height;
				return right->height-left->height;
			}
		};
		node *root=nullptr;
		bool empty(){if(root) return false; return true;}
		void insert(t v){root=insert(v,root);}
		node *insert(t v,node *r){
			if(r==nullptr) return new node(v,1,nullptr,nullptr);
			if(v>r->val)  r->right=insert(v,r->right);
			else	  r->left=insert(v,r->left);
			return rebalance(r);
		}
		bool find(t v){return(find(v,root)==nullptr)?false:true;}
		node *find(t v,node *r){
			if(r==nullptr) return r;
			if(v==r->val) return r;
			if(v>r->val)  return (r->right)?find(v,r->right):nullptr;
			if(v<r->val)  return (r->left)?find(v,r->left):nullptr;
			return nullptr;
		}
		void erase(t v){root=erase(v,root);}
		node *erase(t v, node *r){
			if(r==nullptr) return r;
			if(v>r->val) r->right=erase(v,r->right);
			else if(v<r->val) r->left=erase(v,r->left);	
			else{
				if(r->right && r->left){
					node *tmp=findMin(r->right);
					r->val=tmp->val;
					r->right=erase(r->val,r->right);
				}
				else{
					node *tmp=r;
					if(r->right && !r->left) r=r->right;
					else if(!r->right && r->left) r=r->left;
					else r=nullptr;
					delete tmp;
				}
			}
			if(r==nullptr) return r;
				return rebalance(r);
		}
		void eraseAll(t v){
			while(find(v)) root=erase(v, root);
		}
		t findMin(){return findMin(root)->val;}
		node *findMin(node *r){
			if(r==nullptr) return r;
			if(r->left) return findMin(r->left);
			return r;
		}
		t findMax(){return findMax(root)->val;}
		node *findMax(node *r){
			if(r==nullptr) return r;
			if(r->right) return findMax(r->right);
			return r;
		}
		node *leftRotation(node *r){
			node *tmp=r->right;
			r->right=tmp->left;
			tmp->left=r;
			tmp->calc_height();
			r->calc_height();
			return tmp;
		}
		node *rightRotation(node *r){
			node *tmp=r->left;
			r->left=tmp->right;
			tmp->right=r;
			tmp->calc_height();
			r->calc_height();
			return tmp;
		}
		node *rebalance(node *r){
			if(r==nullptr) return r;
			r->calc_height();
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
			return r;
		}
		void clear(){clear(root); root=nullptr;}
		void clear(node *r){
			if(r==nullptr) return;
			if(r->left){
				clear(r->left);
				r->left=nullptr;
			}
			if(r->right){
				clear(r->right);
				r->right=nullptr;			
			}
			delete r;
		}
		void printNode(node *r){
			if(r==nullptr) return;
			cout<<"     [ Value: "<<r->val<<" ";
			cout<<"Height: "<<r->height<<" ";
			if(r->left) cout<<"Left Child: "<<r->left->val<<" ";
			if(r->right) cout<<"Right Child: "<<r->right->val<<" ";
			cout<<"]\n";
		}
		void printTree(){
			if(root) {cout<<"Tree:\n";printTree(root);}
			else cout<<"Tree is empty\n";
		}
		void printTree(node *r){
			printNode(r);
			if(r->left) printTree(r->left);
			if(r->right) printTree(r->right);
		}
};
