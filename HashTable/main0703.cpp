#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "rng.h"

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

int main()
{
    fstream fin("censusdata.txt");



    /* variables for program */
    int hashAlgoNum;    //used to store user's choice of hash algorithm
    int CRalgoNum;      //used to store user's choice of CR algorithm
    int probeCount;     //If it's greater than 10, switch to linear probing
    char againCheck;
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

    /* Menu */
    start: while(1)
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
        temp[i].hashVal = HashFunction(hashAlgoNum, temp[i].key);
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

                hashed = (hashed+1) % 107;

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
    else if (CRalgoNum == 3)
    //Quadratic probing
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
        //Quadratic probing
        {
            collisionMark = 1;      //First collision occurs, homeBeforeFirst stops counting
            collisionMarkCR = 0;    //Reset the collision mark in CR

            int probe = 0;

            /*3.Home Address Collision*/
            homeWithCollision++;
            while(1)
            {
            //Quadratic probing

                probe++;
                hashed = (hashed + (probe * probe)) % 107;

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
    else if (CRalgoNum == 4)
    //Pseudorandom
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
        //Pseudorandom
        {
            collisionMark = 1;      //First collision occurs, homeBeforeFirst stops counting
            collisionMarkCR = 0;    //Reset the collision mark in CR

            RandomKey rng1(hashed);

            /*3.Home Address Collision*/
            homeWithCollision++;
            while(1)
            {
            //Pseudorandom
            hashed = rng1.GenerateNextRandomKey() % 107;

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
    else if (CRalgoNum == 5)
    //Key offset
    {
    for(i = 0; i < 100; i++)
    {
        hashed = temp[i].hashVal;
        probeCount = 0;

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
        //Key offset
        {
            collisionMark = 1;      //First collision occurs, homeBeforeFirst stops counting
            collisionMarkCR = 0;    //Reset the collision mark in CR

            int offset = table[hashed].key / 107;

            /*3.Home Address Collision*/
            homeWithCollision++;
            while(1)
            {
                //Key offset
                hashed = (hashed + offset) % 107;

                if(probeCount > 10)
                //10 probes but still no result
                //go to linear probing
                {
                    while(1)
                    {
                        hashed = (hashed + 1) % 107;
                        if (table[hashed].key == 0)
                            break;
                    }
                }

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

                probeCount++;
            }
        }
    }
    }

    /* Print hash table */
//    for(i = 0; i < 107; i++)
//    {
//        if(table[i].key != 0)
//        {
//           cout << i << " " << table[i].key << " " << table[i].content << endl;
//        }
//        else
//        {
//            cout << i << " empty" << endl;
//        }
//
//    }

    /* Print statistics */
    cout << endl << "1. Home Address First Collision \t" << homeBeforeFirst << endl;
    cout << "2. Home Address No Collisions \t\t" << homeNoCollision << endl;
    cout << "3. Home Address Collision \t\t" << homeWithCollision << endl;
    cout << "4. CR Address Inserts \t\t\t" << CRnoCollision << endl;
    cout << "5. CR Address Inserts Collisions \t" << CRwithCollision << endl;


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
    else if(hashNum == 2)
    //2. Digit extraction, extract 2nd, 4th, 5th
    {
        int dig1, dig2, dig3, dig4, dig5, dig6;
        //digX stands for different digits in the key
        //key = dig1*100000 + dig2*10000 + dig3*1000 + dig4*100 + dig5*10 + dig6*1
        dig6 = keyVal % 10;
        dig5 = (keyVal % 100 - dig6) / 10;
        dig4 = (keyVal % 1000 - dig5 * 10 - dig6)  / 100;
        dig3 = (keyVal % 10000 - dig4 * 100 - dig5 * 10 - dig6) / 1000;
        dig2 = (keyVal % 100000 - dig3 * 1000 - dig4 * 100 - dig5 * 10 - dig6) / 10000;
        dig1 = keyVal / 100000;
        result = dig2 * 100 + dig4 * 10 + dig5 * 1;
        result = result % 107;
    }
    else if(hashNum == 3)
    //3. Midsquare
    {
        char square[20];    //use char[] to store key squared
        keyVal = keyVal * keyVal;
        itoa(keyVal, square, 20);
        result = square[1]*100 + square[2]*10 + square[3];
        result = result % 107;
    }
    else if(hashNum == 4)
    //4. Fold shift
    {
        int left, right;
        char foldChar[20];  //this is for storing the converted key
        itoa(keyVal, foldChar, 20);
        left = foldChar[0]*100 + foldChar[1]*10 + foldChar[2];
        right = foldChar[3]*100 + foldChar[4]*10 + foldChar[5];
        result = left + right;
        result = result % 107;
    }
    else if(hashNum == 5)
    //5. Fold boundary
    {
        int left, right;
        char foldChar[20];
        itoa(keyVal, foldChar, 20);
        left = foldChar[2]*100 + foldChar[1]*10 + foldChar[0];
        right = foldChar[5]*100 + foldChar[4]*10 + foldChar[3];
        result = left + right;
        result = result % 107;
    }
    else if(hashNum == 6)
    //6. Pseudorandom
    {
        RandomKey rng(keyVal);
        result = rng.GenerateNextRandomKey();
        result = result % 107;
    }

    return result;
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

