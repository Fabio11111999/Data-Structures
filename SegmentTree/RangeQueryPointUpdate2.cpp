template<class T, T merge(T, T)> class SegmentTree {
	
	unsigned int sz;
	vector<T> segtree;
	vector<T> leaves;

	void build_default(unsigned int l, unsigned int r, unsigned int pos, T def) {
		if (l == r) {
			segtree[pos] = def;
		} else {
			unsigned int mid = (l + r) / 2;
			build_default(l, mid, pos * 2 + 1, def);
			build_default(mid + 1, r, pos * 2 + 2, def);
			segtree[pos] = merge(segtree[pos * 2 + 1], segtree[pos * 2 + 2]);
		}
	}

	void build(unsigned int l, int unsigned r, unsigned int pos, vector<T> &v) {
		if (l == r) {
			segtree[pos] = v[l];
		} else {
			unsigned int mid = (l + r) / 2;
			build(l, mid, pos * 2 + 1, v);
			build(mid + 1, r, pos * 2 + 2, v);
			segtree[pos] = merge(segtree[pos * 2 + 1], segtree[pos * 2 + 2]);
		}
	}
	
	void update(unsigned int l, unsigned int r, unsigned int pos, unsigned int i, const T &val) {
		if (l == r) {
			segtree[pos] = val;
			leaves[l] = val;
		} else {
			unsigned int mid = (l + r) / 2;
			if (i <= mid) {
				update(l, mid, pos * 2 + 1, i, val);
			} else {
				update(mid + 1, r, pos * 2 + 2, i, val);
			}
			segtree[pos] = merge(segtree[pos * 2 + 1], segtree[pos * 2 + 2]);
		}
	}

	T query(unsigned int l, unsigned int r, unsigned int pos, unsigned int start, unsigned int end) const {
		if (start <= l && end >= r) {
			return segtree[pos];
		} else {
			unsigned int mid = (l + r) / 2;
			if (end <= mid) {
				return query(l, mid, pos * 2 + 1, start, end);
			} else if (start > mid) {
				return query(mid + 1, r, pos * 2 + 2, start, end);
			} else {
				return merge(query(l, mid, pos * 2 + 1, start, end), query(mid + 1, r, pos * 2 + 2, start, end));
			}
		}	
	}

	// std::ostream &operator must be defined for type T
	void print(unsigned int l, unsigned int r, unsigned int pos) const {
		if (l != r) {
			unsigned int mid = (l + r) / 2;
			print(l, mid, pos * 2 + 1);
			print(mid + 1, r, pos * 2 + 2);
		}
		cout << "Segment = [" + to_string(l) + ", " + to_string(r) + "] ";
		cout << "Value = " << segtree[pos] << endl;
	}

public:

	SegmentTree(unsigned int n, const T &def) : sz(n) {
		assert(n > 0);
		segtree.resize(4 * sz);
		leaves.resize(sz);
		fill(leaves.begin(), leaves.end(), def);
		build_default(0, sz - 1, 0, def);
	}

	SegmentTree(vector<T> &v) : sz(v.size()), leaves(v) {
		assert(v.size() > 0);
		segtree.resize(4 * sz);
		build(0, sz - 1, 0, v);
	}

	template<typename IterT> SegmentTree(IterT begin, IterT end) {
		leaves = vector<T>(begin, end);
		sz = leaves.size();
		assert(sz > 0);
		segtree.resize(4 * sz);
		build(0, sz - 1, 0, leaves);
	}
	
	SegmentTree(const SegmentTree &other) : sz(other.sz) {
		segtree = other.segtree;
		leaves = other.leaves;
	}

	SegmentTree& operator=(const SegmentTree &other) {
		if (this != &other) {
			SegmentTree tmp(other);
			swap(sz, tmp.sz);
			swap(segtree, tmp.segtree);
			swap(leaves, tmp.leaves);
		}
		return *this;
	}

	bool operator==(const SegmentTree &other) const {
		return leaves == other.leaves;
	}	

	~SegmentTree() {}

	void update(unsigned int i, const T &val) {
		assert(i < sz);
		update(0, sz - 1, 0, i, val);
	}

	T query(unsigned int start, unsigned int end) const {
		assert(start <= end);
		assert(end < sz);
		return query(0, sz - 1, 0, start, end);
	}

	unsigned int size() {
		return sz;
	}
	
	T operator[](unsigned int index) const {
		assert(index < sz);
		return leaves[index];
	}

	void print() const {
		cout << "Leaves = [";
		for (unsigned int i = 0; i < leaves.size(); i++) {
			cout << leaves[i] << ",]"[i == leaves.size() - 1];
		}
		cout << endl;
		print(0, sz - 1, 0);
	}
};
