#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "visualizer/components/game_board.h"
#include "visualizer/components/timer_box.h"

namespace sudokugame {

namespace visualizer {

using sudokugame::visualizer::GameBoard;
using sudokugame::visualizer::TimerBox;
using ci::app::KeyEvent;
using glm::vec2;

/**
 * Displays the level box on the screen.
 */
class LevelBox {
public:
  /**
   * Constructs a Level box.
   */
  LevelBox();

  /**
   * Draws the level box on the screen.
   */
  void DrawLevelBox();
  
  /**
   * Changes the level of the game, and also starts a new game.
   * @param event_position the mouse event
   * @param game_board the sudoku game board
   * @param timer_box the timer box
   */
  void ChangeLevels(const vec2& event_position, GameBoard& game_board, 
                    TimerBox& timer_box);

private:
  const size_t kTotalLevels = 3;

  const float kLevelBoxEdgeWidth = 2.0;
  const float kLevelBoxPosYParameter = 2.08;

  const std::string kEasyLevel = "Easy";
  const std::string kMediumLevel = "Medium";
  const std::string kHardLevel = "Hard";
  
  const vec2 kLevelBoxTopLeft = vec2(800, 140);
  const vec2 kLevelBoxBottomRight = vec2(1000, 260);

  const ci::Color kLevelBoxColor = ci::Color8u(219, 229, 214);
  const ci::Color kLevelBoxEdgeColor = "black";

  const Font kLevelFont = Font("Times New Roman", 24);

  std::vector<vec2> level_centers_;
};

} // namespace visualizer

} // namespace sudokugame
