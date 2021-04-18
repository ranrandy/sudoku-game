#include <catch2/catch.hpp>

#include "core/sudoku_board.h"
#include "core/sudoku_solver.h"

using sudokugame::SudokuBoard;
using sudokugame::SudokuSolver;
using std::vector;

TEST_CASE("Generate a board with valid size") {
  REQUIRE_THROWS_AS(SudokuBoard(-1), std::invalid_argument);
  REQUIRE_THROWS_AS(SudokuBoard(0), std::invalid_argument);
  REQUIRE_THROWS_AS(SudokuBoard(1), std::invalid_argument);
  REQUIRE_THROWS_AS(SudokuBoard(2), std::invalid_argument);
  REQUIRE(SudokuBoard(9).GetBoardSize() == 9);
  REQUIRE_THROWS_AS(SudokuBoard(36), std::invalid_argument);
}

TEST_CASE("Generate numbers on the board (size = 9)") {
  SudokuBoard game_board(9);

  SECTION("Generate an empty board") {
    game_board.GenerateValidBoard(0);
    SudokuSolver solution(game_board.GetBoardNumbers());
    REQUIRE(solution.Solve());
    REQUIRE(game_board.GetNumberTotal() == 0);
  }

  SECTION("Generate a board with the most numbers") {
    game_board.GenerateValidBoard(35);
    SudokuSolver solution(game_board.GetBoardNumbers());
    REQUIRE(solution.Solve());
    REQUIRE(game_board.GetNumberTotal() == 35);
  }

  SECTION("Generate a board too many numbers") {
    REQUIRE_THROWS_AS(game_board.GenerateValidBoard(36), std::invalid_argument);
  }
  
  SECTION("Generate board with random size") {
    game_board.GenerateValidBoard(20);
    SudokuSolver solution(game_board.GetBoardNumbers());
    REQUIRE(solution.Solve());
    REQUIRE(game_board.GetNumberTotal() == 20);
  }
}