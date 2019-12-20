#include<bits/stdc++.h>
using namespace std;
struct fraction{
	long long num, den;
	void reduce(){
		long long gcd=__gcd(num,den);
		num/=gcd;
		den/=gcd;
	}
	bool operator<(const fraction &other)const{
		long long mcm=(den*other.den)/__gcd(den,other.den);
		return other.num*(mcm/other.den)>num*(mcm/den);
	}
	bool operator>(const fraction &other)const{
		long long mcm=(den*other.den)/__gcd(den,other.den);
		return other.num*(mcm/other.den)<num*(mcm/den);
	}
	bool operator==(const fraction &other)const{
		long long mcm=(den*other.den)/__gcd(den,other.den);
		return num*(mcm/den)==other.num*(mcm/other.den);
	}
	fraction operator+(const fraction &other)const{
		long long mcm=(den*other.den)/__gcd(den,other.den);
		fraction res={num*(mcm/den)+other.num*(mcm/other.den),mcm};
		res.reduce();
		return res;
	}
	fraction operator-(const fraction &other)const{
		long long mcm=(den*other.den)/__gcd(den,other.den);
		fraction res={num*(mcm/den)-other.num*(mcm/other.den),mcm};
		res.reduce();
		return res;
	}
	fraction operator*(const fraction &other)const{
		fraction a=*this, b=other;
		a.reduce(); b.reduce();
		long long g1=__gcd(a.num,b.den), g2=__gcd(a.den,b.num);
		a.num/=g1; a.den/=g2; b.num/=g2; b.den/=g1;
		return {a.num*b.num,a.den*b.den};
	}
	fraction operator/(const fraction &other)const{
		return (*this)*(fraction){other.den,other.num};
	}
	void operator+=(const fraction &other){
		*this=*this+other;
	}
	void operator-=(const fraction &other){
		*this=*this-other;
	}
	void operator*=(const fraction &other){
		*this=*this*other;
	}
	void operator/=(const fraction &other){
		*this=*this/other;
	}
	
};
ostream& operator<<(ostream& os, fraction& f){
	os<<'['<<f.num<<','<<f.den<<"]\n";
	return os;
}
istream& operator>>(istream& is, fraction& f){
	long long a, b;
	cin>>a>>b;
	f=(b==0)?(fraction){a,1}:(fraction){a,b};
	return is;
}
int main(){
	int n;
	cin>>n;
	vector<fraction> v(n);
	for(int i=0;i<n;i++)
		cin>>v[i];
	sort(v.begin(),v.end());
	for(int i=0;i<n;i++)
		cout<<v[i];
}
