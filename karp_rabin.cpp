#include<bits/stdc++.h>
using namespace std;
int count_karp_rabin(string text, string pattern, int alph_size, int prime, int offset='a'){
	if(text.length()<pattern.length())
		return 0;
	long long diff=1LL, current=0LL, hash=0LL;
	for(int i=0;i<(int)pattern.length()-1;i++)
		diff=(diff*alph_size)%prime;
	for(int i=0;i<(int)pattern.length();i++){
		current=(current*alph_size+text[i]-offset)%prime;
		hash=(hash*alph_size+pattern[i]-offset)%prime;
	}
	int ans=(current==hash);
	for(int i=(int)pattern.length();i<(int)text.length();i++){
		current=((current-((text[i-(int)pattern.length()]-offset)*diff))*alph_size+text[i]-offset)%prime;
		while(current<0) current+=prime;
		if(current==hash) 
			ans++;
	}
	return ans;
}
