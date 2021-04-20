#include "core/sudoku_solver.h"

namespace sudokugame {

SudokuSolver::SudokuSolver(const gameboard &board) {
  tile_to_fill_ = 0;
  sudoku_board_ = board;
  
  // Stores the tiles to be filled in
  for (size_t row = 0; row < board.size(); row++) {
    for (size_t col = 0; col < board.size(); col++) {
      if (board[row][col] == 0) {
        std::pair<size_t, size_t> empty_tile(row, col);
        empty_tiles_.push_back(empty_tile);
      }
    }
  }
}

bool SudokuSolver::Solve() {
  return FillInNumbers();
}

const SudokuSolver::gameboard& SudokuSolver::GetSolution() const {
  return sudoku_board_;
}

bool SudokuSolver::FillInNumbers() {
  // If the board has been filled in completely and 
  // the board is also a valid board, the recursion algorithm ends.
  if (IsFull() && IsValid()) {
    return true;
  }

  // Gets the next tile to fill in a number.
  std::pair<size_t, size_t> starting_point = empty_tiles_.at(tile_to_fill_);
  size_t row = starting_point.first;
  size_t col = starting_point.second;

  // Checks from 1 to the largest number on the board. 
  // Add this number to the tile, 
  // and recursively check if the ultimate board will be valid.
  for (size_t possible_number = 1; possible_number <= sudoku_board_.size(); 
       possible_number++) {
    // If the tile is not empty (this if clause may be redundant).
    if (sudoku_board_[row][col] != 0) {
      break;
    }

    // Add the number to the tile and check.
    if (IsValidTile(row, col, possible_number)) {
      sudoku_board_[row][col] = possible_number;
      tile_to_fill_++;
      if (FillInNumbers()) {
        return true;
      } else {
        sudoku_board_[row][col] = 0;
        tile_to_fill_--;
      }
    }
  }
  // If the board has no solution, then false will be returned.
  return false;
}

bool SudokuSolver::IsFull() const {
  for (const vector<size_t>& row : sudoku_board_) {
    for (size_t col : row) {
      if (col == 0) {
        return false;
      }
    }
  }
  return true;
}

bool SudokuSolver::IsValid() const {
  for (size_t row = 0; row < sudoku_board_.size(); row++) {
    for (size_t col = 0; col < sudoku_board_.size(); col++) {
      if (!IsValidTile(row, col, sudoku_board_[row][col])) {
        return false;
      }
    }
  }
  return true;
}

bool SudokuSolver::IsValidTile(size_t row, size_t col,
                               size_t number) const {
  for (size_t i = 0; i < sudoku_board_.size(); i++) {
    if (i != col && sudoku_board_[row][i] == number) {
      return false;
    }
    if (i != row && sudoku_board_[i][col] == number) {
      return false;
    }
  }

  // If the tile conforms to the rule in sub board.
  size_t sub_board_size = sqrt(sudoku_board_.size());
  for (size_t i = 0; i < sub_board_size; i++) {
    for (size_t j = 0; j < sub_board_size; j++) {
      if (!((row == i + (row / sub_board_size) * sub_board_size) && 
            col == j + (col / sub_board_size) * sub_board_size) &&
          sudoku_board_[i + (row / sub_board_size) * sub_board_size]
                       [j + (col / sub_board_size) * sub_board_size] == 
              number) {
        return false;
      }
    }
  }
  return true;
}

}