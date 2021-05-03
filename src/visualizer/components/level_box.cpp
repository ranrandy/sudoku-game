#include "visualizer/components/level_box.h"

namespace sudokugame {

namespace visualizer {

LevelBox::LevelBox() {}

void LevelBox::DrawLevelBox() {
  ci::Rectf level_box(kLevelBoxTopLeft, kLevelBoxBottomRight);
  ci::gl::color(kLevelBoxColor);
  ci::gl::drawSolidRect(level_box);
  ci::gl::color(kLevelBoxEdgeColor);
  ci::gl::drawStrokedRect(level_box, kLevelBoxEdgeWidth);

  for (size_t row = 0; row < kTotalLevels; row++) {
    float level_box_height = (kLevelBoxBottomRight.y - kLevelBoxTopLeft.y) /
                             kTotalLevels;
    vec2 level_box_top_left = vec2(kLevelBoxTopLeft.x,
                                   kLevelBoxTopLeft.y +
                                   level_box_height * row);
    vec2 level_box_bottom_right = vec2(kLevelBoxBottomRight.x,
                                       kLevelBoxTopLeft.y +
                                       level_box_height * (row + 1.0));
    vec2 level_box_center =
        vec2((level_box_top_left.x + level_box_bottom_right.x) / 2,
             (level_box_top_left.y + level_box_bottom_right.y) /
             kLevelBoxPosYParameter);
    level_centers_.push_back(level_box_center);
    ci::Rectf level_box_edge(level_box_top_left, level_box_bottom_right);
    ci::gl::color(kLevelBoxEdgeColor);
    ci::gl::drawStrokedRect(level_box_edge);
  }

  ci::gl::drawStringCentered(kEasyLevel, level_centers_.at(0),
                             kLevelBoxEdgeColor, kLevelFont);
  ci::gl::drawStringCentered(kMediumLevel, level_centers_.at(1),
                             kLevelBoxEdgeColor, kLevelFont);
  ci::gl::drawStringCentered(kHardLevel, level_centers_.at(2),
                             kLevelBoxEdgeColor, kLevelFont);
}

void LevelBox::ChangeLevels(const MouseEvent& event, GameBoard& game_board, 
                            TimerBox& timer_box) {
  for (size_t level = 0; level < kTotalLevels; level++) {
    if (abs(level_centers_[level].x - float(event.getPos().x)) <
        (kLevelBoxBottomRight.x - kLevelBoxTopLeft.x) / 2 &&
        abs(level_centers_[level].y - float(event.getPos().y)) <
        (kLevelBoxBottomRight.y - kLevelBoxTopLeft.y) / 2) {
      switch (level) {
        case 0: {
          game_board.GenerateValidBoard(GameBoard::Level::kEasy);
          break;
        }
        case 1: {
          game_board.GenerateValidBoard(GameBoard::Level::kMedium);
          break;
        }
        case 2: {
          game_board.GenerateValidBoard(GameBoard::Level::kHard);
          break;
        }
        default: {
          game_board.GenerateValidBoard(GameBoard::Level::kMedium);
        }
      }
      timer_box.Reset();
    }
  }
}

} // namespace visualizer

} // namespace sudokugame
