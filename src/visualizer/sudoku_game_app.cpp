#include "visualizer/sudoku_game_app.h"

namespace sudokugame {

namespace visualizer {

using ci::app::KeyEvent;
using sudokugame::visualizer::GameBoard;

SudokuGameApp::SudokuGameApp() { 
  setWindowSize(kWindowLength, kWindowWidth); 
}

void SudokuGameApp::keyDown(KeyEvent event) {
  if (event.getCode() == KeyEvent::KEY_DELETE) {
    std::cout << "later" << std::endl;
  }
}

void SudokuGameApp::mouseDown(ci::app::MouseEvent event) {
  for (size_t level = 0; level < kTotalLevels; level++) {
    if (abs(level_centers_[level].x - float(event.getX())) < 
            (kLevelBoxBottomRight.x - kLevelBoxTopLeft.x) / 2 && 
        abs(level_centers_[level].y - float(event.getY())) < 
            (kLevelBoxBottomRight.y - kLevelBoxTopLeft.y) / 2) {
      std::cout << "??" << std::endl;
      switch (level) {
      case 0:
        game_board_.SetLevel(GameBoard::Level::kEasy);
        break;
      case 1:
        game_board_.SetLevel(GameBoard::Level::kMedium);
        break;
      case 2:
        game_board_.SetLevel(GameBoard::Level::kHard);
        break;
      default:
        game_board_.SetLevel(GameBoard::Level::kMedium);
      }
    }
  }
}

void SudokuGameApp::draw() {
  ci::gl::clear(kBackGroundColor);
  
  game_board_.Draw();
  
  DrawLevelBox();
}

void SudokuGameApp::update() {
  
}

void SudokuGameApp::DrawLevelBox() {
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
             (level_box_top_left.y + level_box_bottom_right.y) / 2);
    level_centers_.push_back(level_box_center);
    ci::Rectf level_box_edge(level_box_top_left, level_box_bottom_right);
    ci::gl::color(kLevelBoxEdgeColor);
    ci::gl::drawStrokedRect(level_box_edge);
  }

  ci::gl::drawStringCentered(kEasyLevel, level_centers_.at(0), 
                             kLevelBoxEdgeColor);
  ci::gl::drawStringCentered(kMediumLevel, level_centers_.at(1), 
                             kLevelBoxEdgeColor);
  ci::gl::drawStringCentered(kHardLevel, level_centers_.at(2), 
                             kLevelBoxEdgeColor);
}

}

} // namespace sudokugame
