#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct Board {

        int width;
        int height;

        int tiles;
        string board_state;

        Board(int width = 3, int height = 3) {
            tiles = width * height;
            fill(board_state.begin(), board_state.begin() + tiles, ' ');
        }
};

/*
void print_cell(int index) {
    string piece;
    if (index == 0)
        string piece = " ";
    else if (index == 1)
        string piece = "X";
    else
        string piece = "O";
    
    cout << " " << piece << " ";
}

void print_board() {
    for (int column = 0; column < 2; ++column) {
        for (int row = 0; row < 2; ++row) {
            print_cell(3 * column + row);
        }
    }
}

void put_piece(int index, int piece) {
    BOARD_STATE[index] = piece;
}
*/

int main() {
    Board my_board;
    cout << "hello" << my_board.board_state[3] << "world";
    cout << my_board.tiles;
    cout << my_board.width;
    cout << my_board.height;
    return 0;
}
