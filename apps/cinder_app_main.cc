#include "sudoku_game_app.h"

using sudokugame::SudokuGameApp;

void prepareSettings(SudokuGameApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(SudokuGameApp, ci::app::RendererGl, prepareSettings);