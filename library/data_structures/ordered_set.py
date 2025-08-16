from array import array
class OrderedSet:
    __slots__ = (
        "value",
        "left",
        "right",
        "size",
        "max_nodes",
        "nodes",
        "free",
        "multiset",
    )
    ALPHA = 0.85  # 0.5 (faster lookups) < ALPHA < 1 (faster modifications)

    def __init__(self, code=None, multiset=False):
        # start with index 1 being the free slot (we don't need to keep extra spot for value)
        self.value = array(code, [0]) if code else [None]
        self.left = array("i", [0, 0])
        self.right = array("i", [0, 0])
        self.size = array("i", [0, 0])
        self.max_nodes = 0
        self.nodes = 0
        self.free = 1
        self.multiset = multiset

    def __len__(self):
        return self.nodes

    def _compress(self, root, size):
        for _ in range(size):
            child = self.right[root]
            self.right[root] = self.right[child]
            root = self.right[root]
            self.right[child] = self.left[root]
            self.left[root] = child

    def _rebalance(self, root):
        size = self.size[root]
        dummy = self.free  # use the free spot for dummy node
        prev_free = self.left[dummy]
        self.left[dummy] = 0
        self.right[dummy] = root
        tail = dummy
        rest = self.right[tail]
        while rest:
            if self.left[rest]:
                tmp = self.left[rest]
                self.left[rest] = self.right[tmp]
                self.right[tmp] = rest
                rest = tmp
                self.right[tail] = tmp
            else:
                tail = rest
                rest = self.right[rest]
        leaves = size + 1 - (1 << (size + 1).bit_length() - 1)
        self._compress(dummy, leaves)
        size -= leaves
        while size > 1:
            size >>= 1
            self._compress(dummy, size)
        self.left[dummy] = self.right[dummy]
        self.right[dummy] = 0
        root = dummy
        while root:
            self.size[root] = 1
            if self.left[root]:
                cur = self.left[root]
                while self.right[cur] and self.right[cur] != root:
                    cur = self.right[cur]
                if self.right[cur]:
                    self.right[cur] = 0
                    parent = root
                    cur = self.left[root]
                    while cur:
                        nxt = self.right[cur]
                        self.right[cur] = parent
                        parent = cur
                        cur = nxt
                    while parent != root:
                        nxt = self.right[parent]
                        self.size[nxt] += self.size[parent]
                        self.right[parent] = cur
                        cur = parent
                        parent = nxt
                    root = self.right[root]
                else:
                    self.right[cur] = root
                    root = self.left[root]
            else:
                root = self.right[root]
        root = self.left[dummy]
        self.left[dummy] = prev_free
        return root

    def add(self, x):
        cur = self.left[0]
        parent = 0
        found = False
        while cur:
            value = self.value[cur]
            if x == value:
                found = True
            if x < value:
                nxt = self.left[cur]
                self.left[cur] = -parent - 1
            else:
                nxt = self.right[cur]
                self.right[cur] = -parent - 1
            parent = cur
            cur = nxt
        insert = not found or self.multiset
        if insert:
            cur = self.free
            prev_free = self.left[cur]
            if parent == 0:
                self.left[0] = cur
            self.left[cur] = self.right[cur] = 0
            self.size[cur] = 1
            if cur == len(self.value):
                self.value.append(x)
                self.left.append(0)
                self.right.append(0)
                self.size.append(0)
                self.free += 1
            else:
                self.value[cur] = x
                self.free = prev_free
            self.nodes += 1
            self.max_nodes = (
                self.nodes if self.nodes > self.max_nodes else self.max_nodes
            )
        while parent:
            left = self.left[parent]
            right = self.right[parent]
            if left < 0:
                self.left[parent] = cur
                cur = parent
                parent = -(left + 1)
            else:
                self.right[parent] = cur
                cur = parent
                parent = -(right + 1)
            left_size = self.size[self.left[cur]]
            right_size = self.size[self.right[cur]]
            self.size[cur] = left_size + right_size + 1
            weight_bound = OrderedSet.ALPHA * self.size[cur]
            if insert and (left_size > weight_bound or right_size > weight_bound):
                cur = self._rebalance(cur)
                insert = False
        self.left[0] = cur

    def delete(self, x):
        cur = self.left[0]
        parent = 0
        while cur:
            value = self.value[cur]
            if x < value:
                nxt = self.left[cur]
                self.left[cur] = -parent - 1
            elif x > value:
                nxt = self.right[cur]
                self.right[cur] = -parent - 1
            else:
                break
            parent = cur
            cur = nxt
        if cur:
            left = self.left[cur]
            right = self.right[cur]
            self.left[cur] = self.free
            self.free = cur
            if left and right:
                succ = succ_parent = self.right[cur]
                while self.left[succ]:
                    self.size[succ] -= 1
                    succ_parent = succ
                    succ = self.left[succ]
                if succ == right:
                    self.left[succ] = left
                    self.size[succ] += self.size[left]
                else:
                    self.left[succ_parent] = self.right[succ]
                    self.left[succ] = left
                    self.right[succ] = right
                    self.size[succ] = self.size[left] + self.size[right] + 1
                if cur == self.left[0]:
                    self.left[0] = succ
                cur = succ
            elif left:
                if cur == self.left[0]:
                    self.left[0] = left
                cur = left
            elif right:
                if cur == self.left[0]:
                    self.left[0] = right
                cur = right
            else:
                if cur == self.left[0]:
                    self.left[0] = 0
                cur = 0
            self.nodes -= 1
        while parent:
            left = self.left[parent]
            right = self.right[parent]
            if left < 0:
                self.left[parent] = cur
                cur = parent
                parent = -(left + 1)
            else:
                self.right[parent] = cur
                cur = parent
                parent = -(right + 1)
            self.size[cur] = self.size[self.left[cur]] + self.size[self.right[cur]] + 1
        if self.nodes <= OrderedSet.ALPHA * self.max_nodes:
            self.left[0] = self._rebalance(self.left[0])
            self.max_nodes = self.nodes

    def atleast(self, x):
        ans = None
        cur = self.left[0]
        while cur:
            value = self.value[cur]
            if value >= x:
                ans = value
                cur = self.left[cur]
            else:
                cur = self.right[cur]
        return ans

    def atmost(self, x):
        ans = None
        cur = self.left[0]
        while cur:
            value = self.value[cur]
            if value <= x:
                ans = value
                cur = self.right[cur]
            else:
                cur = self.left[cur]
        return ans

    def kth_smallest(self, k):
        ans = None
        cur = self.left[0]
        cnt = 0
        while cur:
            lsize = self.size[self.left[cur]]
            if cnt + lsize + 1 > k:
                ans = self.value[cur]
                cur = self.left[cur]
            else:
                cnt += lsize + 1
                cur = self.right[cur]
        return ans

    def count_atmost(self, x):
        ans = 0
        cur = self.left[0]
        while cur:
            if self.value[cur] <= x:
                ans += self.size[self.left[cur]] + 1
                cur = self.right[cur]
            else:
                cur = self.left[cur]
        return ans