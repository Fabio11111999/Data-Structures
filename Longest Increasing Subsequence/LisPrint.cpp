#include <bits/stdc++.h>

using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> v(n), lis, pos, prec(n);
	for(int i = 0; i < n; i++) {
		cin >> v[i];
		if(lis.empty()) {
			lis.push_back(v[i]);
			pos.push_back(0);
			prec[0] = -1;
		}
		else if(lis.back() < v[i]) {
			prec[i] = pos.back();
			lis.push_back(v[i]);
			pos.push_back(i);
		}
		else {
			int offset = lower_bound(lis.begin(), lis.end(), v[i]) - lis.begin();
			prec[i] = (offset != 0) ? pos[offset - 1] : -1;
			lis[offset] = v[i];
			pos[offset] = i; 
		}
	}
	cout << static_cast<int>(lis.size()) << endl;
	vector<int> ans;
	int i = pos.back();
	while(i != -1) {
		ans.push_back(v[i]);
		i = prec[i];
	}
	for(int i = static_cast<int>(ans.size()) - 1; i >= 0; i--){
		cout << ans[i] << " ";
	}
	cout << endl;
	return 0;
}
