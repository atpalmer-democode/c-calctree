#include <stdio.h>
#include <stdlib.h>

enum node_type {
    VALUE_NODE,
    OP_NODE,
};

enum op {
    ADD,
    SUB,
    MULT,
    DIV,
};

struct node {
    enum node_type type;
    union {
        double value;
        int op;
    } data;
    struct node *left;
    struct node *right;
};

struct node *node_new_value(double value) {
    struct node *new = malloc(sizeof *new);
    new->type = VALUE_NODE;
    new->data.value = value;
    new->left = NULL;
    new->right = NULL;
    return new;
}

struct node *node_new_op(enum op op, struct node *l, struct node *r) {
    struct node *new = malloc(sizeof *new);
    new->type = OP_NODE;
    new->data.op = op;
    new->left = l;
    new->right = r;
    return new;
}

void node_free(struct node *this) {
    if(!this)
        return;
    node_free(this->left);
    node_free(this->right);
    free(this);
}

double _value_node_value(struct node *this) {
    return this->data.value;
}

double _op_node_value(struct node *this) {
    switch(this->data.op) {
        /* TODO */
        default:
            return 0;
    }
}

double node_value(struct node *this) {
    switch(this->type) {
        case VALUE_NODE:
            return _value_node_value(this);
        case OP_NODE:
            return _op_node_value(this);
    }
}

int main(void) {
    struct node *calc = node_new_value(5);
    double val = node_value(calc);
    printf("Value: %f\n", val);
    node_free(calc);
}
