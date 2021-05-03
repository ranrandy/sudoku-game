#include "visualizer/sudoku_game_app.h"

namespace sudokugame {

namespace visualizer {

SudokuGameApp::SudokuGameApp()
    : game_board_(), keyboard_(), level_box_(), timer_box_(), solution_box_() { 
  setWindowSize(kWindowLength, kWindowWidth);
}

void SudokuGameApp::keyDown(KeyEvent event) {
  game_board_.HandleHighlighting(event);
  game_board_.AddNumber(keyboard_.HitKeyboard(event));
  game_board_.RemoveNumber(keyboard_.HitDelete(event));
}

void SudokuGameApp::mouseDown(ci::app::MouseEvent event) {
  game_board_.HandleHighlighting(event);
  game_board_.AddNumber(keyboard_.ClickKeyboard(event));
  level_box_.ChangeLevels(event.getPos(), game_board_, timer_box_);
  solution_box_.ShowSolution(event, game_board_, timer_box_);
}

void SudokuGameApp::draw() {
  ci::gl::clear(kBackGroundColor);
  game_board_.Draw();
  keyboard_.DrawKeyboard();
  level_box_.DrawLevelBox();
  timer_box_.Draw();
  solution_box_.DrawSolutionBox();
}

void SudokuGameApp::update() {
  game_board_.InitiateHighlighting();
}

} // namespace visualizer

} // namespace sudokugame
