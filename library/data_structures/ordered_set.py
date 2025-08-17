from array import array
from itertools import repeat
class OrderedSet:
    __slots__ = (
        "_value",
        "_left",
        "_right",
        "_size",
        "_max_nodes",
        "_nodes",
        "_free",
        "_multiset",
    )
    ALPHA = 0.85  # 0.5 (faster lookups) < ALPHA < 1 (faster modifications)

    def __init__(self, iterable=None, multiset=False, code=None):
        self._value = array(code, [0]) if code else [None]
        self._left = array("i", [0, 0])
        self._right = array("i", [0, 0])
        self._size = array("i", [0, 0])
        self._max_nodes = 0
        self._nodes = 0
        self._free = 1
        self._multiset = multiset
        if iterable:
            value = sorted(iterable) if multiset else sorted(set(iterable))
            n = len(value)
            self._value.extend(value)
            self._left.extend(repeat(0, n))
            self._right[-1] = 2
            self._right.extend(range(3, n + 2))
            self._right[-1] = 0
            self._right.append(0)
            self._size.pop()
            self._size.extend(range(n, 0, -1))
            self._size.append(0)
            self._nodes = self._max_nodes = n
            self._free = n + 1
            self._left[0] = self._rebalance(1)

    def __len__(self):
        return self._nodes

    def __iter__(self):
        return iter(self.values())

    def _rebalance(self, root):
        size = self._size[root]
        dummy = self._free
        prev_free = self._left[dummy]
        self._left[dummy] = 0
        self._right[dummy] = root
        tail = dummy
        cur = root
        while cur:
            left = self._left[cur]
            if left:
                left_right = self._right[left]
                self._size[cur] += self._size[left_right] - self._size[left]
                self._size[left] += self._size[cur] - self._size[left_right]
                self._left[cur] = left_right
                self._right[left] = cur
                cur = left
                self._right[tail] = left
            else:
                tail = cur
                cur = self._right[cur]
        leaf_positions = 1 << (size + 1).bit_length() - 1
        leaves = size + 1 - leaf_positions
        if leaves > 0:
            hole_count = leaf_positions - leaves
            hole_index = 1
            next_hole = leaf_positions // hole_count
            cur = dummy
            for i in range(1, leaf_positions):
                if i == next_hole:
                    cur = self._right[cur]
                    hole_index += 1
                    next_hole = (hole_index * leaf_positions) // hole_count
                else:
                    leaf = self._right[cur]
                    self._right[cur] = self._right[leaf]
                    cur = self._right[cur]
                    self._size[leaf] -= self._size[cur]
                    self._size[cur] += self._size[leaf]
                    self._left[cur] = leaf
                    self._right[leaf] = 0
        size -= leaves
        while size > 1:
            size >>= 1
            cur = dummy
            for _ in range(size):
                root = self._right[cur]
                self._right[cur] = self._right[root]
                cur = self._right[cur]
                root_left = self._left[cur]
                self._size[root] += self._size[root_left] - self._size[cur]
                self._size[cur] += self._size[root] - self._size[root_left]
                self._right[root] = self._left[cur]
                self._left[cur] = root
        self._left[dummy] = self._right[dummy]
        self._right[dummy] = 0
        root = self._left[dummy]
        self._left[dummy] = prev_free
        return root

    def add(self, x):
        cur = self._left[0]
        parent = 0
        found = False
        while cur:
            value = self._value[cur]
            if x == value:
                found = True
            if x < value:
                nxt = self._left[cur]
                self._left[cur] = -parent - 1
            else:
                nxt = self._right[cur]
                self._right[cur] = -parent - 1
            parent = cur
            cur = nxt
        if not found or self._multiset:
            cur = self._free
            prev_free = self._left[cur]
            if parent == 0:
                self._left[0] = cur
            self._left[cur] = self._right[cur] = 0
            self._size[cur] = 1
            if cur == len(self._value):
                self._value.append(x)
                self._left.append(0)
                self._right.append(0)
                self._size.append(0)
                self._free += 1
            else:
                self._value[cur] = x
                self._free = prev_free
            self._nodes += 1
            self._max_nodes = (
                self._nodes if self._nodes > self._max_nodes else self._max_nodes
            )
        while parent:
            left = self._left[parent]
            right = self._right[parent]
            if left < 0:
                self._left[parent] = cur
                cur = parent
                parent = -(left + 1)
            else:
                self._right[parent] = cur
                cur = parent
                parent = -(right + 1)
            left_size = self._size[self._left[cur]]
            right_size = self._size[self._right[cur]]
            self._size[cur] = left_size + right_size + 1
            weight_bound = OrderedSet.ALPHA * self._size[cur]
            if left_size > weight_bound or right_size > weight_bound:
                cur = self._rebalance(cur)
        self._left[0] = cur

    def delete(self, x):
        cur = self._left[0]
        parent = 0
        while cur:
            value = self._value[cur]
            if x < value:
                nxt = self._left[cur]
                self._left[cur] = -parent - 1
            elif x > value:
                nxt = self._right[cur]
                self._right[cur] = -parent - 1
            else:
                break
            parent = cur
            cur = nxt
        if cur:
            left = self._left[cur]
            right = self._right[cur]
            self._left[cur] = self._free
            self._free = cur
            if left and right:
                succ = succ_parent = self._right[cur]
                while self._left[succ]:
                    self._size[succ] -= 1
                    succ_parent = succ
                    succ = self._left[succ]
                if succ == right:
                    self._left[succ] = left
                    self._size[succ] += self._size[left]
                else:
                    self._left[succ_parent] = self._right[succ]
                    self._left[succ] = left
                    self._right[succ] = right
                    self._size[succ] = self._size[left] + self._size[right] + 1
                if cur == self._left[0]:
                    self._left[0] = succ
                cur = succ
            elif left:
                cur = left
            elif right:
                cur = right
            else:
                cur = 0
            self._nodes -= 1
        while parent:
            left = self._left[parent]
            right = self._right[parent]
            if left < 0:
                self._left[parent] = cur
                cur = parent
                parent = -(left + 1)
            else:
                self._right[parent] = cur
                cur = parent
                parent = -(right + 1)
            self._size[cur] = (
                self._size[self._left[cur]] + self._size[self._right[cur]] + 1
            )
        self._left[0] = cur
        if self._nodes <= OrderedSet.ALPHA * self._max_nodes:
            self._left[0] = self._rebalance(self._left[0])
            self._max_nodes = self._nodes

    def values(self):
        ans = []
        cur = self._left[0]
        while cur:
            left = self._left[cur]
            right = self._right[cur]
            if left:
                succ = left
                while self._right[succ] and self._right[succ] != cur:
                    succ = self._right[succ]
                if self._right[succ]:
                    ans.append(self._value[cur])
                    self._right[succ] = 0
                    cur = right
                else:
                    self._right[succ] = cur
                    cur = left
            else:
                ans.append(self._value[cur])
                cur = right
        return ans

    def atleast(self, x):
        ans = None
        cur = self._left[0]
        while cur:
            value = self._value[cur]
            if value >= x:
                ans = value
                cur = self._left[cur]
            else:
                cur = self._right[cur]
        return ans

    def atmost(self, x):
        ans = None
        cur = self._left[0]
        while cur:
            value = self._value[cur]
            if value <= x:
                ans = value
                cur = self._right[cur]
            else:
                cur = self._left[cur]
        return ans

    def kth_smallest(self, k):
        ans = None
        cur = self._left[0]
        cnt = 0
        while cur:
            lsize = self._size[self._left[cur]]
            if cnt + lsize + 1 > k:
                ans = self._value[cur]
                cur = self._left[cur]
            else:
                cnt += lsize + 1
                cur = self._right[cur]
        return ans

    def count_atmost(self, x):
        ans = 0
        cur = self._left[0]
        while cur:
            if self._value[cur] <= x:
                ans += self._size[self._left[cur]] + 1
                cur = self._right[cur]
            else:
                cur = self._left[cur]
        return ans