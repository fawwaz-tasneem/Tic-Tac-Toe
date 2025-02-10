# Hex Tic Tac Toe

Hex Tic Tac Toe is a C++ game built using [SFML](https://www.sfml-dev.org/) that reimagines the classic tic tac toe game on a hexagonal honeycomb board. The board features a central hexagon, a ring of 6 hexagons around it, and an outer ring of 12 hexagons—making a total of 19 cells. The game includes a polished UI with animated winner text, a timer, background toggle, and more.

## Features

- **Honeycomb Board:** A true hexagon-based board using axial coordinates.
- **Win Detection:** Checks all six directions to detect three consecutive moves.
- **Animated UI:** Winner text animates with a pulsating effect using a cursive font.
- **Timer:** Displays elapsed time on the screen.
- **Dynamic & Resizable:** Opens in full-screen mode by default and automatically adjusts UI elements when the window is resized.
- **Background Toggle:** Press the **B** key to switch between black and white backgrounds.
- **Game Reset:** Press **R** to restart the game.
- **Signature:** Your name is shown in the bottom-right corner and is kept inside the window bounds.

## Requirements

- **Compiler:** A C++ compiler supporting C++11 or later.
- **SFML:** Simple and Fast Multimedia Library (SFML 2.5 or later recommended).
- **CMake:** (Optional) For building the project.

## Installation and Build

### Using CMake

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/yourusername/hex-tic-tac-toe.git
   cd hex-tic-tac-toe
2.  **Configure and Build:**
  ```bash
  mkdir build && cd build
  cmake ..
  make
3.  **Run the Game:**
  ```bash
  cd ..
  build/hex_tic_tac_toe
