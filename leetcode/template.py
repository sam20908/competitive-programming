from typing import List  # noqa: F401
from ast import literal_eval
import inspect


class Solution:
  def test(self):
    pass


for name, fn in inspect.getmembers(Solution, inspect.isfunction):
  if not name.startswith("_"):
    args = []
    for i in range(len(inspect.signature(fn).parameters) - 1):
      arg = literal_eval(input())
      args.append(arg)
    fn(Solution(), *args)
    break
