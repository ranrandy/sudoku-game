#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "visualizer/components/game_board.h"

namespace sudokugame {

namespace visualizer {

using glm::vec2;

class SolutionBox {
 public:
  /**
   * Constructs a solution box on the screen.
   */
  SolutionBox();
  
  /**
   * Draws the solution box on the screen.
   */
  void DrawSolutionBox();
  
  /**
   * Shows the solution of the game if the solution box is clicked
   * @param event the mouse event
   * @param game_board the sudoku game board
   */
  void ShowSolution(const ci::app::MouseEvent& event, GameBoard& game_board);
  
 private:
  const float kSolutionBoxEdgeWidth = 2.0;
  const float kSolutionBoxPosYParameter = 2.05;

  const std::string kSolutionString = "Solution";

  const vec2 kSolutionBoxTopLeft = vec2(800, 280);
  const vec2 kSolutionBoxBottomRight = vec2(1000, 320);

  const ci::Color kSolutionBoxColor = ci::Color8u(219, 229, 214);
  const ci::Color kSolutionBoxEdgeColor = "black";

  const Font kSolutionFont = Font("Times New Roman", 30);
};

} // namespace visualizer

} // namespace sudokugame
