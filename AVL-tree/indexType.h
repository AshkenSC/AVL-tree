/* CS 210 Assignment 7
Shicheng Ai #200356891
*/

#ifndef INDEXTYPE_H_INCLUDED
#define INDEXTYPE_H_INCLUDED

#include <string>
#include "occurrenceType.h"


using namespace std;

typedef struct indexType
{
    string word;
    occ occurrences[500];
    int occNum = 0;//It's used to record the number of occurrences
} index;


#endif // INDEXTYPE_H_INCLUDED
