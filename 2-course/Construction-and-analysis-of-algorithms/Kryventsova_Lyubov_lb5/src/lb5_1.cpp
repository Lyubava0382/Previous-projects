#include <iostream>
#include <vector>
#include <map>
#define alphabet 5
class Node
{
public:
    char edgename;
    int pattern_count = 0;
    bool logical = false;
    int link = -1;
    int previous_node;
    int next_nodes[alphabet];
    int path[alphabet];
    Node(int prev, char name) : previous_node(prev), edgename(name)
    {
        for (int i = 0; i < alphabet; i++) { next_nodes[i] = -1; path[i] = -1; }
    }
};
class Bor
{   std::vector<Node> Bor_array;
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

    void result(std::vector <std::string>& arraystr, int node_count, int numstring, std::string string, std::vector<std::pair<int, int>> &res)
    {
        for (int i = node_count; i != 0; i = link_suff(i))
            if (Bor_array[i].logical)  res.push_back(std::make_pair(numstring - arraystr[Bor_array[i].pattern_count].size() + 1, Bor_array[i].pattern_count + 1));
    }
public:
    Bor()
    {
        Bor_array.push_back(Node(0, 0));
    }
    void node_add(std::map<char, int> symbols, int count, std::string string)
    {   int number = 0;
        int node;
        for (int index = 0; index < string.size(); index++)
        { char symbol = string[index];
            node = symbols[symbol];
            if (Bor_array[number].next_nodes[node] == -1){
                Bor_array.push_back(Node(number, node));
                Bor_array[number].next_nodes[node] = Bor_array.size() - 1;
            }
            number = Bor_array[number].next_nodes[node];
        }
         Bor_array[number].logical = true;
        Bor_array[number].pattern_count = count;
    }
    void node_find(std::vector<std::string> array, std::string string, std::map<char, int> alphabets, std::vector<std::pair<int, int>> &res)
    {   int count_letter = 0;
        for (int index = 0; index < string.size(); index++)
        {   char letter = string[index];
            int s_edge = alphabets[letter];
            count_letter = next_node(count_letter, s_edge);
            result(array, count_letter, index + 1, string, res);
        }
    }};

int main()
{ std::map<char, int> letters{
        {'A', 0},
        {'C', 1},
        {'G', 2},
        {'T', 3},
        {'N', 4} };
    Bor Bor1;
    std::string document;
    int count;
    std::cin >> document >> count;
    std::string pattern;
    std::vector<std::string> pattern_array;
    std::vector<std::pair<int, int>> results;
    for (int index = 0; index < count; index++)
    {   std::cin >> pattern;
        Bor1.node_add(letters, index, pattern);
        pattern_array.push_back(pattern);  }
    Bor1.node_find(pattern_array, document, letters, results);
    sort(results.begin(), results.end());
    for (int index = 0; index < results.size(); index++)  std::cout << results[index].first << ' ' << results[index].second << std::endl;
    return 0;
}
