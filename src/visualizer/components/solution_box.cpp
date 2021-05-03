#include "visualizer/components/solution_box.h"

namespace sudokugame {

namespace visualizer {

SolutionBox::SolutionBox() {}

void SolutionBox::DrawSolutionBox() {
  ci::Rectf solution_box(kSolutionBoxTopLeft, kSolutionBoxBottomRight);
  ci::gl::color(kSolutionBoxColor);
  ci::gl::drawSolidRect(solution_box);
  ci::gl::color(kSolutionBoxEdgeColor);
  ci::gl::drawStrokedRect(solution_box, kSolutionBoxEdgeWidth);

  vec2 solution_string_center =
      vec2((kSolutionBoxTopLeft.x + kSolutionBoxBottomRight.x) / 2,
           (kSolutionBoxTopLeft.y + kSolutionBoxBottomRight.y) /
           kSolutionBoxPosYParameter);
  ci::gl::drawStringCentered(kSolutionString, solution_string_center,
                             kSolutionBoxEdgeColor, kSolutionFont);
}

void SolutionBox::ShowSolution(const ci::app::MouseEvent& event, 
                               GameBoard& game_board, TimerBox& timer_box) {
  vec2 solution_string_center =
      vec2((kSolutionBoxTopLeft.x + kSolutionBoxBottomRight.x) / 2,
           (kSolutionBoxTopLeft.y + kSolutionBoxBottomRight.y) / 2);
  if (abs(solution_string_center.x - float(event.getX())) <
      (kSolutionBoxBottomRight.x - kSolutionBoxTopLeft.x) / 2 &&
      abs(solution_string_center.y - float(event.getY())) <
      (kSolutionBoxBottomRight.y - kSolutionBoxTopLeft.y) / 2) {
    game_board.ShowSolution();
    timer_box.Stop();
  }
}

} // namespace visualizer

} // namespace sudokugame
