#ifndef ANTISOUND_BYNARYTREE_H
#define ANTISOUND_BYNARYTREE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Node
{
    void* data;

    struct Node* parent;
    struct Node* left;
    struct Node* right;

}binaryTree_t;

/*
 * initializes struct of Node
 * returns pointer to binaryTree_t
 */
binaryTree_t* antiSound_binaryTree_initializeNode();

/*
 * creats newNode with data
 * returns pointer to binaryTree_t
 */
binaryTree_t* antiSound_binaryTree_newNode(void* data);

/*
 * adds newNode to binary tree
 */
bool antiSound_binaryTree_addNewNode(binaryTree_t* node, void* data);

/*
 * finds request data by node
 * returns pointer to node
 */
binaryTree_t* antiSound_binaryTree_getNode(binaryTree_t* node, int id);

/*
 * returns request data by node
 */
void* antiSound_binaryTree_getData(binaryTree_t* node, int id);

/*
 * returns height of binaryTree
 */
int antiSound_binaryTree_height(binaryTree_t* node);

/*
 * checks balance of node
 * returns true in case if node balanced, otherwise returns false
 */
bool antiSound_binaryTree_isBalanced(binaryTree_t* node);

/*
 * definds new node and turns subnodes left to right
 * returns new node
 */
binaryTree_t* antiSound_binaryTree_turnLeftToRight(binaryTree_t* root);

/*
 * definds new node and turns subnodes right to left
 * returns new node
 */
binaryTree_t* antiSound_binaryTree_turnRightToLeft(binaryTree_t* root);

/*
 * finds imbalanced nodes and balances
 * return true in case balancing completed
 */
bool antiSound_binaryTree_balancingSubNodes(binaryTree_t* node);

/*
 * balances node
 * return balansed node
 */
binaryTree_t* balancingNode(binaryTree_t* node);


/*
 * remove node
 * return true in case if node deleted, otherwise returns false
 */
bool antiSound_binaryTree_removeNode(binaryTree_t* root, int id);

/*
 * returns the closest possible node by value on the left side of main root
 */
binaryTree_t* antiSound_binaryTree_getCloseMaxRightValue(binaryTree_t* node);

/*
 * returns the closest possible node by value on the right side of main root
 */
binaryTree_t* antiSound_binaryTree_getCloseMaxLeftValue(binaryTree_t* node);

/*
 * returns new node
 */
binaryTree_t* antiSound_binaryTree_getNewNode(binaryTree_t* node);

int antiSound_binaryTree_max(int a, int b);

/*
 * removes left sub-node of parent of node
 * returns true in case success, otherwise false
 */
bool antiSound_binaryTree_removeParentLeftNode(binaryTree_t* node);

/*
 * removes right sub-node of parent of node
 * returns true in case success, otherwise false
 */
bool antiSound_binaryTree_removeParentRightNode(binaryTree_t* node);

/*
 * removes root node
 * returns true in case success, otherwise false
 */
bool antiSound_binaryTree_removeRoot(binaryTree_t* node);

/*
 * establishes new connections between the parents of a new node right
 */
binaryTree_t* antiSound_binaryTree_getNodeRightSide(binaryTree_t* node);

/*
 * establishes new connections between the parents of a new node right
 */
binaryTree_t* antiSound_binaryTree_getNodeLeftSide(binaryTree_t* node);

//=============================================================================================================

bool antiSound_binaryTree_testInitializeNode();

bool antiSound_bynaryTree_testGetNode(binaryTree_t* node, int id);

#endif // ANTISOUND_BYNARYTREE_H