#include "../Headers/SudokuGenerator.hpp"
#include <unordered_set>
SudokuGenerator::SudokuGenerator(SudokuBoard &b)
    : board(b), SudokuSolverObj(board) {}

// Alert!! this is just my dump idea, dont take it seriously
// it kinda works but takes time to generate (might also stuck)
void SudokuGenerator::generatePuzzle(int clues)
{

  board.clearBoard();
  while (board.countFilledCells() < clues)
  {
    int row = std::rand() % 9;
    int col = std::rand() % 9;
    int val = std::rand() % 9 + 1;
    if (board.getCell(row, col) == 0 && board.isValidMove(row, col, val))
    {
      board.setCell(row, col, val);
      board.setFixed(row, col);
      if (!SudokuSolverObj.isSolvable())
      {
        board.setCell(row, col, 0);
      }
    }
  }
}
