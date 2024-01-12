# Candy Crush Console Game

A simple console-based implementation of the classic Candy Crush game in C++.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Data Structure Used](#data-structure-used)
- [How to Play](#how-to-play)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Overview

This project is a console-based implementation of the popular Candy Crush game. It allows players to move candies in the game board to form matches and earn points. The game is implemented in C++ using a double-linked list structure to represent the game board.

## Features

- **Dynamic Game Board:** The game board is dynamically generated with random candies at the start of the game.

- **User Input:** Players can use arrow keys (`W`, `A`, `S`, `D`) to move the candy selector and swap candies. The `E` key is used to confirm the move.

- **Match Detection:** The game detects and destroys matching candies, updating the score accordingly.

- **Gravity Effect:** Candies fall down to fill empty spaces after matches are made.

- **Border Matches:** Special consideration for matches on the borders of the game board.

## Data Structure Used

This Candy Crush game is implemented using a data structure known as a **double-linked list**. The game board is represented as an array of doubly linked lists, where each linked list represents a row in the game board. Each node in the linked list holds information about a candy, including its type (represented by characters 'A', 'B', 'C', 'D', 'E').

### Double-Linked List

A **double-linked list** is a data structure in which elements are stored in nodes, and each node contains a reference to the next and the previous nodes in the sequence. This structure is advantageous for this game as it allows for efficient traversal of rows and columns in the game board.

### Game Board Representation

The game board is dynamically initialized with random candies at the start of the game. Each cell in the board corresponds to a node in the linked list. The candies are manipulated by swapping nodes to create matches.

### Gravity Effect

The game simulates a gravity effect for candies by moving them down the columns after matches are made. This is achieved by shifting candies in each column's linked list, creating a visually appealing falling effect.

### Match Detection

The double-linked list structure facilitates easy detection of horizontal and vertical matches. When a match is detected, the game updates the linked list, destroys the matching candies, and generates new candies to fill the empty spaces.

### Border Matches

Special consideration is given to matches on the borders of the game board. Horizontal and vertical matches on the borders are checked to ensure a seamless gaming experience.

## How to Play

1. Use arrow keys (`W`, `A`, `S`, `D`) to move the candy selector.
2. Press `E` to select a candy.
3. Use arrow keys again to swap the selected candy with an adjacent one.
4. Form matches of three or more candies of the same type horizontally or vertically to earn points.
5. Candies involved in matches will be destroyed, and new candies will fall to fill the empty spaces.

## Installation

To run the game, ensure you have a C++ compiler installed on your system.

```bash
g++ -o CandyCrush CandyCrush.cpp

git clone https://github.com/Abdallah2110678/Candy-Crush-Game.git
