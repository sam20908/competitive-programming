from typing import *
from ast import literal_eval
import inspect
from functools import *
from math import *
from collections import *
from heapq import *


class Solution:
  def test(self):
    pass


for name, fn in inspect.getmembers(Solution, inspect.isfunction):
  if not name.startswith("_"):
    print(fn(Solution(), *[literal_eval(input()) for _ in range(len(inspect.signature(fn).parameters) - 1)]))
    break
