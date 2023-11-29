#include<iostream>

using namespace std;

class node {
    node* up;
    node* down;
    node* right;
    node* left;
    node* header;
    int coords[3];
    int is_header;
    int size;

    void wire_nodes(node**, int, int, int);
    
    public:
        node( ) {
            up = nullptr;
            down = nullptr;
            right = nullptr;
            left = nullptr;
            header = nullptr;
            is_header = false;
            size = -1;
            coords[3] = {0};
        }

        void init_colheaders();
        void init_nodes(node**, char*);
};

void node::wire_nodes(node** matrix, int row, int pos, int val) {
    for(int j=0; j<4; j++) {
        matrix[row][j].left = (j-1 >= 0? matrix[row]+j-1 : matrix[row]+3);
        matrix[row][j].right = matrix[row]+((j+1)%4);
        matrix[row][j].coords[0] = pos/4;
        matrix[row][j].coords[1] = pos%4;
        matrix[row][j].coords[2] = val;

        switch(j) {
            case 0:
                matrix[row][j].header = this+pos+1;
                break;

            case 1:
                matrix[row][j].header = this+9*(pos/9)+val+81;
                break;

            case 2:
                matrix[row][j].header = this+9*(pos%9)+val+162;
                break;
            
            case 3:
                matrix[row][j].header = this+(9*(3*((pos/9)/3)+(pos%9)/3))+val+243;
                break;
        }

        node* p = matrix[row][j].header;
        for(p; p->down != nullptr; p = p->down);
        p->down = &matrix[row][j];
        matrix[row][j].up = p;

        matrix[row][j].size++;
    }
}

void node::init_colheaders() {
    for(int i=0; i<325; i++) {
        (this+i)->right = this+((i+1)%325);
        (this+i)->left = this+(i-1 >= 0? i-1 : 324);
        this->is_header = true;
        this->size = 0;
    }
}

void node::init_nodes(node** matrix, char* puzzle) {
    int row = 0;

    for(int i=0; i<strlen(puzzle); i++) {
        if(puzzle[i] >= '1' && puzzle[i] <= '9') {
            this->wire_nodes(matrix, row, i, puzzle[i]-'0');
            row++;
        }
        else {
            for(int val=1; val <= 9; val++) {
                this->wire_nodes(matrix, row, i, val);
                row++;
            }
        }
    }
}