#include "visualizer/components/timer_box.h"

namespace sudokugame {

namespace visualizer {

TimerBox::TimerBox(bool start_on_construction) {
  timer_ = Timer(start_on_construction);  
}

void TimerBox::Draw() {
  // Draws the time into the timer box.
  vec2 box_center = vec2((kTimerBoxTopLeft.x + kTimerBoxBottomRight.x) / 2,
                         (kTimerBoxTopLeft.y + kTimerBoxBottomRight.y) / 2);
  std::string time_str = ConvertTimeToString();
  
  ci::gl::drawStringCentered(time_str, box_center, kTimerBoxEdgeColor,
                             kTimerFont);
}

void TimerBox::Stop() {
  timer_.stop();
}

void TimerBox::Resume() {
  timer_.resume();
}

void TimerBox::Reset() {
  timer_.start();
}

std::string TimerBox::ConvertTimeToString() {
  std::string time_str;
  size_t hour = size_t(timer_.getSeconds()) / (kTimeScale * kTimeScale);
  if (hour / 10 == 0) {
    time_str += kTimePlaceHolder + std::to_string(hour) + kTimeDelimiter;
  } else if (hour < 100){
    time_str += std::to_string(hour) + kTimeDelimiter;
  }
  
  size_t minute = (size_t(timer_.getSeconds()) - kTimeScale * kTimeScale * 
                                                     hour) / kTimeScale;
  if (minute / 10 == 0) {
    time_str += kTimePlaceHolder + std::to_string(minute) + kTimeDelimiter;
  } else if (minute < 60) {
    time_str += std::to_string(minute) + kTimeDelimiter;
  }
  
  size_t second = size_t(timer_.getSeconds()) - kTimeScale * minute;
  if (second / 10 == 0) {
    time_str += kTimePlaceHolder + std::to_string(second);
  } else if (second < 60) {
    time_str += std::to_string(second);
  }
  return time_str;
}

} // visualizer

} // sudokugame