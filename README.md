# LeetCode C++ Template

### Brief explanation

This was created because I had enough of manually changing LeetCode inputs to be C++ compatible. For example, every time the input was a list, I have to conver it to a `std::vector`, which was annoying as heck. You can only imagine the pain for linked lists and binary trees... As a bonus with this template, **you can copy the entire file for LeetCode submission!** Just like how competitive programmers do it :)

I have provided some common macros and `typedef`s that were collected from both seeing some competitive programmers as well as me finding out that I do certain things a lot. You can expect things like *ll*, *INF*, *EPS*, *dx*, *dy*, browse the file for yourself :)

There is also a debug macro **dbg** that prints out the expression's name with their result, so this is an example usage (some types aren't supported):

```cpp
map<int, vector<pair<int, int>>> a{{3, {{4, 5}, {6, 7}}}};
int b = INF;
dbg(a, b);
// [a = [3, [{4, 5}, {6, 7}]]] [b = 1000000000]
```

**dbg will only work locally (running run.bat)!**, so you can just paste the entire file for LeetCode submission without having to worry about removing debug calls.

This template was also designed to read inputs **FAST**, meaning it'll construct the appropriate input objects as it reads the input *character by character*. It has to be fast because the majority of problems will have **HUGE** inputs, often to the size of *MILLIONS*. The outputting of the solution is going to be slower, simply because I can't "undo" writes and the answer in 90% of the problems are going to be much less than the inputs.

### Supported types:

- Inputs:
  
  - Integers [-2^31, 2^31 - 1]
  
  - Strings
  
  - Linked lists (of integers values, from LeetCode's format)
  
  - Binary Trees (of integers values, from LeetCode's format)
  
  - Nth dimensional lists (of the supported types above)

- Outputs:
  
  - Integers [-2^31, 2^31 - 1]
  
  - Floating points
  
  - Booleans (as "true" or "false" strings)
  
  - Strings
  
  - Linked lists (of integer values, serialized to LeetCode's format)
  
  - Binary Trees (of integer values, serialized to LeetCode's format)
  
  - Nth dimensional lists (of the supported types above)

### How to use?

Every time you get a LeetCode problem, there's only 3 places you have to modify:

1. ```cpp
   // ----- CHANGE FOR PROBLEM -----
   class Solution {
   public:
     void test() {}
   };
   // ----- CHANGE FOR PROBLEM -----
   ```

2. ```cpp
   exec(&Solution::test); // CHANGE FOR PROBLEM
   ```

3. ```
   "CHANGE FOR PROBLEM"
   /"CHANGE FOR PROBLEM - IGNORED LINE"
   ```

As you can see, since LeetCode has different `Solution` body and method, you'll have to update them manually **1 and 2** exists in `main.cpp` and **3** exists in `input.txt`. Yes, you can literally grab the input from LeetCode and just paste it, it'll work!

**Every line that starts with `/`, the entire line will get ignored**. This is very useful for keeping all the tests around to test regressions but you only want to debug certain ones right now.

**Note: If the input doesn't match the parameter type, the behavior is undefined!**

Then you just call the `run` batch script and watch the magic happen! **`run.bat` will automatically detect whether you have MSVC, GCC, or Clang, and build the executable with the compiler it detects.**
