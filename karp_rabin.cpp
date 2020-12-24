#include <bits/stdc++.h>

using namespace std;

template<typename function>
vector<int> karp_rabin(const string &text, const string &pattern, int alph_size, int n_primes, function char_map) {
	unsigned int n = text.length(), m = pattern.length();
	if(n < m)
		return vector<int>(0);
	const int primes [] = {
		1000000007, 
		1000000009,
		1000000021,
		1000000033,
		1000000087,
		1000000093,
		1000000097,
		1000000103,
		1000000123,
		1000000181
	};
	n_primes = max(1, min(n_primes, 10));
	vector<long long> diff(n_primes, 1LL), text_hash(n_primes, 0LL), pattern_hash(n_primes, 0LL);
	for(unsigned int i = 0; i < m - 1; i++)
		for(unsigned int j = 0; j < n_primes; j++)
			diff[j] = (diff[j] * alph_size) % primes[j];
	for(unsigned int i = 0; i < m; i++)
		for(unsigned int j = 0; j < n_primes; j++) {
			text_hash[j] = (text_hash[j] * alph_size + char_map(text[i])) % primes[j];
			pattern_hash[j] = (pattern_hash[j] * alph_size + char_map(pattern[i])) % primes[j];
		}
	vector<int> ans;
	bool correct = true;
	for(unsigned int j = 0; j < n_primes && correct; j++)
		if(text_hash[j] != pattern_hash[j])
			correct = false;
	if(correct)
		ans.push_back(0);
	for(unsigned int i = m; i < n; i++) {
		correct = true;
		for(unsigned int j = 0; j < n_primes; j++) {
			text_hash[j] = ((text_hash[j] - (char_map(text[i - m]) * diff[j])) * alph_size + char_map(text[i])) % primes[j];
			while(text_hash[j] < 0LL)
				text_hash[j] += primes[j];
			if(text_hash[j] != pattern_hash[j])
				correct = false;
		}
		if(correct)
			ans.push_back(i - m + 1);
	}
	return ans;
}
// Example of char_map functin
int my_map(const char &c) {
	return c - '0';
}
