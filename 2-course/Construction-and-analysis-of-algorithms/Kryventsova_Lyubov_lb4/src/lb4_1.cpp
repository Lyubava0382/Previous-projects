#include <iostream>
#include <vector>
#include <cassert>
#define MAX 55000000
using namespace std;
bool continiud = true;
int pos[MAX];
int ptr = 0;

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
{ ptr = 0;
    cout << "KMP demonstration:\n";
    vector<int> pi = Function_pre(pattern);
    int index = 0;
    cout  << "Pattern: " << pattern << "\n";
    cout  << "Text: "<< text << "\n";
    for (int i = 0; i < text.length(); i++)
    {cout  << "Text[" << i << "]  Pattern[" << index  << "] ? ";
        while (index > 0 && pattern[index] != text[i]) {
            index = pi[index - 1];
            cout  << " != \n";}
        if (pattern[index] == text[i]){
            index++;
            cout  << " Found a match!" << "\n";
        }
        if (index == pattern.length())
        {
            cout <<"Found a word! = " << i - index + 1 << "\n";
            cout <<"!!!!!!!!!!!!!!!!!\n";
            pos[ptr++] =  i - index + 1;
        }
    }
}

void TestKMP(){
    //  Общий случай:
    int realpos[] = {0,5,10,15,19,27};
    KMP("qwertqwerhqweryqwerqwerqwqwqwerlk", "qwer");
    assert( pos[0] == realpos[0] and pos[1] == realpos[1]
            and pos[2] == realpos[2]
            and pos[3] == realpos[3]
            and  pos[4] == realpos[4]
            and  pos[5] == realpos[5]);
    
	// Крайний случай - нет вхождений:
    KMP("qwertqwerhqweryqwerqwerqwqwqwerlk", "qwerty");
    assert(ptr ==  0);
    
	// Крайний случай - длинна образа больше длины строки:
    KMP("abc", "abcabcabc");
    assert(ptr ==  0);
    
	// Случай, в котором обязательно задействованы значения префикс-функции:
    KMP("htyjhtyht", "htyht");
    assert(pos[0] == 4);

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
        KMP(text,word);
        for(int i = 0; i < ptr; i++)
        {
            if (i) std::cout << ',';

            cout <<pos[i];
        }
        if (ptr == 0) cout << -1;
        return 0; }
    else if (choose == 't'){
        TestFunction_pre();
        TestKMP();
    }
    return 0;
}