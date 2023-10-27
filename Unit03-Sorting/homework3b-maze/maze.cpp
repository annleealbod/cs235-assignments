#include <iostream>
#include <fstream>
#include <vector>
#include "Grid.h"

// Modify the solveMaze function to accept the output file as a parameter
bool solveMaze(Grid& maze, int row, int column, int level, std::ofstream& solutionFile) {
    // Check if we have reached the end of the maze
    if (row == maze.height() - 1 && column == maze.width() - 1 && level == maze.depth() - 1) {
        return true;  // Found a solution
    }

    // Mark the current cell as visited
    maze.at(row, column, level) = 2;

    // Define possible moves (up, down, left, right, in, out)
    int moves[6][3] = {{-1, 0, 0}, {1, 0, 0}, {0, -1, 0}, {0, 1, 0}, {0, 0, -1}, {0, 0, 1}};

    for (int i = 0; i < 6; i++) {
        int newRow = row + moves[i][0];
        int newColumn = column + moves[i][1];
        int newLevel = level + moves[i][2];

        // Check if the new move is within bounds and leads to a passable space
        if (newRow >= 0 && newRow < maze.height() &&
            newColumn >= 0 && newColumn < maze.width() &&
            newLevel >= 0 && newLevel < maze.depth() &&
            maze.at(newRow, newColumn, newLevel) == 1) {
            // Updated distance check
            int dr = abs(newRow - row);
            int dc = abs(newColumn - column);
            int dl = abs(newLevel - level);

            // Check if the movement is valid (one step in any direction)
            if ((dr == 1 && dc == 0 && dl == 0) ||  // Move in the same level
                (dr == 0 && dc == 1 && dl == 0) ||  // Move in the same level
                (dr == 0 && dc == 0 && dl == 1)) {   // Move to a different level
                // Valid move, do nothing
            } else {
                // Invalid move
                continue;  // Skip this move
            }

            // Recursively explore the new move
            if (solveMaze(maze, newRow, newColumn, newLevel, solutionFile)) {
                // If a solution is found, write the current coordinates to the output file
                solutionFile << row << " " << column << " " << level << std::endl;
                return true;
            }
        }
    }

    // If no solution is found, backtrack by marking the cell as visited (value 2)
    maze.at(row, column, level) = 0;

    // Updated: Return false only after all paths have been explored
    return false;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <maze_file> <solution_file>" << std::endl;
        return 1;
    }

    std::ifstream mazeFile(argv[1]);
    if (!mazeFile) {
        std::cerr << "Error: Unable to open maze file." << std::endl;
        return 1;
    }

    Grid maze;
    mazeFile >> maze;
    mazeFile.close();

    // Check if the maze is solvable
    std::ofstream solutionFile(argv[2]);
    if (solveMaze(maze, 0, 0, 0, solutionFile)) {
        solutionFile << "SOLUTION" << std::endl; // Write "SOLUTION" at the beginning
        solveMaze(maze, 0, 0, 0, solutionFile); // Continue to generate the solution path
    } else {
        solutionFile << "NO SOLUTION" << std::endl;
    }
    solutionFile.close();

    return 0;
}

