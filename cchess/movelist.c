// Hendrik Junkawitsch

#include "movelist.h"

Node *movelist_add(Node *node, const Move *move) {
    Node *new_node = (Node *) malloc(sizeof(Node));
    assert(new_node != NULL);
    new_node->move = (Move *) move;
    new_node->next = node;
    return new_node;
}

void movelist_destroy(Node *node) {
    do {
        Node *next = node->next;
        move_destroy(node->move);
        assert(node != NULL);
        free(node);
        node = next;
    } while (node != NULL);
}

void movelist_print(const Node *node) {
    if (node == NULL) {
        printf("\nNO LEGAL MOVES\n");
        return;
    }
    printf("\nLEGAL MOVES: ");
    U8 amount = 0;
    do {
        amount++;
        Node *next = node->next;
        move_print(node->move);
        printf(" ");
        node = next;
    } while (node != NULL);
    printf("(total: %d)\n\n", amount);
}