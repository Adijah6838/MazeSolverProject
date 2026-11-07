# Pathfinding Maze Solver (BFS)

## Project Overview
This repository contains a Python implementation of a **Breadth-First Search (BFS)** algorithm designed to find the shortest path through a 2D maze. 

## How the Algorithm Works
Unlike depth-first approaches that might wander down dead ends, BFS explores the maze layer by layer (like ripples in a pond). It uses a **Queue** (`collections.deque`) to track the next cells to visit and a **Dictionary** to keep a record of the path (`came_from`). Because it explores evenly in all directions, the first time it reaches the `E` (End), it is guaranteed to be the shortest possible path.

## Features
*   **Animated Search:** The terminal visually displays the BFS ripples with `.` characters before drawing the final path.
*   **Path Reconstruction:** Traces back from the End to the Start to draw the path using `*` characters.
*   **Wall Detection:** Automatically routes around `#` walls.

## How to Run
1. Ensure you have Python installed.
2. Open your terminal in the project directory.
3. Run the script:
```bash
python main.py