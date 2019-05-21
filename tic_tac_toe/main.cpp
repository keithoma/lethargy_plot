#include <array>
#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

// <TODO>: don't confuse "" and '' in c++; fix this
// <TODO>: change board_state_ from one dimensional vector to two

struct Position {
	unsigned row;
	unsigned column;
};

enum class State {
	Unset,
	X,
	O,
};

ostream& operator<<(ostream& os, State s)
{
	switch (s)
	{
		case State::O:
			return os << 'O';
		case State::X:
			return os << 'X';
		case State::Unset:
		default:
			return os << ' ';
	}
}

class Board {
  public:
	Board(unsigned width, unsigned height);

	/// Default-constructs board with 3x3 dimension.
	Board() : Board{3, 3} {}

	constexpr size_t offsetOf(Position const& p) const noexcept { return p.row * height_ + p.column; }

	void print_board() const;

	void place_cross(Position const& p) { board_state_[offsetOf(p)] = State::X; }
	void place_nought(Position const& p) { board_state_[offsetOf(p)] = State::O; }

	State& operator[](Position const& p) { return board_state_[offsetOf(p)]; }

	unsigned width() const noexcept { return width_; }
	unsigned height() const noexcept { return height_; }
	vector<State> const& board_state() const noexcept { return board_state_; }

  private:
	unsigned width_;
	unsigned height_;
	vector<State> board_state_;
};

Board::Board(unsigned width, unsigned height) : width_{width}, height_{height}, board_state_{}
{
	board_state_.resize(width * height);
}

// <TODO>: the formating doesn't work exactly as it should
// <TODO>: something is really wrong
void Board::print_board() const
{
	for (unsigned i = 0; i < height_ - 1; ++i)
	{
		for (unsigned j = 0; j < width_ - 1; ++j)
			cout << " " << board_state_[i * height_ + j] << " )";

		cout << " " << board_state_[i * width_ + 2] << " \n";
		cout << " -   -   - \n";
	}

	for (unsigned j = width_ * (height_ - 1); j < width_ * height_ - 1; ++j)
		cout << " " << board_state_[j] << " )";

	cout << " " << board_state_[width_ * height_ - 1] << '\n';
}

void initialize_random(Board& board)
{
	static constexpr array<State, 3> states{State::Unset, State::X, State::O};

	mt19937 rng;
	rng.seed(time(nullptr));

	for (unsigned i = 0; i < 3; ++i)
		for (unsigned j = 0; j < 3; ++j)
			board[{i, j}] = states[uniform_int_distribution{0, 2}(rng)];
}

int main()
{
	Board board{3, 3};

	// Randomly initialize the board.
	initialize_random(board);

	// or explicitly set field to given state
	board[{2, 2}] = State::X;

	board.print_board();

	return EXIT_SUCCESS;
}
