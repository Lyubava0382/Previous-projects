import graphviz
import functools

BLACK = 'black'
RED = 'red'

@functools.total_ordering

class Node:
    def __init__(self, key = None, color = BLACK, parent=None, left=None, right=None):
        self.key = key
        self.parent = parent
        self.left = left
        self.right = right
        self.color = color

    def __eq__(self, other):
        return self.key == other.key

    def __lt__(self, other):
        return self.key < other.key

    def __bool__(self):
        return self.key is not None

    def __str__(self):
        left = self.left.key if self.left else None
        right = self.right.key if self.right else None
        parent = self.parent.key if self.parent else None
        return 'key: {}, left: {}, right: {}, color: {}, parent: {}'.format(self.key, left, right, self.color, parent)

    def Grandfather(self):
        if self.parent:
            return self.parent.parent
        return None

    def Uncle(self):
        gp = self.Grandfather()
        if not gp:
            return None
        if gp.left and self.parent == gp.left:
            return gp.right
        if gp.right and self.parent == gp.right:
            return gp.left

def BreadthSearch(root, dot):
    tree = [root]
    dot.node(str(root.key), color=root.color)
    while tree:
        unit = []
        for element in tree:
            if element.left and element.left.key:
                dot.node(str(element.left.key), color=element.left.color)
                dot.edge(str(element.key), str(element.left.key))
                unit.append(element.left)
            if element.right and element.right.key:
                dot.node(str(element.right.key), color=element.right.color)
                dot.edge(str(element.key), str(element.right.key))
                unit.append(element.right)
        tree = unit



class RBTree:
    def __init__(self, key=None, color=BLACK, parent=None, left=None, right=None):
        self.root = None
        self.nil = Node()

    def LeftRotate(self, node):
        right = node.right
        if node.parent:
            if node > node.parent:
                node.parent.right = right
            else:
                node.parent.left = right
        else:
            self.root = node.right
        right.parent = node.parent
        node.parent = right
        node.right = right.left
        if right.left:
            right.left.parent = node
        right.left = node

    def RightRotate(self, node):
        left = node.left
        if node.parent:
            if node > node.parent:
                node.parent.right = node.left
            else:
                node.parent.left = node.left
        else:
            self.root = node.left
        left.parent = node.parent
        node.parent = left
        node.left = left.right
        if left.right:
            left.right.parent = node
        left.right = node

    def _find(self, key, root):
        current = root
        if key == current.key:
            return root
        while current.key and not key == current.key:
            if key > current.key:
                if current.right:
                    current = current.right
                else:
                    return current
            elif key < current.key:
                if current.left:
                    current = current.left
                else:
                    return current
        return current

    def Find(self, key):
        res = self._find(key, self.root)
        if res.key == key:
            return res
        return None

    @staticmethod
    def Next(node):
        if node.right:
            node = node.right
            while node.left:
                node = node.left
            return node
        while node.parent:
            if node.parent > node:
                break
            node = node.parent
        return node.parent

    def Insert(self, key):
        if not self.root:
            self.root = Node(key, BLACK, None, self.nil, self.nil)
            return

        node = self._find(key, self.root)
        if key == node.key:
            return

        if key > node.key:
            node.right = Node(key, RED, node, self.nil, self.nil)
            node = node.right
        elif key < node.key:
            node.left = Node(key, RED, node, self.nil, self.nil)
            node = node.left

        self.FixTree_INSERT(node)

    def Remove(self, key):
        if not self.root:
            return
        node = self._find(key, self.root)
        if node.key != key:
            return
        if not node.left or not node.right:
            y = node
        else:
            y = self.Next(node)

        if y.left:
            x = y.left
        else:
            x = y.right
        x.parent = y.parent
        if y.parent:
            if y == y.parent.left:
                y.parent.left = x
            else:
                y.parent.right = x
        else:
            self.root = x
        if y != node:
            node.key = y.key
        if y.color == BLACK:
            self.FixTree_REMOVE(x)

    def  FixTree_INSERT(self, node):
        p = node.parent
        if not p:
            node.color = BLACK
            return
        u = node.Uncle()
        g = node.Grandfather()
        if p.color == BLACK:
            return
        if u and u.color == RED:
            p.color = BLACK
            u.color = BLACK
            g.color = RED
            self.FixTree_INSERT(g)
            return
        if p.right and p.right == node and g.left and p == g.left:
            self.LeftRotate(p)
            node = node.left
        elif p.left and p.left == node and g.right and p == g.right:
            self.RightRotate(p)
            node = node.right
        p = node.parent
        g = node.Grandfather()
        p.color = BLACK
        g.color = RED
        if p.left and p.left == node and g.left and p == g.left:
            self.RightRotate(g)
        else:
            self.LeftRotate(g)

    def FixTree_REMOVE(self, node):
        while self.root and node.parent and node.color == BLACK:
            if node == node.parent.left:
                brother = node.parent.right
                if brother.color == RED:
                    brother.color = BLACK
                    node.parent.color = RED
                    self.LeftRotate(node.parent)
                    brother = node.parent.right
                if brother.left.color == BLACK and brother.right.color == BLACK:
                    brother.color = RED
                    node = node.parent
                else:
                    if brother.right.color == BLACK:
                        brother.left.color = RED
                        brother.color = BLACK
                        self.RightRotate(brother)
                        brother = node.parent.right
                    brother.color = node.parent.color
                    node.parent.color = RED
                    brother.right.color = RED
                    self.LeftRotate(node.parent)
                    node = self.root
            elif node == node.parent.right:
                brother = node.parent.left
                if brother.color == RED:
                    brother.color = BLACK
                    node.parent.color = RED
                    self.RightRotate(node.parent)
                    brother = node.parent.left
                if brother.right.color == BLACK and brother.left.color == BLACK:
                    brother.color = RED
                    node = node.parent
                else:
                    if brother.left.color == BLACK:
                        brother.right.color = BLACK
                        brother.color = RED
                        self.LeftRotate(brother)
                        brother = node.parent.left
                    brother.color = node.parent.color
                    node.parent.color = BLACK
                    brother.left.color = BLACK
                    self.RightRotate(node.parent)
                    node = self.root
        node.color = BLACK

def main():
    nodes = list(map(int, input().split()))
    rb_tree = RBTree()
    for index, node in enumerate(nodes):
        dot = graphviz.Digraph()
        rb_tree.Insert(node)
        BreadthSearch(rb_tree.root, dot)
        dot.render('g{}.gv'.format(index))

    rb_tree.Remove(5)
    print(rb_tree.Find(5))
    print(rb_tree.Find(3))

main()