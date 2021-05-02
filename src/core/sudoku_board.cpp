#include "core/sudoku_board.h"
#include "cinder/Rand.h"

namespace sudokugame {

SudokuBoard::SudokuBoard(size_t board_size) {
  // Checks if the board size is a square number.
  if (sqrt(board_size) * sqrt(board_size) == board_size && 
      board_size >= kMinBoardSize && board_size <= kMaxBoardSize) {
    board_size_ = board_size;
    board_ = vector<vector<size_t>>(board_size_, 
                                    vector<size_t>(board_size_, 0));
  } else {
    throw std::invalid_argument("This is an invalid board size.");
  }
}

SudokuBoard::SudokuBoard(const vector<vector<size_t>>& board) {
  // Checks if the board size is a square number.
  if (sqrt(board.size()) * sqrt(board.size()) == board.size() &&
      board.size() >= kMinBoardSize && board.size() <= kMaxBoardSize) {
    board_size_ = board.size();
    board_ = board;
  } else {
    throw std::invalid_argument("This is an invalid board size.");
  }
}

void SudokuBoard::GenerateValidBoard(size_t number_total) {
  if (number_total > board_size_ * board_size_) {
    throw std::invalid_argument("There are too many numbers");
  }
  
  if (GetNumberTotal() > 0) {
    board_ = vector<vector<size_t>>(board_size_,
                                    vector<size_t>(board_size_, 0));
  }
  
  // Randomly generate some numbers on the board until the board is solvable.
  GenerateNumbers(board_size_ * board_size_ / kGeneratingParameter);
  while (!SudokuSolver(board_).Solve()) {
    board_ = vector<vector<size_t>>(board_size_, 
                                    vector<size_t>(board_size_, 0));
    GenerateNumbers(board_size_ * board_size_ / kGeneratingParameter);
  }
  
  // Solve the board.
  SudokuSolver sudoku_solver(board_);
  sudoku_solver.Solve();
  
  // Get a solved full board.
  board_ = sudoku_solver.GetSolution();
  
  // Removes some numbers from the board to leave only number_total numbers.
  RemoveNumbers(board_size_ * board_size_ - number_total);
}

void SudokuBoard::AddNumber(const glm::vec2& position, size_t number) {
  // Checks if the position is original fixed or player added.
  bool is_added_by_player = false;
  for (const glm::vec2& tile_added_number : tiles_added_number_) {
    if (position == tile_added_number) {
      is_added_by_player = true;
    }
  }
  
  // Checks if the number is within range and if the tile is empty or the tile 
  // was added by the player.
  if ((board_[position.x][position.y] == 0 || is_added_by_player) && 
      number <= kMaxBoardSize && number != 0) {
    board_[position.x][position.y] = number;
    tiles_added_number_.push_back(position);
  }
}

bool SudokuBoard::AddNumber(size_t row, size_t col, size_t number) {
  if (!IsValidTile(row, col, number)) {
    return false;
  }
  board_[row][col] = number;
  return true;
}

size_t SudokuBoard::GetBoardSize() const {
  return board_size_;
}

const vector<vector<size_t>>& SudokuBoard::GetBoardNumbers() const {
  return board_;
}

size_t SudokuBoard::GetNumberTotal() const {
  size_t number_total = 0;
  for (const std::vector<size_t>& row : board_) {
    for (size_t col : row) {
      if (col != 0) {
        number_total++;
      }
    }
  }
  return number_total;
}

const vector<glm::vec2>& SudokuBoard::GetTilesAddedNumber() const {
  return tiles_added_number_;
}

void SudokuBoard::ClearTilesAddedNumber() {
  tiles_added_number_.clear();
}

void SudokuBoard::SetBoardNumbers(const vector<vector<size_t>>& board) {
  board_ = board;
}

void SudokuBoard::GenerateNumbers(size_t number_total) {
  for (size_t count = 0; count < number_total; count++) {
    std::random_device rd;
    size_t random_row = rd() % board_size_;
    size_t random_col = rd() % board_size_;
    size_t random_element = rd() % board_size_ + 1;

    while (!AddNumber(random_row, random_col, random_element)) {
      random_row = rd() % board_size_;
      random_col = rd() % board_size_;
      random_element = rd() % board_size_ + 1;
    }
    board_[random_row][random_col] = random_element;
  }
}

void SudokuBoard::RemoveNumbers(size_t number_to_remove) {
  for (size_t i = 0; i < number_to_remove; i++) {
    std::random_device rd;
    size_t random_row = rd() % board_size_;
    size_t random_col = rd() % board_size_;
    while (board_[random_row][random_col] == 0) {
      random_row = rd() % board_size_;
      random_col = rd() % board_size_;
    }
    board_[random_row][random_col] = 0;
  }
}

bool SudokuBoard::IsValidTile(size_t row, size_t col, size_t number) const {
  // Checks if the tile is empty.
  if (board_[row][col] != 0) {
    return false;
  }

  // Checks if adding the number conforms to the rule in sub board.
  if (!IsValidSubBoard(row, col, number)) {
    return false;
  }

  // Checks if adding the number conforms to the rule in row and column.
  for (size_t i = 0; i < board_size_; i++) {
    if (board_[i][col] == number || board_[row][i] == number) {
      return false;
    }
  }
  return true;
}

bool SudokuBoard::IsValidSubBoard(size_t row, size_t col, size_t number) const {
  size_t sub_board_size = sqrt(board_size_);
  std::vector<size_t> sub_board_elements;
  size_t starting_row = row / sub_board_size * sub_board_size;
  size_t starting_col = col / sub_board_size * sub_board_size;
  
  for (size_t i = 0; i < sub_board_size; i++) {
    for (size_t j = 0; j < sub_board_size; j++) {
      if (board_[i+starting_row][j+starting_col] == number) {
        return false;
      }
    }
  }
  return true;
}

} // namespace sudokugame

