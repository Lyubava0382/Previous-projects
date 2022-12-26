intermediate_result = []
def merge_sorting(array):
    global intermediate_result
    done_array = []
    if len(array) == 1:
        return array
    center = len(array) // 2
    before_index = 0
    after_index = 0
    before_center = merge_sorting(array[:center])
    after_center = merge_sorting(array[center:])
    while (before_index < len(before_center) or after_index < len(after_center)):
        if before_index == len(before_center):
            done_array.extend(after_center[after_index:])
            after_index = len(after_center)
        elif after_index == len(after_center):
            done_array.extend(before_center[before_index:])
            before_index = len(before_center)
        elif before_center[before_index][1] <= after_center[after_index][1]:
            done_array.append(before_center[before_index])
            before_index += 1
        elif before_center[before_index][1] > after_center[after_index][1]:
            done_array.append(after_center[after_index])
            after_index += 1
    intermediate_result.append([j[0] for j in done_array])
    print(" ".join(map(lambda a: str(a[0]), done_array)))
    return done_array


def calculate_sums_of_main_diagonal():
    sums_of_main_diagonal = 0
    dimension_of_matrix = int(input())
    for diagonal_element in range(dimension_of_matrix):
        sums_of_main_diagonal += int(input().split()[diagonal_element])
    return sums_of_main_diagonal


count_of_matrices = int(input())
sorting_array = []
for matrix_number in range(count_of_matrices):
    sorting_array.append((matrix_number, calculate_sums_of_main_diagonal()))
print(" ".join(map(lambda a: str(a[0]), merge_sorting(sorting_array))))

def pattern_test_for_sorting(test_array, answer):
    global intermediate_result
    intermediate_result.clear()
    assert [j[0] for j in merge_sorting(test_array)] == answer[1] and intermediate_result == answer[0], "\nTest: {}\nGot: {}\nExpected: {}" .format(test_array, [j[0] for j in merge_sorting(test_array)],answer[1])


def test_for_sorting():
    test_array = [(0, 1), (1, 2), (2, 3)]
    answer = ([[1, 2], [0, 1, 2]], [0, 1, 2])
    pattern_test_for_sorting(test_array, answer)

    test_array = [(0, 0), (1, 0)]
    answer = ([[0, 1]],[0, 1])
    pattern_test_for_sorting(test_array, answer)

    test_array = [(0, 65), (1, -365), (2, 65), (3, -365)]
    answer = ([[1, 0], [3, 2], [1, 3, 0, 2]], [1, 3, 0, 2])
    pattern_test_for_sorting(test_array, answer)

test_for_sorting()

print("All tests were successfully passed")

