template <typename T, typename = void> struct is_tuple_like {
  static constexpr bool value = false;
};
template <typename T>
struct is_tuple_like<T, void_t<typename tuple_size<T>::type>> {
  static constexpr bool value = true;
};
template <typename T, typename = void> struct is_hashable {
  static constexpr bool value = false;
};
template <typename T> struct is_hashable<T, void_t<decltype(hash<T>{}(T{}))>> {
  static constexpr bool value = true;
};
vec<size_t> VALS;
struct custom_hash {
  static size_t getfixed(int i) {
    while ((int)VALS.size() < i + 1)
      if (VALS.empty())
        VALS.push_back(
            (size_t)chrono::steady_clock::now().time_since_epoch().count());
      else
        VALS.push_back(splitmix64(VALS.back()));
    return VALS[i];
  }
  static size_t splitmix64(size_t x) {
    x += (size_t)0x9e3779b97f4a7c15;
    x = (x ^ (x >> (size_t)30)) * (size_t)0xbf58476d1ce4e5b9;
    x = (x ^ (x >> (size_t)27)) * (size_t)0x94d049bb133111eb;
    return x ^ (x >> (size_t)31);
  }
  template <typename T>
  enable_if_t<is_hashable<T>::value, size_t> operator()(const T &t) const {
    return splitmix64(hash<T>{}(t) + getfixed(0));
  }
  template <typename T>
  enable_if_t<is_tuple_like<T>::value, size_t> operator()(const T &t) const {
    int ic = 0;
    size_t rh = 0;
    apply(
        [&](auto &&...args) {
          ((rh ^=
            splitmix64(hash<decay_t<decltype(args)>>{}(args) + getfixed(ic++))),
           ...);
        },
        t);
    return rh;
  }
};
template <typename A, typename B> using tensor_map = umap<A, B, custom_hash>;
template <typename A> using tensor_set = uset<A, custom_hash>;