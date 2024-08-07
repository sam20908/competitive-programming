template <typename CItr, typename Itr, typename Cmp, typename Alloc>
struct node_update {
  typedef null_type metadata_type; // change metadata_type
  void operator()(Itr it, CItr end) { /* compute node data from left/right childs */ }
  virtual CItr node_begin() const = 0;
  virtual CItr node_end() const = 0;
  virtual ~node_update() {}
};