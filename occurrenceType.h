/* CS 210 Assignment 7
Shicheng Ai #200356891
*/

#ifndef OCCURRENCE_TYPE_H
#define OCCURRENCE_TYPE_H

typedef struct occurrenceType
{
    int page;
    int position;
    //int cntr;

    occurrenceType()
    {
        page=0;
        position=0;
    }
} occ;

#endif // OCCURRENCE_TYPE_H

