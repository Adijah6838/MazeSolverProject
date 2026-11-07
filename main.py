import time
import os
from collections import deque

# '#' = Wall, ' ' = Empty space, 'S' = Start, 'E' = End
maze = [
    ["#", "#", "#", "#", "#", "#", "#", "#", "#", "#"],
    ["#", "S", " ", " ", "#", " ", " ", " ", " ", "#"],
    ["#", "#", "#", " ", "#", " ", "#", "#", " ", "#"],
    ["#", " ", " ", " ", " ", " ", "#", " ", " ", "#"],
    ["#", " ", "#", "#", "#", " ", "#", "#", "#", "#"],
    ["#", " ", " ", " ", "#", " ", " ", " ", "E", "#"],
    ["#", "#", "#", "#", "#", "#", "#", "#", "#", "#"]
]

def print_maze(maze, clear_screen=False):
    if clear_screen:
        os.system('cls' if os.name == 'nt' else 'clear')
    for row in maze:
        print("".join(row))

def solve_maze(maze, animate=False):
    rows = len(maze)
    cols = len(maze[0])
    
    start = None
    end = None
    
    # Find the Start and End coordinates
    for r in range(rows):
        for c in range(cols):
            if maze[r][c] == 'S':
                start = (r, c)
            elif maze[r][c] == 'E':
                end = (r, c)

    if not start or not end:
        print("Maze must have a Start (S) and an End (E)!")
        return False

    # Queue for BFS: stores tuples of (row, col)
    queue = deque([start])
    
    # Dictionary to keep track of how we reached a cell: (row, col) -> (parent_row, parent_col)
    came_from = {start: None}
    
    # Directions: Up, Down, Left, Right
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
    
    found = False

    while queue:
        current = queue.popleft() # Take the first item out of the queue
        
        if current == end:
            found = True
            break
            
        # If animating, mark the visited cell with '.' and redraw
        if animate and current != start:
            maze[current[0]][current[1]] = '.'
            print_maze(maze, clear_screen=True)
            time.sleep(0.05)

        # Check all 4 neighbors
        for dr, dc in directions:
            nr, nc = current[0] + dr, current[1] + dc
            
            # Check if the neighbor is inside the maze and is not a wall
            if 0 <= nr < rows and 0 <= nc < cols and maze[nr][nc] != '#':
                if (nr, nc) not in came_from:
                    queue.append((nr, nc))
                    came_from[(nr, nc)] = current

    if not found:
        print("No path found!")
        return False

    # Reconstruct the path by tracing back from End to Start
    path = []
    current = end
    while current != start:
        path.append(current)
        current = came_from[current]
    path.append(start)
    path.reverse() # Flip it so it goes Start -> End

    # Draw the path on the maze using '*'
    for r, c in path:
        if maze[r][c] not in ('S', 'E'):
            maze[r][c] = '*'

    return True

print("Original Maze:")
print_maze(maze)
time.sleep(1)

print("\nSearching for the shortest path...")
# We will set animate=True to watch the BFS algorithm ripple through the maze
if solve_maze(maze, animate=True):
    print_maze(maze, clear_screen=True)
    print("\nShortest path found! (Marked with *)")
else:
    print_maze(maze, clear_screen=True)
    print("\nNo path found.")
