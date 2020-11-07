#include "../include/board.hpp"
 
Board::Board() {
    Valid = false;
    M_ = 0;
    N_ = 0;
    MatrixBoard_.resize(0);
}

Board::Board(int M,int N) {
    Valid = false;
    M_ = M;
    N_ = N;
    MatrixBoard_.resize((N_+2));
    for (int i = 0; i < N_ + 2; i++) {
        MatrixBoard_[i].resize((M_+2));
    }
    for (int i = 0; i < N_ + 2; i++) {
        ChangeState(i,0,Wall);
        ChangeState(i,M_+1,Wall);
    }
    for (int i = 0; i < M_ + 2; i++) {
        ChangeState(0,i,Wall);
        ChangeState(N_+1,i,Wall);
    } 
}


Board::Board(std::string filename) {
    std::ifstream reader(filename);
    if (!reader) {
        std::cerr << "Error: file could not be opened\n";
        exit(1);
    }
    reader >> N_ >> M_;
    M_ = M_ - 2;
    N_ = N_ - 2;
    MatrixBoard_.resize((N_+2));
    for (int i = 0; i < N_ + 2; i++) {
        MatrixBoard_[i].resize((M_+2));
    }
    int nstate;
    for (int i = 0; i < N_ + 2; i++) 
        for (int j = 0; j < M_ + 2; j++) {
            reader >> nstate;
            ChangeState(i,j,static_cast<state>(nstate));
        }
    reader.close();
}

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
        os << GetN() + 2 << " " << GetM() + 2 << std::endl;
        for (int i = 0; i < GetN() + 2; i++) { 
            for (int j = 0; j < GetM() + 2; j++) {  
                os << GetState(i,j);
                if (j != GetM() + 1) { 
                    os << " ";
                }
            }
            if (i != GetN() + 2) { 
                os << std::endl;
            }
        }
    } else if (mode == terminalicons) {
        for (int i = 0; i < GetN() + 2; i++) { 
            for (int j = 0; j < GetM() + 2; j++) {  
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
            if (i != GetN() + 2) { 
                os << std::endl;
            }
        }
    } else if (mode == terminalcords) {
        
        for (int i = 0; i < GetN() + 2; i++) { 
            for (int j = 0; j < GetM() + 2; j++) {  
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
            if (i != GetN() + 2) { 
                os << std::endl;
            }
        }
    } else {
        os << "Write mode is invalid or something went wrong";
    }
}

Board::~Board() {}

