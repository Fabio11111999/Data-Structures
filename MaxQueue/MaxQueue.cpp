#include <bits/stdc++.h>
using namespace std;
template <class t> class maxQueue
{
	public:
		deque<pair<t, int > > D;	//pair:: (t)value , (int) index;
		void push(t value, int index){
			while(!D.empty() && D.back().first<=value) D.pop_back();
			D.push_back(make_pair(value,index));
		}
		void pop(int index){
			while(!D.empty() && D.front().second<=index) D.pop_front();
		}
		t top(){
			return D.front().first;
		}
};
