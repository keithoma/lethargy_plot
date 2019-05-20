#include <iostream>
#include <vector>

using namespace std;


class Board {
    public:
        // <TODO>: add defualt values such as width, height = 3
        Board(const unsigned width, const unsigned height);

        void print_board();
        void place_nought(int index);
        void place_cross(int index);

        unsigned width() { return width_; }
        unsigned height() { return height_; }
        vector<char> board_state() { return board_state_; }
    
    private:
        unsigned width_;
        unsigned height_;
        // better is two dimensional vector
        vector<char> board_state_;

};

Board::Board(unsigned width, unsigned height) {
    // save width and height as private attributes
    width_ = width;
    height_ = height;
    board_state_ = vector<char>(width * height, 'x'); // change back later to char(32)
};

// <TODO>: the formating doesn't work exactly as it should
void Board::print_board() {
    for (int i = 0; i < height_; ++i) {
        for (int j = 0; j < width_ - 1; ++j) {
            cout << ' ' << board_state_[i * height_ + j] << ' ' << '|';
        }
        cout << ' ' << board_state_[i * width_] << ' ' << '\n';
        cout << " -   -   - \n";
    }
    cout << ' ' << board_state_[width_ * height_] << ' ';
}

int main() {
    Board board(3, 3);
    board.print_board();

    return 0;
}