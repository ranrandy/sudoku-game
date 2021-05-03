#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "core/sudoku_board.h"
#include "visualizer/components/game_board.h"
#include "visualizer/components/keyboard.h"
#include "visualizer/components/level_box.h"
#include "visualizer/components/timer_box.h"
#include "visualizer/components/solution_box.h"

namespace sudokugame {

namespace visualizer {

using sudokugame::visualizer::GameBoard;
using sudokugame::visualizer::Keyboard;
using sudokugame::visualizer::LevelBox;
using sudokugame::visualizer::TimerBox;
using sudokugame::visualizer::SolutionBox;
using ci::app::KeyEvent;
using glm::vec2;

/**
 * An app for visualizing the sudoku game interface.
 */
class SudokuGameApp : public ci::app::App {
public:
  /**
   * Default Constructor for a sudoku game app.
   */
  SudokuGameApp();

  /**
   * Handles key events.
   * @param event key event on the keyboard
   */
  void keyDown(KeyEvent event) override;
  
  /**
   * Handles mouse events.
   * @param event mouse event on a mouse
   */
  void mouseDown(ci::app::MouseEvent event) override;
  
  /**
   * Draws the screen based on components 
   * including game board, level box, solution box and keyboard box.
   */
  void draw() override;
  
  /**
   * Updates the screen per frame.
   */
  void update() override;

private:
  // provided that you can see the entire UI on your screen.
  const int kWindowLength = 1100;
  const int kWindowWidth = 800;
  
  const size_t kBoardSize = 9;
  
  const vec2 kBoardTopLeft = vec2(80, 80);
  const vec2 kBoardRightBottom = vec2(710, 710);
  const vec2 kSolutionBoxTopLeft = vec2(800, 280);
  const vec2 kSolutionBoxBottomRight = vec2(1000, 320);

  const ci::Color kBackGroundColor = ci::Color8u(219, 229, 214);
  
  GameBoard game_board_;
  
  Keyboard keyboard_;
  
  LevelBox level_box_;
  
  TimerBox timer_box_;
  
  SolutionBox solution_box_;
};

} // namespace visualizer

} // namespace sudokugame
