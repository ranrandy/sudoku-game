#include "sudoku_solution.h"

namespace sudokugame {

SudokuSolution::SudokuSolution(const gameboard &board) {
  tile_to_fill_ = 0;
  sudoku_board_ = board;
  for (size_t row = 0; row < 9; row++) {
    for (size_t col = 0; col < 9; col++) {
      if (board[row][col] == '.') {
        std::pair<size_t, size_t> empty_tile(row, col);
        empty_tiles_.push_back(empty_tile);
      }
    }
  }
}

bool SudokuSolution::Solve() {
  return FillInNumbers(sudoku_board_);
}

bool SudokuSolution::FillInNumbers(gameboard &board) {
  if (IsFull(board) && IsValid(board)) {
    return true;
  }

  std::pair<size_t, size_t> starting_point = empty_tiles_.at(tile_to_fill_);
  size_t row = starting_point.first;
  size_t col = starting_point.second;

  for (char possible_number = '1'; possible_number <= '9';
       possible_number++) {
    if (board[row][col] != '.') {
      break;
    }

    if (IsValidTile(board, row, col, possible_number)) {
      board[row][col] = possible_number;
      tile_to_fill_++;
      if (FillInNumbers(board)) {
        return true;
      } else {
        board[row][col] = '.';
        tile_to_fill_--;
      }
    }
  }
  return false;
}

bool SudokuSolution::IsFull(const gameboard &board) {
  for (size_t i = 0; i < board.size(); i++) {
    for (size_t j = 0; j < board.size(); j++) {
      if (board[i][j] == '.') {
        return false;
      }
    }
  }
  return true;
}

bool SudokuSolution::IsValid(const gameboard& board) {
  for (size_t row = 0; row < 9; row++) {
    for (size_t col = 0; col < 9; col++) {
      if (!IsValidTile(board, row, col, board[row][col])) {
        return false;
      }
    }
  }
  return true;
}

bool SudokuSolution::IsValidTile(const gameboard &board, size_t row, 
                                 size_t col, char number) {
  for (size_t i = 0; i < 9; i++) {
    if (i != col && board[row][i] == number) {
      return false;
    }
    if (i != row && board[i][col] == number) {
      return false;
    }
  }

  for (size_t i = 0; i < 3; i++) {
    for (size_t j = 0; j < 3; j++) {
      if (!((row == i + (row / 3) * 3) && col == j + (col / 3) * 3) &&
          board[i + (row / 3) * 3][j + (col / 3) * 3] == number) {
        return false;
      }
    }
  }
  return true;
}


}