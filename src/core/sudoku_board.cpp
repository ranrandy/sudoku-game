#include "core/sudoku_board.h"
#include "cinder/Rand.h"

namespace sudokugame {

SudokuBoard::SudokuBoard(size_t board_size) {
  if (sqrt(board_size) * sqrt(board_size) == board_size && 
      board_size >= kMinBoardSize && board_size <= kMaxBoardSize) {
    board_size_ = board_size;
    number_total_ = 0;
    board_ = vector<vector<size_t>>(board_size_, 
                                    vector<size_t>(board_size_, 0));
  } else {
    throw std::invalid_argument("This is an invalid board size.");
  }
}

void SudokuBoard::GenerateValidBoard(size_t number_total) {
  if (number_total > kSizeNineMaxTotalNumber && board_size_ == kMaxBoardSize) {
    throw std::invalid_argument("The total number is too large.");
  }
  
  GenerateNumbers(number_total);
  
  while (!SudokuSolver(board_).Solve()) {
    board_ = vector<vector<size_t>>(board_size_, 
                                    vector<size_t>(board_size_, 0));
    number_total_ = 0;
    GenerateNumbers(number_total);
  }
}

bool SudokuBoard::InsertNumber(size_t row, size_t col, size_t number) {
  if (!IsValidTile(row, col, number)) {
    return false;
  }
  board_[row][col] = number;
  number_total_++;
  return true;
}

size_t SudokuBoard::GetBoardSize() const {
  return board_size_;
}

const vector<vector<size_t>>& SudokuBoard::GetBoardNumbers() const {
  return board_;
}

size_t SudokuBoard::GetNumberTotal() const {
  return number_total_;
}


void SudokuBoard::GenerateNumbers(size_t number_total) {
  for (size_t count = 0; count < number_total; count++) {
    std::random_device rd;
    size_t random_row = rd() % board_size_;
    size_t random_col = rd() % board_size_;
    size_t random_element = rd() % board_size_ + 1;

    while (!InsertNumber(random_row, random_col, random_element)) {
      random_row = rd() % board_size_;
      random_col = rd() % board_size_;
      random_element = rd() % board_size_ + 1;
    }
    board_[random_row][random_col] = random_element;
  }
}

bool SudokuBoard::IsValidTile(size_t row, size_t col, size_t number) const {
  if (board_[row][col] != 0) {
    return false;
  }

  if (!IsValidSubBoard(row, col, number)) {
    return false;
  }
    
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

