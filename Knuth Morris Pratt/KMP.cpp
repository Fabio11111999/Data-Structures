#include<bits/stdc++.h>
using namespace std;
int const MAXN=3000000;
int lps[MAXN];
void LPS(int m, string pat);
int KMP(string pat, string text){
	int m=pat.length(), n=text.length();
	LPS(m, pat);
	int i=0, j=0, sol=0;
	while(i<n){
		if(pat[j]==text[i])		i++, j++;
		if(j==m){
			cout<<"PATTERN FOUND AT: "<<i-j<<"\n";
			sol++;
			j=lps[j-1];
		}
		else if(i<n && pat[j]!=text[i]){
			if(j!=0) j=lps[j-1];
			else	 i++;
		}
	}
	return sol;
}
void LPS(int m, string pat){
	int len=0, i=1;
	lps[0]=0;
	while(i<m){
		if(pat[i]==pat[len])	lps[i++]=++len;
		else{
			if(len!=0)	len=lps[len-1];
			else		lps[i++]=0;
		}
	}
}
