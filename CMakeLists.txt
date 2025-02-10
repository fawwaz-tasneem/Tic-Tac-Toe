cmake_minimum_required(VERSION 3.10)
project(HexTicTacToe)

set(CMAKE_CXX_STANDARD 17)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Include headers
include_directories(include)

# Add source files from src/
add_executable(hex_tic_tac_toe 
    src/main.cpp 
    src/Game.cpp 
    src/UI.cpp 
    src/HexBoard.cpp
)

# Link SFML libraries
target_link_libraries(hex_tic_tac_toe sfml-graphics sfml-window sfml-system)

