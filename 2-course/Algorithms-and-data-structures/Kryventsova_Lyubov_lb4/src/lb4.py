B = 13
Q = 256

def get_hash(pattern: str) -> int:
    global B, Q
    length = len(pattern)
    result = 0
    for i in range(length):
        result = (B * result + ord(pattern[i])) % Q
    return result

def search_patterns_in_text(main_text: str, pattern: str):
    global B, Q
    pattern_len = len(pattern)
    main_text_len = len(main_text)
    result = []
    multiplier = 1
    for i in range(1, pattern_len):
        multiplier = (multiplier * B) % Q

    pattern_hash = get_hash(pattern)
    main_text_hash = get_hash(main_text[:pattern_len])

    for index_symbol in range(main_text_len - pattern_len + 1):
        if pattern_hash == main_text_hash:
            if main_text[index_symbol: index_symbol + pattern_len] == pattern:
                result.append(index_symbol)
        if index_symbol < main_text_len - pattern_len:
            main_text_hash = ((main_text_hash - ord(main_text[index_symbol]) * multiplier) * B + ord(
                main_text[index_symbol + pattern_len])) % Q

            if main_text_hash < 0:
                main_text_hash += Q
    return result

def pattern_test(test_string, pattern, answer):
    assert search_patterns_in_text(test_string, pattern) == answer,\
        "\nTest: {} in {}\nGot: {}\nExpected: {}"\
        .format(pattern, test_string, search_patterns_in_text(test_string, pattern),
                answer)

def test_for_search_patterns():
    pattern = "aba"
    test_string = "abacaba"
    answer = [0,4]
    pattern_test(test_string, pattern, answer)

    pattern = "findf"
    test_string = "findfindfindfind"
    answer = [0,4,8]
    pattern_test(test_string, pattern, answer)

    pattern = "!!"
    test_string = "!!!!!!"
    answer = [0, 1, 2, 3, 4]
    pattern_test(test_string, pattern, answer)

    pattern = "A#"
    test_string = "A#"
    answer = [0]
    pattern_test(test_string, pattern, answer)

    pattern = "ABCABC"
    test_string = "abcabc"
    answer = []
    pattern_test(test_string, pattern, answer)


s1 = input()
s2 = input()
print(" ".join(map(lambda a: str(a), search_patterns_in_text(s2, s1))))
test_for_search_patterns()

print("All tests were successfully passed")