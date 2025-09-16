#include "../Headers/SudokuBoard.hpp"
#include <iostream>
#include <fstream>

SudokuBoard::SudokuBoard()
{
  board = std::vector(SIZE, std::vector<int>(SIZE, 0));
  fixed = std::vector(SIZE, std::vector<bool>(SIZE, false));
  loadFromFile("InitialPuzzle.txt");
}

// load a puzzle from a file to board
bool SudokuBoard::loadFromFile(const std::string &filename)
{
  std::ifstream in("../Puzzles/" + filename);
  if (!in)
    return false;

  for (int r = 0; r < SIZE; r++)
  {
    std::string line;
    if (!(in >> line) || line.size() < SIZE)
      return false;

    for (int c = 0; c < SIZE; c++)
    {
      int val = line[c] - '0'; // subtracting the ASCII value of a '0' from any other string digit returns int value of the digit
      board[r][c] = val;
      fixed[r][c] = (val != 0); // marks non 0 cells (original puzzle values) as true to make them immutable
    }
  }
  return true;
}

// save current board to a file
bool SudokuBoard::saveToFile(const std::string &filename) const
{
  std::ofstream out("../Saves/" + filename);
  if (!out)
    return false;

  for (int r = 0; r < SIZE; r++)
  {
    for (int c = 0; c < SIZE; c++)
    {
      out << board[r][c];
    }
    out << "\n";
  }
  return true;
}

// print the board to the console
void SudokuBoard::print() const
{
  std::cout << "\n";
  std::cout << "      1  2  3     4  5  6     7  8  9 \n";
  std::cout << "    -----------------------------------\n";

  for (int r = 0; r < SIZE; r++)
  {
    std::cout << "  " << r + 1 << "  ";

    for (int c = 0; c < SIZE; c++)
    {
      if (c == 3 || c == 6)
        std::cout << " | ";
      if (board[r][c] == 0)
      {
        std::cout << " . ";
      }
      else
      {
        if (fixed[r][c])
        {
          std::cout << " \033[1;34m" << board[r][c] << "\033[0m ";
        }
        else
        {
          std::cout << " \033[1;32m" << board[r][c] << "\033[0m ";
        }
      }
    }
    std::cout << "\n";
    if (r == 2 || r == 5)
      std::cout << "    -----------------------------------\n";
  }
  std::cout << "    -----------------------------------\n";
}

// set empty cells by the passed value after validation
bool SudokuBoard::setCell(int row, int col, int value)
{
  // prevent overwrite original cell with different value
  if (fixed[row][col] && value != board[row][col])
  {
    return false;
  }

  // check for empty cells and validating sudoku rules
  if (value != 0 && !isValidMove(row, col, value))
  {
    return false;
  }

  board[row][col] = value;
  return true;
}

// validating sudoku rules
bool SudokuBoard::isValidMove(int row, int col, int value) const
{
  return !rowContains(row, value) && !colContains(col, value) && !subgridContains(row, col, value);
}

// checks whether a given row already contains the specified value
bool SudokuBoard::rowContains(int row, int value) const
{
  for (int c = 0; c < SIZE; c++)
  {
    if (board[row][c] == value)
      return true;
  }
  return false;
}

// checks whether a given column already contains the specified value.
bool SudokuBoard::colContains(int col, int value) const
{
  for (int r = 0; r < SIZE; r++)
  {
    if (board[r][col] == value)
      return true;
  }
  return false;
}

// checks whether the 3×3 subgrid that contains the cell (row, col) already has the specified value
bool SudokuBoard::subgridContains(int row, int col, int value) const
{
  int subGridRow = (row / 3) * 3;
  int subGridCol = (col / 3) * 3;
  for (int r = 0; r < 3; r++)
  {
    for (int c = 0; c < 3; c++)
    {
      if (board[subGridRow + r][subGridCol + c] == value)
        return true;
    }
  }
  return false;
}

// get specified cell (row, col)
int SudokuBoard::getCell(int row, int col) const
{
  return board[row][col];
}

// checks the completeness of the board
bool SudokuBoard::isComplete() const
{
  for (int r = 0; r < SIZE; r++)
  {
    for (int c = 0; c < SIZE; c++)
    {
      if (board[r][c] == 0)
        return false;
    }
  }
  return true;
}

// set all the cells to 0
void SudokuBoard::clearBoard()
{
  for (int r = 0; r < SIZE; r++)
  {
    for (int c = 0; c < SIZE; c++)
    {
      fixed[r][c] = false;
      board[r][c] = 0;
    }
  }
}

// return the number of filled cells
int SudokuBoard::countFilledCells() const
{
  int count = 0;
  for (int row = 0; row < 9; row++)
  {
    for (int col = 0; col < 9; col++)
    {
      if (getCell(row, col) != 0)
      {
        count++;
      }
    }
  }
  return count;
}

// set a specified cell fixed value to true
void SudokuBoard::setFixed(int row, int col)
{
  fixed[row][col] = true;
}