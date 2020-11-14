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
    MatrixBoard_.resize(M_);
    for (int i = 0; i < M_; i++) {
        MatrixBoard_[i].resize(N_,ClearPath);
    }
}


Board::Board(std::string filename) {
    std::ifstream reader(filename);
    if (!reader) {
        std::cerr << "Error: file could not be opened\n";
        exit(1);
    }
    reader >> M_ >> N_;
    MatrixBoard_.resize(M_);
    for (int i = 0; i < M_; i++) {
        MatrixBoard_[i].resize(N_);
    }
    int nstate;
    for (int i = 0; i < M_; i++) 
        for (int j = 0; j < N_; j++) {
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

void Board::ShuffleMap(int obstnum) {
    std::srand(time(NULL)); //Generamos una seed aleatoria

    ChangeState(std::rand()%GetM(),std::rand()%GetN(),Car); //Random Car

    int rx = std::rand()%GetM(); //Random Finish
    int ry = std::rand()%GetN();
    if (GetState(rx,ry) == ClearPath) {
        ChangeState(rx,ry,Finish);
    } else {
        while (GetState(rx,ry) != ClearPath) {
            int rx = std::rand()%GetM();
            int ry = std::rand()%GetN();
            if (GetState(rx,ry) == ClearPath) {
                ChangeState(rx,ry,Finish);
                break;
            }
        }
    }

    for (int i = 0; i < obstnum; i++) { //Random obstacles
        int rx = std::rand()%GetM();
        int ry = std::rand()%GetN();
        if (GetState(rx,ry) == ClearPath) {
            ChangeState(rx,ry,Obstacle);
        } else {
            while (GetState(rx,ry) != ClearPath) {
                int rx = std::rand()%GetM();
                int ry = std::rand()%GetN();
                if (GetState(rx,ry) == ClearPath) {
                    ChangeState(rx,ry,Obstacle);
                    break;
                }
            }
        }
    }
}


void Board::Write(std::ostream &os, writemode mode) const {
    if (mode == file) {
        os << GetM() << " " << GetN() << std::endl;
        for (int i = 0; i < GetM(); i++) { 
            for (int j = 0; j < GetN(); j++) {  
                os << GetState(i,j);
                if (j != GetN() - 1) { 
                    os << " ";
                }
            }
            if (i != GetM() - 1) { 
                os << std::endl;
            }
        }
    } else if (mode == terminalicons) {
        for (int i = 0; i < GetM(); i++) {
            if (i == 0 || i == GetM() - 1){
                for(int j = 0; j < GetN(); j++){
                    os << "🧱";
                }
            }
            os << "🧱";
            for (int j = 0; j < GetN(); j++) {  
                switch (GetState(i,j))
                {
                case ClearPath:
                    os << "⬜" ;
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
            os << "🧱";
            if (i != GetM() - 1) { 
                os << std::endl;
            }
        }
        os << std::endl;
    } else if (mode == terminalcords) {
        for (int i = 0; i < GetM(); i++) { 
            for (int j = 0; j < GetN(); j++) {  
                switch (GetState(i,j))
                {
                case ClearPath:
                    os << YELLOW;
                    break;
                case Obstacle:
                    os << GREEN;
                    break;
                case Car:
                    os << MAGENTA;
                    break;
                case Finish:
                    os << RED;
                    break;
                default:
                    os << WHITE;
                    break;
                }
                os << "(" << i << "," << j << ")\t" << RESET;
            }
            os << "\n";
        }
        os << YELLOW << "(Espacio vacío) " << GREEN << "(Obstáculo) " << MAGENTA << "(Coche) " << RED << "(Meta) " << WHITE << "(Error) " << RESET << std::endl;
    } else {
        os << "Write mode is invalid or something went wrong";
    }
}

Board::~Board() { }