#pragma GCC optimize ("O3")
#include<bits/stdc++.h>
using namespace std;
namespace io{
	//******************************//
	// Call fast() to use fastI/O   //
	// Call use_file() to use files //
	//******************************//
	#ifdef _WIN32
	inline int getchar_unlocked() { return getchar(); }
	inline void putchar_unlocked(int v) { putchar(v); }
	#endif
	using namespace std;
	void use_file(){
		freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
	}
	void use_input_file(){ freopen("input.txt", "r", stdin); }
	void use_output_file(){ freopen("output.txt", "w", stdout); }
	bool __fast=false;
	void fast(bool state=true){	__fast=state;	}
	template<class t> void slow_read(t &x){ cin>>x;	}
	void fast_read(long long int &x){
		char ch=0; bool flag=false; x=0;
		while(ch!='-' && (ch<'0' || ch>'9')) ch=getchar_unlocked();
		if(ch=='-'){ ch=getchar_unlocked(); flag=true;}
		for(;ch>='0' && ch<='9';ch=getchar_unlocked())	x=x*10+ch-'0';
		x=(flag)?-x:x;
	}
	void fast_read(int &x){ long long y; fast_read(y); x=y; }	
	void fast_read(double &x){ cin>>x; }
	void fast_read(string &s){ cin>>s; }
	void fast_read(char &ch){ ch=getchar_unlocked(); }
	void fast_read(bool &b){ cin>>b; }
	template<class t> void read(t &x){
		if(__fast) fast_read(x);
		else	slow_read(x);
	}
	template<typename Arg,typename ...Args>
	void read(Arg& arg,Args&... args){read(arg);read(args...);}
	template<class t> void slow_print(t &x){ cout<<x; }
	void fast_print(long long int x){
		char buf[29]; int p=0;
		if(x<0){ putchar_unlocked('-'); x=-x;}
		for(;x;x/=10) buf[p++]=x%10;
		while(p--) putchar_unlocked(buf[p]+'0');
	}
	void fast_print(int x){
		char buf[14]; int p=0;
		if(x<0){ putchar_unlocked('-'); x=-x;}
		for(;x;x/=10) buf[p++]=x%10;
		while(p--) putchar_unlocked(buf[p]+'0');
	}
	void fast_print(double x){ cout<<x; }
	void fast_print(string s){ cout<<s;	}
	void fast_print(char ch){ putchar_unlocked(ch); }
	void fast_print(bool b) { cout<<b;}
 	template<class t> void print(t x){
		if(__fast) fast_print(x);
		else slow_print(x);
	}
	template<typename Arg,typename ...Args>
	void print(const Arg& arg,const Args&... args){print(arg);print(args...);}
}
using namespace io;
