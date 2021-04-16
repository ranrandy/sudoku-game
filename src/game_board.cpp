#include "game_board.h"
#include "cinder/Rand.h"

namespace sudokugame {

GameBoard::GameBoard(size_t board_size): board_size_(board_size) {
  board_ = vector<vector<size_t>>(board_size_, vector<size_t>(board_size_, 0));
}

void GameBoard::GenerateNumbers(size_t number_total) {
  number_total_ = number_total;
  for (size_t count = 0; count < number_total; count++) {
    size_t random_row = ci::randInt(board_size_) + 1;
    size_t random_col = ci::randInt(board_size_) + 1;
    size_t random_element = ci::randInt(board_size_) + 1;
    
    while (board_[random_row][random_col] != 0) {
      random_row = ci::randInt(board_size_) + 1;
      random_col = ci::randInt(board_size_) + 1;
    }
    
    board_[random_row][random_col] = random_element;
  }
}

} // namespace sudokugame

