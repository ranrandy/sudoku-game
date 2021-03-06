#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Text.h"
#include "cinder/Timer.h"

namespace sudokugame {

namespace visualizer {

using ci::Timer;
using ci::Font;
using glm::vec2;

class TimerBox {
 public:
  /**
   * Constructs a timer for the current sudoku game.
   */
  TimerBox();
  
  /**
   * Draws the timer box on the screen. 
   */
  void Draw();
  
  /**
   * Stops the timer, or stops the game.
   */
  void Stop();
  
  /**
   * Resumes the timer, or resume the game.
   */
  void Resume();
  
  /**
   * Resets the timer, or start a new game.
   */
  void Reset();
  
 private:
  // Board margin color
  const ci::Color kTimerBoxEdgeColor = "black";
  
  // Keyboard top left and bottom right positions
  const vec2 kTimerBoxTopLeft = vec2(850, 80);
  const vec2 kTimerBoxBottomRight = vec2(950, 100);
  
  // Timer font
  const Font kTimerFont = Font("Times New Roman", 36);
  
  const size_t kTimeScale = 60;
  const size_t kMaxHour = 100;
  const size_t kMaxMinute = 60;
  const size_t kMaxSecond = 60;
  
  const std::string kTimeDelimiter = ":";
  const std::string kTimePlaceHolder = "0";
  
  /**
   * Convert the system timer to a time string
   * @return the time string
   */
  std::string ConvertTimeToString();
  
  Timer timer_;
};

} // namespace visualizer

} // namespace sudokugame