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
    for (int i = 0; i < N_; i++) {
        ChangeState(i,0,Wall);
        ChangeState(i,M_+1,Wall);
    }
    for (int i = 0; i < M_; i++) {
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
    MatrixState map;
    MatrixBoard_.resize((N_+2));
    for (int i = 0; i < N_ + 2; i++) {
        MatrixBoard_[i].resize((M_+2));
    }
    int nstate;
    state newstate;
    for (int i = 0; i < N_ + 2; i++) 
        for (int j = 0; j < M_ + 2; j++) {
            reader >> nstate;
            newstate = GetState(nstate);
            ChangeState(i,j,newstate);
        }
    Write(std::cout, terminalicons);
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

state Board::GetState(int nstate) const {
    if (nstate == 0) return ClearPath;
    else if (nstate == 1) return Wall;
    else if (nstate == 2) return Obstacle;
    else if (nstate == 3) return Car;
    else if (nstate == 4) return Finish;
    else std::cerr << "Error: state not valid.\n"; 
    exit(1);
}

void Board::ChangeState(int x, int y, state newstate) {
    MatrixBoard_[x][y] = newstate;
}

void Board::Write(std::ostream &os, writemode mode) const {
    if (mode == file) {
        os << GetM() << std::endl << GetN() << std::endl;
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

