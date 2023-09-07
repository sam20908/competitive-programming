# LeetCode C++ Template

This was created for ease of solving LeetCode problems locally. The template is able to parse LeetCode inputs and constructs the appropriate data to pass into the solution. Integration with editors requires minimal work since this template is designed to be minimal.

### Features

- Supports LeetCode inputs and outputs
- Ignore certain lines in `input.txt` to test regressions
- A debug macro `dbg` to pretty-print variables
- Copy the entire file for submission

### How to use?

1. To set up for a LeetCode problem, only modify `main.cpp` and `input.txt`:
  - ```cpp
     // ----- CHANGE FOR PROBLEM -----
     class Solution {
     public:
       void test() {}
     };
     // ----- CHANGE FOR PROBLEM -----
     ```

  - ```cpp
     exec(&Solution::test); // CHANGE FOR PROBLEM
     ```

  - ```
     "CHANGE FOR PROBLEM"
     /"CHANGE FOR PROBLEM - IGNORED LINE"
     ```

2. Execute `run.bat` (or `run.sh`, and make sure `g++` is in `PATH`):
    ```
    run.bat
    ```

### Output example

- For solutions that return a value:
  ```
  > run.bat
  *some compiler message*

  10
  Elapsed time: 10ms

  Total elapsed time: 10ms
  ```

- For solution that modifies a parameter in-place:
    ```
  > run.bat
  *some compiler message*

  New state of parameters:
  #1: [1,2,3,4]
  #2: 10
  Elapsed time: 10ms

  Total elapsed time: 10ms
  ```

**Note: If the input doesn't match the parameter type, the behavior is undefined!**

### Debugging example

```cpp
map<int, vector<pair<int, int>>> a{{3, {{4, 5}, {6, 7}}}};
int b = INF;
dbg(a, b);
// [a = [{3,[{4,5},{6,7}]}]] [b = 1000000000]
```
