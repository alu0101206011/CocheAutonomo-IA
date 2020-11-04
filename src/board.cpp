#include "../include/board.hpp"

Board::Board() {
    M_ = 0;
    N_ = 0;
    MatrixState map;
    for (int i = 0; i < M_+2; i++) {
        map.resize(N_+2);
    }
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

Board::Board(int M,int N) {
    M_ = M;
    N_ = N;
    MatrixState map;
    for (int i = 0; i < M_+2; i++) {
        map.resize(N_+2);
    }
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

state Board::GetState(int x, int y) const {
    return MatrixBoard_[x][y];
}

void Board::ChangeState(int x, int y, state newstate) {
    MatrixBoard_[x][y] = newstate;
}

void Board::Write(std::ostream &os, writemode mode) const {
    if (mode == file) {
        os << GetM() << std::endl << GetN() << std::endl;
        for (int i = 0; i < GetN() + 1; i++) { 
            for (int j = 0; j < GetM() + 1; j++) {  
                os << GetState(i,j);
                if (j != GetM() + 1) { 
                    os << " ";
                }
            }
            if (i != GetN() + 1) { 
                os << std::endl;
            }
        }
    } else if (mode == terminalicons) {
        for (int i = 0; i < GetN() + 1; i++) { 
            for (int j = 0; j < GetM() + 1; j++) {  
                switch (GetState(i,j))
                {
                case ClearPath:
                    os << "⬜" ;
                    break;
                case Wall:
                    os << "🧱" ;
                    break;
                case Obstacle:
                    os << "🚧" ;
                    break;
                case Car:
                    os << "🚗" ;
                    break;
                case Finish:
                    os << "🏁";
                    break;
                default:
                    os << "❓";
                    break;
                }
            }
            if (i != GetN() + 1) { 
                os << std::endl;
            }
        }
    } else if (mode == terminalcords) {
        
        for (int i = 0; i < GetN() + 1; i++) { 
            for (int j = 0; j < GetM() + 1; j++) {  
                switch (GetState(i,j))
                {
                case ClearPath:
                    os << YELLOW;
                    break;
                case Wall:
                    os << BLACK;
                    break;
                case Obstacle:
                    os << GREEN;
                    break;
                case Car:
                    os << CYAN;
                    break;
                case Finish:
                    os << RED;
                    break;
                default:
                    os << WHITE;
                    break;
                }
                os << "(" << GetM() << "," << GetN() << ")" << RESET;
            }
            if (i != GetN() + 1) { 
                os << std::endl;
            }
        }
    } else {
        os << "Write mode is invalid or something went wrong";
    }
}



