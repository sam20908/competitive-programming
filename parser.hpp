#pragma once

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left = nullptr;
  TreeNode *right = nullptr;
};
struct ListNode {
  int val;
  ListNode *next = nullptr;
};

template <typename = void> inline constexpr bool always_false = false;
template <typename T>
concept has_to_string = requires(T t) {
  { t.to_string() } -> same_as<std::string>;
};
template <typename T>
concept tuple_like = requires { typename tuple_size<T>::type; };
template <typename T>
concept iterable = requires(T t) {
  t.begin();
  t.end();
};

template <typename T>
void print_impl(FILE *f, const T &val, bool write_newline) {
  if constexpr (same_as<T, int>)
    fprintf(f, "%d", val);
  else if constexpr (same_as<T, float>)
    fprintf(f, "%.f", val);
  else if constexpr (same_as<T, double>)
    fprintf(f, "%.18f", val);
  else if constexpr (same_as<T, long long>)
    fprintf(f, "%lld", val);
  else if constexpr (same_as<T, unsigned int>)
    fprintf(f, "%u", val);
  else if constexpr (same_as<T, unsigned long long>)
    fprintf(f, "%llu", val);
  else if constexpr (same_as<T, bool>)
    fprintf(f, "%s", val ? "true" : "false");
  else if constexpr (same_as<T, string>)
    fprintf(f, "\"%s\"", val.data());
  else if constexpr (same_as<T, TreeNode *>) {
    queue<TreeNode *> q;
    fprintf(f, "[");
    if (val) {
      q.push(val);
      fprintf(f, "%d", val->val);
    }
    while (!q.empty()) {
      auto cur = q.front();
      q.pop();
      if (cur->left) {
        q.push(cur->left);
        fprintf(f, ",%d", cur->left->val);
      } else
        fprintf(f, ",null");
      if (cur->right) {
        q.push(cur->right);
        fprintf(f, ",%d", cur->right->val);
      } else
        fprintf(f, ",null");
    }
    fprintf(f, "]");
  } else if constexpr (tuple_like<T>) {
    fprintf(f, "{");
    apply(
        [&, c = 0](auto &&...args) mutable {
          ((fprintf(f, c++ ? "," : ""), print_impl(f, args, false)), ...);
        },
        val);
    fprintf(f, "}");
  } else if constexpr (same_as<T, ListNode *>) {
    auto cur = val;
    fprintf(f, "[");
    while (cur) {
      if (cur != val)
        fprintf(f, ",");
      fprintf(f, "%d", cur->val);
      cur = cur->next;
    }
    fprintf(f, "]");
  } else if constexpr (iterable<T>) {
    fprintf(f, "[");
    for (auto it = val.begin(); it != val.end(); it++) {
      if (it != val.begin())
        fprintf(f, ",");
      print_impl(f, *it, false);
    }
    fprintf(f, "]");
  } else
    static_assert(always_false<T>, "printing for type not supported");
  if (write_newline)
    fprintf(f, "\n");
}

#define CONCAT_IMPL(x, y) x##y
#define CONCAT(x, y) CONCAT_IMPL(x, y)
#define NUM_ARGS_IMPL(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, N, ...) N
#define NUM_ARGS(...) NUM_ARGS_IMPL(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
#define DBG_VAL(x)                                                             \
  [&]() {                                                                      \
    auto val = x;                                                              \
    fprintf(stderr, "[%s = ", #x);                                             \
    print_impl(stderr, val, false);                                            \
    fprintf(stderr, "] ");                                                     \
  }()
#define DBG_1(x) DBG_VAL(x)
#define DBG_2(x, ...) DBG_VAL(x), DBG_1(__VA_ARGS__)
#define DBG_3(x, ...) DBG_VAL(x), DBG_2(__VA_ARGS__)
#define DBG_4(x, ...) DBG_VAL(x), DBG_3(__VA_ARGS__)
#define DBG_5(x, ...) DBG_VAL(x), DBG_4(__VA_ARGS__)
#define DBG_6(x, ...) DBG_VAL(x), DBG_5(__VA_ARGS__)
#define DBG_7(x, ...) DBG_VAL(x), DBG_6(__VA_ARGS__)
#define DBG_8(x, ...) DBG_VAL(x), DBG_7(__VA_ARGS__)
#define DBG_9(x, ...) DBG_VAL(x), DBG_8(__VA_ARGS__)
#define DBG_10(x, ...) DBG_VAL(x), DBG_9(__VA_ARGS__)
#define dbg(...)                                                               \
  CONCAT(DBG_, NUM_ARGS(__VA_ARGS__))(__VA_ARGS__), fprintf(stderr, "\n");
// supports up to 10 arguments debugging at one time

template <typename T> T parse() {
  T ans;
  if constexpr (same_as<T, char>)
    scanf("\"%c\"", &ans);
  else if constexpr (same_as<T, int>)
    scanf("%d", &ans);
  else if constexpr (same_as<T, long long>)
    scanf("%lld", &ans);
  else if constexpr (same_as<T, unsigned int>)
    scanf("%u", &ans);
  else if constexpr (same_as<T, unsigned long long>)
    scanf("%llu", &ans);
  else if constexpr (same_as<T, float>)
    scanf("%f", &ans);
  else if constexpr (same_as<T, double>)
    scanf("%lf", &ans);
  else if constexpr (same_as<T, string>) {
    char *buf;
    scanf(" \"%m[^\"]\"", &buf);
    ans = buf;
    free(buf);
  } else if constexpr (same_as<T, TreeNode *>) {
    bool right = true;
    auto dummy = new TreeNode{};
    queue<TreeNode *> q;
    q.push(dummy);
    scanf(" %*c");
    if (int c = getchar(); c != ']') {
      ungetc(c, stdin);
      while (!q.empty()) {
        char *buf;
        scanf(" %m[^],]", &buf);
        getchar();
        if (strcmp(buf, "null") != 0) {
          auto new_node = new TreeNode{atoi(buf)};
          if (right)
            q.front()->right = new_node;
          else
            q.front()->left = new_node;
          q.push(new_node);
        }
        if (right)
          q.pop();
        right = !right;
        free(buf);
      }
    }
    ans = dummy->right;
    delete dummy;
  } else if constexpr (same_as<T, ListNode *>) {
    auto dummy = new ListNode{};
    auto cur = dummy;
    scanf(" %*c");
    if (int c = getchar(); c != ']') {
      ungetc(c, stdin);
      while (true) {
        cur->next = new ListNode{parse<int>()};
        cur = cur->next;
        if (getchar() == ']')
          break;
      }
    }
    ans = dummy->next;
    delete dummy;
  } else if constexpr (iterable<T>) {
    scanf(" %*c");
    if (int c = getchar(); c != ']') {
      ungetc(c, stdin);
      while (true) {
        ans.emplace_back(parse<typename T::value_type>());
        if (getchar() == ']')
          break;
      }
    }
  } else
    static_assert(always_false<T>, "parsing for type not supported");
  return ans;
}

template <typename T> void free_var(T &t) {
  if constexpr (same_as<T, ListNode *>) {
    auto cur = t;
    while (cur) {
      auto next = cur->next;
      delete cur;
      cur = next;
    }
  } else if constexpr (same_as<T, TreeNode *>) {
    auto f = [&](auto &self, TreeNode *cur) {
      if (!cur)
        return;
      self(self, cur->left);
      self(self, cur->right);
      delete cur;
    };
    f(f, t);
  }
}

template <typename Solution, typename R, typename... Ts>
void exec(R (Solution::*fn)(Ts...)) {
  long long total_elapsed = 0;
  while (true) {
    int c = getchar();
    if (c == EOF)
      break;
    if (c == '/') {
      do {
        c = getchar();
      } while (!isspace(c) && c != EOF);
    } else {
      ungetc(c, stdin);
      tuple<Solution, decay_t<Ts>...> args;
      get<0>(args) = Solution{};
      [&]<size_t... Idx>(index_sequence<Idx...>) {
        ((get<Idx + 1>(args) = parse<decay_t<Ts>>()), ...);
      }(index_sequence_for<Ts...>{});
      long long elapsed = 0;
      if constexpr (same_as<R, void>) {
        const clock_t start = clock();
        apply(fn, args);
        const clock_t now = clock();
        elapsed = (now - start) / (CLOCKS_PER_SEC / 1000);
        []<size_t... Idx>(auto &&args, index_sequence<Idx...>) {
          ((printf("#%lld: ", Idx + 1),
            print_impl(stdout, get<Idx + 1>(args), true)),
           ...);
        }(args, index_sequence_for<Ts...>{});
      } else {
        auto start = clock();
        auto res = apply(fn, args);
        auto now = clock();
        elapsed = (now - start) / (CLOCKS_PER_SEC / 1000);
        print_impl(stdout, res, true);
        free_var(res);
      }
      [&]<size_t... Idx>(index_sequence<Idx...>) {
        (free_var(get<Idx + 1>(args)), ...);
      }(index_sequence_for<Ts...>{});
      total_elapsed += elapsed;
      printf("Elapsed time: %lldms\n", elapsed);
      fprintf(stderr, "\n"); // separate debug output from different testcases
    }
  }
  printf("\nTotal elapsed time: %lldms", total_elapsed);
}
