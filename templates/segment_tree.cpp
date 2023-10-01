template <typename T>
struct segment
{
    int m = 0;
    vector<T> tree;
    segment(int n) : m(n), tree(4 * n) {}
    void update(int i, T v)
    {
        auto f = [&](auto &self, int tl, int tr, int n) -> T
        {
            if (tr < i || tl > i || tl > tr)
                return T();
            if (tl == i && tr == i)
                return tree[n] += v;
            int mid = tl + (tr - tl) / 2;
            return tree[n] = self(self, tl, mid, 2 * n) +
                             self(self, mid + 1, tr, 2 * n + 1);
        };
        f(f, 0, m - 1, 1);
    }
    T query(int l, int r)
    {
        auto f = [&](auto &self, int tl, int tr, int n) -> T
        {
            if (tr < l || tl > r || tl > tr)
                return T();
            if (tl >= l && tr <= r)
                return tree[n];
            int mid = tl + (tr - tl) / 2;
            return self(self, tl, mid, 2 * n) +
                   self(self, mid + 1, tr, 2 * n + 1);
        };
        return f(f, 0, m - 1, 1);
    }
};