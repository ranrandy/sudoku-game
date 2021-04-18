#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "sudoku_solver.h"

namespace sudokugame {

using std::vector;

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
   * Insert a number to the board.
   * @param row the row index to insert number
   * @param col the column index to insert number
   * @param number the number to be inserted to the board
   * @return if the number is successfully inserted
   */
  bool InsertNumber(size_t row, size_t col, size_t number);
  
  /**
   * Gets the board size.
   * @return the size of the board
   */
  size_t GetBoardSize() const;

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
  
private:
  const size_t kMaxBoardSize = 9;
  const size_t kMinBoardSize = 4;
  const size_t kSizeNineMaxTotalNumber = 35;
  
  void GenerateNumbers(size_t number_total);
  
  bool IsValidTile(size_t row, size_t col, size_t number) const;
  bool IsValidSubBoard(size_t row, size_t col, size_t number) const;
  
  size_t board_size_;
  size_t number_total_;

  vector<vector<size_t>> board_;
};

} // namespace sudokugame

