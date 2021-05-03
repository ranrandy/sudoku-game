#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "cinder/Text.h"
#include "core/sudoku_board.h"
#include "core/sudoku_solver.h"

namespace sudokugame {

namespace visualizer {

using sudokugame::SudokuBoard;
using ci::app::KeyEvent;
using ci::Font;
using glm::vec2;

/**
 * Displays the game board on the screen
 */
class GameBoard {
 public:
  // Represents different levels of the sudoku game
  enum class Level {
    kEasy, 
    kMedium, 
    kHard
  };
  
  /**
   * Constructs a board on the screen
   */
  GameBoard();

  /**
   * Draw the game board.
   */
  void Draw();
  
  /**
   * Sets level for the game and generate a new board for the new level.
   * @param level the level of the game
   */
  void GenerateValidBoard(Level level);
  
  /**
   * Shows a solution (full) board of the game
   * @return if the board has a solution
   */
  bool ShowSolution();
  
  /**
   * Adds a number to the board on the screen.
   * @param number the number to be added
   */
  void AddNumber(size_t number);
  
  /**
   * Removes the number on the clicked tile.
   * @param if the delete key is hit
   */
  void RemoveNumber(bool is_hit);
  
  /**
   * Handles highlighting related row, column and sub board on the screen 
   * after clicking on some tile.
   * @param event the mouse event
   */
  void HandleHighlighting(const ci::app::MouseEvent& event);
  
  /**
   * Handles highlighting related row, column and sub board on the screen 
   * after using computer keyboard to move the clicked tile.
   * @param event the key event
   */
  void HandleHighlighting(const ci::app::KeyEvent& event);

  /**
   * Initiate vectors related to highlighting.
   */
  void InitiateHighlighting();

 private:
  // Board background color
  const ci::Color kBoardColor = ci::Color8u(219, 229, 214);
  
  // Board margin color
  const ci::Color kSquareEdgeColor = "black";
  
  // Related tiles highlighting color
  const ci::Color kRelatedTileColor = ci::Color8u(207, 231, 196);
  
  // If the player clicks on a tile that has been filled with some number, 
  // the color of that tile
  const ci::Color kClickedOriginalTileColor = ci::Color8u(78, 123, 77);
  
  // If the player clicks on an empty tile, the color of that empty tile
  const ci::Color kClickedEmptyTileColor = ci::Color8u(167, 211, 151);
  
  // If the player clicks on a tile with some number, 
  // the color of those tiles who are filled with the same number and 
  // those numbers
  const ci::Color kSameNumberTileColor = ci::Color8u(132, 172, 68);
  const ci::Color kSameNumberTileNumberColor = "white";
  
  // The color of numbers who are added by the player
  // but not originally generated
  const ci::Color kAddedNumberTileColor = "blue";
  
  // Game board position
  const vec2 kBoardTopLeft = vec2(80, 80);
  const vec2 kBoardBottomRight = vec2(710, 710);

  // Different total number range in different game levels
  const size_t kDefaultNumberTotal = 30;
  const size_t kEasyLevelMaxTotal = 44;
  const size_t kEasyLevelMinTotal = 39;
  const size_t kMediumLevelMaxTotal = 38;
  const size_t kMediumLevelMinTotal = 33;
  const size_t kHardLevelMaxTotal = 32;
  const size_t kHardLevelMinTotal = 22;

  // Size of a sudoku game board
  const size_t kBoardSize = 9;
  
  const float kSubBoardMarginWidth = 3.0;
  const float kTileLineWidth = 1.0;
  
  // Parameters to fit the location of number strings on the screen
  // into the tiles
  const float kNumberPosXParameter = 0.5;
  const float kNumberPosYParameter = 0.25;
  
  const Font kNumberFont = Font("Times New Roman", 48);
  
  /**
   * Draws squares on the screen.
   * @param square_length the size (length) of each square
   * @param edge_line_width the width of the margin line of the square
   * @param number the number of squares to draw
   * @param is_tile if the square to be drawn is a tile
   */
  void DrawSquares(double square_length, float edge_line_width, size_t number, 
                   bool is_tile = true);
  
  /**
   * Draws number strings on the screen.
   */
  void DrawNumbers();

  // The position of the clicked tile
  vec2 clicked_tile_;
  
  // Related tiles in the same row, column or sub board to be highlighted
  vector<vec2> tiles_to_highlight_;
  
  // Tiles with identical numbers to be highlighted
  vector<vec2> same_number_tiles_to_highlight_;
  
  // A sudoku board object containing the numbers data and 
  // operate adding and removing numbers from the board
  SudokuBoard sudoku_board_;
};

} // namespace visualizer

} // namespace sudokugame