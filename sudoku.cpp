#include<iostream>
#include<cstring>

#include "dlx.hpp"

using namespace std;

int calculate_size(char puzzle[]) {
    int len = 0;
    for(int i=0; i<strlen(puzzle); i++)
        if(puzzle[i] == '.')
            len += 9;
        else
            len++;

    return len;
}

int main(int argc, char** argv) {
    if(argc == 2) {
        char* puzzle = argv[1];

        if(is_valid_puzzle(puzzle)) {
            node* root = new node[325];
            root->init_colheaders();

            int rows = calculate_size(puzzle);
            node** matrix = new node*[rows];
            for(int i=0; i<rows; i++)
                matrix[i] = new node[4];
            root->init_nodes(matrix, puzzle);

            int** solution = new int*[81];
            for(int i=0; i<81; i++)
                solution[i] = new int[3];
            root->dlx(matrix, solution, 0, 0);
            
            return 0;
        }
        else
            return 2;
    }
    else {
        cout << "Error: Expected 1 argument, received " << argc-1 << endl;
        return 1;
    }
    
}