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
using ci::Font;
using glm::vec2;

class GameBoard {
public:
  enum class Level {
    kEasy, 
    kMedium, 
    kHard
  };
  
  GameBoard(const vec2& board_top_left, const vec2& board_right_bottom, 
            size_t board_size, Level level = Level::kMedium);

  void Draw();
  
  void SetLevel(Level level);
  bool ShowSolution();
  void AddNumber(size_t number);
  void HandleHighlighting(const ci::app::MouseEvent& event);
  
private:
  const ci::Color kBoardColor = ci::Color8u(219, 229, 214);
  const ci::Color kSquareEdgeColor = "black";
  const ci::Color kRelatedTileColor = ci::Color8u(207, 231, 196);
  const ci::Color kClickedOriginalTileColor = ci::Color8u(78, 123, 77);
  const ci::Color kClickedEmptyTileColor = ci::Color8u(167, 211, 151);
  const ci::Color kSameNumberTileColor = ci::Color8u(132, 172, 68);
  const ci::Color kSameNumberTileNumberColor = "white";
  const ci::Color kAddedNumberTileColor = "yellow";

  const size_t kDefaultNumberTotal = 30;
  const size_t kEasyLevelMaxTotal = 44;
  const size_t kEasyLevelMinTotal = 39;
  const size_t kMediumLevelMaxTotal = 38;
  const size_t kMediumLevelMinTotal = 33;
  const size_t kHardLevelMaxTotal = 32;
  const size_t kHardLevelMinTotal = 22;
  const size_t kBoardSize = 9;
  
  const float kSubBoardLineWidth = 3.0;
  const float kTileLineWidth = 1.0;
  const float kNumberPosXParameter = 0.5;
  const float kNumberPosYParameter = 0.25;
  
  const Font kNumberFont = Font("Times New Roman", 48);
  
  void DrawSquares(size_t square_length, size_t edge_line_width, size_t number, 
                   bool is_tile = true);
  void DrawNumbers();
  
  size_t board_size_;
  
  vec2 board_top_left_;
  vec2 board_bottom_right_;
  vec2 clicked_tile_;
  
  vector<vec2> tiles_to_highlight_;
  vector<vec2> same_number_tiles_to_highlight_;
  
  SudokuBoard sudoku_board_;
};

} // visualizer

} // sudokugame