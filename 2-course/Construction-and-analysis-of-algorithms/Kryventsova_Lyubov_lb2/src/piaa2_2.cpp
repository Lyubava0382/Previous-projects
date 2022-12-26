#include <iostream>
#include <vector>
#include <cstring>
#include <math.h>
#include <cassert>
using namespace std;


struct edge{
    char letter;
    float g = 0; // Расстояние от начала до вершины
    float f = 0; // Расстояние + эвристический вес
    float h = 0;
    vector <pair<char,float> > neighbours = {};
    bool open = false; //Находится ли вершина в очереди
    bool closed = false; // Пройдена ли вершина
    int from = -1;
};

vector<edge> graph = {}; //Список вершин
vector<int> closed; //Список пройдённых вершин
vector<int> open; // Очередь вершин
int start, finish;
char char_start, char_finish;

int find( char lttr){
    for (int i = 0; i < graph.size(); i++){
        if (graph[i].letter == lttr)
            return i;
    }
    return -1;
}

void Testfind(){
    graph.erase(graph.begin(), graph.end());
    graph = {{'a'},{'b'},{'c'},{'d'}};
    assert(find('k') == -1);
    graph.push_back({'e'});
    assert(find('e') == 4);
    assert(find('c') == 2);
    assert(find('a') == 0);
    cout << endl << "Function find: Test OK" << endl;
}

void delete_open( int index){
    for (int i = 0; i < open.size(); i++){
        if (open[i] == index)
            open.erase(open.begin() + i);
    }
}

void Test_delete(){
    int test = 0, i = 0;
    while (open.size() > 0){
        //i = open.size() - 1;
        test = open[i];
        assert(std::find(open.begin(),
                         open.end(), test) != open.end());
        delete_open(test);
        assert(std::find(open.begin(),
                         open.end(), test) == open.end());
    }
    cout << endl << "Function delete_open: Test OK" << endl;
}

float h(char a, char b){ // Эвристическая функция
    return abs(static_cast<float>(a) - static_cast<float>(b));
}

void Test_h(){
    assert(h('x','y') == 1);
    assert(h('a','z') == 25);
    assert(h('e','e') == 0);
    assert(h('f','b') == 4);
    cout << endl << "Function heuristic: Test OK" << endl;
}

int min_f(){
    if (open.empty()) return -1;
    float min = graph[open[0]].f;
    int index_min = open[0];
    for(int i = 0; i < open.size(); i++){
        if (graph[open[i]].f < min ||
            ( graph[open[i]].f == min &&
              static_cast<float>(graph[open[i]].letter) <
              static_cast<float>(graph[open[i]].letter))) {
            min = graph[open[i]].f;
            index_min = open[i];
        }
    }
    return index_min;
}

void Test_minf(){
    open.erase(open.begin(), open.end());
    assert(min_f() == -1);

    graph = {{'a',0, 1, 1}};
    open = {0};
    assert(min_f() == 0);

    graph = {{'a',0, 1, 1},
             {'b', 1, 2, 1},
             {'c', 2, 3, 1},
             {'d', 3, 4, 1},
            {'e', 4, 4, 0},
             {'f', 2, 5, 3},
             {'g', 8, 8, 0},
             {'h',0, 1, 1}};
    open = {1,2,3,4};
    assert(min_f() == 1);
    open = {3,4};
    assert(min_f() == 3);
    open = {1,2,3,4,5,6,7};
    assert(min_f() == 7);
    cout << endl << "Function min_f: Test OK" << endl;
}


int a_star(){
    int current;
    pair<char,float> neighbour;
    open.push_back(start);
    graph[start].open = true;
    graph[start].g = 0;  graph[start].f =  graph[start].g
                                           + graph[start].h;
    while (open.size() >= 0){
        current = min_f();
        if (current == finish) return current;
        delete_open(current);
        graph[current].open = false;
        closed.push_back(current);
        graph[current].closed = true;
        int count_neigh = 0;
        while (graph[current].neighbours.size() > count_neigh){
            neighbour = graph[current].neighbours[count_neigh];
            int neigh_index = find(neighbour.first);
                float temp_g = graph[current].g + neighbour.second;
                if (!graph[neigh_index].open && !graph[neigh_index].closed || temp_g < graph[neigh_index].g){
                    graph[neigh_index].from = current;
                    graph[neigh_index].g = temp_g;
                    graph[neigh_index].f = graph[neigh_index].g + graph[neigh_index].h;
                }
                if (!graph[neigh_index].open && !graph[neigh_index].closed) {
                    graph[neigh_index].open = true;
                    open.push_back(neigh_index);
                }

            count_neigh++;
        }
    }
    return -1;
}

void Test_a(){
    vector<char> result;
    vector<char> right_result;
    closed = {}; //Список пройдённых вершин
    open = {}; // Очередь вершин
    start = 0;
    finish = 3;
     char_start = 'a';
     char_finish = 'd';
    graph = {{'a',0, 0, 1,
              {{'b', 1}}},
             {'b', 0, 0, 2,
                     {{'c', 2}}},
             {'c', 0, 0, 3,
                     {{'d', 3}}},
             {'d', 0, 0, 4,
                     {{'a', 1}}}};
    right_result = {'a','b','c','d'};
   int goal = a_star();
    if ( goal < 0 )  result = {};
    else {result.emplace(result.begin(), graph[goal].letter);
        while(graph[goal].from >= 0){
            goal = graph[goal].from;
            result.emplace(result.begin(), graph[goal].letter);}
}
    assert(result == right_result);

    result = {};
    closed = {}; //Список пройдённых вершин
    open = {}; // Очередь вершин
    start = 0;
    finish = 5;
    char_start = 'n';
    char_finish = 'a';
    graph = {{'n',0, 0, 20,
                     {{'m', 1}, {'c', 20}}},
             {'m', 0, 0, 19,
                     {{'l', 1}}},
             {'l', 0, 0, 18,
                     {{'c', 1}}},
             {'c', 0, 0, 2,
                     {{'b', 1}}},
             {'b', 0, 0, 1,
                     {{'a', 20}}},
             {'a', 0, 0, 0,
                     {}}};
    right_result = {'n', 'm', 'l', 'c', 'b', 'a'};
    goal = a_star();
    if ( goal < 0 )  result = {};
    else {result.emplace(result.begin(), graph[goal].letter);
        while(graph[goal].from >= 0){
            goal = graph[goal].from;
            result.emplace(result.begin(), graph[goal].letter);}
    }
    assert(result == right_result);

    cout << endl << "Function a_star: Test OK" << endl;
}


int main() {
    vector<char> result;
    int count;
    std::cin >> char_start >> char_finish >> count;
    for (int m = 0; m < count; m++){
        edge node;
        std::cin >> node.letter;
        char node2; float distance;
        std::cin >> node2 >> distance;
        int findletter = find(node.letter);
        if (findletter >= 0) {
            graph[findletter].neighbours.emplace_back(make_pair(node2,distance));
        }
        else {
            node.neighbours.emplace_back(make_pair(node2,distance));
            graph.push_back(node);
        }
        int findletter2 = find(node2);
        if (findletter2 < 0) {
            edge new_node;
            new_node.letter = node2;
            graph.push_back(new_node);
        }
    }
    for (int l = 0; l < count; l++){
        cout << "Heuristics for vertex " << graph[l].letter << ":\n";
        cin >> graph[l].h;
    }
    start = find(char_start);
    finish = find(char_finish);
    int goal = a_star();
    if ( goal < 0 ) return 0 ;
    result.emplace(result.begin(), graph[goal].letter);
    while(graph[goal].from >= 0){
        goal = graph[goal].from;
        result.emplace(result.begin(), graph[goal].letter);
    }
    for (int loop = 0; loop < result.size(); loop++)
        cout << result[loop];
    Testfind();
    Test_h();
    Test_delete();
    Test_minf();
    Test_a();
    return 0;
}
