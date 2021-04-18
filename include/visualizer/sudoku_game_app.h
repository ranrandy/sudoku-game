#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "visualizer/game_board.h"
#include "core/sudoku_board.h"

namespace sudokugame {

namespace visualizer {

using sudokugame::visualizer::GameBoard;
using ci::app::KeyEvent;
using glm::vec2;

/**
 * An app for visualizing the sudoku game interface.
 */
class SudokuGameApp : public ci::app::App {
public:
  SudokuGameApp();

  void keyDown(KeyEvent event) override;
  void mouseDown(ci::app::MouseEvent event) override;
  void draw() override;
  void update() override;

private:
  // provided that you can see the entire UI on your screen.
  const int kWindowLength = 1100;
  const int kWindowWidth = 800;
  
  const size_t kBoardSize = 9;
  const size_t kTotalLevels = 3;
  
  const float kLevelBoxEdgeWidth = 2.0;
  
  const std::string kEasyLevel = "Easy";
  const std::string kMediumLevel = "Medium";
  const std::string kHardLevel = "Hard";

  const vec2 kBoardTopLeft = vec2(80, 80);
  const vec2 kBoardRightBottom = vec2(710, 710);
  const vec2 kLevelBoxTopLeft = vec2(800, 80);
  const vec2 kLevelBoxBottomRight = vec2(1000, 200);

  // light yellow
  const ci::Color8u kBackGroundColor = ci::Color8u(255, 246, 148);
  const ci::Color kLevelBoxColor = "white";
  const ci::Color kLevelBoxEdgeColor = "black";

  void DrawLevelBox();

  GameBoard game_board_ = GameBoard(kBoardTopLeft, kBoardRightBottom,
                                    kBoardSize);
  std::vector<vec2> level_centers_;
};

} // namespace visualizer

} // namespace sudokugame
