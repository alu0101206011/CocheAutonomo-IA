#include "../include/board.hpp"
 
Board::Board() {
    Valid = false;
    M_ = 0; 
    N_ = 0;
    MatrixBoard_.resize(0);
}

Board::Board(int M,int N) {
    Valid = false;
    Car_ = false;
    Finish_ = false;
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
            if (static_cast<state>(nstate) == Car) Car_ = true;
            else if (static_cast<state>(nstate) == Finish) Finish_ = true;
        }
    reader.close();
} 

int Board::GetM() const {
    return M_;
}

int Board::GetN() const {
    return N_;
}

bool Board::GetCar() const {
    return Car_;
}

bool Board::GetFinish() const {
    return Finish_;
}

void Board::SetCar(bool NewCar) {
    Car_ = NewCar;
}

void Board::SetFinish(bool NewFinish) {
    Finish_ = NewFinish;
}

state Board::GetState(int x, int y) const {
    return MatrixBoard_[x][y];
}

void Board::ChangeState(int x, int y, state newstate) {
    MatrixBoard_[x][y] = newstate;
}

void Board::ShuffleMap(int obstnum) {
    std::srand(time(NULL)); //Generamos una seed aleatoria

    if (!GetCar())
        ChangeState(std::rand()%GetM(),std::rand()%GetN(),Car); //Random Car

    if (!GetFinish())
        ChangeState(std::rand()%GetM(),std::rand()%GetN(),Finish);
        
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
            if (i == 0){
                for(int j = 0; j < GetN() + 2; j++){
                    os << "🧱";
                }
                os << "\n";
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
                case Path:
                    os << "🟩";
                    break;
                default:
                    os << "❓";
                    break;
                }
            }
            os << "🧱";
            os << std::endl;
            if (i == GetM() - 1){
                for(int j = 0; j < GetN() + 2; j++){
                    os << "🧱";
                }
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
                case Path:
                    os << BLUE;
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

void Board::ClearMap() {
    for (int i = 0; i < GetM(); i++) { 
        for (int j = 0; j < GetN(); j++) { 
            ChangeState(i,j,ClearPath);
        }
    }
    Car_ = false;
    Finish_ = false;
}

Board::~Board() { }