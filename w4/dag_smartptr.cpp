#include <memory>
#include <vector>

struct node {
    const char *value;
    // each node can have multiple outgoing edges
    // a node 'owns' the nodes it points to
    // because a single node can have multiple nodes pointing to it, this ownership is shared
    
    std::vector<std::shared_ptr<node>> edges_to;

    // so that's a vector of pointers to nodes
    
    // constructor
    
    node(const char *v) {
        value = v;
    }

    // add an outgoing edge (with destination)
    
    void add_edge_to(std::shared_ptr<node> n) {
        edges_to.push_back(n);
    }

    // no deconstructor needed - because each node will be created in a shared_ptr and that will destroy itself?
    
};

typedef struct node node;

std::shared_ptr<node> create_diamond() {
    std::shared_ptr<node> a = std::make_shared<node>("a");  // recall that this invokes the constructor, wraps in a ptr

    a->add_edge_to(std::make_shared<node>("b"));
    a->add_edge_to(std::make_shared<node>("c"));

    std::shared_ptr<node> d = std::make_shared<node>("d");

    a->edges_to[0]->add_edge_to(d);
    a->edges_to[1]->add_edge_to(d);

    return a;

}

// creates a diamon-shaped DAG and returns a pointer to the 'a' node
//
//
//
//                          a
//
//                      /       \
//
//
//                  /               \
//
//              b                       c
//
//                  \               /
//
//                      \       /
//
//                          d
//
//
//  like that i guess
//

int main() {

    create_diamond();

}
