#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <utility>
#include <thread>
#include <chrono>

using namespace std;

void print_maze(const vector<vector<char>>& maze, bool clear_screen = false) {
    if (clear_screen) { system("cls"); }
    for (const auto& row : maze) {
        for (char c : row) { cout << c; }
        cout << endl;
    }
}

void solve_maze(vector<vector<char>>& maze, bool animate = false) {
    int rows = maze.size();
    int cols = maze[0].size();
    pair<int, int> start = {-1, -1};
    pair<int, int> end = {-1, -1};

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (maze[r][c] == 'S') start = {r, c};
            if (maze[r][c] == 'E') end = {r, c};
        }
    }

    if (start.first == -1 || end.first == -1) {
        cout << "Maze must have a Start (S) and an End (E)!" << endl;
        return;
    }

    queue<pair<int, int>> q;
    q.push(start);
    map<pair<int, int>, pair<int, int>> came_from;
    came_from[start] = {-1, -1}; 
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    bool found = false;

    while (!q.empty()) {
        pair<int, int> current = q.front();
        q.pop();

        if (current == end) { found = true; break; }

        if (animate && current != start) {
            maze[current.first][current.second] = '.';
            print_maze(maze, true);
            this_thread::sleep_for(chrono::milliseconds(50));
        }

        for (auto dir : directions) {
            int nr = current.first + dir.first;
            int nc = current.second + dir.second;
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && maze[nr][nc] != '#') {
                if (came_from.find({nr, nc}) == came_from.end()) {
                    q.push({nr, nc});
                    came_from[{nr, nc}] = current;
                }
            }
        }
    }

    if (!found) { cout << "No path found!" << endl; return; }

    pair<int, int> current = end;
    while (current != start) {
        if (maze[current.first][current.second] != 'E') { maze[current.first][current.second] = '*'; }
        current = came_from[current];
    }
    print_maze(maze, true);
    cout << "\nShortest path found! (Marked with *)" << endl;
}

int main() {
    vector<vector<char>> maze = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', 'S', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#'},
        {'#', '#', '#', ' ', '#', ' ', '#', '#', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#'},
        {'#', ' ', '#', '#', '#', ' ', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', 'E', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
    };
    cout << "Original Maze:" << endl;
    print_maze(maze);
    cout << "\nSearching for shortest path..." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    solve_maze(maze, true);
    return 0;
}
