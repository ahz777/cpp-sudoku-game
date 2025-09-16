cmake_minimum_required(VERSION 3.8)
project(SudokuProject)

# Use C++17 (adjust if you need a different standard)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Core source files
set(SOURCES
    ./Sources/SudokuBoard.cpp
    ./Sources/SudokuGame.cpp
    ./Sources/SudokuGenerator.cpp
    ./Sources/SudokuSolver.cpp
    ./Sources/main.cpp
)

# Header files (not strictly required for add_executable, but good for clarity)
set(HEADERS
    ./Headers/SudokuBoard.hpp
    ./Headers/SudokuGame.hpp
    ./Headers/SudokuGenerator.hpp
    ./Headers/SudokuSolver.hpp
)

# Create the final executable
add_executable(SudokuProject ${SOURCES} ${HEADERS})

# Place the executable inside "bin/executable" folder under the build directory
set_target_properties(SudokuProject PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Copy Puzzles and Saves into "bin" (next to executable folder)
add_custom_command(TARGET SudokuProject POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/Puzzles ${CMAKE_BINARY_DIR}/bin/Puzzles
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/Saves ${CMAKE_BINARY_DIR}/bin/Saves
)

# For example usage, you might do:
#    cmake -S . -B build
#    cmake --build build
#
# In that case, the project will build without the optional modules.
