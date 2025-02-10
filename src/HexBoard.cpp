// HexBoard.cpp
#include "HexBoard.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstring>

HexBoard::HexBoard() {
    // Generate all valid cells for a hex board with radius BOARD_RADIUS.
    // Valid axial coordinates satisfy: |q| <= BOARD_RADIUS, |r| <= BOARD_RADIUS, and |q + r| <= BOARD_RADIUS.
    for (int q = -BOARD_RADIUS; q <= BOARD_RADIUS; q++) {
        int r1 = std::max(-BOARD_RADIUS, -q - BOARD_RADIUS);
        int r2 = std::min(BOARD_RADIUS, -q + BOARD_RADIUS);
        for (int r = r1; r <= r2; r++) {
            HexCell cell;
            cell.q = q;
            cell.r = r;
            cell.value = ' ';
            cells.push_back(cell);
        }
    }
}

bool HexBoard::makeMove(int q, int r, char player) {
    // Find the cell with axial coordinates (q, r)
    for (auto &cell : cells) {
        if (cell.q == q && cell.r == r) {
            if (cell.value == ' ') {
                cell.value = player;
                return true;
            }
            return false;
        }
    }
    return false;
}

char HexBoard::checkWinner() {
    // Axial neighbor directions for flat-topped hexagons.
    // Standard offsets: { (1,0), (0,1), (-1,1), (-1,0), (0,-1), (1,-1) }
    int directions[6][2] = {
        {1, 0}, {0, 1}, {-1, 1},
        {-1, 0}, {0, -1}, {1, -1}
    };
    // For each cell that is not empty, check in all 6 directions for 2 consecutive matching neighbors.
    for (const auto &cell : cells) {
        if (cell.value == ' ') continue;
        for (int d = 0; d < 6; d++) {
            int dq = directions[d][0];
            int dr = directions[d][1];
            int q1 = cell.q + dq, r1 = cell.r + dr;
            int q2 = cell.q + 2 * dq, r2 = cell.r + 2 * dr;
            char v1 = ' ', v2 = ' ';
            bool found1 = false, found2 = false;
            for (const auto &c : cells) {
                if (c.q == q1 && c.r == r1) { v1 = c.value; found1 = true; }
                if (c.q == q2 && c.r == r2) { v2 = c.value; found2 = true; }
            }
            if (found1 && found2 && v1 == cell.value && v2 == cell.value) {
                std::cout << "Debug: Winning condition found: Cell (" << cell.q << "," << cell.r 
                          << ") with value " << cell.value << " has consecutive neighbors at ("
                          << q1 << "," << r1 << ") and (" << q2 << "," << r2 
                          << ") in direction (" << dq << "," << dr << ")\n";
                return cell.value;
            }
        }
    }
    return ' ';
}

bool HexBoard::isFull() {
    for (const auto &cell : cells) {
        if (cell.value == ' ')
            return false;
    }
    return true;
}

std::vector<HexCell>& HexBoard::getCells() {
    return cells;
}

sf::Vector2f HexBoard::axialToPixel(int q, int r) {
    // Conversion formula for flat-topped hexagons:
    // x = HEX_SIZE * 3/2 * q
    // y = HEX_SIZE * sqrt(3) * (r + q/2)
    float x = HEX_SIZE * 1.5f * q;
    float y = HEX_SIZE * std::sqrt(3) * (r + q / 2.0f);
    return sf::Vector2f(x, y);
}

void HexBoard::draw(sf::RenderWindow& window, const sf::Vector2f& offset) {
    for (const auto &cell : cells) {
        sf::Vector2f pos = axialToPixel(cell.q, cell.r) + offset;
        sf::CircleShape hex(HEX_SIZE, 6);
        // Rotate 30° to get flat-topped hexagons.
        hex.setRotation(30);
        sf::Color fillColor;
        if (cell.value == 'X')
            fillColor = AMU_RED;
        else if (cell.value == 'O')
            fillColor = AMU_GREEN;
        else
            fillColor = AMU_WHITE;
        hex.setFillColor(fillColor);
        hex.setOutlineColor(sf::Color::Black);
        hex.setOutlineThickness(2);
        hex.setPosition(pos);
        hex.setOrigin(HEX_SIZE, HEX_SIZE);
        window.draw(hex);
    }
}
