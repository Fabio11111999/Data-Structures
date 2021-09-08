template<class T, T merge(T, T)> class SegmentTree {
	
	unsigned int sz;
	vector<T> segtree;
	vector<int> pos_leaves;
 
	void build_default(unsigned int l, unsigned int r, unsigned int pos, T def) {
		if (l == r) {
			segtree[pos] = def;
			pos_leaves[l] = pos;
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
			pos_leaves[l] = pos;
		} else {
			unsigned int mid = (l + r) / 2;
			build(l, mid, pos * 2 + 1, v);
			build(mid + 1, r, pos * 2 + 2, v);
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
		pos_leaves.resize(sz);
		build_default(0, sz - 1, 0, def);
	}
 
	SegmentTree(vector<T> &v) : sz(v.size()) {
		assert(v.size() > 0);
		segtree.resize(4 * sz);
		pos_leaves.resize(sz);
		build(0, sz - 1, 0, v);
	}
 
	template<typename IterT> SegmentTree(IterT begin, IterT end) {
		vector<T> elements(begin, end);
		sz = elements.size();
		assert(sz > 0);
		segtree.resize(4 * sz);
		pos_leaves.resize(sz);
		build(0, sz - 1, 0, elements);
	}
	
	SegmentTree(const SegmentTree &other) : sz(other.sz) {
		segtree = other.segtree;
		pos_leaves = other.pos_leaves;
		sz = other.sz;
	}
 
	SegmentTree& operator=(const SegmentTree &other) {
		if (this != &other) {
			SegmentTree tmp(other);
			swap(sz, tmp.sz);
			swap(segtree, tmp.segtree);
			swap(pos_leaves, tmp.pos_leaves);
		}
		return *this;
	}
 
	bool operator==(const SegmentTree &other) const {
		if (sz != other.sz) {
			return false;
		}
		for (int pos : pos_leaves) {
			if (segtree[pos] != other.segtree[pos]) {
				return false;
			}
		}
		return true;
	}	
 
	~SegmentTree() {}
 
	void update(unsigned int i, const T &val) {
		assert(i < sz);
		segtree[pos_leaves[i]] = val;
		if (pos_leaves[i] > 0) {
			int pos = (pos_leaves[i] - 1) / 2;
			while (pos != 0) {
				segtree[pos] = merge(segtree[pos * 2 + 1], segtree[pos * 2 + 2]);
				pos = (pos - 1) / 2;
			}	
			segtree[0] = merge(segtree[1], segtree[2]);
		}
	}
 
	T query(unsigned int start, unsigned int end) const {
		assert(start <= end);
		assert(end < sz);
		return query(0, sz - 1, 0, start, end);
	}
 
	unsigned int size() const {
		return sz;
	}
	
	T operator[](unsigned int index) const {
		assert(index < sz);
		return segtree[pos_leaves[index]];
	}
 
	void print() const {
		cout << "Leaves = [";
		for (unsigned int i = 0; i < pos_leaves.size(); i++) {
			cout << segtree[pos_leaves[i]] << ",]"[i == sz - 1];
		}
		cout << endl;
		print(0, sz - 1, 0);
	}
};
