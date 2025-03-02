struct fast_hasher {
  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
    x += FIXED_RANDOM + 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x;
  }
};
template <typename K, typename V>
using fast_hash_table = unordered_map<K, V, fast_hasher>;
template <typename V>
using fast_hash_set = unordered_set<V, fast_hasher>;