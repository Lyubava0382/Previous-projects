#include <iostream>
#include <vector>
#include <chrono>
struct board {
    int x;
    int y;
    int w;
};

int bestcount;
std::vector<board> bestarray;
int n;
int boardsize;

bool Collision(std::vector<board>& one, int x, int y) {
    for (board square:one) {
        if (x >= square.x && x < square.x + square.w &&
            y >= square.y && y < square.y + square.w) {
            return true;
        }
    }
    return false;
}
void Backtracking(std::vector<board>& one, int summ, int boardlen, int minx, int miny) {
    for (int x = minx; x < n; x++) {
        for (int y = miny; y < n; y++) {
            // проверка текущей клетки на пересечение с уже поставленными квадратами
            if (!Collision(one,x,y)) {
                // максимально возможный радиус
                int right = std::min(n-1, std::min(n-x, n-y));
                for (board square:one) {
                    if (square.x+square.w > x && square.y > y) {
                        right = std::min(right, square.y-y);
                    }
                }
                // перебор всех возможных радиусов
                for (int r = right; r > 0; r--) {
                    board square({x, y, r});
                    std::vector<board> b = one;
                    b.push_back(square);
                    // заполено ли поле
                    if (summ + square.w * square.w == n * n) {
                        // обновление ответа
                        if (boardlen + 1 < bestcount) {
                            bestcount = boardlen + 1;
                            bestarray = b;
                        }
                    }
                    else {
                        // отсечение решений, которые заведомо хуже текущего лучшего
                        if (boardlen + 1 < bestcount)
                            Backtracking(b, summ + square.w * square.w, boardlen + 1, x, y+r);
                        else return;
                    }
                }
                return;
            }
        }
        miny = n/2;
    }
}
int main() {
    std::cin >> n;
    // поиск наибольшего делителя n
    for (int i = 1; i < n; i++) {
        if (n%i == 0) boardsize = i;
    }
    n = n / boardsize;
    // начальное приближение
    bestcount = 2 * n + 1;
    std::vector<board> table;
    table.push_back(board({0,0,(n + 1)/2}));
    table.push_back({0,(n + 1)/2,n/2});
    table.push_back({(n + 1)/2,0,n/2});
    auto begin = std::chrono::steady_clock::now();
    Backtracking(table, ((n + 1)/2)*((n + 1)/2) + 2 *(n/2)*(n/2), 3,
                 n/2, (n + 1)/2);
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time: " << elapsed_ms.count() << " ms\n";
    std::cout << bestcount << '\n';
    for (auto i: bestarray) {
        std::cout << i.x * boardsize << ' ' << i.y * boardsize
                  << ' ' << i.w * boardsize << '\n';
    }
}
