#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../AntiSound_Item/AntiSound_Item.h"
#include "../AntiSound_BinaryTree/AntiSound_BinaryTree.h"

binaryTree_t* antiSound_binaryTree_initializeNode()
{
    binaryTree_t* node = malloc(sizeof(binaryTree_t));

    node->data  = NULL;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;

    return node;
}

binaryTree_t* antiSound_binaryTree_newNode(void* data)
{
    binaryTree_t* newNode = antiSound_binaryTree_initializeNode();
    newNode->data = data;

    return newNode;
}

bool antiSound_binaryTree_addNewNode(binaryTree_t* node, void* data)
{
    item_t* newData = data;

    binaryTree_t* getedNode = antiSound_binaryTree_getNode(node, newData->id);
    
    item_t* getedItem = getedNode->data;

    if(getedNode == node && getedNode->data == NULL)
    {
        getedNode->data = data;
        return;
    }

    if(newData->id < getedItem->id)
    {
        getedNode->left = antiSound_binaryTree_newNode(data);
        getedNode->left->parent = getedNode;
    }

    if(newData->id > getedItem->id)
    {
        getedNode->right = antiSound_binaryTree_newNode(data);
        getedNode->right->parent = getedNode;
    }

    return true;
}

binaryTree_t* antiSound_binaryTree_getNode(binaryTree_t* node, int id)
{
    if(node == NULL)
    {
        return NULL;
    }

    if(node->data == NULL)
    {
        return node;
    }

    item_t* item = node->data;

    if(item->id == id)
    {
        return node;
    }

    if(id < item->id && node->left != NULL)
    {
        node = antiSound_binaryTree_getNode(node->left, id);
    }

    if(id > item->id && node->right != NULL)
    {
        node = antiSound_binaryTree_getNode(node->right, id);
    }

    return node;
}

void* antiSound_binaryTree_getData(binaryTree_t* node, int id)
{
    binaryTree_t* getedNode = antiSound_binaryTree_getNode(node, id);

    return getedNode->data;
}

int antiSound_binaryTree_height(binaryTree_t* node)
{
    if(node == NULL)
    {
        return -1;
    }

    return 1 + antiSound_binaryTree_max(antiSound_binaryTree_height(node->left), antiSound_binaryTree_height(node->right));
}

bool antiSound_binaryTree_isBalanced(binaryTree_t* node)
{
    if(node == NULL)
    {
        return true;
    }

    if(abs((antiSound_binaryTree_height(node->left)) - (antiSound_binaryTree_height(node->right))) <= 1 && antiSound_binaryTree_isBalanced(node->left) && antiSound_binaryTree_isBalanced(node->right))
    {
        return true;
    }
    
    return false;
}

bool antiSound_binaryTree_balancingSubNodes(binaryTree_t* node)
{
    if(node == NULL)
    {
        return true;
    }
      
    antiSound_binaryTree_balancingSubNodes(node->left);
    antiSound_binaryTree_balancingSubNodes(node->right);
   
    node->left = balancingNode(node->left);
    node->right = balancingNode(node->right);

    return true;
}

binaryTree_t* antiSound_binaryTree_turnRightToLeft(binaryTree_t* root)
{
    binaryTree_t* oldRoot = root;
    binaryTree_t* newRoot = oldRoot->right;

    if(oldRoot->parent != NULL)
    {
        newRoot->parent = oldRoot->parent;
    }
    else
    {
        newRoot->parent = NULL;
    }

    oldRoot->parent = newRoot;
    oldRoot->right = newRoot->left;
    newRoot->left = oldRoot;

    return newRoot;
}

binaryTree_t* antiSound_binaryTree_turnLeftToRight(binaryTree_t* root)
{
    binaryTree_t* oldRoot = root;
    binaryTree_t* newRoot = oldRoot->left;
    
    if(oldRoot->parent != NULL)
    {
        newRoot->parent = oldRoot->parent;
    }
    else
    {
        newRoot->parent = NULL;
    }

    oldRoot->parent = newRoot;
    oldRoot->left = newRoot->right;
    newRoot->right = oldRoot;

    return newRoot;
}

binaryTree_t* balancingNode(binaryTree_t* node)
{
    if(antiSound_binaryTree_isBalanced(node) == false)
    {
        int rightHeight = antiSound_binaryTree_height(node->right);
        int leftHeight = antiSound_binaryTree_height(node->left);

        int subLeftHeight = antiSound_binaryTree_height(node->right->left);

        if(rightHeight > leftHeight && subLeftHeight == -1)
        {
            node = antiSound_binaryTree_turnRightToLeft(node);
        }

        if(rightHeight > leftHeight && subLeftHeight != -1)
        {
            node->right = antiSound_binaryTree_turnLeftToRight(node->right);
            node = antiSound_binaryTree_turnRightToLeft(node);
            antiSound_binaryTree_balancingSubNodes(node);
        }

        int subRightHeight = antiSound_binaryTree_height(node->left->right);

        if(leftHeight > rightHeight && subRightHeight == -1)
        {
            node = antiSound_binaryTree_turnLeftToRight(node);
        }

        if(leftHeight > rightHeight && subRightHeight != -1)
        {
            node->right = antiSound_binaryTree_turnRightToLeft(node->right);
            node = antiSound_binaryTree_turnLeftToRight(node);
            antiSound_binaryTree_balancingSubNodes(node);
        }
    }
    
    return node;
}

bool antiSound_binaryTree_removeNode(binaryTree_t* node, int id)
{
    binaryTree_t* removeNode = antiSound_binaryTree_getNode(node, id);

    if(removeNode->parent == NULL)
    {
        return antiSound_binaryTree_removeRoot(removeNode);
    }

    if(removeNode->parent->left == removeNode)
    {
        return antiSound_binaryTree_removeParentLeftNode(removeNode);
    }

    if(removeNode->parent->right == removeNode)
    {
        return antiSound_binaryTree_removeParentRightNode(removeNode);
    }

    return false;
}

binaryTree_t* antiSound_binaryTree_getCloseMaxRightValue(binaryTree_t* node)
{
    if(node == NULL)
    {
        return NULL;
    }

    if(node->right != NULL)
    {
        node = antiSound_binaryTree_getCloseMaxRightValue(node->right);
    }

    return node;
}

binaryTree_t* antiSound_binaryTree_getCloseMaxLeftValue(binaryTree_t* node)
{
    if(node == NULL)
    {
        return NULL;
    }

    if(node->left != NULL)
    {
       node = antiSound_binaryTree_getCloseMaxLeftValue(node->left);
    }

    return node;
}

binaryTree_t* antiSound_binaryTree_getNewNode(binaryTree_t* node)
{
    if(node == NULL)
    {
        return NULL;
    }

    binaryTree_t* newNode = NULL;

    if(node->parent == NULL)
    {
        if(node->right != NULL)
        {
            newNode = antiSound_binaryTree_getNodeRightSide(node);
        }
        else
        {
            newNode = antiSound_binaryTree_getNodeLeftSide(node);
        }

        return newNode;
    }

    if(node->parent->right == node)
    {
        newNode = antiSound_binaryTree_getNodeRightSide(node);
    }

    if(node->parent->left == node)
    {
        newNode = antiSound_binaryTree_getNodeLeftSide(node);
    }

    newNode->parent = node->parent;

    return newNode;
}

int antiSound_binaryTree_max(int a, int b)
{
    if(a > b)
    {
        return a;
    }
   
    return b;
}

bool antiSound_binaryTree_removeParentLeftNode(binaryTree_t* node)
{
    int leftHeight = antiSound_binaryTree_height(node->left);
    int rightHeight = antiSound_binaryTree_height(node->right);

    if(leftHeight == -1 && rightHeight == -1)
    {
        node->parent->left = NULL;
        free(node);
        return true;
    }

    if(leftHeight != -1 && rightHeight != -1)
    {
        node->parent->left = antiSound_binaryTree_getNewNode(node);
        free(node);
        return true;
    }
    
    if(leftHeight != -1 && rightHeight == -1)
    {   
        node->parent->left = node->left;
        free(node);
        return true;
    }

    if(leftHeight == -1 && rightHeight != -1)
    {   
        node->parent->left = node->right;
        free(node);
        return true;
    }

    return false;
}

bool antiSound_binaryTree_removeParentRightNode(binaryTree_t* node)
{
    int leftHeight = antiSound_binaryTree_height(node->left);
    int rightHeight = antiSound_binaryTree_height(node->right);

    if(leftHeight == -1 && rightHeight == -1)
    {
        node->parent->right = NULL;
        free(node);
        return true;
    }

    if(leftHeight != -1 && rightHeight != -1)
    {
        node->parent->right = antiSound_binaryTree_getNewNode(node);
        free(node);
        return true;
    }

    if(rightHeight != -1 && leftHeight == -1)
    {   
        node->parent->right = node->right;
        free(node);
        return true;
    }

    if(rightHeight == -1 && leftHeight != -1)
    {   
        node->parent->right = node->left;
        free(node);
        return true;
    }

    return false; 
}

bool antiSound_binaryTree_removeRoot(binaryTree_t* node)
{
    int leftHeight = antiSound_binaryTree_height(node->left);
    int rightHeight = antiSound_binaryTree_height(node->right);

    if(leftHeight == -1 && rightHeight == -1)
    {
        node->data = NULL;
        free(node);
        return true;
    }

    binaryTree_t* newNode = antiSound_binaryTree_getNewNode(node);

    node->data = newNode->data;
    
    free(newNode);

    return true;
}

binaryTree_t* antiSound_binaryTree_getNodeRightSide(binaryTree_t* node)
{
    binaryTree_t* newNode = antiSound_binaryTree_getCloseMaxLeftValue(node->right);

    if(newNode->right != NULL)
    {
        newNode->parent->left = newNode->right; 
    }
    else
    {
        newNode->parent->left = NULL;
    }

    return newNode;
}

binaryTree_t* antiSound_binaryTree_getNodeLeftSide(binaryTree_t* node)
{
    binaryTree_t* newNode = antiSound_binaryTree_getCloseMaxRightValue(node->left);

    if(newNode->left != NULL)
    {
        newNode->parent->right = newNode->left;
    }
    else
    {
        newNode->parent->right = NULL;
    }

    return newNode;
}
