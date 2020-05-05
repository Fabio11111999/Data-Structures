#include<bits/stdc++.h>
using namespace std;
template<class T> class RB_LIS{
	public:
		void add(T x){
			if(lowest.empty() || lowest.back()<x){
				lowest.push_back(x);
				moves.push_back({-1,x});
			}
			else{
				int i=lower_bound(lowest.begin(),lowest.end(),x)-lowest.begin();
				moves.push_back({i,lowest[i]});
				lowest[moves.back().first]=x;
			}
		}
		int size(){ return (int) lowest.size(); } 
		void rollback(){
			if(moves.back().first==-1)	lowest.pop_back();
			else lowest[moves.back().first]=moves.back().second;
			moves.pop_back();
		}
	private:
		vector<T> lowest;
		vector<pair<int,T>> moves;
};
