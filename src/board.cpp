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
    MatrixInt map(M_+2, std::vector<int>(N_+2,0));
    MatrixBoard_= map;
    for (int i = 0; i < N_; i++) {
        ChangeState(i,0,Wall);
        ChangeState(i,M_+1,Wall);
    }
    for (int i = 0; i < M_; i++) {
        ChangeState(0,i,Wall);
        ChangeState(N_+1,i,Wall);
    }
}

Board::Board(std::string filename) {}

int Board::GetM() const {
    return M_;
}

int Board::GetN() const {
    return N_;
}

void Board::ChangeState(int x, int y, state newstate) {
    MatrixBoard_[x][y] = newstate;
}