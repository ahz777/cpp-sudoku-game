#ifndef SUDOKUSOLVER_HPP
#define SUDOKUSOLVER_HPP

#include "SudokuBoard.hpp"

// Backtracking method to find a solution or detect unsolvability

class SudokuSolver
{
private:
  SudokuBoard &board;

public:
  SudokuSolver(SudokuBoard &board);

  bool solve();
  bool isSolvable();
};
#endif // SUDOKUSOLVER_HPP
