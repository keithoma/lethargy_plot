#include <iostream>
#include <vector>

using namespace std;

// <TODO>: don't confuse "" and '' in c++; fix this
// <TODO>: change board_state_ from one dimensional vector to two

class Board {
    public:
        // <TODO>: add defualt values such as width, height = 3
        Board(const unsigned width, const unsigned height);

        void print_board();
        void place_cross(int index) { board_state_[index] = 'X'; }
        void place_nought(int index) { board_state_[index] = 'O'; }

        unsigned width() { return width_; }
        unsigned height() { return height_; }
        vector<char> board_state() { return board_state_; }
    
    private:
        unsigned width_;
        unsigned height_;
        vector<char> board_state_;

};

Board::Board(unsigned width, unsigned height) {
    // save width and height as private attributes
    width_ = width;
    height_ = height;
    board_state_ = vector<char>(width * height - 1, ' '); // change back later to char(32)
};

// <TODO>: the formating doesn't work exactly as it should
// <TODO>: something is really wrong
void Board::print_board() {
    for (int i = 0; i < height_ - 1; ++i) {
        for (int j = 0; j < width_ - 1; ++j) {
            cout << " " << board_state_[i * height_ + j] << " )";
        }
        cout << " " << board_state_[i * width_ + 2] << " \n";
        cout << " -   -   - \n";
    }

    for (int j = width_ * (height_ - 1); j < width_ * height_ - 1; ++j) {
        cout << " " << board_state_[j] << " )";
    }
    cout << " " << board_state_[width_ * height_ - 1] << '\n';
}

int main() {
    Board board(3, 3);
    board.place_cross(0);
    board.place_cross(1);
    board.place_nought(2);
    board.place_cross(3);
    board.place_cross(4);
    board.place_cross(5);
    board.place_cross(6);
    board.place_nought(8);
    board.print_board();

    return 0;
}