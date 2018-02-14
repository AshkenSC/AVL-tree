/* CS 210 Assignment 7
Shicheng Ai #200356891
*/

#include "occurrenceType.h"
#include "indexType.h"
#include "main.h"

int Max (int a, int b)
{
    if(a > b)
        return a;
    else
        return b;
}

int Height (NODE* p)
{
    if(p == NULL)
        return -1;
    else
        //return p->height;
        return p->height;
}

NODE* LL(NODE* p)
{
    NODE* p1;

    p1 = p->left;
    p->left = p1->right;
    p1->right = p;

    p->height = Max(Height(p->left), Height(p->right))+1;
    p1->height = Max(Height(p1->left), Height(p1->right))+1;

    p = p1;
    return p;
}

NODE* RR(NODE* p)
{
    NODE* p1;

    p1 = p->right;
    p->right = p1->left;
    p1->left = p;

    p->height = Max(Height(p->left), Height(p->right))+1;
    p1->height = Max(Height(p1->left), Height(p1->right))+1;

    p = p1;
    return p1;
}

NODE* LR(NODE* p)
{
    p->left = RR(p->left);
    p = LL(p);
    return p;
}
NODE* RL(NODE* p)
{
    p->right = LL(p->right);
    p = RR(p);
    return p;
}

NODE* Insert(NODE* p, string bufferS, int page, int pos)
{
    //NODE* q;
    if(p == NULL)
    {
        p = new NODE;
        p->data.word = bufferS;
        p->data.occurrences[p->data.occNum].page = page;
        p->data.occurrences[p->data.occNum].position = pos;
        p->data.occNum++;
        //p = q;
        //return;
    }
    else if(bufferS < p->data.word)
    {
        p->left = Insert(p->left, bufferS, page, pos);

        if(Height(p->left)-Height(p->right) == 2)
        {
            if(bufferS < p->left->data.word)
                p = LL(p);
            else
                p = LR(p);
        }
    }
    else if(bufferS > p->data.word)
    {
        p->right = Insert(p->right, bufferS, page, pos);

        if(Height(p->right)-Height(p->left) == 2)
        {
            if(bufferS > p->right->data.word)
                p = RR(p);
            else
                p = RL(p);
        }
    }
    else if (bufferS == p->data.word)
    {
        AddOccurrence(p,page,pos);
    }

    p->height = Max(Height(p->left),Height(p->right)) + 1;
    return p;
}
