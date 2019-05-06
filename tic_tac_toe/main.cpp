#include <iostream>
#include <string>

using namespace std;

int BOARD_STATE[9] {};

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

int main() {
    print_board();
}
