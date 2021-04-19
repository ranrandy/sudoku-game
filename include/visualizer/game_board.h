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
  void HandleAddNumber(const ci::app::MouseEvent& event, size_t number);

private:
  const ci::Color kBoardColor = "white";
  const ci::Color kSquareEdgeColor = "black";
  const ci::Color8u kTileToAddNumberColor = ci::Color8u(255, 246, 148);

  const size_t kDefaultNumberTotal = 30;
  const size_t kEasyLevelMaxTotal = 44;
  const size_t kEasyLevelMinTotal = 39;
  const size_t kMediumLevelMaxTotal = 38;
  const size_t kMediumLevelMinTotal = 33;
  const size_t kHardLevelMaxTotal = 32;
  const size_t kHardLevelMinTotal = 22;
  
  const float kSubBoardLineWidth = 3.0;
  const float kTileLineWidth = 1.0;
  const float kNumberPosXParameter = 0.5;
  const float kNumberPosYParameter = 0.25;

  const vec2 kDefaultTileToAddNumberPosition = vec2(-1, -1);

  const Font kNumberFont = Font("Times New Roman", 48);
  
  void DrawSquares(size_t square_length, size_t edge_line_width, size_t number, 
                   bool is_tile = true);
  void DrawNumbers();
  
  size_t board_size_;
  
  vec2 board_top_left_;
  vec2 board_bottom_right_;
  vec2 tile_to_add_number;
  
  SudokuBoard sudoku_board_;
};

} // visualizer

} // sudokugame