#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

struct edge{
    char r1;
    char r2;
    int weight;
    int real_w;
    bool direction;
    bool open_forward;
    bool open_back;
};

vector<edge> current = {};
vector<edge> graph = {};
char start, finish;
bool continiud = true, sign = false;
int result = 0, wt = 0;

void mysort(){
    edge temp;
    for (int i = 0; i < graph.size() - 1; i++) {
        for (int j = 0; j < graph.size() - i - 1; j++) {
            if (int(graph[j].r1) > int(graph[j + 1].r1)) {
                temp = graph[j];
                graph[j] = graph[j + 1];
                graph[j + 1] = temp;
            }
            else if (int(graph[j].r1) == int(graph[j + 1].r1)){
                if (int(graph[j].r2) > int(graph[j + 1].r2)) {
                    temp = graph[j];
                    graph[j] = graph[j + 1];
                    graph[j + 1] = temp;
                }
            }
        }
    }
}
void TestMysort(){
    graph.erase(graph.begin(), graph.end());
    graph = {{'n','x'},
            {'n','g'},
             {'d', 'r'}};
    mysort();
    assert(graph[0].r1 == 'd' and graph[0].r2 == 'r');
    assert(graph[1].r1 == 'n' and graph[1].r2 == 'g');
    assert(graph[2].r2 == 'x');
    graph.push_back({'a','b'});
    graph.push_back({'y','x'});
    mysort();
    assert(graph[graph.size()-1].r1 == 'y' and graph[graph.size()-1].r2 == 'x');
    cout << endl << "Function mysort: Test OK" << endl;
}

int minimum_curr_weight(){
    int min;
    if (current[0].direction) min = current[0].weight;
    else min = current[0].real_w;
    for (int i = 1; i < current.size(); i++){
        if (current[i].direction and current[i].weight < min){
            min = current[i].weight;
        }

        if  (!current[i].direction and current[i].real_w < min){
            min = current[i].real_w;
        }
    }
    return min;
}

void TestMinimum_curr_weight(){
    current.erase(current.begin(), current.end());
   current = {{'n','x', 35, 51, true, true, true}
    ,{'n','x', 95, 81, true, true, true},
    {'m', 'w', 33, 46, true, true, true}};
    assert(minimum_curr_weight() == 33);
    current.push_back({'a','n', 4, 7, true, true, true});
    assert(minimum_curr_weight() == 4);
    cout << endl << "Function minimum_curr_weight: Test OK" << endl;
}

bool Collision(char node){
    for (int i = 0; i < current.size(); i++){
        if (current[i].r1 == node or current[i].r2 == node){
            return false;
        }
    }
    return true;
}
void TestCollision(){
    current.erase(current.begin(), current.end());
    current = {{'a', 'b'},{'b','c'},{'c','d'}};
    assert(Collision('k'));
    assert(Collision('m'));
    current.push_back({'d','m'});
    assert(!Collision('c'));
    assert(!Collision('m'));
    assert(!Collision('a'));
    cout << endl << "Function Collision: Test OK" << endl;
}

int into_index(char node){
    int minindex = -1; int t = 0, min = -1;
    for (int i = 0; i < graph.size(); i++)
        min = min + static_cast<int>(graph[i].r1) + static_cast<int>(graph[i].r2);
    for (t = 0; t <= graph.size(); t++){
        if ((graph[t].r1 == node and Collision(graph[t].r2))
                and graph[t].open_forward and graph[t].weight > 0
                and static_cast<int>(graph[t].r2) < min){
            minindex = t;
            min = static_cast<int>(graph[t].r2);
        }
        else if (graph[t].r2 == node and Collision(graph[t].r1)
                 and graph[t].open_back
                 and graph[t].real_w > 0
                 and static_cast<int>(graph[t].r1) < min) {
            minindex = t;
            min = static_cast<int>(graph[t].r1);
        }
    }
    if (minindex < 0) return -1;
    if (graph[minindex].r2 == node) graph[minindex].direction = false;
    return minindex;
}

void TestInto(){
    graph.erase(graph.begin(), graph.end());
    current.erase(current.begin(), current.end());
    current = {};
    graph = {{'a', 'b', 3,1, true, true},
             {'b','c',2, 0, true,true,true},
             {'a','c',1,1, true,true, true}};
    assert(into_index('a') == 0);
    assert(into_index('c') == 2);
    graph.push_back({'a','a',3});
    assert(into_index('m') == -1);
    graph.push_back({'d','e',0,0});
    assert(into_index('e') == -1);
    cout << endl << "Function into_index: Test OK" << endl;
}

void recurs(char node){
    edge curredge;
    int index;
    if (node == start) continiud = true;
    else continiud = false;
    do{
        index = into_index(node);
        if (index < 0) {
            sign = true;
            return;
        }
        curredge = graph[index];
        if (curredge.weight != 0 and curredge.r1 == node
                                     or curredge.real_w != 0 and curredge.r2 == node){
            current.push_back(curredge);
            if (curredge.r1 == finish or curredge.r2 == finish){
                wt = minimum_curr_weight();
                result += wt;
            }
            else {
                if (curredge.r1 == node) recurs(curredge.r2);
                else if (curredge.r2 == node) {
                    recurs(curredge.r1);
                }
                if (sign) {
                    if (graph[index].direction) {graph[index].open_forward = false;
                        curredge.open_forward = false;}
                    else {
                        graph[index].open_back = false;
                        curredge.open_back = false;
                    }
                    sign = false;
                }
            }
            if (curredge.r1 == node) {
                graph[index].weight -= wt;
                graph[index].real_w += wt;
                curredge.weight -= wt;
                curredge.real_w += wt;
            }
            else if (curredge.r2 == node) {
                graph[index].weight += wt;
                graph[index].real_w -= wt;
                curredge.weight += wt;
                curredge.real_w -= wt;
                graph[index].direction = true;
            }
            current.pop_back();
        }
        if (node == start) {
            continiud = true;
            wt = 0;
        }
    }
    while (curredge.r1 != finish and curredge.r2 != finish and !sign and
           continiud);
}

void TestRecurs(){
    graph.erase(graph.begin(), graph.end());
    current.erase(current.begin(), current.end());
    current = {};
    start = 'a', finish = 'c';
    continiud = true; sign = false;
    result = 0; wt = 0;
    graph = {{'a', 'b', 20,0, true, true, true},
             {'a','d',40, 0, true,true,true},
             {'a','e',30,0, true,true, true},
             {'e', 'd', 50,0, true, true},
             {'e','c',40, 0, true,true,true},
             {'d','b',20,0, true,true, true},
             {'d', 'c', 30,0, true, true},
             {'b','c',30, 0, true,true,true}
    };
    mysort();
    recurs(start);
    assert(result == 90);
    graph.erase(graph.begin(), graph.end());
    current.erase(current.begin(), current.end());
    current = {};
    start = 'a', finish = 'e';
    graph = {{'a', 'b', 20,0, true, true},
             {'b','a',20, 0, true,true,true},
             {'a','d',10,0, true,true, true},
             {'d', 'a', 10,0, true, true},
             {'a','c',30, 0, true,true,true},
             {'c','a',30,0, true,true, true},
             {'b', 'c', 40,0, true, true},
             {'c','b',40, 0, true,true,true},
             {'c', 'd', 20,0, true, true},
             {'d','c',20, 0, true,true,true},
             {'c','e',20,0, true,true, true},
             {'e', 'c', 20,0, true, true},
             {'b','e',30, 0, true,true,true},
             {'e','b',30,0, true,true, true},
             {'d', 'e', 10,0, true, true},
             {'e','d',10, 0, true,true,true}
    };
    result = 0; wt = 0;
    mysort();
    recurs(start);
    assert(result == 60);
    cout << endl << "Function recurs: Test OK" << endl;
}

int main() {
    int count = 0; char choose;
    cout << "Choose an action:" << endl;
    cout << "d - enter data" << endl;
    cout << "t - run tests" << endl;
    std::cin >> choose;
    if (choose == 'd'){
        std::cin >> count >> start >> finish;
        for (int i = 0; i < count; i++){
            edge a;
            std::cin >> a.r1 >> a.r2 >> a.weight;
            a.real_w = 0;
            a.direction = true;
            a.open_forward = true;
            a.open_back = true;
            graph.push_back(a);
        }
        mysort();
        recurs(start);
        cout << result << endl;
        for (int t = 0; t < graph.size();t++){
            cout << graph[t].r1 << ' ' << graph[t].r2
                 << ' ' << graph[t].real_w << endl;
        }
    }
        else if (choose == 't'){
        TestMysort();
        TestMinimum_curr_weight();
        TestCollision();
        TestInto();
        TestRecurs();
        }
            else return 0;

    return 0;
}

