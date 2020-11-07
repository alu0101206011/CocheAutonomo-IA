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
    MatrixBoard_.resize((M_+2));

    for (int i = 0; i < M_ + 2; i++) {
        MatrixBoard_[i].resize((N_+2));
    }
    for (int i = 0; i < M_ + 2; i++) { //Ancho
        ChangeState(i,0,Wall); // primera fila
        ChangeState(i,N_+1,Wall); //ultima fila
    }
    for (int i = 0; i < N_ + 2; i++) {
        ChangeState(0,i,Wall); 
        ChangeState(M_+1,i,Wall);
    } 
}


Board::Board(std::string filename) {
    std::ifstream reader(filename);
    if (!reader) {
        std::cerr << "Error: file could not be opened\n";
        exit(1);
    }
    reader >> M_ >> N_;
    MatrixBoard_.resize((M_+2));
    for (int i = 0; i < M_ + 2; i++) {
        MatrixBoard_[i].resize((N_+2));
    }
    int nstate;
    for (int i = 0; i < N_ + 2; i++) 
        for (int j = 0; j < M_ + 2; j++) {
            reader >> nstate;
            ChangeState(j,i,static_cast<state>(nstate));
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
        os << GetM() << " " << GetN() << std::endl;
        for (int i = 0; i < GetN() + 2; i++) { 
            for (int j = 0; j < GetM() + 2; j++) {  
                os << GetState(j,i);
                if (j != GetM() + 1) { 
                    os << " ";
                }
            }
            if (i != GetN() + 1) { 
                os << std::endl;
            }
        }
    } else if (mode == terminalicons) {
        for (int i = 0; i < GetN() + 2; i++) { 
            for (int j = 0; j < GetM() + 2; j++) {  
                switch (GetState(j,i))
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
        os << std::endl;
    } else if (mode == terminalcords) {
        
        for (int i = 0; i < GetN() + 2; i++) { 
            for (int j = 0; j < GetM() + 2; j++) {  
                switch (GetState(j,i))
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
                os << "(" << j << "," << i << ")\t" << RESET;
            }
            if (i != GetN() + 1) { 
                os << std::endl;
            }
        }
        os << std::endl;
    } else {
        os << "Write mode is invalid or something went wrong";
    }
}

Board::~Board() {}

