# Hex Tic Tac Toe Detailed Documentation

This document provides an in‐depth explanation of the design decisions, coordinate systems, equations, and methodologies used in Hex Tic Tac Toe—a modern twist on the classic tic tac toe game played on a hexagonal honeycomb board.

---

## 1. Overview

Hex Tic Tac Toe is implemented in C++ using SFML for graphics and window management. Unlike the traditional 3×3 grid, the game is played on a hexagon‐shaped board consisting of 19 cells arranged as follows:
- 1 **central cell**
- A first ring of 6 cells around the center
- An outer ring of 12 cells

Players alternate placing their marks ('X' or 'O') on the board, and the game declares a win when three consecutive cells in a straight line (in any of the six directions) are occupied by the same player.

---

## 2. Board Design and Coordinate Systems

### 2.1 Axial Coordinates

Hex Tic Tac Toe uses an **axial coordinate system** to represent the positions of hexagonal cells. In this system, each cell is identified by two coordinates, \(q\) and \(r\). This representation simplifies neighbor calculations and the conversion to pixel coordinates.

#### Valid Cells Generation

For a board with a **radius \(R = 2\)** (which produces a board with side length 3), valid axial coordinates must satisfy:
- \(|q| \leq R\)
- \(|r| \leq R\)
- \(|q + r| \leq R\)

For \(R = 2\), these inequalities yield 19 cells:
- The **central cell**: \((0,0)\)
- The **first ring** (6 cells): for example, \((0, -1)\), \((1, -1)\), \((1, 0)\), \((0, 1)\), \((-1, 1)\), and \((-1, 0)\)
- The **outer ring** (12 cells): cells with axial coordinates satisfying the constraints but not included in the inner ring

### 2.2 Axial-to-Pixel Conversion

To render hexagons on the screen, we convert axial coordinates \((q, r)\) to pixel coordinates \((x, y)\). For **flat-topped hexagons**, the standard conversion is:

\[
x = \text{HEX\_SIZE} \times \frac{3}{2} \times q
\]
\[
y = \text{HEX\_SIZE} \times \sqrt{3} \times \left(r + \frac{q}{2}\right)
\]

Where:
- **HEX_SIZE** is the size of the hexagon (the distance from its center to any vertex).
- \(q\) and \(r\) are the axial coordinates.

This conversion ensures proper spacing and staggering of the hexagons. Additionally, when drawing the hexagons, a rotation of 30° is applied to achieve a flat-topped appearance.

---

## 3. Winning Condition Calculation

The game is won when three consecutive cells in a straight line are occupied by the same player's mark. The calculation is done in the following manner:

### 3.1 Standard Direction Vectors

For flat-topped hexagons in an axial coordinate system, the six neighbor directions (or axial offsets) are defined as:

1. \((1, 0)\)
2. \((0, 1)\)
3. \((-1, 1)\)
4. \((-1, 0)\)
5. \((0, -1)\)
6. \((1, -1)\)

### 3.2 Winning Condition Check

For each cell with coordinates \((q, r)\) that is not empty (i.e., its value is 'X' or 'O'):
1. For each direction \((dq, dr)\) in the list above:
   - Calculate the first neighbor:
     \[
     (q_1, r_1) = (q + dq, \; r + dr)
     \]
   - Calculate the second neighbor:
     \[
     (q_2, r_2) = (q + 2 \times dq, \; r + 2 \times dr)
     \]
2. The winning condition is satisfied if:
   - Both \((q_1, r_1)\) and \((q_2, r_2)\) are valid cells on the board.
   - Both cells contain the same mark as the starting cell.

**Example Calculation:**

If a cell at \((0, 0)\) has the mark 'X' and we check the direction \((1, 0)\):
- The first neighbor is at \((0+1, 0+0) = (1, 0)\).
- The second neighbor is at \((0+2, 0+0) = (2, 0)\).
- If both cells \((1, 0)\) and \((2, 0)\) exist on the board and also contain 'X', then player 'X' wins.

Debugging statements are output to the terminal when a winning condition is met, showing the starting cell, direction, and coordinates of the consecutive neighbors.

---

## 4. UI and Graphics Design

### 4.1 Dynamic Layout

- **Full-Screen and Resizable:**  
  The game opens in full-screen mode by default using `sf::VideoMode::getDesktopMode()` with `sf::Style::Fullscreen` (or `sf::Style::Default` for a resizable window). When resized, the board and UI elements adjust dynamically.

- **Margins and Spacing:**  
  The UI is designed with generous top and bottom margins (e.g., 150 pixels) to ensure that elements like the title, current turn text, timer, and restart prompt do not overlap with the board.

### 4.2 UI Elements

- **Title:**  
  Displayed at the top center (e.g., "Hex Tic Tac Toe") using a large, clear font.

- **Current Turn:**  
  Shown below the title, in the color corresponding to the current player (AMU_RED for 'X', AMU_GREEN for 'O').

- **Timer:**  
  A timer in the top-right corner shows the elapsed game time in seconds. It is rendered on a semi-transparent background panel for clarity.

- **Winner Text:**  
  When the game ends, an animated (pulsating) winner message is shown at the bottom. This text uses a cursive font and is displayed in the winning player's color (or white in the case of a draw).

- **Restart and Background Toggle Prompts:**  
  Instructions for restarting the game (press R) and toggling the background color (press B) are displayed at the bottom.

- **Signature:**  
  A small signature (e.g., "fawwaz") is rendered at the bottom-right corner and is clamped so that it remains visible even if the window is resized very small.

### 4.3 Rendering Techniques

- **Drop Shadows:**  
  All UI text is rendered with a drop shadow effect (by drawing a black offset copy of the text) to improve visibility over varying backgrounds.

- **Animations:**  
  The winner text pulsates using a sine wave function to vary its scale over time, drawing the player's attention to the win message.

---

## 5. Code Organization and Methodologies

### 5.1 Modular Structure

The project is organized into the following modules:
- **main.cpp:**  
  The application entry point, which creates a `Game` object and calls its `run()` method.
  
- **Game Module (Game.h / Game.cpp):**  
  Handles the main game loop, event handling (mouse clicks, key presses, window resizing), dynamic UI layout, background color toggling, and game state management.

- **Board Module (HexBoard.h / HexBoard.cpp):**  
  Implements the hexagonal board using axial coordinates. Includes functions for generating valid cells, converting axial coordinates to pixel positions, placing moves, and checking win conditions.

- **UI Module (UI.h / UI.cpp):**  
  Provides helper functions for drawing text with drop shadows, centering text, and applying animation scaling. Two different fonts are used:
  - A standard font (Arial) for most UI text.
  - A cursive font for the animated winner message.

- **Colors Module (Colors.cpp):**  
  Contains global definitions for theme colors (AMU_RED, AMU_GREEN, AMU_WHITE).

### 5.2 Event Handling

The SFML event loop captures:
- **Mouse Clicks:**  
  Detects clicks near a hexagon’s center by converting screen coordinates to board coordinates.
  
- **Keyboard Events:**  
  - **R Key:** Resets the game.
  - **B Key:** Toggles the background color between black and white.
  
- **Window Resizing:**  
  The view is updated on resize events, and UI elements are repositioned accordingly.

### 5.3 Debugging

Debugging statements are printed to the terminal for:
- Moves (showing the axial coordinates of the cell clicked).
- Win condition detection (showing the starting cell, direction, and neighbor coordinates).
- Game resets and background toggles.

---

## 6. Future Enhancements

Some potential future improvements include:
- **AI Opponent:**  
  Adding an artificial intelligence component to allow single-player mode.
- **Audio Effects:**  
  Integrating sound effects for moves, wins, and UI interactions.
- **Enhanced Animations:**  
  More sophisticated animations and particle effects could further enhance the user experience.
- **Settings Menu:**  
  A user interface for adjusting settings such as font sizes, colors, and sound volume.
- **Online Multiplayer:**  
  Enabling networked play for competitive online matches.

---

## 7. Conclusion

Hex Tic Tac Toe is an innovative reinterpretation of a classic game that leverages modern C++ programming, modular design, and the SFML library for an engaging graphical interface. This detailed documentation covers the coordinate systems, equations, win condition calculations, and UI methodologies used in the project. Developers and contributors are encouraged to study and extend this design.

For further questions or contributions, please consult the source code or open an issue on the project's repository.
