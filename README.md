# Hex Tic Tac Toe

Hex Tic Tac Toe is a C++ game built using [SFML](https://www.sfml-dev.org/) that reimagines the classic tic tac toe game on a hexagonal honeycomb board. The board features a central hexagon, a ring of 6 hexagons around it, and an outer ring of 12 hexagons—making a total of 19 cells. The game includes a polished UI with animated winner text, a timer, background toggle, and various UI enhancements.

## Features

- **Honeycomb Board:**  
  A true hexagon-based board using axial coordinates. The board consists of 19 cells arranged in a honeycomb pattern (one center, 6 around it, and 12 on the outer ring).

- **Win Detection:**  
  Checks all six directions for three consecutive cells with the same mark.

- **Animated UI:**  
  Winner text is animated with a pulsating effect using a cursive font. The current turn text is shown in the corresponding player's color.

- **Timer:**  
  Displays elapsed time on-screen in a semi-transparent panel.

- **Dynamic Layout:**  
  Opens by default in full-screen mode (using the desktop resolution) and dynamically adjusts all UI elements when the window is resized.

- **Background Toggle:**  
  Press the **B** key to toggle the background color between black and white.

- **Game Reset:**  
  Press the **R** key to restart the game.

- **Signature:**  
  Your signature (e.g., "fawwaz") is displayed in the bottom-right corner and is kept inside the window regardless of resizing.

## Requirements

- **Compiler:**  
  A C++ compiler supporting C++11 or later.

- **SFML:**  
  Simple and Fast Multimedia Library (SFML 2.5 or later recommended).

- **CMake:**  
  (Optional) For building the project.

## Installation and Build

### Using CMake

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/yourusername/hex-tic-tac-toe.git
   cd hex-tic-tac-toe
   ```

2. **Configure and Build:**
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```

3. **Run the Game:**
   ```bash
   ./hex_tic_tac_toe
   ```

### Manual Compilation (Linux/macOS)

Ensure SFML is installed, then compile with:
```bash
g++ -o hex_tic_tac_toe \
    src/main.cpp src/Game.cpp src/HexBoard.cpp src/UI.cpp src/Colors.cpp \
    -Iinclude -lsfml-graphics -lsfml-window -lsfml-system
./hex_tic_tac_toe
```

*On Windows, adjust your compiler settings and include SFML libraries accordingly.*

## Controls

- **Mouse Click:**  
  Place your move on a hexagon.

- **R Key:**  
  Restart the game.

- **B Key:**  
  Toggle the background color between black and white.

- **Fullscreen:**  
  The game starts in full-screen mode by default and is resizable.

## Assets

- **Fonts:**  
  - `assets/Arial.ttf` is used for standard UI text.
  - `assets/Cursive.ttf` is used for the winner text (cursive style).

Ensure these files are placed in the `assets/` directory.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgments

- [SFML](https://www.sfml-dev.org/) for the graphics and windowing library.
- Tribute to Aligarh Muslim University (AMU) with theme colors.

Enjoy playing Hex Tic Tac Toe!
```
