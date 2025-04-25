# LeetCode with C++

### Features

- Parses LeetCode inputs and outputs the answer in LeetCode format
  - **Requires C++ macro `LC_LOCAL` to be defined!**
  - Each line of the testcase should end with a newline (enter key)
  - To signal that you're done with the (possibly more than one) testcase, send an empty newline
- `dbg` macro to pretty-print most of common STL structures (up to 10 variables per `dbg` call)
- Copy the entire file for submission

### How to use?

Copy `template.cpp` into another file and adjust accordingly to the problem. Then the program can be compiled and run as normal.

### `dbg` macro!

```cpp
map<int, vector<pair<int, int>>> a{{3, {{4, 5}, {6, 7}}}};
int b = 1e9;
dbg(a, b);
// [a = [{3,[{4,5},{6,7}]}]] [b = 1000000000]
```
