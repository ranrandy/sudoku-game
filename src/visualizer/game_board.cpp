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
      sudoku_board_(SudokuBoard(board_size)) {
  SetLevel(level);
}

void GameBoard::Draw() {
  // Draw board background
  ci::Rectf board_bounding_box(board_top_left_, board_bottom_right_);
  ci::gl::color(kBoardColor);
  ci::gl::drawSolidRect(board_bounding_box);

  // Draw Tiles
  DrawSquares((board_bottom_right_.x - board_top_left_.x) / board_size_,
              kTileLineWidth, board_size_ * board_size_);

  // Draw sub boards
  DrawSquares((board_bottom_right_.x - board_top_left_.x) / sqrt(board_size_),
              kSubBoardLineWidth, board_size_, false);

  // Draw original numbers
  DrawNumbers();
}

void GameBoard::SetLevel(Level level) {
  std::random_device rd;
  switch (level) {
  case Level::kEasy:
    sudoku_board_.GenerateValidBoard(rd() % (kEasyLevelMaxTotal -
                                            kEasyLevelMinTotal) +
                                    kEasyLevelMinTotal);
    break;
  case Level::kMedium:
    sudoku_board_.GenerateValidBoard(rd() % (kMediumLevelMaxTotal -
                                            kMediumLevelMinTotal) +
                                    kMediumLevelMinTotal);
    break;
  case Level::kHard:
    sudoku_board_.GenerateValidBoard(rd() % (kHardLevelMaxTotal -
                                            kHardLevelMinTotal) +
                                    kHardLevelMinTotal);
    break;
  default:
    sudoku_board_.GenerateValidBoard(kDefaultNumberTotal);
  }
  InitiateHighlighting();
  sudoku_board_.ClearTilesAddedNumber();
}

bool GameBoard::ShowSolution() {
  SudokuSolver sudoku_solver(sudoku_board_.GetBoardNumbers());
  if (sudoku_solver.Solve()) {
    sudoku_board_.SetBoardNumbers(sudoku_solver.GetSolution());
    return true;
  } else {
    return false;
  }
}

void GameBoard::AddNumber(size_t number) {
  sudoku_board_.AddNumber(clicked_tile_, number);
}

void GameBoard::HandleHighlighting(const ci::app::MouseEvent &event) {
  vec2 game_board_center =
      vec2((board_top_left_.x + board_bottom_right_.x) / 2,
           (board_top_left_.y + board_bottom_right_.y) / 2);
  if (abs(game_board_center.x - float(event.getX())) <
      (board_bottom_right_.x - board_top_left_.x) / 2 &&
      abs(game_board_center.y - float(event.getY())) <
      (board_bottom_right_.y - board_top_left_.y) / 2) {
    tiles_to_highlight_.clear();
    same_number_tiles_to_highlight_.clear();
    
    size_t square_length = (board_bottom_right_.x - board_top_left_.x) /
                           board_size_;
    size_t clicked_tile_x = (event.getX() - int(board_top_left_.x)) / 
                            square_length;
    size_t clicked_tile_y = (event.getY() - int(board_top_left_.y)) / 
                            square_length;
    clicked_tile_ = vec2(clicked_tile_x, clicked_tile_y);
    size_t tile_number = sudoku_board_.GetBoardNumbers()[clicked_tile_x]
                                                        [clicked_tile_y];
    
    // Checks if the tile clicked is empty or not.
    if (tile_number != 0) {
      for (size_t row = 0; row < board_size_; row++) {
        for (size_t col = 0; col < board_size_; col++) {
          if (sudoku_board_.GetBoardNumbers()[row][col] == tile_number) {
            same_number_tiles_to_highlight_.emplace_back(row, col);
          }
        }
      }
    }
    
    // Stores tiles in the same column and same row with the clicked tile.
    for (size_t i = 0; i < kBoardSize; i++) {
      tiles_to_highlight_.emplace_back(vec2(clicked_tile_x, i));
      tiles_to_highlight_.emplace_back(vec2(i, clicked_tile_y));
    }
    
    // Stores tiles in the same sub board with the clicked tile.
    size_t sub_board_size = sqrt(board_size_);
    size_t sub_board_row = clicked_tile_x / sub_board_size * sub_board_size;
    size_t sub_board_col = clicked_tile_y / sub_board_size * sub_board_size;
    for (size_t i = 0; i < sub_board_size; i++) {
      for (size_t j = 0; j < sub_board_size; j++) {
        tiles_to_highlight_.emplace_back(vec2(i+sub_board_row, 
                                              j+sub_board_col));
      }
    }
  }
}

void GameBoard::DrawSquares(size_t square_length, size_t edge_line_width, 
                            size_t number, bool is_tile) {
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
      
      // Checks if the tile is clicked tile and the tile is empty.
      if (vec2(row, col) == clicked_tile_ && is_tile && 
          sudoku_board_.GetBoardNumbers()[row][col] == 0) {
        ci::gl::color(kClickedEmptyTileColor);
        ci::gl::drawSolidRect(square_bounding_box);
      }

      // Checks iif the tile is clicked tile but is not empty.
      if (vec2(row, col) == clicked_tile_ && is_tile &&
          sudoku_board_.GetBoardNumbers()[row][col] != 0) {
        ci::gl::color(kClickedOriginalTileColor);
        ci::gl::drawSolidRect(square_bounding_box);
      }
      
      // Highlights those tiles which are in the same row, column or 
      // sub board with the clicked tile.
      for (const vec2& tile_to_highlight : tiles_to_highlight_) {
        if (vec2(row, col) == tile_to_highlight && 
            vec2(row, col) != clicked_tile_ && is_tile) {
          ci::gl::color(kRelatedTileColor);
          ci::gl::drawSolidRect(square_bounding_box);
        }
      }
      
      // Highlights the tiles who are filled in with the same color as
      // the clicked tile
      for (const vec2& same_number_tile_to_highlight : 
           same_number_tiles_to_highlight_) {
        if (vec2(row, col) == same_number_tile_to_highlight &&
            vec2(row, col) != clicked_tile_ && is_tile) {
          ci::gl::color(kSameNumberTileColor);
          ci::gl::drawSolidRect(square_bounding_box);
        }
      }
      
      // Draw the margin lines of each square.
      ci::gl::color(kSquareEdgeColor);
      ci::gl::drawStrokedRect(square_bounding_box, edge_line_width);
    }
  }
}

void GameBoard::DrawNumbers() {
  size_t square_length = (board_bottom_right_.x - board_top_left_.x) / 
                         board_size_;
  for (size_t row = 0; row < sudoku_board_.GetBoardSize(); ++row) {
    for (size_t col = 0; col < sudoku_board_.GetBoardSize(); ++col) {
      if (sudoku_board_.GetBoardNumbers()[row][col] != 0) {
        vec2 square_center = board_top_left_ +
                             vec2((row + kNumberPosXParameter) * square_length,
                                  (col + kNumberPosYParameter) * square_length);
        
        ci::gl::drawStringCentered(
            std::to_string(sudoku_board_.GetBoardNumbers()[row][col]),
            square_center, kSquareEdgeColor, kNumberFont);
        
        // Highlights the tiles who are filled with the same number
        // as the clicked tile
        for (const vec2& same_number_tile_to_highlight : 
             same_number_tiles_to_highlight_) {
          // The tile is not the clicked tile itself.
          if (vec2(row, col) == same_number_tile_to_highlight &&
              vec2(row, col) != clicked_tile_) {
            ci::gl::drawStringCentered(
                std::to_string(sudoku_board_.GetBoardNumbers()[row][col]),
                square_center, kSameNumberTileNumberColor, kNumberFont);
          }

          // The tile is the clicked tile itself.
          if (vec2(row, col) == clicked_tile_ &&
              sudoku_board_.GetBoardNumbers()[row][col] != 0) {
            ci::gl::drawStringCentered(
                std::to_string(sudoku_board_.GetBoardNumbers()[row][col]),
                square_center, kSameNumberTileNumberColor, kNumberFont);
          }
        }

        // Draws the player added numbers with some different color.
        for (const vec2& tile_added_number :
            sudoku_board_.GetTilesAddedNumber()) {
          if (vec2(row, col) == tile_added_number) {
            ci::gl::drawStringCentered(
                std::to_string(sudoku_board_.GetBoardNumbers()[row][col]),
                square_center, kAddedNumberTileColor, kNumberFont);
          }
        }
      }
    }
  }
}

void GameBoard::InitiateHighlighting() {
  tiles_to_highlight_.clear();
  same_number_tiles_to_highlight_.clear();
  
  // Stores the tiles whose row or column index is same as the clicked tile.
  for (size_t i = 0; i < kBoardSize; i++) {
    tiles_to_highlight_.emplace_back(vec2(clicked_tile_.x, i));
    tiles_to_highlight_.emplace_back(vec2(i, clicked_tile_.y));
  }

  // Stores the tiles that are in the same sub board as with the clicked tile.
  size_t sub_board_size = sqrt(board_size_);
  size_t sub_board_row = clicked_tile_.x / sub_board_size * sub_board_size;
  size_t sub_board_col = clicked_tile_.y / sub_board_size * sub_board_size;
  for (size_t i = 0; i < sub_board_size; i++) {
    for (size_t j = 0; j < sub_board_size; j++) {
      tiles_to_highlight_.emplace_back(vec2(i+sub_board_row, j+sub_board_col));
    }
  }

  // Stores the tiles who are filled with the same color as the clicked tile.
  size_t tile_number = sudoku_board_.GetBoardNumbers()[clicked_tile_.x]
                                                      [clicked_tile_.y];
  if (tile_number != 0) {
    for (size_t row = 0; row < board_size_; row++) {
      for (size_t col = 0; col < board_size_; col++) {
        if (sudoku_board_.GetBoardNumbers()[row][col] == tile_number) {
          same_number_tiles_to_highlight_.emplace_back(row, col);
        }
      }
    }
  }
}

} // visualizer

} // sudokugame