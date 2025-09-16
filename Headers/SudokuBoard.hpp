#ifndef SUDOKUBOARD_HPP
#define SUDOKUBOARD_HPP

#include <vector>
#include <string>

/*
Stores and manipulates the 9×9 grid.
Validates row/column/box constraints.
Prints the board.
Loads and saves puzzle data to a file.
*/

class SudokuBoard
{
private:
  std::vector<std::vector<int>> board;
  std::vector<std::vector<bool>> fixed;

public:
  SudokuBoard();
  static const int SIZE = 9;
  static const std::string PUZZLE_DIR;
  static const std::string SAVE_DIR;
  bool loadFromFile(const std::string &filename);
  bool saveToFile(const std::string &filename) const;
  void print() const;
  bool setCell(int row, int col, int value);
  int getCell(int row, int col) const;
  bool rowContains(int row, int value) const;
  bool colContains(int col, int value) const;
  bool subgridContains(int row, int col, int value) const;
  bool isValidMove(int row, int col, int value) const;
  bool isComplete() const;
  int countFilledCells() const;
  void setFixed(int row, int col);
  void clearBoard();
};

#endif // SUDOKUBOARD_HPP