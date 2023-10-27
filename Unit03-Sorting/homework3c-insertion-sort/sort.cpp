#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void insertionSort(std::vector<std::string> &lines) {
    for (int i = 1; i < lines.size(); ++i) {
        std::string key = lines[i];
        int j = i - 1;
        while (j >= 0 && key < lines[j]) {
            lines[j + 1] = lines[j];
            --j;
        }
        lines[j + 1] = key;
    }
}

int main(int argc, char *argv[]) {
    std::vector<std::string> lines;

    // Read lines from standard input or a file
    if (argc == 1) {
        // Read from standard input
        std::string line;
        while (std::getline(std::cin, line)) {
            lines.push_back(line);
        }
    } else if (argc == 2) {
        // Read from a file
        std::ifstream input(argv[1]);
        if (!input.is_open()) {
            std::cerr << "Error: Cannot open the file." << std::endl;
            return 1;
        }
        std::string line;
        while (std::getline(input, line)) {
            lines.push_back(line);
        }
        input.close();
    } else {
        std::cerr << "Usage: " << argv[0] << " [input_file]" << std::endl;
        return 1;
    }

    // Sort the lines using insertion sort
    insertionSort(lines);

    // Print the sorted lines to standard output
    for (const std::string &line : lines) {
        std::cout << line << std::endl;
    }

    return 0;
}
