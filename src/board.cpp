#include "../include/board.hpp"

Board::Board() {
    M_ = 0;
    N_ = 0;
    MatrixInt map(M_, std::vector<int>(N_));
    MatrixBoard_= map;
}

Board::Board(int M,int N) {
    M_ = M;
    N_ = N;
    MatrixInt map(M_, std::vector<int>(N_));
    MatrixBoard_= map;
}

Board::Board(std::string filename) {}

int Board::GetM() const{
    return M_;
}

int Board::GetN() const{
    return N_;
}