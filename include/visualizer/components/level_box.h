#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "visualizer/components/game_board.h"

namespace sudokugame {

namespace visualizer {

using sudokugame::visualizer::GameBoard;
using ci::app::KeyEvent;
using glm::vec2;

/**
 * Displays the level box on the screen.
 */
class LevelBox {
public:
  /**
   * Default Constructor for a Level box.
   */
  LevelBox();

  void DrawLevelBox();
  void ChangeLevels(const vec2& event_position, GameBoard& game_board);

private:
  const size_t kTotalLevels = 3;

  const float kLevelBoxEdgeWidth = 2.0;
  const float kLevelBoxPosYParameter = 2.08;

  const std::string kEasyLevel = "Easy";
  const std::string kMediumLevel = "Medium";
  const std::string kHardLevel = "Hard";
  
  const vec2 kLevelBoxTopLeft = vec2(800, 80);
  const vec2 kLevelBoxBottomRight = vec2(1000, 200);

  const ci::Color kLevelBoxColor = ci::Color8u(219, 229, 214);
  const ci::Color kLevelBoxEdgeColor = "black";

  const Font kLevelFont = Font("Times New Roman", 24);

  std::vector<vec2> level_centers_;
};

} // namespace visualizer

} // namespace sudokugame
