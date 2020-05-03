#include <memory>

struct node {

    const void *value_ptr;
    
    // the parent owns both children uniquely, so we use unique pointers
    
    std::unique_ptr<struct node> left_child;
    std::unique_ptr<struct node> right_child;

    // each child knows its parent, but doesn't own it
    // therefore we use regular pointers
    
    struct node *parent;

    // constructor...
    
    node(const void *value_ptr_) {
        value_ptr = value_ptr_;
        left_child = NULL;
        right_child = NULL;
        parent = NULL;
    }

    // left_child and right_child destructors are called automatically?
    
    ~node() {   }

    void add_left_child(const void *value_ptr) {
     
        // make_unique allocates memory for a node on the heap, and calls the node-constructor
        // i.e. you pass a <dtype> and any (arguments) and it calls the constructor, returns a unique_ptr to it

        left_child = std::make_unique<struct node>(value_ptr);
    
    }

    void add_right_child(const void *value_ptr) {
        right_child = std::make_unique<struct node>(value_ptr);
    }

};

int main() {

    int i = 69;
    int *i_ptr = &i;
    struct node root(i_ptr);

}
