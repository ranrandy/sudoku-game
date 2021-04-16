#include "game_board.h"
#include "cinder/Rand.h"

namespace sudokugame {

GameBoard::GameBoard(size_t board_size) {
  if (sqrt(board_size) * sqrt(board_size) == board_size && 
      board_size >= kMinBoardSize && board_size <= kMaxBoardSize) {
    board_size_ = board_size;
  } else {
    throw std::invalid_argument("This is an invalid board size.");
  }
  board_ = vector<vector<size_t>>(board_size_, vector<size_t>(board_size_, 0));
}

void GameBoard::GenerateNumbers(size_t number_total) {
  number_total_ = number_total;
  for (size_t count = 0; count < number_total; count++) {
    size_t random_row = ci::randInt(board_size_);
    size_t random_col = ci::randInt(board_size_);
    size_t random_element = ci::randInt(board_size_) + 1;
    
    while (!IsValidBoard(random_row, random_col, random_element)) {
      random_row = ci::randInt(board_size_);
      random_col = ci::randInt(board_size_);
      random_element = ci::randInt(board_size_) + 1;
    }
    board_[random_row][random_col] = random_element;
  }
  
  for (size_t i = 0; i < board_size_; i++) {
    for (size_t j = 0; j < board_size_; j++) {
      if (board_[i][j] != 0) {
        std::cout << board_[i][j] << "\t";
      } else {
        std::cout << "_" << "\t";
      }
    }
    std::cout << std::endl;
  }
}

size_t GameBoard::GetBoardSize() const {
  return board_size_;
}

bool GameBoard::IsValidBoard(size_t row, size_t col, size_t number) {
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

bool GameBoard::IsValidSubBoard(size_t row, size_t col, size_t number) {
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

