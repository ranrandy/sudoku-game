#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "sudoku_solver.h"

namespace sudokugame {

using std::vector;

/**
 * A Sudoku board containing the data (numbers) of one sudoku game.
 */
class SudokuBoard {
 public:
  /**
   * Constructs an empty sudoku board given the board size.
   * @param board_size the size of the board
   */
  explicit SudokuBoard(size_t board_size);
  
  /**
   * Constructs a sudoku board given a 2D vector board with numbers.
   * @param board a 2D array consisting numbers in it
   */
  explicit SudokuBoard(const vector<vector<size_t>>& board);
  
  /**
   * Generates a valid board of numbers given the number total on the board.
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
   * Removes a number that is added by the player from the board.
   * @param position the position where the player wants to remove a number
   */
  void RemoveNumber(const glm::vec2& position);

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
   * @return a vector of tile positions at where the number is added by player
   */
  const vector<glm::vec2>& GetAddedTiles() const;
  
  /**
   * Clears the vector storing tiles whose number is added by the player
   */
  void ClearAddedTiles();
  
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
   * Checks if adding number to a certain tile conforms to the rule.
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
  
  /**
   * Checks if the number at this position was added by the player.
   * @param position the position to check
   * @return true if the number was not originally generated
   */
  bool IsAddedByPlayer(const glm::vec2& position);
  
  // The size of the sudoku game board
  size_t board_size_;

  // Stores the tiles whose number was added by the player.
  vector<glm::vec2> tiles_added_number_;

  // Stores a 2D vector containing the numbers on a board.
  vector<vector<size_t>> board_;
};

} // namespace sudokugame

