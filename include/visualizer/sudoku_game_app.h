#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "core/sudoku_board.h"
#include "visualizer/components/game_board.h"
#include "visualizer/components/level_box.h"

namespace sudokugame {

namespace visualizer {

using sudokugame::visualizer::GameBoard;
using sudokugame::visualizer::LevelBox;
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
  const size_t kKeyBoardEdgeOffset = 10;

  const float kKeyboardEdgeWidth = 2.0;
  const float kSolutionBoxEdgeWidth = 2.0;
  const float kKeyBoardEdgeWidth = 2.0;
  const float kSolutionBoxPosYParameter = 2.05;
  const float kKeyBoardPosYParameter = 2.05;
  
  const std::string kSolutionString = "Solution";
  const std::string kNoSolutionString = "No Solution";
  
  const std::vector<size_t> kKeyBoardNumbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  const vec2 kBoardTopLeft = vec2(80, 80);
  const vec2 kBoardRightBottom = vec2(710, 710);
  const vec2 kSolutionBoxTopLeft = vec2(800, 280);
  const vec2 kSolutionBoxBottomRight = vec2(1000, 320);
  const vec2 kKeyBoardTopLeft = vec2(800, 380);
  const vec2 kKeyBoardBottomRight = vec2(1001, 680);

  const ci::Color kBackGroundColor = ci::Color8u(219, 229, 214);
  const ci::Color kSolutionBoxColor = ci::Color8u(219, 229, 214);
  const ci::Color kSolutionBoxEdgeColor = "black";
  const ci::Color kKeyBoardColor = ci::Color8u(219, 229, 214);
  const ci::Color kKeyBoardEdgeColor = "black";

  const Font kSolutionFont = Font("Times New Roman", 30);
  const Font kKeyBoardFont = Font("Times New Roman", 48);
  
  void DrawSolutionBox(const std::string& solution_status);
  void ShowSolution(const ci::app::MouseEvent& event);
  
  void DrawKeyBoard();
  void ClickKeyBoard(const ci::app::MouseEvent& event);
  
  GameBoard game_board_;
  
  LevelBox level_box_;
  
  std::string solution_status_ = kSolutionString;
};

} // namespace visualizer

} // namespace sudokugame
