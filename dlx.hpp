

class node {
    node* up;
    node* down;
    node* right;
    node* left;
    node* header;
    bool is_header;
    int size;
    int coords[3];

    public:
        node(node* h) {
            right = h;
        }

        node() {
            up = nullptr;
            down = nullptr;
            right = nullptr;
            left = nullptr;
            header = nullptr;
            is_header = false;
            size = -1;
            value = -1;
        }

        friend node* convert(char puzzle[]) {
            int i=0;
            while(puzzle[i] != '\0') {
                cout << "line\n";
            } 
        }

        void dlx() {
            if right == this {
                // add to solution
            } 
            else {
                int c = choose_col();
                cover(c);
            }
        }
};