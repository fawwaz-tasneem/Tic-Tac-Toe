# Hex Tic Tac Toe Detailed Documentation

This document provides an in-depth explanation of the design decisions, coordinate systems, equations, and methodologies used in **Hex Tic Tac Toe**—a modern twist on the classic tic tac toe game played on a hexagonal honeycomb board.

---

## 1. Overview

**Hex Tic Tac Toe** is implemented in C++ using SFML for graphics and window management. Unlike the traditional 3×3 grid, the game is played on a hexagon-shaped board consisting of **19 cells** arranged as follows:
- **1 central cell**
- A first ring of **6 cells** around the center
- An outer ring of **12 cells**

Players alternate placing their marks ('X' or 'O') on the board, and the game declares a win when three consecutive cells in a straight line (in any of the six directions) are occupied by the same player.

---

## 2. Board Design and Coordinate Systems

### 2.1 Axial Coordinates

Hex Tic Tac Toe uses an **axial coordinate system** to represent the positions of hexagonal cells. In this system, each cell is identified by two coordinates, \(q\) and \(r\). This representation simplifies neighbor calculations and the conversion to pixel coordinates.

#### Valid Cells Generation

For a board with a **radius \(R = 2\)** (which produces a board with side length 3), valid axial coordinates must satisfy:

$$
|q| \leq R,\quad |r| \leq R,\quad |q + r| \leq R
$$

For \(R = 2\), these inequalities yield exactly 19 cells:
- The **central cell**: \((0, 0)\)
- The **first ring** (6 cells): e.g., \((0, -1)\), \((1, -1)\), \((1, 0)\), \((0, 1)\), \((-1, 1)\), \((-1, 0)\)
- The **outer ring** (12 cells): the remaining cells satisfying the above conditions

### 2.2 Axial-to-Pixel Conversion

To render hexagons on the screen, we convert axial coordinates \((q, r)\) to pixel coordinates \((x, y)\). For **flat-topped hexagons**, the standard conversion is:

$$
x = \text{HEX\_SIZE} \times \frac{3}{2} \times q
$$

$$
y = \text{HEX\_SIZE} \times \sqrt{3} \times \left(r + \frac{q}{2}\right)
$$

Where:
- **HEX_SIZE** is the size of the hexagon (the distance from its center to any vertex).
- \(q\) and \(r\) are the axial coordinates.

This conversion ensures proper spacing and staggering of the hexagons. Additionally, when drawing, a rotation of 30° is applied to achieve the flat-topped appearance.

---

## 3. Winning Condition Calculation

The game is won when **three consecutive cells** in a straight line are occupied by the same player's mark. The winning condition is calculated as follows:

### 3.1 Standard Direction Vectors

For flat-topped hexagons in an axial coordinate system, the six neighbor directions (axial offsets) are:

$$
(1, 0),\quad (0, 1),\quad (-1, 1),\quad (-1, 0),\quad (0, -1),\quad (1, -1)
$$

### 3.2 Checking for a Win

For each nonempty cell at coordinates \((q, r)\) (with mark \(M\)):
1. For each direction \((dq, dr)\) from the list above, compute the coordinates of the two consecutive neighbors:
   - First neighbor:
     $$
     (q_1, r_1) = (q + dq, \; r + dr)
     $$
   - Second neighbor:
     $$
     (q_2, r_2) = (q + 2 \times dq, \; r + 2 \times dr)
     $$
2. The winning condition is satisfied if:
   - Both \((q_1, r_1)\) and \((q_2, r_2)\) are valid cells on the board.
   - Both these cells contain the same mark \(M\).

**Example:**

If a cell at \((0, 0)\) contains 'X' and we check the direction \((1, 0)\):
- First neighbor: 
  $$
  (q_1, r_1) = (0 + 1, \; 0) = (1, 0)
  $$
- Second neighbor:
  $$
  (q_2, r_2) = (0 + 2, \; 0) = (2, 0)
  $$
If both cells \((1, 0)\) and \((2, 0)\) exist and also contain 'X', then player 'X' wins.

Debug messages are output to the terminal when a winning condition is met, detailing:
- The starting cell \((q, r)\)
- The direction \((dq, dr)\)
- The coordinates of the consecutive neighbors

---

## 4. UI and Graphics Design

### 4.1 Dynamic Layout

- **Fullscreen and Resizable:**  
  The game starts in fullscreen mode (using `sf::VideoMode::getDesktopMode()`) and is resizable. The UI recalculates positions on window resize events.

- **Margins and Spacing:**  
  Generous top and bottom margins (e.g., 150 pixels) ensure that UI elements (title, current turn, timer, restart prompt) do not overlap the board.

### 4.2 UI Elements

- **Title:**  
  Displayed at the top center (e.g., "Hex Tic Tac Toe") using a clear, large font.

- **Current Turn:**  
  Shown below the title in the current player’s color:
  - **AMU_RED** for player 'X'
  - **AMU_GREEN** for player 'O'

- **Timer:**  
  Displays the elapsed game time in seconds at the top-right on a semi-transparent panel.

- **Winner Text:**  
  When the game ends, an animated (pulsating) winner message is shown at the bottom using a cursive font, in the winning player's color (or white in case of a draw).

- **Restart and Background Toggle Prompts:**  
  Prompts to reset the game (press **R**) and toggle the background color (press **B**) are displayed at the bottom.

### 4.3 Rendering Techniques

- **Drop Shadows:**  
  UI text is rendered with a drop shadow effect to improve contrast over various backgrounds.

- **Animations:**  
  The winner text is animated with a pulsating effect, calculated using a sine wave function:
  $$
  \text{scale} = 1.0 + 0.2 \times \sin\left(2\pi \times t\right)
  $$
  where \(t\) is the elapsed time in seconds.

---

## 5. Code Organization and Methodologies

### 5.1 Modular Structure

The project is divided into several modules:

- **main.cpp:**  
  The entry point that initializes and runs the game.

- **Game Module (Game.h / Game.cpp):**  
  Manages the game loop, event handling (mouse clicks, key presses, window resizing), UI layout, background toggling, and game state.

- **Board Module (HexBoard.h / HexBoard.cpp):**  
  Implements the hexagonal board using axial coordinates, including cell generation, axial-to-pixel conversion, move placement, and win checking.

- **UI Module (UI.h / UI.cpp):**  
  Provides functions for rendering text with drop shadows, centering text, and animating the winner message using different fonts.

- **Colors Module (Colors.cpp):**  
  Contains global color definitions (e.g., AMU_RED, AMU_GREEN, AMU_WHITE) used to maintain a consistent theme.

### 5.2 Event Handling

- **Mouse Clicks:**  
  Clicks are processed by converting the screen coordinates to board coordinates and checking proximity to cell centers.

- **Keyboard Input:**  
  - **R Key:** Resets the game.
  - **B Key:** Toggles the background color.
  
- **Window Resizing:**  
  The view and board offset are recalculated on resize events to maintain proper UI layout.

### 5.3 Debugging

- Debug messages print to the terminal for:
  - Each move (with cell coordinates).
  - Winning condition detection (with starting cell, direction, and neighbor coordinates).
  - Game resets and background toggles.

---

## 6. Future Enhancements

Potential future improvements include:
- **AI Opponent:**  
  Adding an AI component for single-player mode.
- **Audio Effects:**  
  Integrating sound effects for moves, wins, and other interactions.
- **Enhanced Animations:**  
  More sophisticated animations (e.g., particle effects) for better visual appeal.
- **Settings Menu:**  
  A runtime interface for adjusting UI settings (font sizes, colors, sound volume).
- **Online Multiplayer:**  
  Enabling networked gameplay for competitive matches.

---

## 7. Conclusion

**Hex Tic Tac Toe** is an innovative reinterpretation of a classic game that leverages modern C++ programming, modular design, and SFML for an engaging graphical interface. This documentation has detailed the mathematical foundations (including axial coordinates, axial-to-pixel conversion, and winning condition equations), UI design principles, and overall code architecture. We welcome contributions and suggestions for future improvements.

For further questions or contributions, please consult the source code or open an issue in the project repository.

---
