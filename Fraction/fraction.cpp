#include<bits/stdc++.h>
using namespace std;
struct fraction{
	typedef long long T;
	T num, den;
	fraction(): num(0), den(1) {}
	fraction(T n, T d): num(n), den(d) {} 
	void reduce(){
		T gcd=__gcd(num,den);
		num/=gcd, den/=gcd;
	}
	bool operator<(const fraction &other)const{
		T lcm=(den*other.den)/__gcd(den,other.den);
		return other.num*(lcm/other.den)>num*(lcm/den);
	}
	bool operator>(const fraction &other)const{
		T lcm=(den*other.den)/__gcd(den,other.den);
		return other.num*(lcm/other.den)<num*(lcm/den);
	}
	bool operator==(const fraction &other)const{
		return (!(*this<other) && !(*this>other));
	}
	fraction operator+(const fraction &other)const{
		T lcm=(den*other.den)/__gcd(den,other.den);
		fraction res={num*(lcm/den)+other.num*(lcm/other.den),lcm};
		res.reduce();
		return res;
	}
	fraction operator-(const fraction &other)const{
		T lcm=(den*other.den)/__gcd(den,other.den);
		fraction res={num*(lcm/den)-other.num*(lcm/other.den),lcm};
		res.reduce();
		return res;
	}
	fraction operator*(const fraction &other)const{
		fraction a=*this, b=other;
		a.reduce(); b.reduce();
		T g1=__gcd(a.num,b.den), g2=__gcd(a.den,b.num);
		a.num/=g1; a.den/=g2; b.num/=g2; b.den/=g1;
		return {a.num*b.num,a.den*b.den};
	}
	fraction operator/(const fraction &other)const{
		return (*this)*(fraction){other.den,other.num};
	}
	fraction& operator+=(const fraction &other){
		*this=*this+other;
		return *this;
	}
	fraction& operator-=(const fraction &other){
		*this=*this-other;
		return *this;
	}
	fraction& operator*=(const fraction &other){
		*this=*this*other;
		return *this;
	}
	fraction& operator/=(const fraction &other){
		*this=*this/other;
		return *this;
	}
	
};
ostream& operator<<(ostream& os, fraction& f){
	os<<'['<<f.num<<','<<f.den<<"]\n";
	return os;
}
//Make sure that the type of a and b is compatible with T
istream& operator>>(istream& is, fraction& f){
	long long a, b;
	cin>>a>>b;
	f=(b==0)?(fraction){a,1}:(fraction){a,b};
	return is;
}
