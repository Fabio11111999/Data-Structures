#include<bits/stdc++.h>
using namespace std;
template<class T> class LIS{
	public:
		void add(T x){
			if(lowest.empty())	lowest.push_back(x);
			else if(lowest.back()<x) lowest.push_back(x);
			else *(lower_bound(lowest.begin(),lowest.end(),x))=x;
		}
		int size(){ return (int) lowest.size(); } 
	private:
		vector<T> lowest;
};
