/* CS 210 Assignment 7
Shicheng Ai #200356891
*/

#ifndef MAIN_H
#define MAIN_H

#include "indexType.h"

typedef struct treeNode
{
    index data;
    treeNode* left;
    treeNode* right;
    int distance;   //the distance to the left edge of the screen. It's used in printing the tree.
    int height;

    treeNode ()
    {
        left = NULL;
        right = NULL;
        //height = 0;
    }
} NODE;

void DataIn(int i);
void Filter(char* c);
void AddOccurrence(NODE* p, int page, int pos);
int Max(int a, int b);
int Height(NODE* p);
NODE* LL(NODE* p);
NODE* RR(NODE* p);
NODE* LR(NODE* p);
NODE* RL(NODE* p);
NODE* Insert(NODE* p, string budderS, int page, int pos);
//void NewLeftChild(NODE* p,string bufferS, int page, int pos);
//void NewRightChild(NODE* p,string bufferS, int page, int pos);

void WithOcc(NODE* p);
void FirstOcc(NODE* p);
void PreOrder(NODE* p);
void InOrder(NODE* p);
void PreOrder(NODE* p, string s);
void PostOrder(NODE* p);
void Search(NODE* p);

NODE* DeQueue();
void EnQueue(NODE* P);
int IsEmpty();
void PrintTree(NODE* p);


#endif // MAIN_H

