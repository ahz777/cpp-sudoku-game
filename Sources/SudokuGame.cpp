#include "../Headers/SudokuGame.hpp"
#include <iostream>
#include <limits>

// hello message
SudokuGame::SudokuGame()
{
  std::cout << "    \033[35m==================================\033[0m\n";
  std::cout << "    \033[35m===== Welcome to Sudoku Game =====\033[0m\n";
  std::cout << "    \033[35m==================================\033[0m\n";
}

// main menu
void SudokuGame::showMenu() const
{
  std::cout << "1) Enter a move\n";
  std::cout << "2) Solve automatically\n";
  std::cout << "3) Generate random puzzle\n";
  std::cout << "4) Check if the puzzle Solvable\n";
  std::cout << "5) Load puzzle from file\n";
  std::cout << "6) Save current puzzle to file\n";
  std::cout << "0) Exit\n";
  std::cout << "Choice: ";
}

// main game loop
// print the board
// show main menu
// take user input for an option
void SudokuGame::run()
{
  int choice;
  while (true)
  {
    SudokuBoardObj.print();
    showMenu();
    if (!(std::cin >> choice))
    {
      std::cout << "\033[31mInvalid Choice. Can only enter numbers\033[0m\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }
    if (choice < 0 || choice > 7)
    {
      std::cout << "\033[31mInvalid Choice. Can only use numbers from 0 to 5\033[0m\n";
      continue;
    }
    if (choice == 1)
    {
      handleMove();
      continue;
    }
    if (choice == 2)
    {
      handleSolvePuzzle();
      continue;
    }
    if (choice == 3)
    {
      handlePuzzleGeneration();
      continue;
    }
    if (choice == 4)
    {
      checkSolvability();
      continue;
    }
    if (choice == 5)
    {
      handleLoadPuzzle();
      continue;
    }
    if (choice == 6)
    {
      handleSavePuzzle();
      continue;
    }
    if (choice == 0)
    {
      std::cout << "Goodbye!";
      break;
    }
  }
}

// take row col value from user input and make sure they are in the needed range
// checks the validity of the move and set the cell throw SudokuBoard class member functions
// checks if the board is completed
void SudokuGame::handleMove()
{
  int row, col, value;
  std::cout << "Enter row (1-9), column (1-9), and value (1-9): ";
  if (!(std::cin >> row >> col >> value))
  {
    std::cout << "\033[31mInvalid Choice. Can only enter numbers\033[0m\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return;
  }
  if (row < 1 || row > 9)
  {
    std::cout << "\033[31mRow must be between 1 and 9.\033[0m\n";
    return;
  }
  if (col < 1 || col > 9)
  {
    std::cout << "\033[31mColumn must be between 1 and 9.\033[0m\n";
    return;
  }
  if (value < 1 || value > 9)
  {
    std::cout << "\033[31mValue must be between 1 and 9.\033[0m\n";
    return;
  }
  row--;
  col--;
  if (!SudokuBoardObj.setCell(row, col, value))
  {
    if (SudokuBoardObj.getCell(row, col) != 0)
    {
      std::cout << "\033[31mThat cell is already occupied.\033[0m\n";
    }
    else if (!SudokuBoardObj.isValidMove(row, col, value))
    {
      std::cout << "\033[31mThat move breaks Sudoku rules.\033[0m\n";
    }
  }
  else
  {
    std::cout << "\033[32mMove accepted!\033[0m\n";
  }
  if (SudokuBoardObj.isComplete())
  {
    std::cout << "\033[32mPuzzle complete! Good job.\033[0m\n";
  }

  return;
}

// call the solve member function from SudokuSolver class
void SudokuGame::handleSolvePuzzle()
{
  SudokuSolver SudokuSolverObj(SudokuBoardObj);
  if (SudokuSolverObj.solve())
  {
    std::cout << "\033[32mPuzzle solved\033[0m\n";
  }
  else
  {
    std::cout << "\033[31mThis puzzle cannot be solved.\033[0m\n";
  }
}

// display a list of available puzzles and take a user input to choose a puzzle
// load the puzzle to the board
void SudokuGame::handleLoadPuzzle()
{
  std::vector<std::string> puzzles = {
      "InitialPuzzle.txt",
      "Beginner.txt",
      "Easy.txt",
      "Hard.txt",
      "Moderate.txt",
      "Expert.txt",
      "Challenging.txt"};

  std::cout << "Available puzzles:\n";
  for (size_t i = 0; i < puzzles.size(); i++)
  {
    std::cout << i << ") " << puzzles[i].substr(0, puzzles[i].size() - 4) << "\n";
  }

  std::cout << "Choose puzzle number (0 - " << puzzles.size() - 1 << "): ";
  int choice;
  if (!(std::cin >> choice) || choice < 0 || choice >= (int)puzzles.size())
  {
    std::cout << "\033[31mInvalid choice.\033[0m\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return;
  }

  if (SudokuBoardObj.loadFromFile(puzzles[choice]))
  {
    std::cout << "\033[32mLoaded " << puzzles[choice].substr(0, puzzles[choice].size() - 4) << " puzzle successfully.\033[0m\n";
  }
  else
  {
    std::cout << "\033[31mFailed to load " << puzzles[choice].substr(0, puzzles[choice].size() - 4) << ".\033[0m\n";
  }
}

// save the current board to a file
void SudokuGame::handleSavePuzzle()
{
  std::string filename;
  std::cout << "Enter filename to save: ";
  std::cin >> filename;
  if (SudokuBoardObj.saveToFile(filename))
  {
    std::cout << "\033[32mPuzzle saved!\033[0m\n";
  }
  else
  {
    std::cout << "\033[31mFailed to save puzzle.\033[0m\n";
  }
}

// check if the puzzle is solvable or not without changing the current board
void SudokuGame::checkSolvability()
{
  SudokuSolver SudokuSolverObj(SudokuBoardObj);
  if (SudokuSolverObj.isSolvable())
  {
    std::cout << "\033[32mThis puzzle is solvable\033[0m\n";
  }
  else
  {
    std::cout << "\033[31mThis puzzle cannot be solved.\033[0m\n";
  }
}

// generate random puzzle with a choosen number of clues
void SudokuGame::handlePuzzleGeneration()
{
  int clues;

  std::cout << "Enter the number of clues between(include) 17 and 30: ";
  if (!(std::cin >> clues))
  {
    std::cout << "\033[31mInvalid Choice. Can only enter numbers\033[0m\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return;
  }
  if (clues < 17 || clues > 30)
  {
    std::cout << "\033[31mInvalid Choice. Enter a number between(include) 17 and 30\033[0m\n";
    return;
  }

  SudokuGenerator generator(SudokuBoardObj);
  generator.generatePuzzle(clues);
}