#include "visualizer/components/keyboard.h"

namespace sudokugame {

namespace visualizer {

Keyboard::Keyboard() {}

void Keyboard::DrawKeyboard() {
  ci::Rectf level_box(kKeyboardTopLeft, kKeyboardBottomRight);
  ci::gl::color(kKeyboardColor);
  ci::gl::drawSolidRect(level_box);
  ci::gl::color(kKeyboardEdgeColor);
  ci::gl::drawStrokedRect(level_box, kKeyboardEdgeWidth);

  size_t rect_width = (kKeyboardBottomRight.x - kKeyboardTopLeft.x) /
                      sqrt(kKeyboardNumbers.size());
  size_t rect_length = (kKeyboardBottomRight.y - kKeyboardTopLeft.y) /
                       sqrt(kKeyboardNumbers.size());
  for (size_t row = 0; row < sqrt(kKeyboardNumbers.size()); row++) {
    for (size_t col = 0; col < sqrt(kKeyboardNumbers.size()); col++) {
      vec2 square_top_left =
          kKeyboardTopLeft +
          vec2(row * rect_width + kKeyboardEdgeOffset,
               col * rect_length + kKeyboardEdgeOffset);
      vec2 square_bottom_right =
          kKeyboardTopLeft +
          vec2((row + 1) * rect_width - kKeyboardEdgeOffset,
               (col + 1) * rect_length - kKeyboardEdgeOffset);
      ci::Rectf square_bounding_box(square_top_left,
                                    square_bottom_right);
      ci::gl::color(kKeyboardEdgeColor);
      ci::gl::drawStrokedRect(square_bounding_box, kKeyboardEdgeWidth);
      vec2 Keyboard_center = vec2((square_top_left.x +
                                   square_bottom_right.x) / 2,
                                  (square_top_left.y + square_bottom_right.y) /
                                  kKeyboardPosYParameter);
      ci::gl::drawStringCentered(
          std::to_string(kKeyboardNumbers[col * sqrt(kKeyboardNumbers.size()) +
                                          row]), Keyboard_center,
          kKeyboardEdgeColor, kKeyboardFont);
    }
  }
}

size_t Keyboard::ClickKeyboard(const ci::app::MouseEvent& event) {
  size_t rect_length = (kKeyboardBottomRight.y - kKeyboardTopLeft.y) /
                       sqrt(kKeyboardNumbers.size());
  size_t rect_width = (kKeyboardBottomRight.x - kKeyboardTopLeft.x) /
                      sqrt(kKeyboardNumbers.size());
  vec2 clicked_key_position =
      vec2((event.getX() - int(kKeyboardTopLeft.x)) / rect_width,
           (event.getY() - int(kKeyboardTopLeft.y)) / rect_length);

  vec2 clicked_key_center = kKeyboardTopLeft +
                            vec2((clicked_key_position.x + 0.5) * rect_width,
                                 (clicked_key_position.y + 0.5) * rect_length);

  if (abs(int(clicked_key_center.x) - event.getX()) <
      rect_length / 2 - kKeyboardEdgeOffset &&
      abs(int(clicked_key_center.y) - event.getY()) <
      rect_width / 2 - kKeyboardEdgeOffset) {
    return kKeyboardNumbers[clicked_key_position.y * 
                                sqrt(kKeyboardNumbers.size()) +
                            clicked_key_position.x];
  }
  return 0;
}

size_t Keyboard::HitKeyboard(const ci::app::KeyEvent& event) {
  switch (event.getCode()) { 
  case KeyEvent::KEY_1:
    return kKeyboardNumbers[0];
  case KeyEvent::KEY_2:
    return kKeyboardNumbers[1];
  case KeyEvent::KEY_3:
    return kKeyboardNumbers[2];
  case KeyEvent::KEY_4:
    return kKeyboardNumbers[3];
  case KeyEvent::KEY_5:
    return kKeyboardNumbers[4];
  case KeyEvent::KEY_6:
    return kKeyboardNumbers[5];
  case KeyEvent::KEY_7:
    return kKeyboardNumbers[6];
  case KeyEvent::KEY_8:
    return kKeyboardNumbers[7];
  case KeyEvent::KEY_9:
    return kKeyboardNumbers[8];
  default:
    return 0;
  }
}

bool Keyboard::HitDelete(const ci::app::KeyEvent &event) {
  if (event.getCode() == KeyEvent::KEY_DELETE || 
      event.getCode() == KeyEvent::KEY_BACKSPACE) {
    return true;
  }
  return false;
}

} // visualizer

} // sudokugame