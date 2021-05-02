#include "visualizer/sudoku_game_app.h"

namespace sudokugame {

namespace visualizer {

using ci::app::KeyEvent;
using sudokugame::visualizer::GameBoard;

SudokuGameApp::SudokuGameApp()
    : game_board_(GameBoard(kBoardTopLeft, kBoardRightBottom, kBoardSize)) { 
  setWindowSize(kWindowLength, kWindowWidth);
}

void SudokuGameApp::keyDown(KeyEvent event) {
  if (event.getCode() == KeyEvent::KEY_DELETE) {
    std::cout << "later" << std::endl;
  }
}

void SudokuGameApp::mouseDown(ci::app::MouseEvent event) {
  level_box_.ChangeLevels(event.getPos(), game_board_);
  ShowSolution(event);
  game_board_.HandleHighlighting(event);
  ClickKeyBoard(event);
}

void SudokuGameApp::draw() {
  ci::gl::clear(kBackGroundColor);
  
  game_board_.Draw();
  
  level_box_.DrawLevelBox();
  
  DrawSolutionBox(solution_status_);
  
  DrawKeyBoard();
}

void SudokuGameApp::update() {
  
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
          (kSolutionBoxBottomRight.x - kSolutionBoxTopLeft.x) / 2 && 
      abs(solution_string_center.y - float(event.getY())) < 
          (kSolutionBoxBottomRight.y - kSolutionBoxTopLeft.y) / 2) {
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
  ci::gl::drawStrokedRect(level_box, kKeyboardEdgeWidth);

  size_t rect_width = (kKeyBoardBottomRight.x - kKeyBoardTopLeft.x) / 
                      sqrt(kKeyBoardNumbers.size());
  size_t rect_length = (kKeyBoardBottomRight.y - kKeyBoardTopLeft.y) / 
                       sqrt(kKeyBoardNumbers.size());
  for (size_t row = 0; row < sqrt(kKeyBoardNumbers.size()); row++) {
    for (size_t col = 0; col < sqrt(kKeyBoardNumbers.size()); col++) {
      vec2 square_top_left = 
          kKeyBoardTopLeft +
          vec2(row * rect_width + kKeyBoardEdgeOffset,
               col * rect_length + kKeyBoardEdgeOffset);
      vec2 square_bottom_right = 
          kKeyBoardTopLeft + 
          vec2((row + 1) * rect_width - kKeyBoardEdgeOffset,
               (col + 1) * rect_length - kKeyBoardEdgeOffset);
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

void SudokuGameApp::ClickKeyBoard(const ci::app::MouseEvent& event) {
  size_t rect_length = (kKeyBoardBottomRight.y - kKeyBoardTopLeft.y) / 
                         sqrt(kKeyBoardNumbers.size());
  size_t rect_width = (kKeyBoardBottomRight.x - kKeyBoardTopLeft.x) /
                         sqrt(kKeyBoardNumbers.size());
  vec2 clicked_key_position =
      vec2((event.getX() - int(kKeyBoardTopLeft.x)) / rect_width,
           (event.getY() - int(kKeyBoardTopLeft.y)) / rect_length);
  
  vec2 clicked_key_center = kKeyBoardTopLeft +
                            vec2((clicked_key_position.x + 0.5) * rect_width,
                                 (clicked_key_position.y + 0.5) * rect_length);

  if (abs(int(clicked_key_center.x) - event.getX()) < 
      rect_length / 2 - kKeyBoardEdgeOffset && 
      abs(int(clicked_key_center.y) - event.getY()) <
          rect_width / 2 - kKeyBoardEdgeOffset) {
    game_board_.AddNumber(kKeyBoardNumbers[clicked_key_position.y * 
                                               sqrt(kKeyBoardNumbers.size()) + 
                                           clicked_key_position.x]);
  }
}

} // namespace visualizer

} // namespace sudokugame
