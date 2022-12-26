#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#define alphabet 5
class Node
{
public:
    char edgename;
    std::vector<int> position;
    bool logical = false;
    int link = -1;
    int previous_node;
    int next_nodes[alphabet];
    int path[alphabet];
    Node(int prev, char name) : previous_node(prev), edgename(name)
    {position.resize(0); {
        for (int i = 0; i < alphabet; i++) { next_nodes[i] = -1; path[i] = -1; }
    }}
};
class Bor
{   std::vector<Node> Bor_array;
    std::vector<std::string> patterns;
    int link_suff(int node_count)
    {    if (Bor_array[node_count].link == -1)
        {   if (node_count == 0 || Bor_array[node_count].previous_node == 0)
                Bor_array[node_count].link = 0;
            else
                Bor_array[node_count].link = next_node(link_suff(Bor_array[node_count].previous_node),
                                                             Bor_array[node_count].edgename);}
        return Bor_array[node_count].link;
    }

    int next_node(int node_count, int name)
    {   if (Bor_array[node_count].path[name] == -1){
            if (Bor_array[node_count].next_nodes[name] != -1)
                Bor_array[node_count].path[name] = Bor_array[node_count].next_nodes[name];
            else
                if (node_count == 0)
                    Bor_array[node_count].path[name] = 0;
                else Bor_array[node_count].path[name] = next_node(link_suff(node_count), name);
        }
        return Bor_array[node_count].path[name];
    }
    void result(int node, int i, std::vector<int>& extraarray, std::vector<int> len_of_pattern)
    { for (int n = node; n != 0; n = link_suff(n)) {
            if (Bor_array[n].logical) {
                for (const auto& j : Bor_array[n].position)
                    if ((i - len_of_pattern[j] < extraarray.size())) extraarray[i - len_of_pattern[j]]++;
            } } }
public:
    Bor()
    {
        Bor_array.push_back(Node(0, 0));
    }
    void node_add(std::map<char, int> symbols, std::string string){   int number = 0;
        int node;
        for (int index = 0; index < string.size(); index++) {
            char letter = string[index];
            node = symbols[letter];
            if (Bor_array[number].next_nodes[node] == -1) {
                Bor_array.push_back(Node(number, node));
                Bor_array[number].next_nodes[node] = Bor_array.size() - 1;
            }
            number = Bor_array[number].next_nodes[node];
        }
            Bor_array[number].logical = true;
            patterns.push_back(string);
            Bor_array[number].position.push_back(patterns.size() - 1);
        }
    void node_find(std::map<char, int> letters, std::string& string,
                   std::vector <int>& extraarray, const std::vector <int>& len_of_pattern)
    {   int n = 0;
        for (int index = 0; index < string.length(); index++)
        {   char symbol = string[index];
            int node = letters[symbol];
            n = next_node(n, node);
            result(n, index + 1, extraarray, len_of_pattern);
        }
    }
    std::vector<int> pattern(std::map<char, int> letters, std::stringstream& pattern, char jester)
    {   std::vector<int> len_of_patterns;
        int len = 0;
        std::string cast;
        while (getline(pattern, cast, jester))
        { if (cast.size() > 0)
            {  len += cast.size();
                len_of_patterns.push_back(len);
                node_add(letters, cast);
            } len++;
        }
        return len_of_patterns;
    }
    void print(const std::vector<int>& extraarray, int size, int len)
    {
        for (int i = 0; i < size; i++)
            if ((extraarray[i] == patterns.size()) && (i + len <= size))  std::cout << i + 1 << std::endl;
    }};

int main()
{ std::map<char, int> letters{
        {'A', 0},
        {'C', 1},
        {'G', 2},
        {'T', 3},
        {'N', 4} };
    Bor Bor1;
    std::string string;
    std::string pattern;
    std::vector<int> len_of_patterns;
    char jester;
    std::cin >> string >> pattern >> jester;
    std::stringstream stream(pattern);
    len_of_patterns = Bor1.pattern(letters, stream, jester);
    std::vector<int> extraarray(string.size(), 0);
    Bor1.node_find(letters, string, extraarray, len_of_patterns);
    Bor1.print(extraarray, string.size(), pattern.size());
    return 0;
}
