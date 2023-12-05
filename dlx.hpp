#include<iostream>

using namespace std;

//  Finds out if the entered puzzle is valid
bool is_valid_puzzle(char* puzzle) {
    // Entered puzzle MUST be of 81 characters
    if(strlen(puzzle) != 81) {
        cerr << "Error: Puzzle input must have 81 characters" << endl << "\tCurrent input has " << strlen(puzzle) << endl;
        return false;
    }

    // Puzzle must only have valid characters
    for(int i=0; i<81; i++) {
        if(!((puzzle[i] >= '1' && puzzle[i] <= '9') || puzzle[i] == '.')) {
            cerr << "Error: Puzzle input can only contain numbers from 1 to 9 and '.'" << endl << "\tCharacter " << i+1 << " is \"" << puzzle[i] << "\"" << endl;
            return false;
        }
    }

    // No row must have repeated values
    for(int i=0; i<9; i++) {
        int row[9];
        int c = 0;
        for(int j=0; j<9; j++) {
            if(puzzle[9*i + j] >= '1' && puzzle[9*j + i] <= '9') {
                row[c] = puzzle[9*i + j] - '0';
                c++;
            }
        }

        for(int j=0; j<c; j++) {
            for(int k=j+1; k<c; k++) {
                if(row[j] == row[k]) {
                    cerr << "Illegal puzzle: Number " << row[j] << " repeated in row " << i+1 << " of sudoku table" << endl;
                    return false;
                }
            }
        }
    }

    // No column must have repeated values
    for(int i=0; i<9; i++){
        int col[9];
        int c = 0;
        for(int j=0; j<9; j++) {
            if(puzzle[9*j + i] >= '1' && puzzle[9*j +i] <= '9') {
                col[c] = puzzle[9*j + i] - '0';
                c++;
            }
        }

        for(int j=0; j<c; j++) {
            for(int k=j+1; k<c; k++) {
                if(col[j] == col[k]) {
                    cerr << "Illegal puzzle: Number " << col[j] << " repeated in column " << i+1 << " of sudoku table" << endl;
                    return false;
                }
            }
        }
    }

    // No box must have repeated values
    for(int i=0; i<9; i++) {
        int box[9];
        int c = 0;
        for(int j=0; j<3; j++) {
            for(int k=0; k<3; k++) {
                if(puzzle[9*((i/3)*3+j) + ((i%3)*3)+k] >= '1' && puzzle[9*((i/3)*3+j) + ((i%3)*3)+k] <= '9') {
                    box[c] = puzzle[9*((i/3)*3+j) + ((i%3)*3)+k] - '0';
                    c++;
                }
            } 
        }

        for(int j=0; j<c; j++) {
            for(int k=j+1; k<c; k++) {
                if(box[j] == box[k]) {
                    cerr << "Illegal puzzle: Number " << box[j] << " repeated in box " << i+1 << " of sudoku table" << endl;
                    return false;
                }
            }
        }
    }

    return true;
}

// Defines contents of one node of the linked list matrix
class node {
    // Pointers to surrounding nodes
    node* up;
    node* down;
    node* right;
    node* left;
    node* header;
    
    // Element 0 and 1 will hold the location in the 9*9 sudoku table to which the row corresponds
    // Element 2 will hold the value, ranging from 1 to 9
    int coords[3];

    int is_header;

    // Number of nodes connected to the header
    int size;

    void wire_nodes(node**, int, int, int);
    node* choose_col();
    void cover();
    void uncover();
    
    public:
        node() {
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
        void dlx(node**, int**, int, int);
};

// Function to properly wire the nodes of the matrix, written separately only to reduce repetition in init_nodes()
void node::wire_nodes(node** matrix, int row, int pos, int val) {
    for(int j=0; j<4; j++) {
        matrix[row][j].left = (j-1 >= 0? matrix[row]+j-1 : matrix[row]+3);
        matrix[row][j].right = matrix[row]+((j+1)%4);
        matrix[row][j].coords[0] = pos/9;
        matrix[row][j].coords[1] = pos%9;
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
        matrix[row][j].header->size++;
    }
}

void node::init_colheaders() {
    for(int i=0; i<325; i++) {
        (this+i)->right = this+((i+1)%325);
        (this+i)->left = this+(i-1 >= 0? i-1 : 324);
        (this+i)->is_header = true;
        (this+i)->size = 0;
    }
}

void node::init_nodes(node** matrix, char* puzzle) {
    int row = 0;

    for(int i=0; i<81; i++) {
        if(puzzle[i] >= '1' && puzzle[i] <= '9') {
            wire_nodes(matrix, row, i, puzzle[i]-'0');
            row++;
        }
        else {
            for(int val=1; val <= 9; val++) {
                wire_nodes(matrix, row, i, val);
                row++;
            }
        }
    }

    for(int i=1; i<325; i++) {
        node* p = this+i;
        for(p; p->down != nullptr; p = p->down);
        p->down = this+i;
        (this+i)->up = p;
    }
}

// Chooses the column header with the lowest number of nodes connected to it
node* node::choose_col() {
    node* p = right;
    node* lowest = right;   
    for(p; p != this; p = p->right)
        if(p->size < lowest->size)
            lowest = p;

    return lowest;
}

void node::cover() {
    right->left = left;
    left->right = right;

    node* p = down;
    for(p; p != this; p = p->down) {
        node* q = p->right;
        for(q; q != p; q = q->right) {
            (q->down)->up = q->up;
            (q->up)->down = q->down;
            (q->header)->size--;
        }
    }
}

void node::uncover() {
    node* p = up;
    for(p; p != this; p = p->up) {
        node* q = p->left;
        for(q; q != p; q = q->left) {
            (q->header)->size++;
            (q->down)->up = q;
            (q->up)->down = q;
        }
    }

    right->left = this;
    left->right = this;
}

void print_solution(int** solution) {
    int sudoku[9][9];
    for(int i=0; i<81; i++) {
        sudoku[solution[i][0]][solution[i][1]] = solution[i][2];
    }

    for(int i=0; i<9; i++) {
        if(i%3 == 0 && i != 0) {
            cout << "|-------+-------+-------|\n";
        }
        cout << "| ";
        for(int j=0; j<9; j++) {
            cout << sudoku[i][j] << " ";
            if((j+1)%3 == 0)
                cout << "| ";
        }
        cout << endl;
    }
    cout << endl << endl;
}

void node::dlx(node** matrix, int** solution, int i, int depth) {
    if(right == this) {
        print_solution(solution);
        return;
    }

    node* c = choose_col();
    c->cover();

    node* p = c->down;
    for(p; p != c; p = p->down) {
        solution[i] = p->coords;
        i++;

        node* q = p->right;
        for(q; q != p; q = q->right)
            (q->header)->cover();

        dlx(matrix, solution, i, depth+1);

        i--;
        q = p->left;
        for(q; q != p; q = q->left)
            (q->header)->uncover();
    }

    c->uncover();
}

