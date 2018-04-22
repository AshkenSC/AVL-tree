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
data temp[200];     //Temporarily store data here

int main()
{
    fstream fin("censusdata.txt");

    /* statistics */
    int homeBeforeFirst = 0;
    int homeNoCollision = 0;
    int homeWithCollision = 0;
    int CRnoCollision = 0;
    int CRwithCollision = 0;
    int probeNum = 0;

    int collisionMark = 0;
    int collisionMarkCR = 0;
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

    //Print data in the temp[] array (not in hash table yet)
//    for(i = 0; i < 200; i++)
//    {
//        if(temp[i].key == 0)
//            break;
//        cout << i << " " << temp[i].key << "\t" << temp[i].content << endl;
//    }

    /* Get Hash Value */
    for(i = 0; i < 200; i++)
    {
        temp[i].hashVal = temp[i].key % 107;
    }
    //Add data from temp[] to hash table
    //Hash algorithm: Modulo 107
    for(i = 0; i < 100; i++)
    {
        int hashed = temp[i].hashVal;

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
                //hashed++;

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
            //if you put hashed++ here "else" statement above
            //will always be executed
            }
        }
    }


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

    cout << endl << "1. " << homeBeforeFirst << endl;
    cout << "2. " << homeNoCollision << endl;
    cout << "3. " << homeWithCollision << endl;
    cout << "4. " << CRnoCollision << endl;
    cout << "5. " << CRwithCollision << endl;

    return 0;
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

