#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

typedef struct censusData
{
    long key;       //Store original key value
    string content; //Store data
    int hashVal;    //Store hashed value

    censusData()
    //Constructor, in order to set default key value to 0
    {
        key = 0;
    }
} data;

data table[107];    //Hash table
data temp[100];     //Temporarily store data here
int hashed;         //used to store hashed address

/* variables for statistics */
int homeBeforeFirst = 0;
int homeNoCollision = 0;
int homeWithCollision = 0;
int CRnoCollision = 0;
int CRwithCollision = 0;
int probeNum = 0;

int collisionMark = 0;
int collisionMarkCR = 0;
/* variables end */

void LinearProbing();
int HashFunction(int, long);
int CRFunction(int, int);

int main()
{
    fstream fin("censusdata.txt");



    /* variables for program */
    int hashAlgoNum;    //used to store user's choice of hash algorithm
    int CRalgoNum;      //used to store user's choice of CR algorithm
    /* variables end */


    /* Data Input */
    string tempString;  //Temporarily store string
    int i = 0;
    while(getline(fin,tempString))
    //Data temporarily stored in temp[]
    {
        temp[i].content = tempString;
        temp[i].key = atoi(temp[i].content.c_str());
        i++;
    }

    /* User's choice */
    while(1)
    {
        cout << "Please select a hash algorithm:" << endl
        << "1. Modulo 107" << endl
        << "2. Digit Extraction" << endl
        << "3. Mid Square  " << endl
        << "4. Fold Shift" << endl
        << "5. Fold Boundary" << endl
        << "6. Pseudorandom" << endl;
        scanf("%d", &hashAlgoNum);
        if (hashAlgoNum != 1 && hashAlgoNum != 2 && hashAlgoNum != 3
        && hashAlgoNum != 4 && hashAlgoNum != 5 && hashAlgoNum != 6)
        {
            cout << "Invalid input!" << endl << endl;
            continue;
        }
        else
        {
            break;
        }
    }

    while(1)
    {
        cout << "Please select a CR algorithm:" << endl;
        cout << "1. Linear probing" << endl;
        cout << "2. Alternating linear probing" << endl;
        cout << "3. Quadratic" << endl;
        cout << "4. Pseudorandom" << endl;
        cout << "5. Key offset" << endl;
        scanf("%d", &CRalgoNum);
        if(CRalgoNum != 1 && CRalgoNum != 2 && CRalgoNum != 3
        && CRalgoNum != 4 && CRalgoNum != 5 && CRalgoNum != 6)
        {
            cout << "Invalid input!" << endl << endl;
            continue;
        }
        else
        {
            break;
        }
    }


    /* Get Hash Value */
    for(i = 0; i < 100; i++)
    {
        //temp[i].hashVal = temp[i].key % 107;
        temp[i].hashVal = HashFunction(1, temp[i].key);
    }
    //Add data from temp[] to hash table
    //Hash algorithm: Modulo 107
    if (CRalgoNum == 1)
    //Linear Probing
    {

    for(i = 0; i < 100; i++)
    {
        hashed = temp[i].hashVal;

        if(table[hashed].key == 0)
        {
            table[hashed].key = temp[i].key;
            table[hashed].content = temp[i].content;
            /*Home Address First Collision */
            homeNoCollision++;
            if (collisionMark == 0)
            {
                /*2.Home Address No Collisions */
                homeBeforeFirst++;
            }

        }
        else
        {
            collisionMark = 1;      //First collision occurs, homeBeforeFirst stops counting
            collisionMarkCR = 0;    //Reset the collision mark in CR

            int probe = 0;
            int rightAdd = hashed;
            int leftAdd = hashed;

            /*3.Home Address Collision*/
            homeWithCollision++;
            while(1)
            {

                if(hashed > 106 || hashed == 106)
                //beyond the boundary, reset to 0
                {
                    hashed = 0;
                    continue;
                }

                hashed++;

                if(table[hashed].key == 0)
                {
                    if (collisionMarkCR == 0)
                    {
                        /*4.CR Address Inserts*/
                        CRnoCollision++;
                    }
                    else
                    {
                        /*5.CR Address Inserts Collisions*/
                        CRwithCollision++;
                    }
                    table[hashed].key = temp[i].key;
                    table[hashed].content = temp[i].content;
                    break;
                }
                else
                //After CR it still collides
                {
                    collisionMarkCR = 1;   //Collision in CR occurs
                }
            //if you put hashed++ here "else" statement above
            //will always be executed
            }
        }
    }
    }
    else if (CRalgoNum == 2)
    //Alternating linear probing
    {
    for(i = 0; i < 100; i++)
    {
        hashed = temp[i].hashVal;

        if(table[hashed].key == 0)
        {
            table[hashed].key = temp[i].key;
            table[hashed].content = temp[i].content;
            /*Home Address First Collision */
            homeNoCollision++;
            if (collisionMark == 0)
            {
                /*2.Home Address No Collisions */
                homeBeforeFirst++;
            }

        }
        else
        //Alternating Linear probing
        {
            collisionMark = 1;      //First collision occurs, homeBeforeFirst stops counting
            collisionMarkCR = 0;    //Reset the collision mark in CR

            int probe = 0;
            int rightAdd = hashed;
            int leftAdd = hashed;

            /*3.Home Address Collision*/
            homeWithCollision++;
            while(1)
            {

                if(hashed > 106 || hashed == 106)
                //beyond the boundary, reset to 0
                {
                    hashed = 0;
                    continue;
                }

                //Alternating linear probing
                /* Instead of simple hashed++ we use algorithm below */
                probe = 1 - probe;
                if(probe == 1)
                {
                    rightAdd++;
                    hashed = rightAdd % 107;
                }
                else
                {
                    leftAdd--;
                    if(leftAdd < 0)
                    {
                        leftAdd = 106;
                    }
                    hashed = leftAdd;
                }
                /* Instead of simple hashed++ we use algorithm above */

                if(table[hashed].key == 0)
                {
                    if (collisionMarkCR == 0)
                    {
                        /*4.CR Address Inserts*/
                        CRnoCollision++;
                    }
                    else
                    {
                        /*5.CR Address Inserts Collisions*/
                        CRwithCollision++;
                    }
                    table[hashed].key = temp[i].key;
                    table[hashed].content = temp[i].content;
                    break;
                }
                else
                //After CR it still collides
                {
                    collisionMarkCR = 1;   //Collision in CR occurs
                }
            }
        }
    }
    }

    /* Print hash table */
    for(i = 0; i < 107; i++)
    {
        if(table[i].key != 0)
        {
           cout << i << " " << table[i].key << " " << table[i].content << endl;
        }
        else
        {
            cout << i << " empty" << endl;
        }

    }

    /* Print statistics */
    cout << endl << "1. " << homeBeforeFirst << endl;
    cout << "2. " << homeNoCollision << endl;
    cout << "3. " << homeWithCollision << endl;
    cout << "4. " << CRnoCollision << endl;
    cout << "5. " << CRwithCollision << endl;

    return 0;
}

int HashFunction(int hashNum, long keyVal)
{
    int result;
    if(hashNum == 1)
    //1. Modulo 107
    {
        result = keyVal % 107;
    }
    else
    {
    /* Instead of simple hashed++ we use algorithm below */
        int probe = 0;
        int rightAdd = keyVal;
        int leftAdd = keyVal;
        probe = 1 - probe;
        if(probe == 1)
        {
            rightAdd++;
            result = rightAdd % 107;
        }
        else
        {
            leftAdd--;
            if(leftAdd < 0)
            {
                leftAdd = 106;
            }
            result = leftAdd;
        }
    /* Instead of simple hashed++ we use algorithm above */
    }
    return result;
}

int CRFunction(int CRnum, int hashVal)
{
    int result;

    if(CRnum == 1)
    //1. Linear probing
    {
        result =  hashVal + 1;
    }
    else if(CRnum == 2)
    //2. Alternating linear probing
    {
        /* Instead of simple hashed++ we use algorithm below */
        int probe = 0;
        int rightAdd = hashVal;
        int leftAdd = hashVal;

        probe = 1 - probe;
        if(probe == 1)
        {
            rightAdd++;
            result = rightAdd % 107;
        }
        else
        {
            leftAdd--;
            if(leftAdd < 0)
            {
                leftAdd = 106;
            }
            result = leftAdd;
        }
        /* Instead of simple hashed++ we use algorithm above */
    }
    return result;
}

void LinearProbing ()
{
    for(int i = 0; i < 100; i++)
    {
        hashed = temp[i].hashVal;

        if(table[hashed].key == 0)
        {
            table[hashed].key = temp[i].key;
            table[hashed].content = temp[i].content;
            /*Home Address First Collision */
            homeNoCollision++;
            if (collisionMark == 0)
            {
                /*2.Home Address No Collisions */
                homeBeforeFirst++;
            }

        }
        else
        //Alternating Linear probing
        {
            collisionMark = 1;      //First collision occurs, homeBeforeFirst stops counting
            collisionMarkCR = 0;    //Reset the collision mark in CR

            /*3.Home Address Collision*/
            homeWithCollision++;
            while(1)
            {

                if(hashed > 106 || hashed == 106)
                //beyond the boundary, reset to 0
                {
                    hashed = 0;
                    continue;
                }

                hashed = CRFunction(2,hashed);
                hashed++;

                if(table[hashed].key == 0)
                {
                    if (collisionMarkCR == 0)
                    {
                        /*4.CR Address Inserts*/
                        CRnoCollision++;
                    }
                    else
                    {
                        /*5.CR Address Inserts Collisions*/
                        CRwithCollision++;
                    }
                    table[hashed].key = temp[i].key;
                    table[hashed].content = temp[i].content;
                    break;
                }
                else
                //After CR it still collides
                {
                    collisionMarkCR = 1;   //Collision in CR occurs
                }
            //if you put hashed++ here "else" statement above
            //will always be executed
            }
        }
    }
}



//void linearProbing ()
//{
//            collisionMark = 1;      //First collision occurs, homeBeforeFirst stops counting
//            collisionMarkCR = 0;    //Reset the collision mark in CR
//
//            /*3.Home Address Collision*/
//            homeWithCollision++;
//            while(1)
//            {
//
//                if(hashed > 106 || hashed == 106)
//                //beyond the boundary, reset to 0
//                {
//                    hashed = 0;
//                    continue;
//                }
//                hashed++;
//                if(table[hashed].key == 0)
//                {
//                    if (collisionMarkCR == 0)
//                    {
//                        /*4.CR Address Inserts*/
//                        CRnoCollision++;
//                    }
//                    else
//                    {
//                        /*5.CR Address Inserts Collisions*/
//                        CRwithCollision++;
//                    }
//                    table[hashed].key = temp[i].key;
//                    table[hashed].content = temp[i].content;
//                    break;
//                }
//                else
//                //After CR it still collides
//                {
//                    collisionMarkCR = 1;   //Collision in CR occurs
//                }
//            //if you put hashed++ here "else" statement above
//            //will always be executed
//            }
//        }

