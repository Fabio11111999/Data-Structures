#include<bits/stdc++.h>
using namespace std;
template<typename T> T dijkstra(int N, int start, int end, vector<vector<pair<int,T>>> &graph){
	vector<T> dist(N,-1);
	priority_queue<pair<T,int>,vector<pair<T,int>>,greater<pair<int,T>>> pq;
	dist[start]=0;
	pq.push({0,start});
	while(!pq.empty()){
		auto [d,node]=pq.top();
		if(node==end)
			return d; 
		pq.pop();
		for(auto next:graph[node])
			if(dist[next.first]==-1 || dist[next.first]>d+next.second){
				dist[next.first]=d+next.second;
				pq.push({dist[next.first],next.first});
			}
	}
	return -1;
}
