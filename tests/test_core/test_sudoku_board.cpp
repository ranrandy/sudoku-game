#include <catch2/catch.hpp>

#include "core/sudoku_board.h"
#include "core/sudoku_solver.h"

using sudokugame::SudokuBoard;
using sudokugame::SudokuSolver;
using std::vector;
using glm::vec2;

TEST_CASE("Generate a board with valid size") {
  REQUIRE_THROWS_AS(SudokuBoard(-1), std::invalid_argument);
  REQUIRE_THROWS_AS(SudokuBoard(0), std::invalid_argument);
  REQUIRE_THROWS_AS(SudokuBoard(1), std::invalid_argument);
  REQUIRE_THROWS_AS(SudokuBoard(2), std::invalid_argument);
  REQUIRE(SudokuBoard(9).GetBoardSize() == 9);
  REQUIRE_THROWS_AS(SudokuBoard(36), std::invalid_argument);
}

TEST_CASE("Generate numbers on the board (size = 9)") {
  SudokuBoard sudoku_board(9);

  SECTION("Generate an empty board") {
    sudoku_board.GenerateValidBoard(0);
    SudokuSolver solution(sudoku_board.GetBoardNumbers());
    REQUIRE(solution.Solve());
    REQUIRE(sudoku_board.GetNumberTotal() == 0);
  }

  SECTION("Generate a full board") {
    sudoku_board.GenerateValidBoard(81);
    SudokuSolver solution(sudoku_board.GetBoardNumbers());
    REQUIRE(solution.Solve());
    REQUIRE(sudoku_board.GetNumberTotal() == 81);
  }

  SECTION("Generate a board with too many numbers") {
    REQUIRE_THROWS_AS(sudoku_board.GenerateValidBoard(82), 
                      std::invalid_argument);
  }
  
  SECTION("Generate board with random size") {
    sudoku_board.GenerateValidBoard(20);
    SudokuSolver solution(sudoku_board.GetBoardNumbers());
    REQUIRE(solution.Solve());
    REQUIRE(sudoku_board.GetNumberTotal() == 20);
  }
}

TEST_CASE("Generate numbers on the board (size = 4)") {
  SudokuBoard sudoku_board(4);

  SECTION("Generate an empty board") {
    sudoku_board.GenerateValidBoard(0);
    SudokuSolver solution(sudoku_board.GetBoardNumbers());
    REQUIRE(solution.Solve());
    REQUIRE(sudoku_board.GetNumberTotal() == 0);
  }

  SECTION("Generate a board with the most numbers") {
    sudoku_board.GenerateValidBoard(16);
    SudokuSolver solution(sudoku_board.GetBoardNumbers());
    REQUIRE(solution.Solve());
    REQUIRE(sudoku_board.GetNumberTotal() == 16);
  }

  SECTION("Generate a board too many numbers") {
    REQUIRE_THROWS_AS(sudoku_board.GenerateValidBoard(17), 
                      std::invalid_argument);
  }

  SECTION("Generate board with random size") {
    sudoku_board.GenerateValidBoard(7);
    SudokuSolver solution(sudoku_board.GetBoardNumbers());
    REQUIRE(solution.Solve());
    REQUIRE(sudoku_board.GetNumberTotal() == 7);
  }
}

TEST_CASE("Add a number to the board") {
  SudokuSolver::gameboard board = {
      {5, 3, 0, 0, 7, 0, 0, 0, 0}, 
      {6, 0, 0, 1, 9, 5, 0, 0, 0},
      {0, 9, 8, 0, 0, 0, 0, 6, 0}, 
      {8, 0, 0, 0, 6, 0, 0, 0, 3},
      {4, 0, 0, 8, 0, 3, 0, 0, 1}, 
      {7, 0, 0, 0, 2, 0, 0, 0, 6},
      {0, 6, 0, 0, 0, 0, 2, 8, 0}, 
      {0, 0, 0, 4, 1, 9, 0, 0, 5},
      {0, 0, 0, 0, 8, 0, 0, 7, 9}};
  SudokuBoard sudoku_board(board);

  SECTION("Add to a position which already has a number "
          "and that number was originally generated") {
    sudoku_board.AddNumber(vec2(0, 1), 1);
    REQUIRE(sudoku_board.GetNumberTotal() == 30);
    REQUIRE(sudoku_board.GetBoardNumbers()[0][1] == 3);
    REQUIRE(sudoku_board.GetAddedTiles().empty());
  }

  SECTION("Add to a position that already has a number "
          "but that number was added by the player") {
    sudoku_board.AddNumber(vec2(0, 2), 1);
    sudoku_board.AddNumber(vec2(0, 2), 2);
    REQUIRE(sudoku_board.GetNumberTotal() == 31);
    REQUIRE(sudoku_board.GetBoardNumbers()[0][2] == 2);
    REQUIRE(sudoku_board.GetAddedTiles()[0] == vec2(0, 2));
    REQUIRE(sudoku_board.GetAddedTiles().size() == 1);
  }
  
  SECTION("Add to a position that originally was not holding any number") {
    sudoku_board.AddNumber(vec2(0, 7), 1);
    REQUIRE(sudoku_board.GetNumberTotal() == 31);
    REQUIRE(sudoku_board.GetBoardNumbers()[0][7] == 1);
    REQUIRE(sudoku_board.GetAddedTiles()[0] == vec2(0, 7));
    REQUIRE(sudoku_board.GetAddedTiles().size() == 1);
  }
  
  SECTION("Clear all the tiles modified by the player") {
    sudoku_board.AddNumber(vec2(0, 2), 2);
    sudoku_board.AddNumber(vec2(0, 7), 1);
    sudoku_board.ClearAddedTiles();
    REQUIRE(sudoku_board.GetAddedTiles().empty());
  }
}

