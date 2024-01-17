# LeetCode C++

This was created for ease of solving LeetCode problems locally. The template is able to parse LeetCode inputs and constructs the appropriate data to pass into the solution. Integration with editors requires minimal work since this template was designed to be minimal.

### Features

- Parses LeetCode inputs and outputs (and the ability to ignore lines)
  - The parser reads from **stdin**, outputs to **stdout**, and prints debug information to **stderr**
  - If the input is ill-formed or does not match the parameter types, the behavior is undefined!
- Comes with commonly useful data structures and algorithms
- A debug macro `dbg` to pretty-print multiple variables at once
- Copy the entire file for submission

**Tip: Make Git skip changes to `main.cpp`, `input.txt` and `output.txt` with `git update-index --skip-worktree main.cpp input.txt output.txt`**

### How to use?

1. To set up for a LeetCode problem, modify `main.cpp` and `input.txt`:
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

  *dbg(...) messages*

  10
  Elapsed time: 10ms

  Total elapsed time: 10ms
  ```

- For solution that modifies the parameters in-place:
    ```
  > run.bat
  *some compiler message*

  *dbg(...) messages*

  New state of parameters:
  #1: [1,2,3,4]
  #2: 10
  Elapsed time: 10ms

  Total elapsed time: 10ms
  ```

### `dbg` example

```cpp
map<int, vector<pair<int, int>>> a{{3, {{4, 5}, {6, 7}}}};
int b = 1e9;
dbg(a, b);
// [a = [{3,[{4,5},{6,7}]}]] [b = 1000000000]
```
