#include <catch2/catch.hpp>
#include <iostream>

#include "core/sudoku_solver.h"

using sudokugame::SudokuSolver;
using std::vector;

TEST_CASE("Sudoku solver can solve a board") {
  SudokuSolver::gameboard board = {
      {5, 3, 0, 0, 7, 0, 0, 0, 0},
      {6, 0, 0, 1, 9, 5, 0, 0, 0},
      {0, 9, 8, 0, 0, 0, 0, 6, 0},
      {8, 0, 0, 0, 6, 0, 0, 0, 3},
      {4, 0, 0, 8, 0, 3, 0, 0, 1},
      {7, 0, 0, 0, 2, 0, 0, 0, 6},
      {0, 6, 0, 0, 0, 0, 2, 8, 0},
      {0, 0, 0, 4, 1, 9, 0, 0, 5},
      {0, 0, 0, 0, 8, 0, 0, 7, 9}};
  
  SudokuSolver::gameboard empty_board(9, std::vector<size_t>(9, 0));
  
  SudokuSolver::gameboard unsolvable_board = {
      {5, 5, 0, 0, 7, 0, 0, 0, 0}, // repetitive 5
      {6, 0, 0, 1, 9, 5, 0, 0, 0},
      {0, 9, 8, 0, 0, 0, 0, 6, 0},
      {8, 0, 0, 0, 6, 0, 0, 0, 3},
      {4, 0, 0, 8, 0, 3, 0, 0, 1},
      {7, 0, 0, 0, 2, 0, 0, 0, 6},
      {0, 6, 0, 0, 0, 0, 2, 8, 0},
      {0, 0, 0, 4, 1, 9, 0, 0, 5},
      {0, 0, 0, 0, 8, 0, 0, 7, 9}};

  SudokuSolver normal_board_solution(board);
  SudokuSolver empty_board_solution(empty_board);
  SudokuSolver unsolvable_board_solution(unsolvable_board);
  
  bool is_normal_solvable = normal_board_solution.Solve();
  bool is_empty_solvable = empty_board_solution.Solve();
  bool is_unsolvable_solvable = unsolvable_board_solution.Solve();
  REQUIRE(is_normal_solvable);
  REQUIRE(is_empty_solvable);
  REQUIRE(!is_unsolvable_solvable);
  
  SudokuSolver::gameboard solved_normal_board = 
      normal_board_solution.GetSolution();
  SudokuSolver::gameboard solved_empty_board = 
      empty_board_solution.GetSolution();
  SudokuSolver::gameboard solved_unsolvable_board =
      unsolvable_board_solution.GetSolution();

  // Normal board is full
  for (const vector<size_t>& row : solved_normal_board) {
    for (size_t col : row) {
      REQUIRE(col != 0);
    }
  }
  
  // Empty board is full
  for (const vector<size_t>& row : solved_empty_board) {
    for (size_t col : row) {
      REQUIRE(col != 0);
    }
  }

  // Unsolvable board is unchanged
  for (size_t i = 0; i < 9; i++) {
    for (size_t j = 0; j < 9; j++) {
      REQUIRE(solved_unsolvable_board[i][j] == unsolvable_board[i][j]);
    }
  }

  for (size_t row = 0; row < 9; row++) {
    for (size_t col = 0; col < 9; col++) {
      for (size_t i = 0; i < 9; i++) {
        if (i != col) {
          REQUIRE(solved_normal_board[row][i] != solved_normal_board[row][col]);
          REQUIRE(solved_empty_board[row][i] != solved_empty_board[row][col]);
        }
        if (i != row) {
          REQUIRE(solved_normal_board[i][col] != solved_normal_board[row][col]);
          REQUIRE(solved_empty_board[i][col] != solved_empty_board[row][col]);
        }
      }

      for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
          if (!(row == i + (row / 3) * 3 &&
                col == j + (col / 3) * 3)) {
            REQUIRE(solved_normal_board[i + (row / 3) * 3][j + (col / 3) * 3] != 
                    solved_normal_board[row][col]);
            REQUIRE(solved_empty_board[i + (row / 3) * 3][j + (col / 3) * 3] !=
                    solved_empty_board[row][col]);
          }
        }
      }
    }
  }
}
