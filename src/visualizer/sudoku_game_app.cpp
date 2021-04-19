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
  ChangeLevels(event);
  ShowSolution(event);
  game_board_.HandleAddNumber(event);
}

void SudokuGameApp::draw() {
  ci::gl::clear(kBackGroundColor);
  
  game_board_.Draw();
  
  DrawLevelBox();
  
  DrawSolutionBox(solution_status_);
  
  DrawKeyBoard();
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

void SudokuGameApp::ChangeLevels(const ci::app::MouseEvent& event) {
  for (size_t level = 0; level < kTotalLevels; level++) {
    if (abs(level_centers_[level].x - float(event.getX())) <
        (kLevelBoxBottomRight.x - kLevelBoxTopLeft.x) / 2 &&
        abs(level_centers_[level].y - float(event.getY())) <
        (kLevelBoxBottomRight.y - kLevelBoxTopLeft.y) / 2) {
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

void SudokuGameApp::DrawSolutionBox(const std::string& solution_status) {
  ci::Rectf solution_box(kSolutionBoxTopLeft, kSolutionBoxBottomRight);
  ci::gl::color(kSolutionBoxColor);
  ci::gl::drawSolidRect(solution_box);
  ci::gl::color(kSolutionBoxEdgeColor);
  ci::gl::drawStrokedRect(solution_box, kSolutionBoxEdgeWidth);
  
  vec2 solution_string_center = 
      vec2((kSolutionBoxTopLeft.x + kSolutionBoxBottomRight.x) / 2,
           (kSolutionBoxTopLeft.y + kSolutionBoxBottomRight.y) / 
               kSolutionBoxPosYParameter);
  ci::gl::drawStringCentered(solution_status, solution_string_center, 
                             kSolutionBoxEdgeColor, kSolutionFont);
}

void SudokuGameApp::ShowSolution(const ci::app::MouseEvent& event) {
  vec2 solution_string_center =
      vec2((kSolutionBoxTopLeft.x + kSolutionBoxBottomRight.x) / 2,
           (kSolutionBoxTopLeft.y + kSolutionBoxBottomRight.y) / 2);
  if (abs(solution_string_center.x - float(event.getX())) < 
          (kLevelBoxBottomRight.x - kLevelBoxTopLeft.x) / 2 && 
      abs(solution_string_center.y - float(event.getY())) < 
          (kLevelBoxBottomRight.y - kLevelBoxTopLeft.y) / 2) {
    if (!game_board_.ShowSolution()) {
      solution_status_ = kNoSolutionString;
    }
  }
}

void SudokuGameApp::DrawKeyBoard() {
  ci::Rectf level_box(kKeyBoardTopLeft, kKeyBoardBottomRight);
  ci::gl::color(kKeyBoardColor);
  ci::gl::drawSolidRect(level_box);
  ci::gl::color(kKeyBoardEdgeColor);
  ci::gl::drawStrokedRect(level_box, kLevelBoxEdgeWidth);

  size_t rect_width = (kKeyBoardBottomRight.x - kKeyBoardTopLeft.x) / 
                      sqrt(kKeyBoardNumbers.size());
  size_t rect_length = (kKeyBoardBottomRight.y - kKeyBoardTopLeft.y) / 
                       sqrt(kKeyBoardNumbers.size());
  for (size_t row = 0; row < sqrt(kKeyBoardNumbers.size()); ++row) {
    for (size_t col = 0; col < sqrt(kKeyBoardNumbers.size()); ++col) {
      vec2 square_top_left = kKeyBoardTopLeft +
                             vec2(row * rect_width + 10,
                                  col * rect_length + 10);
      vec2 square_bottom_right = kKeyBoardTopLeft +
                                 vec2((row + 1) * rect_width - 10,
                                      (col + 1) * rect_length - 10);
      ci::Rectf square_bounding_box(square_top_left,
                                    square_bottom_right);
      ci::gl::color(kKeyBoardEdgeColor);
      ci::gl::drawStrokedRect(square_bounding_box, kKeyBoardEdgeWidth);
      vec2 keyboard_center = vec2((square_top_left.x + 
                                    square_bottom_right.x) / 2, 
                                   (square_top_left.y + square_bottom_right.y) / 
                                       kKeyBoardPosYParameter);
      ci::gl::drawStringCentered(
          std::to_string(kKeyBoardNumbers[col * sqrt(kKeyBoardNumbers.size()) + 
                                          row]), keyboard_center, 
          kKeyBoardEdgeColor, kKeyBoardFont);
    }
  }

}

}

} // namespace sudokugame
