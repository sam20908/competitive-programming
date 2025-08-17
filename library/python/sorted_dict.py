from array import array
from collections.abc import MutableMapping
from itertools import repeat


class SortedDict(MutableMapping):
    __slots__ = (
        "__key",
        "__value",
        "__left",
        "__right",
        "__size",
        "__root",
        "__max_nodes",
        "__nodes",
        "__free",
        "__multimap",
    )
    ALPHA = 0.85  # 0.5 (faster lookups) < ALPHA < 1 (faster modifications)

    def __init__(self, iterable=None, multimap=False, key_code=None, value_code=None):
        self.__key = array(key_code, [0]) if key_code else [None]
        self.__value = array(value_code, [0]) if value_code else [None]
        self.__left = array("i", [0])
        self.__right = array("i", [0])
        self.__size = array("i", [0])
        self.__root = self.__nodes = self.__max_nodes = self.__free = 0
        self.__multimap = multimap
        if iterable:
            elems = sorted(iterable if multimap else dict(iterable).items())
            n = len(elems)
            if n > 0:
                for key, value in elems:
                    self.__key.append(key)
                    self.__value.append(value)
                self.__left.extend(repeat(0, n))
                self.__right.extend(range(2, n + 1))
                self.__right.append(0)
                self.__size.extend(range(n, 0, -1))
                self.__nodes = self.__max_nodes = n
                self.__root = self.__rebalance(1)

    def __len__(self):
        return self.__nodes

    def __str__(self):
        return str(list(self))

    def __iter__(self):
        return map(self.__key.__getitem__, self.__inorder())

    def __contains__(self, key):
        cur = self.__root
        while cur > 0:
            cur_key = self.__key[cur]
            if cur_key == key:
                return True
            if cur_key > key:
                cur = self.__left[cur]
            else:
                cur = self.__right[cur]
        return False

    def __getitem__(self, key):
        cur = self.__root
        while cur > 0:
            cur_key = self.__key[cur]
            if cur_key == key:
                break
            if cur_key > key:
                cur = self.__left[cur]
            else:
                cur = self.__right[cur]
        if cur == 0:
            raise KeyError(key)
        return self.__value[cur]

    def __setitem__(self, key, value):
        cur = self.__root
        parent = 0
        while cur:
            cur_key = self.__key[cur]
            if key == cur_key and not self.__multimap:
                break
            if key < cur_key:
                nxt = self.__left[cur]
                self.__left[cur] = -parent - 1
            else:
                nxt = self.__right[cur]
                self.__right[cur] = -parent - 1
            parent = cur
            cur = nxt
        if cur:
            self.__value[cur] = value
        else:
            cur = self.__free
            if cur:
                self.__free = self.__left[cur]
                self.__key[cur] = key
                self.__value[cur] = value
                self.__left[cur] = self.__right[cur] = 0
                self.__size[cur] = 1
            else:
                cur = self.__nodes + 1
                self.__key.append(key)
                self.__value.append(value)
                self.__left.append(0)
                self.__right.append(0)
                self.__size.append(1)
            self.__nodes += 1
            self.__max_nodes = (
                self.__nodes if self.__nodes > self.__max_nodes else self.__max_nodes
            )
        while parent:
            left = self.__left[parent]
            right = self.__right[parent]
            if left < 0:
                self.__left[parent] = cur
                cur = parent
                parent = -(left + 1)
            else:
                self.__right[parent] = cur
                cur = parent
                parent = -(right + 1)
            left_size = self.__size[self.__left[cur]]
            right_size = self.__size[self.__right[cur]]
            self.__size[cur] = left_size + right_size + 1
            weight_bound = SortedDict.ALPHA * self.__size[cur]
            if left_size > weight_bound or right_size > weight_bound:
                cur = self.__rebalance(cur)
        self.__root = cur

    def __delitem__(self, key):
        cur = self.__root
        parent = 0
        while cur:
            cur_key = self.__key[cur]
            if key == cur_key:
                break
            if key < cur_key:
                nxt = self.__left[cur]
                self.__left[cur] = -parent - 1
            else:
                nxt = self.__right[cur]
                self.__right[cur] = -parent - 1
            parent = cur
            cur = nxt
        if cur:
            cur = self.__remove(cur)
            deleted = True
        else:
            deleted = False
        while parent:
            left = self.__left[parent]
            right = self.__right[parent]
            if left < 0:
                self.__left[parent] = cur
                cur = parent
                parent = -(left + 1)
            else:
                self.__right[parent] = cur
                cur = parent
                parent = -(right + 1)
            left_size = self.__size[self.__left[cur]]
            right_size = self.__size[self.__right[cur]]
            self.__size[cur] = left_size + right_size + 1
        if self.__nodes <= SortedDict.ALPHA * self.__max_nodes:
            cur = self.__rebalance(cur)
            self.__max_nodes = self.__nodes
        self.__root = cur
        if not deleted:
            raise KeyError(key)

    def __inorder(self):
        cur = self.__root
        while cur:
            left = self.__left[cur]
            right = self.__right[cur]
            if left:
                succ = left
                while self.__right[succ] and self.__right[succ] != -cur - 1:
                    succ = self.__right[succ]
                if self.__right[succ]:
                    self.__right[succ] = 0
                    yield cur
                    cur = right
                else:
                    self.__right[succ] = -cur - 1
                    cur = left
            else:
                yield cur
                cur = right if right >= 0 else -(right + 1)

    def __rebalance(self, root):
        size = self.__size[root]
        dummy = self.__free
        self.__right[dummy] = root
        tail = dummy
        cur = root
        while cur:
            left = self.__left[cur]
            if left:
                left_right = self.__right[left]
                self.__size[cur] += self.__size[left_right] - self.__size[left]
                self.__size[left] += self.__size[cur] - self.__size[left_right]
                self.__left[cur] = left_right
                self.__right[left] = cur
                cur = left
                self.__right[tail] = left
            else:
                tail = cur
                cur = self.__right[cur]
        leaf_positions = 1 << (size + 1).bit_length() - 1
        leaves = size + 1 - leaf_positions
        if leaves > 0:
            hole_count = leaf_positions - leaves
            hole_index = 1
            next_hole = leaf_positions // hole_count
            cur = dummy
            for i in range(1, leaf_positions):
                if i == next_hole:
                    cur = self.__right[cur]
                    hole_index += 1
                    next_hole = (hole_index * leaf_positions) // hole_count
                else:
                    leaf = self.__right[cur]
                    self.__right[cur] = self.__right[leaf]
                    cur = self.__right[cur]
                    self.__size[leaf] -= self.__size[cur]
                    self.__size[cur] += self.__size[leaf]
                    self.__left[cur] = leaf
                    self.__right[leaf] = 0
        size -= leaves
        while size > 1:
            size >>= 1
            cur = dummy
            for _ in range(size):
                root = self.__right[cur]
                self.__right[cur] = self.__right[root]
                cur = self.__right[cur]
                root_left = self.__left[cur]
                self.__size[root] += self.__size[root_left] - self.__size[cur]
                self.__size[cur] += self.__size[root] - self.__size[root_left]
                self.__right[root] = self.__left[cur]
                self.__left[cur] = root
        return self.__right[dummy]

    def __remove(self, cur):
        left = self.__left[cur]
        right = self.__right[cur]
        self.__left[cur] = self.__free
        self.__free = cur
        if left and right:
            succ = succ_parent = self.__right[cur]
            while self.__left[succ]:
                self.__size[succ] -= 1
                succ_parent = succ
                succ = self.__left[succ]
            if succ == right:
                self.__left[succ] = left
                self.__size[succ] += self.__size[left]
            else:
                self.__left[succ_parent] = self.__right[succ]
                self.__left[succ] = left
                self.__right[succ] = right
                self.__size[succ] = self.__size[left] + self.__size[right] + 1
            cur = succ
        elif left:
            cur = left
        elif right:
            cur = right
        else:
            cur = 0
        self.__nodes -= 1
        return cur

    def clear(self):
        for i in self.__inorder():
            free = self.__free
            self.__free = i
            self.__left[i] = free
        self.__nodes = self.__max_nodes = self.__root = 0

    def discard(self, x):
        cur = self.__root
        parent = 0
        deleted = False
        while cur:
            value = self.__key[cur]
            if x < value:
                nxt = self.__left[cur]
                self.__left[cur] = -parent - 1
            elif x > value:
                nxt = self.__right[cur]
                self.__right[cur] = -parent - 1
            else:
                deleted = True
                break
            parent = cur
            cur = nxt
        if cur:
            cur = self.__remove(cur)
        while parent:
            left = self.__left[parent]
            right = self.__right[parent]
            if left < 0:
                self.__left[parent] = cur
                cur = parent
                parent = -(left + 1)
            else:
                self.__right[parent] = cur
                cur = parent
                parent = -(right + 1)
            left_size = self.__size[self.__left[cur]]
            right_size = self.__size[self.__right[cur]]
            self.__size[cur] = left_size + right_size + 1
        if self.__nodes <= SortedDict.ALPHA * self.__max_nodes:
            cur = self.__rebalance(cur)
            self.__max_nodes = self.__nodes
        self.__root = cur
        return deleted

    def at(self, index):
        if index < 0:
            index += self.__nodes
        if index < 0 or index >= self.__nodes:
            raise IndexError("list index out of range")
        node = None
        cur = self.__root
        cnt = 0
        while cur > 0:
            new_cnt = cnt + self.__size[self.__left[cur]] + 1
            if new_cnt > index:
                node = cur
                cur = self.__left[cur]
            else:
                cnt = new_cnt
                cur = self.__right[cur]
        return (self.__key[node], self.__value[node])

    def atleast(self, x):
        ans = None
        cur = self.__root
        while cur > 0:
            value = self.__key[cur]
            if value >= x:
                ans = value
                cur = self.__left[cur]
            else:
                cur = self.__right[cur]
        return ans

    def atmost(self, x):
        ans = None
        cur = self.__root
        while cur > 0:
            value = self.__key[cur]
            if value <= x:
                ans = value
                cur = self.__right[cur]
            else:
                cur = self.__left[cur]
        return ans

    def count_atmost(self, x):
        ans = 0
        cur = self.__root
        while cur > 0:
            if self.__key[cur] <= x:
                ans += self.__size[self.__left[cur]] + 1
                cur = self.__right[cur]
            else:
                cur = self.__left[cur]
        return ans
