#pragma once

#include <vector>

namespace sudokugame {

using std::vector;

class SudokuSolution {
public:
  typedef vector<vector<char>> gameboard;
  
  SudokuSolution(const gameboard& board);

  bool Solve();

private:
  bool FillInNumbers(gameboard& board);

  bool IsFull(const gameboard& board);

  bool IsValid(const gameboard& board);

  bool IsValidTile(const gameboard& board, size_t row, size_t col, char number);
  
  gameboard sudoku_board_;
  std::vector<std::pair<size_t, size_t>> empty_tiles_;
  size_t tile_to_fill_;
};

} // namespace sudokugame
