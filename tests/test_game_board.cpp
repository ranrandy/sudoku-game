#include <catch2/catch.hpp>

#include "game_board.h"

using sudokugame::GameBoard;

TEST_CASE("Generate a board with valid size") {
  REQUIRE_THROWS_AS(GameBoard(-1), std::invalid_argument);
  REQUIRE_THROWS_AS(GameBoard(0), std::invalid_argument);
  REQUIRE_THROWS_AS(GameBoard(1), std::invalid_argument);
  REQUIRE_THROWS_AS(GameBoard(2), std::invalid_argument);
  REQUIRE(GameBoard(9).GetBoardSize() == 9);
  REQUIRE_THROWS_AS(GameBoard(36), std::invalid_argument);
}

TEST_CASE("Generate numbers on the board") {
  GameBoard game_board(25);
  
  game_board.GenerateNumbers(500);
  
}