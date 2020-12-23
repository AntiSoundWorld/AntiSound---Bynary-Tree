#include "Test.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main()
{
    list_t* root = newList();

    int i = 0;

    while(i != 20)
    {
        addList(root, i);

        i++;
    }

    root = balancingRightList(root);
    balancingLeftList(root);

    //balancingLeftList(root);

}

void addList(list_t* root, int value)
{
    if(root->i == -1)
    {
        root->i = value;
        root->parent = root;
        return;
    }

    list_t* pointer = getItem(root, value);

    if(value < pointer->i)
    {
        pointer->left = newList();
        pointer->left->i = value;
        pointer->left->parent = pointer;

        pointer->left->left = NULL;
        pointer->left->right = NULL;

        pointer->balanceFactor = -1;

        //printf("left [%d]\n", value);
    }

    if(value > pointer->i)
    {
        pointer->right = newList();
        pointer->right->i = value;
        pointer->right->parent = pointer;
        
        pointer->right->left = NULL;
        pointer->right->right = NULL;

        pointer->balanceFactor = +1;

        //printf("right [%d]\n", value);
    }
}


list_t* getItem(list_t* root, int id)
{
    list_t* pointer = root;

    while (true)
    {
        if(id == pointer->i)
        {
            return pointer;
        }

        if(id < pointer->i)
        {
            if(pointer->left == NULL)
            {
                return pointer;
            }

            pointer = pointer->left;
        }

        if(id > pointer->i)
        {
            if(pointer->right == NULL)
            {
                return pointer;
            }
            pointer = pointer->right;
        }
        
    }
    
    return pointer;
}

list_t* getCenterRight(list_t* root)
{
    list_t* pointer = root;

    int i = 0;
    while (pointer != NULL)
    {
        pointer = pointer->right;
        i++;
    }
    
    if(i % 2 != 0)
    {
        i = i - 1;

        if(i == 2)
        {
            return NULL;
        }
    }

    pointer = root;

    int j = 0;

    while (j != i / 2 + 1)
    {
        pointer = pointer->right;
        j++;
    }
    
    //printf("pointer [%d]\n", pointer->i);

    return pointer;
}

list_t* getCenterLeft(list_t* root)
{
    list_t* pointer = root;

    int i = 0;
    while (pointer->left != NULL)
    {
        pointer = pointer->left;
        i++;
    }
    
    if(i % 2 != 0)
    {
        i = i - 1;
        if(i == 2)
        {
            return NULL;
        }
    }

    int j = 0;

    while (j != i / 2 + 1)
    {
        pointer = pointer->parent;
        j++;
    }
    
    //printf("pointer [%d]\n", pointer->i);

    return pointer;
}

list_t* newList()
{
    list_t* list = malloc(sizeof(list_t));
    list->i = -1;
    list->parent = NULL;
    list->left = NULL;
    list->right = NULL;
    list->balanceFactor = 0;

    return list;
}


person_t* newPerson()
{
    person_t* person = malloc(sizeof(person_t));
    person->id = -1;
    person->name = NULL;

    return person;
}

list_t* balancingRightList(list_t* root)
{
    list_t* center = getCenterRight(root);

    if(center == NULL)
    {
        printf("\n[Right list balanced]\n\n");
        return root;
    }
    else
    {
        printf("right list balancing......\n");
    }
    

    list_t* pointer = center;

    while (pointer != root)
    {
        pointer->left = pointer->parent;

        pointer = pointer->left;
    }
    
    while (pointer != center)
    {
        pointer->parent = pointer->right;

        pointer->right = NULL;

        pointer = pointer->parent;
    }

    center->parent = root;
    root->right = center;

    balancingRightList(center);
    return pointer;
}

void showListLeft(list_t* root)
{
    list_t* pointer = root;
    
    while (pointer != NULL)
    {
        //printf("[%d]\n", pointer->parent->i);
        printf("%d\n", pointer->i);
        printf("---------------------\n");

        pointer = pointer->left;
    }
}

void showListRight(list_t* root)
{
    list_t* pointer = root;
    
    while (pointer != NULL)
    {
        //printf("[%d]\n", pointer->parent->i);
        printf("%d\n", pointer->i);
        printf("---------------------\n");

        pointer = pointer->right;
    }
}

list_t* balancingLeftList(list_t* root)
{
    list_t* center = getCenterLeft(root);


    if(center == NULL)
    {
        printf("\n[Left List balanced]\n\n");
        return root;
    }
    else
    {
        printf("left list balancing......\n");
    }
    

    list_t* pointer = center;

    while (pointer != root)
    {
        pointer->right = pointer->parent;

        pointer = pointer->right;
    }
    
    while (pointer != center)
    {
        pointer->parent = pointer->left;

        pointer->left = NULL;

        pointer = pointer->parent;
    }

    center->parent = root;
    root->left = center;

    balancingLeftList(center);
    return pointer;
}