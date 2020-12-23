#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


typedef struct Person
{
    char* name;
    int id;
}person_t;


typedef struct List
{

    int i;
    struct List* root;
    struct List* parent;
    struct List* left;
    struct List* right;

    int balanceFactor;
}list_t;

list_t* newList();

person_t* newPerson();

void addList(list_t* list, int value);

list_t* getItem(list_t* list, int id);

list_t* getCenterRight(list_t* root);

list_t* balancingRightList(list_t* root);

list_t* balancingLeftList(list_t* root);

void showListLeft(list_t* root);

void showListRight(list_t* root);




