#include "../Headers/SudokuSolver.hpp"

SudokuSolver::SudokuSolver(SudokuBoard &b) : board(b) {} // reference must be initialized in initializer list

// checks the solvability of the puzzle
bool SudokuSolver::isSolvable()
{
  SudokuBoard copy = board; // make a copy so we don’t alter the original
  SudokuSolver obj(copy);
  return obj.solve();
}

// solves the Sudoku puzzle using recursive backtracking.
bool SudokuSolver::solve()
{
  for (int row = 0; row < SudokuBoard::SIZE; row++)
  {
    for (int col = 0; col < SudokuBoard::SIZE; col++)
    {
      if (board.getCell(row, col) == 0)
      {
        for (int num = 1; num <= 9; num++)
        {
          if (board.isValidMove(row, col, num))
          {
            board.setCell(row, col, num);

            if (solve())   // recursive
              return true; // solved

            board.setCell(row, col, 0); // backtracking
          }
        }
        return false; // backtracking
      }
    }
  }
  return true; // solved
}
