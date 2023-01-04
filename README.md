# LeetCode C++ Template

### Supported platforms:

- Windows (only platform right now, submit a PR if you want more platforms)

### Brief explanation

This was created because I had enough of manually changing LeetCode inputs to be C++ compatible. For example, every time the input was a list, I have to convert it to a `std::vector`, which was annoying as heck. You can only imagine the pain for linked lists and binary trees...

This template was also designed to read inputs **FAST**, meaning it'll construct the appropriate input objects as it reads the input *character by character*. It has to be fast because the majority of problems will have **HUGE** inputs, often to the size of *MILLIONS*. The outputting of the solution is going to be slower, simply because it's usually much less than the input and writing output character by character is painful.

### Features

- Supports all possible LeetCode inputs and outputs, which is done in `input.txt` and `output.txt`
- Ability to ignore certain lines in `input.txt`, to test regressions later on and debug certain tests for now
- Adds common values and type aliases from competitive programming, such as `INF = 1e9` and more
- A dedicated debug macro `dbg` for local debugging only
- Ability to copy the entire file for submission without removing debug calls, and etc

### How to use?

1. Every time you get a new LeetCode problem, you only need to modify `main.cpp` and `input.txt`:
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

2. Execute `run.bat` (make sure your compiler is in `PATH`):
    ```
    run.bat
    ```

### Output example

- For solutions that return a value:
  ```
  > run.bat
  Found MSVC as the compiler

  *some compiler message*

  10
  Elapsed time: 10ms

  Total elapsed time: 10ms
  ```

- For solution that modifies a parameter in-place:
    ```
  > run.bat
  Found MSVC as the compiler

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
