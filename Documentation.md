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

Hex Tic Tac Toe uses an **axial coordinate system** to represent the positions of hexagonal cells. In this system, each cell is identified by two coordinates, $q$ and $r$. This representation simplifies neighbor calculations and the conversion to pixel coordinates.

#### Valid Cells Generation

For a board with a **radius $R = 2$** (which produces a board with side length 3), valid axial coordinates must satisfy:
$$
|q| \leq R,\quad |r| \leq R,\quad |q + r| \leq R
$$
For $R = 2$, these inequalities yield exactly **19 cells**:
- The **central cell**: $(0, 0)$
- The **first ring** (6 cells): e.g., $(0, -1)$, $(1, -1)$, $(1, 0)$, $(0, 1)$, $(-1, 1)$, $(-1, 0)$
- The **outer ring** (12 cells): all remaining cells satisfying the above conditions

### 2.2 Axial-to-Pixel Conversion

To render hexagons on the screen, we convert axial coordinates $(q, r)$ to pixel coordinates $(x, y)$. For **flat-topped hexagons**, the standard conversion is:
$$
x = \text{HEX\_SIZE} \times \frac{3}{2} \times q
$$
$$
y = \text{HEX\_SIZE} \times \sqrt{3} \times \left(r + \frac{q}{2}\right)
$$
where:
- **HEX_SIZE** is the size of the hexagon (i.e., the distance from its center to any vertex).
- $q$ and $r$ are the axial coordinates.

This conversion ensures proper spacing and staggering of the hexagons. Additionally, a rotation of 30° is applied during drawing so that the hexagons appear with flat tops.

---

## 3. Winning Condition Calculation

The game is won when **three consecutive cells** in a straight line are occupied by the same player's mark.

### 3.1 Standard Direction Vectors

For flat-topped hexagons in an axial coordinate system, the six neighbor directions (axial offsets) are defined as:
$$
(1, 0),\quad (0, 1),\quad (-1, 1),\quad (-1, 0),\quad (0, -1),\quad (1, -1)
$$

### 3.2 Checking for a Win

For each nonempty cell at coordinates $(q, r)$ with mark $M$, for each direction $(dq, dr)$:
1. Compute the first neighbor:
   $$
   (q_1, r_1) = (q + dq,\; r + dr)
   $$
2. Compute the second neighbor:
   $$
   (q_2, r_2) = (q + 2dq,\; r + 2dr)
   $$
3. The win condition is satisfied if:
   - Both $(q_1, r_1)$ and $(q_2, r_2)$ are valid cells on the board.
   - Both these cells contain the mark $M$.

**Example:**

If the cell at $(0, 0)$ contains `X` and we check direction $(1, 0)$:
- First neighbor:
  $$
  (1, 0)
  $$
- Second neighbor:
  $$
  (2, 0)
  $$
If both $(1, 0)$ and $(2, 0)$ exist and contain `X`, then player `X` wins.

Debug messages are output to the terminal when a winning condition is met, detailing the starting cell, direction, and the coordinates of the consecutive neighbors.

---

## 4. UI and Graphics Design

### 4.1 Dynamic Layout

- **Fullscreen and Resizable:**  
  The game starts in fullscreen mode using `sf::VideoMode::getDesktopMode()` and is resizable. UI elements recalculate their positions on window resize events.

- **Margins and Spacing:**  
  Generous top and bottom margins (e.g., 150 pixels) ensure that UI elements (title, current turn, timer, restart prompt) do not overlap with the board.

### 4.2 UI Elements

- **Title:**  
  Displayed at the top center (e.g., "Hex Tic Tac Toe") using a large, clear font.
  
- **Current Turn:**  
  Shown below the title, in the color corresponding to the current player:
  - **AMU\_RED** for player `X`
  - **AMU\_GREEN** for player `O`
  
- **Timer:**  
  Displays the elapsed game time (in seconds) at the top-right, rendered on a semi-transparent panel.
  
- **Winner Text:**  
  When the game ends, an animated (pulsating) winner message is displayed at the bottom. This text uses a cursive font and appears in the winning player's color (or white for a draw).
  
- **Restart and Background Toggle Prompts:**  
  Prompts (e.g., "Press R to Restart" and "Press B to Toggle Background") are displayed at the bottom.

### 4.3 Rendering Techniques

- **Drop Shadows:**  
  UI text is rendered with a drop shadow effect for improved contrast over varying backgrounds.
  
- **Animations:**  
  The winner text pulsates using the following formula:
$$
\text{scale} = 1.0 + 0.2 \times \sin(2\pi t)
$$
where $t$ is the elapsed time in seconds.

---

## 5. Code Organization and Methodologies

### 5.1 Modular Structure

The project is organized into several modules:

- **main.cpp:**  
  The application entry point; it initializes the game and calls `Game::run()`.

- **Game Module (Game.h / Game.cpp):**  
  Manages the game loop, event handling (mouse clicks, key presses, window resizing), dynamic UI layout, background toggling, and overall game state.

- **Board Module (HexBoard.h / HexBoard.cpp):**  
  Implements the hexagonal board using axial coordinates, including:
  - Cell generation (based on axial coordinate constraints).
  - Axial-to-pixel conversion.
  - Move placement.
  - Win condition checking.

- **UI Module (UI.h / UI.cpp):**  
  Provides helper functions for rendering text with drop shadows, centering text, and animating the winner message. Two different fonts are used:
  - A standard sans-serif font (Arial) for general UI text.
  - A cursive font for the winner text.

- **Colors Module (Colors.cpp):**  
  Contains global color definitions (e.g., AMU\_RED, AMU\_GREEN, AMU\_WHITE) used throughout the project.

### 5.2 Event Handling

- **Mouse Clicks:**  
  Mouse clicks are processed by converting screen coordinates to board coordinates and checking for proximity to cell centers.

- **Keyboard Input:**  
  - **R Key:** Resets the game.
  - **B Key:** Toggles the background color.
  
- **Window Resizing:**  
  On resize events, the view and UI element positions are recalculated to maintain proper layout.

### 5.3 Debugging

Debug statements are printed to the terminal for:
- Each move (showing the cell’s axial coordinates).
- Win condition detection (showing the starting cell, direction, and coordinates of consecutive neighbors).
- Game resets and background toggles.

---

## 6. Future Enhancements

Some potential future improvements include:
- **AI Opponent:**  
  Implementing an AI component for single-player mode.
- **Audio Effects:**  
  Adding sound effects for moves, wins, and UI interactions.
- **Enhanced Animations:**  
  Introducing more sophisticated animations and particle effects.
- **Settings Menu:**  
  A user interface for adjusting UI parameters (e.g., font sizes, colors, sound volume).
- **Online Multiplayer:**  
  Enabling networked gameplay for competitive matches.

---

## 7. Conclusion

**Hex Tic Tac Toe** is an innovative reinterpretation of a classic game that leverages modern C++ programming, modular design, and SFML for an engaging graphical interface. This document has detailed the mathematical foundations (including axial coordinates, the axial-to-pixel conversion, and winning condition equations), the UI design principles, and the overall code architecture. Contributions and suggestions for further improvements are welcome.

For further questions or contributions, please consult the source code or open an issue in the project repository.

---
