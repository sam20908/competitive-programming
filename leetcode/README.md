# LeetCode C++

This was created for ease of solving LeetCode problems locally. The template is able to parse LeetCode inputs and constructs the appropriate data to pass into the solution. Integration with editors requires minimal work since this template was designed to be minimal.

### Features

- Parses LeetCode inputs **from stdin** and outputs **to stdout** (lines starting with "/" are ignored)
  - If the input is ill-formed or does not match the parameter types, the behavior is undefined!
- Comes with templates for various data structures and algorithms
- A debug macro `dbg` to pretty-print multiple variables at once **to stderr** (up to 10 per `dbg` call)
- Copy the entire file for submission

### How to use?

1. To set up for a LeetCode problem, copy `template.cpp` to another file (commonly `main.cpp`) and change the following parts:
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

2. Run `run.sh _your_solution_filename_` (or `run.bat`, and **make sure `g++` is in `PATH`**)
  - If you want to use a file as input, run `run.sh _your_solution_filename_ < _your_input_filename_`
  - Similarly, if you want to output to a file, run `run.sh _your_solution_filename_ > _your_output_filename_`

### `dbg` example

```cpp
map<int, vector<pair<int, int>>> a{{3, {{4, 5}, {6, 7}}}};
int b = 1e9;
dbg(a, b);
// [a = [{3,[{4,5},{6,7}]}]] [b = 1000000000]
```
