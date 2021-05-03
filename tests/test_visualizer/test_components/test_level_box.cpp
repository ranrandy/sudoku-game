#include <catch2/catch.hpp>

#include "visualizer/components/level_box.h"
#include "visualizer/components/game_board.h"

using sudokugame::visualizer::LevelBox;
using sudokugame::visualizer::GameBoard;
using std::vector;
using glm::vec2;

TEST_CASE("Change levels of the game") {
  LevelBox level_box;
  GameBoard game_board;
  game_board.GenerateValidBoard(GameBoard::Level::kMedium);
  
  /*
  SECTION("Click inside the level box") {
    level_box.ChangeLevels(vec2(900, 120), game_board);
  }
   */
}