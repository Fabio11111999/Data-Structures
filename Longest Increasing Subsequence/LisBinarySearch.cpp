//longest increasing subsequence O(NlogN)
#include<bits/stdc++.h>
using namespace std;
ifstream in("input.txt");
ofstream out("output.txt");
int const MAXN=10010;
int n, lis[MAXN], last=0;
int main(){
	in>>n;
	for(int i=0;i<n;i++){
		int val;
		in>>val;
		if(i==0)
			lis[0]=val;
		else{
			if(lis[0]>val)
				lis[0]=val;
			else if(lis[last]<val)
				lis[++last]=val;
			else{	
				int s=0, m, e=last, sol;
				while(s<=e){
					m=(s+e)/2;
					if(lis[m]>=val){
						sol=m;
						e=m-1;
					}else
						s=m+1;
				}
				lis[sol]=min(lis[sol],val);
			}
		}
	}
	out<<last+1;
}
