#include "../include/gps.hpp"
#include <cmath>
#include <cstring>
#include <cfloat>
#include <set>
#include <stack>

GPS::GPS(const Board& map): map_(map) {
    for (unsigned i = 0; i < map_.GetM(); i++) {
        for (unsigned j = 0; j < map_.GetN(); j++) {
            if (map_.GetState(i,j) == (Car)) {
                start_.first = i;
                start_.second = j;
            } else if (map_.GetState(i,j) == Finish) {
                end_.first = i;
                end_.second = j;
            }
        }
    }
}

GPS::~GPS() {}

Pair GPS::get_start() {
    return start_;
}
Pair GPS::get_end() {
    return end_;
}
Board GPS::get_map() {
    return map_;
}

void GPS::set_start(Pair new_start) {
    start_ = new_start;
}
void GPS::set_end(Pair new_end) {
    end_ = new_end;
}
void GPS::set_board(Board new_map) {
    map_ = new_map;
}


bool GPS::isValid(int i, int j) {
    return (i >= 0) && (i < map_.GetM()) && // M es el tamaño de las filas del mapa
           (j >= 0) && (j < map_.GetN());   // N es el tamaño de las columnas del mapa
}

bool GPS::isUnBlocked(int i, int j) {
    if(map_.GetState(i,j) == ClearPath)
        return true;
    else
        return false;
}

double GPS::CalculateHManhattan(int i, int j) {
    return double (abs (i - end_.first) + abs (j - end_.second));
}

double GPS::CalculateHEuclidean(int i, int j) {
    return ((double)sqrt ((i - end_.first) * (i - end_.first) + (j - end_.second) * (j - end_.second)));
}

void GPS::tracePath(matrixCell& posDetails) {
    int row = end_.first;
    int col = end_.second;

    std::stack<Pair> Path;

    while (!(posDetails[row][col].parent_i == row && posDetails[row][col].parent_j == col)) {
        Path.push(std::make_pair(row, col));
        int temp_row = posDetails[row][col].parent_i;
        int temp_col = posDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }
    Path.push(std::make_pair(row, col));
    while (!Path.empty()) {
        Pair p = Path.top();
        Path.pop();
        if (map_.GetState(p.first, p.second) != Car && map_.GetState(p.first, p.second) != Finish)
            map_.ChangeState(p.first, p.second, state::Path);
    }
    return;
}

void GPS::AStarSearch(hMethod method) {
    int i, j;
    int ROW = map_.GetM();
    int COL = map_.GetN();
    bool visited[ROW][COL];
    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            visited[i][j] = false;
        }
    }
    matrixCell posDetails;
    posDetails.resize(ROW);
    for (i = 0; i < ROW; i++)
        posDetails[i].resize(COL);

    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            posDetails[i][j].f = FLT_MAX;
            posDetails[i][j].g = FLT_MAX;
            posDetails[i][j].h = FLT_MAX;
            posDetails[i][j].parent_i = -1;
            posDetails[i][j].parent_j = -1;
        }
    }

    i = start_.first, j = start_.second;
    posDetails[i][j].f = 0.0;
    posDetails[i][j].g = 0.0;
    posDetails[i][j].h = 0.0;
    posDetails[i][j].parent_i = i;
    posDetails[i][j].parent_j = j;
    
    std::set<pPair> optimalPos;
    optimalPos.insert(std::make_pair(0.0, std::make_pair(i, j)));

    while (!optimalPos.empty()) {
        pPair p = *optimalPos.begin();
        optimalPos.erase(optimalPos.begin());

        i = p.second.first;
        j = p.second.second;
        visited[i][j] = true;

        double gNew, hNew, fNew;

        for(int dir = N; dir <= W; dir++){    //preguntamos a todas las direcciones
            int next_i = i + i_d[dir];
            int next_j = j + j_d[dir];

            if (isValid(next_i, next_j)) {
                if (map_.GetState(next_i, next_j) == Finish) {
                    posDetails[next_i][next_j].parent_i = i;
                    posDetails[next_i][next_j].parent_j = j;
                    std::cout << "Encontrao!!!\n";
                    tracePath(posDetails);
                    return;
                } else if (!visited[next_i][next_j] && isUnBlocked(next_i, next_j)) {
                    gNew = posDetails[i][j].g + 1.0;
                    if (method == Manhattan)
                        hNew = CalculateHManhattan(i, j);
                    else if (method == Euclidean)
                        hNew = CalculateHEuclidean(i, j);
                    fNew = gNew + hNew;

                    if (posDetails[next_i][next_j].f == FLT_MAX || posDetails[next_i][next_j].f > fNew) {
                        optimalPos.insert(std::make_pair(fNew, std::make_pair(next_i, next_j)));
                        
                        posDetails[next_i][next_j].f = fNew;
                        posDetails[next_i][next_j].g = gNew;
                        posDetails[next_i][next_j].h = hNew;
                        posDetails[next_i][next_j].parent_i = i;
                        posDetails[next_i][next_j].parent_j = j;
                    }
                }
            }
        }
    }
    std::cout << "No encontrao!!!\n";
}
