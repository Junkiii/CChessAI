// Hendrik Junkawitsch

/**
 * This file introduces a straightforward singly linked list that 
 * efficiently links moves together to create a final move list.
 */

#pragma once

#include <stdio.h>
#include <assert.h>
#include "typedefs.h"

#include "move.h"

/* 
 * Linked List Node
 * ----------------
 * move: pointer to move
 * next: pointer to next node element in list
 *  - if next is NULL this node is the end of the list
 */
typedef struct node {
    Move *move;
    Node *next;
} Node;

/**
 * Function: movelist_add
 * ----------------------
 * Generates a node structure with the provided move and adds the node 
 * to the beginning of the list. Returns the newly created node.
 *
 * NOTE: If the given node pointer is NULL, a new linked list is created, 
 * and the node is returned.
 */
Node *movelist_add(Node *node, const Move *move);

/**
 * Function: movelist_destroy
 * --------------------------
 * Deallocates the linked list starting from the provided node. 
 * It also frees all move structures contained within the list.
 */
void movelist_destroy(Node *node);

/**
 * Function: movelist_print
 * ------------------------
 * Prints the entire move list starting from the provided node.
 * Please note that this function only prints 256 nodes.
 */
void movelist_print(const Node *node);