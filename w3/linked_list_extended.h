struct node {
    char value;
    struct node * next;
};


struct node * create_node(char value);

void add_node_to_list(struct node* list, struct node* node);

void free_list(struct node* list);
