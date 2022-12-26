#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

struct edge{
    char r1;
    char r2;
    float weight;
};

vector<edge> current = {};
vector<edge> mass = {};
char start, finish;
bool continiud = true;

bool Collision(edge point){
    for (int i = 0; i < current.size(); i++){
        if (point.r1 == current[i].r1 &&
            point.r2 == current[i].r2 &&
            point.weight == current[i].weight)
            return false;
    }
    return true;
}

void mysort(){
    edge temp;
    for (int i = 0; i < mass.size() - 1; i++) {
        for (int j = 0; j < mass.size() - i - 1; j++) {
            if (mass[j].weight > mass[j + 1].weight) {
                temp = mass[j];
                mass[j] = mass[j + 1];
                mass[j + 1] = temp;
            }
        }
    }
}

int recurs(char node) {
    float k = 0; char node1 = start;
    if (node == finish) {
        continiud = false;
        return 0;
    }
    else {
        if (current.size() != 0)
            node1 = current.back().r2;
        while (node1 != finish && k < mass.size() && continiud) {
            while (k < mass.size() && (mass[k].r1 != node)) {
                k++;
            }
            if (k < mass.size()) {
                if (Collision(mass[k])) {
                    current.push_back(mass[k]);
                    recurs(current.back().r2);
                }
                k++;
            }
            if (k >= mass.size() && continiud) {
                current.pop_back();
            }
        }
    }
}

int main() {
    std::cin >> start >> finish;
    while (std::cin){
        edge a;
        std::cin >> a.r1 >> a.r2 >> a.weight;
        if (mass.size() > 0 && ( a.weight < mass.front().weight))
        {
            mass.emplace(mass.begin(), move( a ));
        }
        else mass.push_back(a);
    }
    mysort();
    recurs(start);
    if (current.size() != 0) {
        if (current.back().r1 != finish &&  current.back().r2 != finish)
            current.clear();
        else {cout << current.front().r1;
            for (int i = 0; i <current.size() ;i++)
                cout << current[i].r2 ;
        }

    }

    return 0;
}

