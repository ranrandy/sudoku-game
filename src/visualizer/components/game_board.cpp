#include "visualizer/components/game_board.h"

namespace sudokugame {

namespace visualizer {

GameBoard::GameBoard() : sudoku_board_(SudokuBoard(kBoardSize)) {
  GenerateValidBoard(Level::kMedium);
}

void GameBoard::Draw() {
  // Draw board background
  ci::Rectf board_bounding_box(kBoardTopLeft, kBoardBottomRight);
  ci::gl::color(kBoardColor);
  ci::gl::drawSolidRect(board_bounding_box);

  // Draw Tiles
  DrawSquares((kBoardBottomRight.x - kBoardTopLeft.x) / double(kBoardSize),
              kTileLineWidth, kBoardSize * kBoardSize);

  // Draw sub boards
  DrawSquares((kBoardBottomRight.x - kBoardTopLeft.x) / sqrt(kBoardSize),
              kSubBoardMarginWidth, kBoardSize, false);

  // Draw original numbers
  DrawNumbers();
}

void GameBoard::GenerateValidBoard(Level level) {
  std::random_device rd;
  switch (level) {
    case Level::kEasy: {
      sudoku_board_.GenerateValidBoard(rd() % (kEasyLevelMaxTotal -
                                               kEasyLevelMinTotal) +
                                       kEasyLevelMinTotal);
      break;
    }
    case Level::kMedium: {
      sudoku_board_.GenerateValidBoard(rd() % (kMediumLevelMaxTotal -
                                               kMediumLevelMinTotal) +
                                       kMediumLevelMinTotal);
      break;
    }
    case Level::kHard: {
      sudoku_board_.GenerateValidBoard(rd() % (kHardLevelMaxTotal -
                                               kHardLevelMinTotal) +
                                       kHardLevelMinTotal);
      break;
    }
    default: {
      sudoku_board_.GenerateValidBoard(kDefaultNumberTotal);
    }
  }
  InitiateHighlighting();
  sudoku_board_.ClearAddedTiles();
}

bool GameBoard::ShowSolution() {
  sudoku_board_.RemoveNumbers(sudoku_board_.GetAddedTiles());
  sudoku_board_.ClearAddedTiles();
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

void GameBoard::RemoveNumber(bool is_hit) {
  if (is_hit) {
    sudoku_board_.RemoveNumber(clicked_tile_);
  }
}

void GameBoard::HandleHighlighting(const ci::app::MouseEvent& event) {
  vec2 game_board_center =
      vec2((kBoardTopLeft.x + kBoardBottomRight.x) / 2,
           (kBoardTopLeft.y + kBoardBottomRight.y) / 2);
  if (abs(game_board_center.x - float(event.getX())) <
      (kBoardBottomRight.x - kBoardTopLeft.x) / 2 &&
      abs(game_board_center.y - float(event.getY())) <
      (kBoardBottomRight.y - kBoardTopLeft.y) / 2) {
    size_t square_length = size_t(kBoardBottomRight.x - kBoardTopLeft.x) /
                           kBoardSize;
    size_t clicked_tile_x = (event.getX() - int(kBoardTopLeft.x)) / 
                            square_length;
    size_t clicked_tile_y = (event.getY() - int(kBoardTopLeft.y)) / 
                            square_length;
    clicked_tile_ = vec2(clicked_tile_x, clicked_tile_y);
    InitiateHighlighting();
  }
}

void GameBoard::HandleHighlighting(const ci::app::KeyEvent& event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_UP:
    case KeyEvent::KEY_w: {
      if (clicked_tile_.y > 0) {
        clicked_tile_.y -= 1;
      }
      break;
    }
    case KeyEvent::KEY_DOWN:
    case KeyEvent::KEY_s: {
      if (clicked_tile_.y < kBoardSize - 1) {
        clicked_tile_.y += 1;
      }
      break;
    }
    case KeyEvent::KEY_LEFT:
    case KeyEvent::KEY_a: {
      if (clicked_tile_.x > 0) {
        clicked_tile_.x -= 1;
      }
      break;
    }
    case KeyEvent::KEY_RIGHT:
    case KeyEvent::KEY_d: {
      if (clicked_tile_.x < kBoardSize - 1) {
        clicked_tile_.x += 1;
      }
      break;
    }
  }
  InitiateHighlighting();
}

void GameBoard::DrawSquares(double square_length, float edge_line_width, 
                            size_t number, bool is_tile) {
  for (size_t row = 0; row < size_t((sqrt(number))); ++row) {
    for (size_t col = 0; col < size_t(sqrt(number)); ++col) {
      vec2 square_top_left = kBoardTopLeft + 
                             vec2(double(row) * square_length,
                                  double(col) * square_length);
      vec2 square_bottom_right = kBoardTopLeft + 
                                 vec2(double(row + 1) * square_length,
                                      double(col + 1) * square_length);
      ci::Rectf square_bounding_box(square_top_left, 
                                    square_bottom_right);
      
      // Checks if the tile is clicked tile and the tile is empty.
      if (vec2(row, col) == clicked_tile_ && is_tile && 
          sudoku_board_.GetBoardNumbers()[row][col] == 0) {
        ci::gl::color(kClickedEmptyTileColor);
        ci::gl::drawSolidRect(square_bounding_box);
      }

      // Checks if the tile is clicked tile but is not empty.
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
  double square_length = (kBoardBottomRight.x - kBoardTopLeft.x) / 
                         double(kBoardSize);
  for (size_t row = 0; row < sudoku_board_.GetBoardSize(); ++row) {
    for (size_t col = 0; col < sudoku_board_.GetBoardSize(); ++col) {
      if (sudoku_board_.GetBoardNumbers()[row][col] != 0) {
        vec2 square_center = kBoardTopLeft +
                             vec2((double(row) + kNumberPosXParameter) * 
                                      square_length,
                                  (double(col) + kNumberPosYParameter) * 
                                      square_length);
        
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
            sudoku_board_.GetAddedTiles()) {
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
  size_t sub_board_size = sqrt(kBoardSize);
  size_t sub_board_row = size_t(clicked_tile_.x) / sub_board_size * 
                         sub_board_size;
  size_t sub_board_col = size_t(clicked_tile_.y) / sub_board_size * 
                         sub_board_size;
  
  for (size_t i = 0; i < sub_board_size; i++) {
    for (size_t j = 0; j < sub_board_size; j++) {
      tiles_to_highlight_.emplace_back(vec2(i+sub_board_row, j+sub_board_col));
    }
  }

  // Stores the tiles who are filled with the same color as the clicked tile.
  size_t tile_number = sudoku_board_.GetBoardNumbers()[clicked_tile_.x]
                                                      [clicked_tile_.y];
  if (tile_number != 0) {
    for (size_t row = 0; row < kBoardSize; row++) {
      for (size_t col = 0; col < kBoardSize; col++) {
        if (sudoku_board_.GetBoardNumbers()[row][col] == tile_number) {
          same_number_tiles_to_highlight_.emplace_back(row, col);
        }
      }
    }
  }
}

} // namespace visualizer

} // namespace sudokugame