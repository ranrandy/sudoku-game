#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "visualizer/components/game_board.h"

namespace sudokugame {

namespace visualizer {

using sudokugame::visualizer::GameBoard;
using ci::app::KeyEvent;
using ci::Font;
using glm::vec2;

class Keyboard {
 public:
  /**
   * Constructs a keyboard instance.
   */
  Keyboard(); 
  
  /**
   * Draw the keyboard on the screen.
   */
  void DrawKeyboard();
  
  /**
   * Handles clicking on keyboard.
   * @param event the mouse event
   * @return the number to be added to the game board
   */
  size_t ClickKeyboard(const ci::app::MouseEvent& event);
  
  /**
   * Handles hitting on the computer keyboard
   * @param event the key event
   * @return the number to be added to the game board
   */
  size_t HitKeyboard(const ci::app::KeyEvent& event);
  
  /**
   * Handles hitting on the delete key (fn + delete on mac).
   * @param event the key event
   * @return true if delete key is hit
   */
  bool HitDelete(const ci::app::KeyEvent& event);
  
 private:
  // The distance between different keys on the keyboard 
  const size_t kKeyboardEdgeOffset = 10;

  // The margin line width of the keyboard
  const float kKeyboardEdgeWidth = 2.0;
  
  // The parameter used to fit the numbers in the key box to the center
  const float kKeyboardPosYParameter = 2.05;
  
  // The key numbers
  const std::vector<size_t> kKeyboardNumbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  // Keyboard top left and bottom right positions
  const vec2 kKeyboardTopLeft = vec2(800, 380);
  const vec2 kKeyboardBottomRight = vec2(1001, 680);

  // Keyboard background color and edge color
  const ci::Color kKeyboardColor = ci::Color8u(219, 229, 214);
  const ci::Color kKeyboardEdgeColor = "black";

  // The font of the number in key boxes
  const Font kKeyboardFont = Font("Times New Roman", 48);
};

} // namespace visualizer

} // namespace sudokugame
