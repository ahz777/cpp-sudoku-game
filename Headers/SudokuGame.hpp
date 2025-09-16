#ifndef SUDOKUGAME_HPP
#define SUDOKUGAME_HPP

#include "SudokuBoard.hpp"
#include "SudokuSolver.hpp"
#include "SudokuGenerator.hpp"

/*
Presents console menu, reads/writes user input.
Coordinates SudokuBoard and SudokuSolver.
Handles error-checking for moves and file operations.
*/

class SudokuGame
{
private:
  SudokuBoard SudokuBoardObj;

  void showMenu() const;
  void handleMove();
  void handleSolvePuzzle();
  void handlePuzzleGeneration();
  void handleLoadPuzzle();
  void handleSavePuzzle();
  void checkSolvability();

public:
  SudokuGame();
  void run();
};

#endif // SUDOKUGAME_HPP
