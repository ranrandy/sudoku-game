#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "sudoku_solver.h"

namespace sudokugame {

using std::vector;

/**
 * A Sudoku board containing the data of one sudoku game.
 */
class SudokuBoard {
public:
  /**
   * Constructor for a sudoku game board.
   * @param board_size the size of the board
   */
  SudokuBoard(size_t board_size);
  
  /**
   * Generate a valid board of numbers given the total number.
   * @param number_total the total number of numbers on the board
   */
  void GenerateValidBoard(size_t number_total);
  
  /**
   * Gets a 2D array containing the numbers on the board.
   * @return a 2D array containing the numbers on the board
   */
  const vector<vector<size_t>>& GetBoardNumbers() const;
  
  /**
   * Gets the total number of numbers on the board.
   * @return the total number of numbers on the board
   */
  size_t GetNumberTotal() const;

  /**
   * Gets the board size.
   * @return the size of the board
   */
  size_t GetBoardSize() const;
  
private:
  const size_t kMaxBoardSize = 9;
  const size_t kMinBoardSize = 4;
  const size_t kGeneratingParameter = 3;
  
  bool AddNumber(size_t row, size_t col, size_t number);
  void GenerateNumbers(size_t number_total);
  void RemoveNumbers(size_t number_to_remove);
  
  bool IsValidTile(size_t row, size_t col, size_t number) const;
  bool IsValidSubBoard(size_t row, size_t col, size_t number) const;
  
  size_t board_size_;
  size_t number_total_;

  vector<vector<size_t>> board_;
};

} // namespace sudokugame

