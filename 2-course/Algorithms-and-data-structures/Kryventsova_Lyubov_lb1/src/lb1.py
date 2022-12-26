
def find_tree_height(tree, root, height, result, ind):
    height += 1
    try:
        child = tree.index(root, ind)
    except ValueError:
        result = max(result, height)
        return result
    try:
        brother = tree.index(root, child+1)
    except ValueError:
        brother = -1
    if brother >= 0:
        result = max(result, find_tree_height(tree, root, height-1, result, child+1))
    result = max(result, find_tree_height(tree, child, height, result, 0))
    return result

count = int(input())
tree = [int(i) for i in input().split()]
print(find_tree_height(tree, int(tree.index(-1)), 0, 0, 0))

def pattern_test_for_tree(test_tree, answer):
    assert find_tree_height(test_tree,int(test_tree.index(-1)), 0, 0, 0) == answer,\
        "\nTest: {}\nGot: {}\nExpected: {}"\
        .format(test_tree, find_tree_height(test_tree,int(test_tree.index(-1)), 0, 0, 0),
                answer)

def test_for_tree():
    test_tree = [4, -1, 4, 1, 1]
    answer = 3
    pattern_test_for_tree(test_tree, answer)

    test_tree = [1, 2, 3, 4, 5, -1, 4, 3, 3, 6]
    answer = 6
    pattern_test_for_tree(test_tree, answer)

    test_tree = [0, 0, 0, -1, 2, 3, 4, 5, 5, 5, 5, 5, 8, 9]
    answer = 4
    pattern_test_for_tree(test_tree, answer)

    test_tree = [-1, -99, 139, 0, 11]
    answer = 2
    pattern_test_for_tree(test_tree, answer)

test_for_tree()

print("All tests were successfully passed")
