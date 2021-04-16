#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

namespace sudokugame {

using std::vector;

class GameBoard {
public:
  /**
   * Constructor for a sudoku game board.
   * @param board_size the size of the board
   */
  GameBoard(size_t board_size);
  
  /**
   * The total number of integers to generate on the board.
   */
  void GenerateNumbers(size_t number_total);
  
private:
  size_t board_size_;
  size_t number_total_;

  vector<vector<size_t>> board_;
};

} // namespace sudokugame

