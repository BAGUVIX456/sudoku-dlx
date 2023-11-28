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

int main() {
    char puzzle[] = "53..7....6..195....98....6.8...6...34..8.3..17...2...6.6....28....419..5....8..79";
    node* root = new node[325];
    root->init_colheaders();
    cout << calculate_size(puzzle) << endl;
    return 0;
}