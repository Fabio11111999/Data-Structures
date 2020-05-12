#pragma GCC optimize ("O3")
#include<bits/stdc++.h>
template <class t, bool conf(t,t)> class binaryHeap{
public:
    vector<pair<t,int>> tree;
    vector<int> mappa, free_key;
    int next_key=0, last=0;
    binaryHeap(int maxdim){tree.resize(maxdim);mappa.resize(maxdim);}
    binaryHeap(){tree.resize(1e6);mappa.resize(1e6);}
    inline int parent(int i){return (i-1)/2;}
    inline int left(int i){return i*2+1;}
    inline int right(int i){return i*2+2;}
    inline int size(){return last;}
    inline t top(){return tree[0].first;}
    inline void swap(int p1, int p2){
        mappa[tree[p1].second]=p2;
        mappa[tree[p2].second]=p1;
        auto current=tree[p1];
        tree[p1]=tree[p2];
        tree[p2]=current;
    }
    inline int push(t val){ // return the key of the element
        int key;
        if(!free_key.empty()){
            key=free_key.back();
            free_key.pop_back();
        }
        else key=next_key++;
        int i=last++;
        tree[i]={val,key};
        mappa[key]=i;
        while(i>0 && conf(tree[i].first, tree[parent(i)].first)){
            swap(i,parent(i));
            i=parent(i);
        }
        return key;
    }
    inline void pop(){
        if(last==0) return;
        last--;
        free_key.push_back(tree[0].second);
        swap(0,last);
        balance(0);
    }
    inline void balance(int pos){
        int best=pos;
        if(left(pos)<last && conf(tree[left(pos)].first,tree[pos].first)) best=left(pos);
        if(right(pos)<last && conf(tree[right(pos)].first,tree[best].first)) best=right(pos);
        if(best!=pos){
            swap(pos,best);
            balance(best);
        }      
    }
    inline void erase(int key){
        int pos=mappa[key];
        last--;
        free_key.push_back(tree[pos].second);
        swap(pos,last);
        balance(pos);
    }
    inline void modify(int key, t val){
    	int i=mappa[key];
    	tree[i].first=val;
    	 while(i>0 && conf(tree[i].first, tree[parent(i)].first)){
            swap(i,parent(i));
            i=parent(i);
        }
    	balance(i);
	}
};
inline bool max(int a, int b){
    return (a>b)?true:false;
}
binaryHeap<int,max> bh;
