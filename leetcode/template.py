from typing import List
from ast import literal_eval
import inspect
from functools import cache
import collections, math, bisect, heapq


class Solution:
  def test(self):
    pass


for name, fn in inspect.getmembers(Solution, inspect.isfunction):
  if not name.startswith("_"):
    print(fn(Solution(), *[literal_eval(input()) for _ in range(len(inspect.signature(fn).parameters) - 1)]))
    break
