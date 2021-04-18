#include "visualizer/game_board.h"

namespace sudokugame {

namespace visualizer {

GameBoard::GameBoard(const vec2& board_top_left, 
                     const vec2& board_bottom_right, 
                     size_t board_size,
                     Level level) 
    : board_size_(board_size), 
      board_top_left_(board_top_left),
      board_bottom_right_(board_bottom_right), 
      sudoku_board(SudokuBoard(board_size)) {
  SetLevel(level);
}

void GameBoard::Draw() {
  // Draw board contents
  ci::Rectf board_bounding_box(board_top_left_, board_bottom_right_);
  ci::gl::color(kBoardColor);
  ci::gl::drawSolidRect(board_bounding_box);

  // Draw Tiles
  DrawSquares((board_bottom_right_.x - board_top_left_.x) / board_size_,
              kTileLineWidth, board_size_ * board_size_);

  // Draw sub boards
  DrawSquares((board_bottom_right_.x - board_top_left_.x) / sqrt(board_size_),
              kSubBoardLineWidth, board_size_);

  // Draw original numbers
  DrawNumbers();
}

void GameBoard::SetLevel(Level level) {
  std::random_device rd;
  switch (level) {
  case Level::kEasy:
    sudoku_board.GenerateValidBoard(rd() % (kEasyLevelMaxTotal -
                                            kEasyLevelMinTotal) +
                                    kEasyLevelMinTotal);
    break;
  case Level::kMedium:
    sudoku_board.GenerateValidBoard(rd() % (kMediumLevelMaxTotal -
                                            kMediumLevelMinTotal) +
                                    kMediumLevelMinTotal);
    break;
  case Level::kHard:
    sudoku_board.GenerateValidBoard(rd() % (kHardLevelMaxTotal -
                                            kHardLevelMinTotal) +
                                    kHardLevelMinTotal);
    break;
  default:
    sudoku_board.GenerateValidBoard(kDefaultNumberTotal);
  }
}

void GameBoard::DrawSquares(size_t square_length, size_t edge_line_width, 
                            size_t number) {
  for (size_t row = 0; row < sqrt(number); ++row) {
    for (size_t col = 0; col < sqrt(number); ++col) {
      vec2 square_top_left = board_top_left_ + 
                             vec2(row * square_length,
                                  col * square_length);
      vec2 square_bottom_right = board_top_left_ + 
                                 vec2((row + 1) * square_length,
                                      (col + 1) * square_length);
      ci::Rectf square_bounding_box(square_top_left, 
                                    square_bottom_right);
      ci::gl::color(kSquareEdgeColor);
      ci::gl::drawStrokedRect(square_bounding_box, edge_line_width);
    }
  }
}

void GameBoard::DrawNumbers() {
  size_t square_length = (board_bottom_right_.x - board_top_left_.x) / 
                         board_size_;
  for (size_t row = 0; row < sudoku_board.GetBoardSize(); ++row) {
    for (size_t col = 0; col < sudoku_board.GetBoardSize(); ++col) {
      if (sudoku_board.GetBoardNumbers()[row][col] != 0) {
        vec2 square_center = board_top_left_ +
                             vec2((row + 0.5) * square_length,
                                  (col + 0.5) * square_length);
        ci::gl::drawStringCentered(
            std::to_string(sudoku_board.GetBoardNumbers()[row][col]),
            square_center, kSquareEdgeColor);
      }
    }
  }
}

} // visualizer

} // sudokugame