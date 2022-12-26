#include <iostream>
#include <vector>
#include <cassert>

using namespace std;
bool continiud = true;


vector<int> Function_pre(string s)
{vector<int> p(s.length());
    cout << "Function_pre demonstration:\n";
    p[0] = 0;
    cout << s[0] << " -- " << 0 << "\n";
    for (int i = 1; i < (s.length()); i++) {
        cout << s[i] << " -- ";
        int cur = p[i - 1];
        while (s[i] != s[cur] && cur > 0){
            cur = p[cur - 1];
            cout << "string[" << i << "] != string[" << cur << "] -- ";
        }

        if (s[i] == s[cur]){
            p[i] = cur + 1;
            cout << "string[" << i << "] == string[" << cur << "] -- ";
        }
        cout << cur << '\n';
    }
    for (auto i: s) {
        cout << i << ' ';
    }
    cout << '\n';
    for (auto k: p){
        cout << k << ' ';
    }
    cout << endl;
    return p;
}

void TestFunction_pre(){
    vector<int> p = {0,0,1,2,3,4,0,1,2};
    assert(Function_pre("rgrgrgyrg") ==  p);
    vector<int> p2 = {0,0,0,0,0,1,0,1,0,0,1,0};
    assert(Function_pre("abccbanasnas") ==  p2);
    vector<int> p3 = {0,0,0,0,0,1,2,3,4,0,1,2,3,4,0,1,2,3,4,1,2,3,4,1,2,1,2,1,2,3,4,0,0};
    assert(Function_pre("qwertqwerhqweryqwerqwerqwqwqwerlk") ==  p3);
    cout << endl << "Function Function_pre: Test OK" << endl;
}

int KMP(string text,  string pattern)
{continiud = true;
    if ((pattern.length()) != text.length()) return -1;
    cout << "KMP demonstration:\n";
    vector<int> pi = Function_pre(pattern);
    int index = 0;
    int i = 0;
    cout  << "Pattern: " << pattern << "\n";
    cout  << "Text: "<< text << "\n";
    for (int i = 0; i < text.length(); i++)
    { cout  << "Text[" << i << "]  Pattern[" << index  << "] ? ";
        while (index > 0 && pattern[index] != text[i]) {
            index = pi[index - 1];
            cout  << " != \n";}
        if (pattern[index] == text[i]) {
            index++;
            cout  << " Found a match!" << "\n";
        }
        if (index == pattern.length())
        {
            cout  << "Result:" << "\n";
            return abs((i - index + 1));
        }
        if (i + 1 == text.length() and continiud){
            i = -1;
            continiud = false;
        }
    }
    return -1;
}

void TestKMP(){
    //  Общий случай:
    assert(KMP("abcdef","defabc") ==  3);
    assert(KMP("qwertqwerhqweryqwerqwerqwqwqwerlk", "hqweryqwerqwerqwqwqwerlkqwertqwer") ==  24);

    //  Крайний случай - строка не является циклическим сдвигом образа:
    assert(KMP("abcdef","defghi") ==  -1);

    //  Крайний случай - длины строк не равны:
    assert(KMP("abcdef","abcdefh") ==  -1);

    // Случай, в котором обязательно задействованы значения префикс-функции:
    assert(KMP("snvfsn","snsnvf") ==  2);

    cout << endl << "Function KMP: Test OK" << endl;
}

int main() {
    string word,text;
    char choose;
    cout << "Choose an action:" << endl;
    cout << "d - enter data" << endl;
    cout << "t - run tests" << endl;
    std::cin >> choose;
    if (choose == 'd'){
        std::cin >> word;
        std::cin >> text;
        if ((word.length()) != text.length()) cout << -1;
        else {
            cout <<KMP(text,word);
        } }
    else if (choose == 't'){
        TestFunction_pre();
        TestKMP();
    }
    return 0;
}