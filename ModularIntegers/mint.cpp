#include <bits/stdc++.h>

using namespace std;

template <int MOD = 1e9 + 7> struct mint {
	int value;

	mint(long long v = 0) {
		value = v % MOD; 
		if (value < 0) {
			value += MOD;
		}
	}

	mint& operator+=(mint const& b) {
		value += b.value; 
		if (value >= MOD) {
			value -= MOD;
		}
		return *this;
	}
	mint& operator-=(mint const& b) {
		value -= b.value; 
		if (value < 0) {
			value += MOD;
		}
		return *this;
	}
	mint& operator*=(mint const& b) {
		value = (long long)value * b.value % MOD;
		return *this;
	}
	friend mint mexp(mint a, long long e) {
		mint res = 1; 
		while (e) { 
			if (e&1) { 
				res *= a;
			}
			a *= a; 
			e >>= 1;
		}
		return res;
	}
	friend mint inverse(mint a) { 
		return mexp(a, MOD - 2); 
	}

	mint& operator/=(mint const& b) {
		return *this *= inverse(b);
	}
	friend mint operator+(mint a, mint const b) { 
		return a += b;
	}
	friend mint operator-(mint a, mint const b) { 
		return a -= b;
	}
	friend mint operator-(mint const a) { 
		return 0 - a;
	}
	friend mint operator*(mint a, mint const b) { 
		return a *= b;
	}
	friend mint operator/(mint a, mint const b) { 
		return a /= b;
	}
	friend std::ostream& operator<<(std::ostream& os, mint const& a) {
		return os << a.value;
	}
	friend bool operator==(mint const& a, mint const& b) {
		return a.value == b.value;
	}
	friend bool operator!=(mint const& a, mint const& b) {
		return a.value != b.value;
	}
};


const int mod = 1e9+7;

vector<mint<mod>> __fact;
void fill_fact(int up_to) {
	__fact.resize(up_to + 1);
	__fact[0] = 1;
	for(int i = 1; i <= up_to; i++) {
		__fact[i] = __fact[i - 1] * i;
	}
}

int bin(int n, int k) {
	if (max(n, k) > (int)__fact.size()) {
		fill_fact(max(n, k));
	}
	return (__fact[n] * inverse(__fact[k] * __fact[n - k])).value;
}
