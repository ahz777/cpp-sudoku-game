#ifndef SUDOKU_GENERATOR_HPP
#define SUDOKU_GENERATOR_HPP

#include "SudokuBoard.hpp"
#include "SudokuSolver.hpp"

class SudokuGenerator
{
private:
public:
  SudokuBoard &board;
  SudokuSolver SudokuSolverObj;
  SudokuGenerator(SudokuBoard &board);
  void generatePuzzle(int clues);
};

#endif
