#include "visualizer/sudoku_game_app.h"

namespace sudokugame {

namespace visualizer {

SudokuGameApp::SudokuGameApp()
    : game_board_(kBoardTopLeft, kBoardRightBottom, kBoardSize), 
      keyboard_() { 
  setWindowSize(kWindowLength, kWindowWidth);
}

void SudokuGameApp::keyDown(KeyEvent event) {
  game_board_.HandleHighlighting(event);
  game_board_.AddNumber(keyboard_.HitKeyboard(event));
  game_board_.RemoveNumber(keyboard_.HitDelete(event));
}

void SudokuGameApp::mouseDown(ci::app::MouseEvent event) {
  level_box_.ChangeLevels(event.getPos(), game_board_);
  ShowSolution(event);
  game_board_.HandleHighlighting(event);
  game_board_.AddNumber(keyboard_.ClickKeyboard(event));
}

void SudokuGameApp::draw() {
  ci::gl::clear(kBackGroundColor);
  
  game_board_.Draw();
  
  level_box_.DrawLevelBox();
  
  DrawSolutionBox(solution_status_);
  
  keyboard_.DrawKeyboard();
}

void SudokuGameApp::update() {
  game_board_.InitiateHighlighting();
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

} // namespace visualizer

} // namespace sudokugame
