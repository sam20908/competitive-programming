from array import array
from itertools import repeat
class OrderedSet:
    __slots__ = (
        "__value",
        "__left",
        "__right",
        "__size",
        "__max_nodes",
        "__nodes",
        "__free",
        "__multiset",
    )
    ALPHA = 0.85  # 0.5 (faster lookups) < ALPHA < 1 (faster modifications)

    def __init__(self, iterable=None, multiset=False, code=None):
        self.__value = array(code, [0]) if code else [None]
        self.__left = array("i", [0, 0])
        self.__right = array("i", [0, 0])
        self.__size = array("i", [0, 0])
        self.__max_nodes = 0
        self.__nodes = 0
        self.__free = 1
        self.__multiset = multiset
        if iterable:
            value = sorted(iterable) if multiset else sorted(set(iterable))
            n = len(value)
            self.__value.extend(value)
            self.__left.extend(repeat(0, n))
            self.__right[-1] = 2
            self.__right.extend(range(3, n + 2))
            self.__right[-1] = 0
            self.__right.append(0)
            self.__size.pop()
            self.__size.extend(range(n, 0, -1))
            self.__size.append(0)
            self.__nodes = self.__max_nodes = n
            self.__free = n + 1
            self.__left[0] = self.__rebalance(1)

    def __len__(self):
        return self.__nodes

    def __str__(self):
        return str(list(self))

    def __iter__(self):
        return iter([self.__value[i] for i in self.__inorder()])

    def __contains__(self, x):
        return self.atleast(x) == x

    def __getitem__(self, index):
        if index < 0:
            index += self.__nodes
        if index < 0 or index >= self.__nodes:
            raise IndexError("list index out of range")
        node = None
        cur = self.__left[0]
        cnt = 0
        while cur:
            new_cnt = cnt + self.__size[self.__left[cur]] + 1
            if new_cnt > index:
                node = cur
                cur = self.__left[cur]
            else:
                cnt = new_cnt
                cur = self.__right[cur]
        return self.__value[node]

    def __delitem__(self, index):
        if index < 0:
            index += self.__nodes
        if index < 0 or index >= self.__nodes:
            raise IndexError("list index out of range")
        cnt = 0
        cur = self.__left[0]
        parent = 0
        while cur:
            new_cnt = cnt + self.__size[self.__left[cur]] + 1
            if new_cnt == index + 1:
                break
            if new_cnt > index:
                nxt = self.__left[cur]
                self.__left[cur] = -parent - 1
            else:
                cnt = new_cnt
                nxt = self.__right[cur]
                self.__right[cur] = -parent - 1
            parent = cur
            cur = nxt
        cur = self.__remove(cur)
        self.__repair_upwards(cur, parent, False, True)

    def __inorder(self):
        cur = self.__left[0]
        while cur:
            left = self.__left[cur]
            right = self.__right[cur]
            if left:
                succ = left
                while self.__right[succ] and self.__right[succ] != cur:
                    succ = self.__right[succ]
                if self.__right[succ]:
                    self.__right[succ] = 0
                    yield cur
                    cur = right
                else:
                    self.__right[succ] = cur
                    cur = left
            else:
                yield cur
                cur = right

    def __repair_upwards(self, cur, parent, check_subtree, check_root):
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
            if check_subtree:
                weight_bound = OrderedSet.ALPHA * self.__size[cur]
                if left_size > weight_bound or right_size > weight_bound:
                    cur = self.__rebalance(cur)
        if check_root and self.__nodes <= OrderedSet.ALPHA * self.__max_nodes:
            self.__left[0] = self.__rebalance(cur)
            self.__max_nodes = self.__nodes
        else:
            self.__left[0] = cur

    def __remove(self, node):
        left = self.__left[node]
        right = self.__right[node]
        self.__left[node] = self.__free
        self.__free = node
        if left and right:
            succ = succ_parent = self.__right[node]
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
            if node == self.__left[0]:
                self.__left[0] = succ
            node = succ
        elif left:
            node = left
        elif right:
            node = right
        else:
            node = 0
        self.__nodes -= 1
        return node

    def __rebalance(self, root):
        size = self.__size[root]
        dummy = self.__free
        prev_free = self.__left[dummy]
        self.__left[dummy] = 0
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
        self.__left[dummy] = self.__right[dummy]
        self.__right[dummy] = 0
        root = self.__left[dummy]
        self.__left[dummy] = prev_free
        return root

    def clear(self):
        for i in self.__inorder():
            free = self.__free
            self.__free = i
            self.__left[i] = free
        self.__nodes = self.__max_nodes = self.__left[0] = 0

    def add(self, x):
        cur = self.__left[0]
        parent = 0
        found = False
        while cur:
            value = self.__value[cur]
            if x == value:
                found = True
            if x < value:
                nxt = self.__left[cur]
                self.__left[cur] = -parent - 1
            else:
                nxt = self.__right[cur]
                self.__right[cur] = -parent - 1
            parent = cur
            cur = nxt
        if not found or self.__multiset:
            cur = self.__free
            prev_free = self.__left[cur]
            if parent == 0:
                self.__left[0] = cur
            self.__left[cur] = self.__right[cur] = 0
            self.__size[cur] = 1
            if cur == len(self.__value):
                self.__value.append(x)
                self.__left.append(0)
                self.__right.append(0)
                self.__size.append(0)
                self.__free += 1
            else:
                self.__value[cur] = x
                self.__free = prev_free
            self.__nodes += 1
            self.__max_nodes = (
                self.__nodes if self.__nodes > self.__max_nodes else self.__max_nodes
            )
        self.__repair_upwards(cur, parent, True, False)

    def discard(self, x):
        cur = self.__left[0]
        parent = 0
        deleted = False
        while cur:
            value = self.__value[cur]
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
        self.__repair_upwards(cur, parent, False, True)
        return deleted

    def atleast(self, x):
        ans = None
        cur = self.__left[0]
        while cur:
            value = self.__value[cur]
            if value >= x:
                ans = value
                cur = self.__left[cur]
            else:
                cur = self.__right[cur]
        return ans

    def atmost(self, x):
        ans = None
        cur = self.__left[0]
        while cur:
            value = self.__value[cur]
            if value <= x:
                ans = value
                cur = self.__right[cur]
            else:
                cur = self.__left[cur]
        return ans

    def count_atmost(self, x):
        ans = 0
        cur = self.__left[0]
        while cur:
            if self.__value[cur] <= x:
                ans += self.__size[self.__left[cur]] + 1
                cur = self.__right[cur]
            else:
                cur = self.__left[cur]
        return ans