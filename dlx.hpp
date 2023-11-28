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
    
    public:
        node() {
            up = nullptr;
            down = nullptr;
            right = nullptr;
            left = nullptr;
            header = nullptr;
            is_header = false;
            size = -1;
        }

        void init_colheaders() {
            for(int i=0; i<325; i++) {
                (this+i)->right = this+((i+1)%325);
                (this+i)->left = this+(i-1 >= 0? i-1 : 324);
                this->is_header = true;
                this->size = 0;
            }
        }

        void init_nodes(node* root) {

        }
};