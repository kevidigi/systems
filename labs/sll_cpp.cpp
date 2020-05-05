#include <memory>
#include <vector>

// this isn't working yet!

struct node {

    std::vector<float> values;
    std::unique_ptr<struct node> next;          // the member types are smart pointers

    node(std::vector<float> vals, std::unique_ptr<struct node> nxt) {       // and in the constructor, the types have to be the same smart pointers
        next = std::move(nxt);                                              // in the case of unique_ptr, we have to move ownership to the member variable
        values = vals;
    }
    
};

typedef struct node node;

void add_to_node(std::unique_ptr<node> n, float f, int nth) {
    if (nth == 0) {
        n->values.push_back(f);
    }
    else {
        add_to_node(n->next, f, nth-1);
    }
}

int main(){

/*
    node a(std::vector<float>{1, 2, 3}, NULL);
    node b(std::vector<float>{1, 2, 3}, NULL);
    node c(std::vector<float>{3, 5, 4}, NULL);
*/
  
    // using make_unique (calls constructor, wraps in unique_ptr... right?)
    
    std::unique_ptr<node> a = 
        std::make_unique<node>(std::vector<float>{1, 3, 2},
            std::make_unique<node>(std::vector<float>{2, 4, 3},
                std::make_unique<node>(std::vector<float>{3, 5, 4}, NULL)));

    add_to_node(a.get(), 2, 2);

}
