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
   * Constructs a sudoku board given the board size.
   * @param board_size the size of the board
   */
  SudokuBoard(size_t board_size);
  
  /**
   * Constructs a sudoku board given the
   * @param board a 2d array consisting numbers in it
   */
  SudokuBoard(const vector<vector<size_t>>& board);
  
  /**
   * Generate a valid board of numbers given the total number.
   * @param number_total the total number of numbers on the board
   */
  void GenerateValidBoard(size_t number_total);

  /**
   * Adds a number that is added by the player to the board.
   * @param position the position where the player adds number
   * @param number the number to be added
   */
  void AddNumber(const glm::vec2& position, size_t number);

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
  
  /**
   * Gets the tiles whose number is added by the player.
   * @return a vector of tiles whose number is added by the player
   */
  const vector<glm::vec2>& GetTilesAddedNumber() const;
  
  /**
   * Clears the vector storing tiles whose number is added by the player
   */
  void ClearTilesAddedNumber();
  
  /**
   * Sets the numbers on a board
   * @param board the board to copy from
   */
  void SetBoardNumbers(const vector<vector<size_t>>& board);
  
private:
  const size_t kMaxBoardSize = 9;
  const size_t kMinBoardSize = 4;
  const size_t kGeneratingParameter = 3;

  /** 
   * Adds a number to the board.
   * @param row the row index to add number
   * @param col the column index to add number
   * @param number the number to add
   * @return if the number added conforms the rule of the game
   */
  bool AddNumber(size_t row, size_t col, size_t number);
  
  /**
   * Randomly generate some numbers on the board.
   * @param number_total the total number of numbers to be generated
   */
  void GenerateNumbers(size_t number_total);
  
  /**
   * Removes numbers from the board.
   * @param number_to_remove the total number of numbers to be removed
   */
  void RemoveNumbers(size_t number_to_remove);
  
  /**
   * Checks if adding number to a certain tile will conform to the rule.
   * @param row row index
   * @param col column index
   * @param number the number to be added
   * @return if adding the number conforms to the rule
   */
  bool IsValidTile(size_t row, size_t col, size_t number) const;
  
  /**
   * Checks if adding a number to a sub board will conform to the rule.
   * @param row row index
   * @param col column index
   * @param number the number to be added
   * @return if adding the number conforms to the rule in a sub board
   */
  bool IsValidSubBoard(size_t row, size_t col, size_t number) const;
  
  size_t board_size_;

  vector<glm::vec2> tiles_added_number_;

  vector<vector<size_t>> board_;
};

} // namespace sudokugame

