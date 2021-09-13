#include <bits/stdc++.h>

using namespace std;

template<class T> class AVL {
public:

	AVL() {
		disp.resize(100000);
	}

	explicit AVL(int max_size) {
		disp.resize(max_size);
	}
	
	void insert(const T &val) {
		root = insert(root, val);
	}

	bool find(const T &val) const {
		return (find(root, val) > 0);
	}

	int count(const T &val) const {
		return find(root, val);
	}

	T min() const {
		node *min_node = find_min(root);
		assert(min_node);
		return min_node->value;
	}

	T max() const {
		node *max_node = find_max(root);
		assert(max_node);
		return max_node->value;
	}

	void erase(const T &val) {
		root = erase(root, val);
	}

	T get(int pos) const {
		assert(root && pos < size());
		return get(root, pos);
	}

	T operator[](int index) const {
		assert(index < size());
		return get(index);
	}

	int size() const {
		if (!root) {
			return 0;
		} else {
			return root->subtree_cnt;
		}
	}

	bool empty() const {
		return size() == 0;
	}

	void print() const {
		print(root);
	}

	~AVL() {}

	bool operator==(const AVL &other) const {
		if(size() != other.size()) {
			return false;
		} else {
			for (int i = 0; i < size(); i++) {
				if (get(i) != other.get(i)) {
					return false;
				}
			}
			return true;
		}
	}

private: 

	struct node {

		T value;
		int height, cnt, subtree_cnt;
		node *left, *right;
		node() : height(1), cnt(1), subtree_cnt(1), left(nullptr), right(nullptr) {}
		node(const T &v, int times) : value(v), height(1), cnt(times), subtree_cnt(times), left(nullptr), right(nullptr) {}

		void set(const T &v, int h = 1, int times = 1, int subtree = 1, node *l = nullptr, node *r = nullptr) {
			value = v;
			height = h;
			cnt = times;
			subtree_cnt = subtree;
			left = l;
			right = r;
		}

		void calc_height() {
			int l_height = left ? left->height : 0;
			int r_height = right ? right->height : 0;
			height = 1 + (l_height > r_height ? l_height : r_height);
		}	 

		void calc_subtree() {
			int l_cnt = left ? left->subtree_cnt : 0;
			int r_cnt = right ? right->subtree_cnt : 0;
			subtree_cnt = cnt + l_cnt + r_cnt;
		}

		int balance() {
			int l_height = left ? left->height : 0;
			int r_height = right ? right->height : 0;
			return r_height - l_height;
		}

		void update() {
			calc_height();
			calc_subtree();
		}
	};

	node *root = nullptr;
	vector<node> disp;
	int next_disp = 0;

	void chk(node *r) {
		int sz = r->subtree_cnt;
		int h = r->height;
		if (r->left) {
			chk(r->left);
		}
		if (r->right) {
			chk(r->right);
		}
		r->update();
		assert(sz == r->subtree_cnt);
		assert(h == r->height);
	}

	node* left_rotation(node *r) {
		node *tmp = r->right;
		r->right = tmp->left;
		tmp->left = r;
		r->update();
		tmp->update();
		return tmp;
	}

	node* right_rotation(node *r) {
		node *tmp = r->left;
		r->left = tmp->right;
		tmp->right = r;
		r->update();
		tmp->update();
		return tmp;
	}

	node* rebalance(node *r) {
		if (!r) {
			return r;
		} else {
			r->update();
			int balance = r->balance();
			if (balance > 1) {
				if (r->right->balance() < 0) {
					r->right = right_rotation(r->right);
				}
				r = left_rotation(r);
			} else if (balance < -1) {
				if (r->left->balance() > 0) {
					r->left = left_rotation(r->left);
				}
				r = right_rotation(r);
			}
			r->update();
		}
		return r;
	}

	node* insert(node *r, const T &val) {
		if (!r) {
			disp[next_disp].set(val); 
			return r = &disp[next_disp++];
		} else if (val == r->value) {
			r->cnt++;
			r->subtree_cnt++;
			return r;
		} else if (val < r->value) {
			r->left = insert(r->left, val);
		} else {
			r->right = insert(r->right, val);
		}
		return rebalance(r);
	}

	int find(node *r, const T &val) const {
		if (!r) {
			return 0;
		} else if (val == r->value) {
			return r->cnt;
		} else if (val < r->value) {
			return find(r->left, val);
		} else {
			return find(r->right, val);
		}
	}

	node* find_min(node *r) const {
		if (!r) {
			return r;
		} else if (r->left) {
			return find_min(r->left);
		} else {
			return r;
		}
	}

	node* find_max(node *r) const {
		if (!r) {
			return r;
		} else if(r->right) {
			return find_max(r->right);
		} else { 
			return r;
		}
	}

	node* erase(node *r, const T &val) {
		if (!r) {
			return r;
		} else if (val < r->value) {
			r->left = erase(r->left, val);
		} else if (val > r->value) {
			r->right = erase(r->right, val);
		} else {
			if (r->cnt > 1) {
				r->cnt--;
				r->subtree_cnt--;
			} else {
				if (r->left && r->right) {
					node *tmp = find_min(r->right);
					r->value = tmp->value;
					r->cnt = tmp->cnt;
					r->right = erase(r->right, r->value);
				} else {
					if (r->left) {
						r = r->left;
					} else if (r->right) {
						r = r->right;
					} else {
						r = nullptr;
					}
				}
			}
		}
		return rebalance(r);
	}

	T get(node *r, int pos) const {
		int l_size = (r->left) ? r->left->subtree_cnt : 0;
		if (pos >= l_size && pos < l_size + r->cnt) {
			return r->value;
		} else if (pos < l_size) {
			return get(r->left, pos);
		} else {
			return get(r->right, pos - l_size - r->cnt);
		}
	}

	void print(node *r) const {
		if (r) {
			print(r->left);
			cout << '[' << r->value << ',' << r->cnt << "] ";
			print(r->right);
		}
	}
};
