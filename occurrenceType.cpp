/* CS 210 Assignment 7
Shicheng Ai #200356891
*/

#include "occurrenceType.h"
#include "indexType.h"
#include "main.h"

void AddOccurrence(NODE* p, int page, int pos)
{
    p->data.occurrences[p->data.occNum].page = page;
    p->data.occurrences[p->data.occNum].position = pos;
    p->data.occNum++;
}

