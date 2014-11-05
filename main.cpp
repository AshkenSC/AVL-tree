/* CS 210 Assignment 7
Shicheng Ai #200356891
*/

#include <iostream>
#include <fstream>
#include "main.h"

using namespace std;

int foundMark = 0;  //If Search() finds a matched item, it will be set to 1.
int distNum = 1;    //It's used in InOrder() to store the distance between nodes and the left edge.
string st1 = "D:\\data\\";
string st2;     //The two strings are for file destination.
char tempf[10];
char buffer[256];   //The two char arrays are used to temporarily store strings from the file.
string bufferS; //convert from char to string

//A queue for printing the tree.
NODE* nodeQueue[1024];
int head = 0;
int tail = 0;

//A frequently used pointer variable
NODE * p;

//Initialize page and position counter
int page = 1;
int pos = 1;
fstream fin[20];

int main()
{
    for (int i=0; i<=19; i++)   //Different i stands for different pages
        DataIn(i);

    //Print each word the first time it appears.
    cout<<"1. Print each word the first time it is encountered."<<endl;
    FirstOcc(p);

    //Print the index without occurrences in AVL tree format.
    cout<<endl<<"2. Print the index without occurrences in AVL tree format."<<endl;
    InOrder(p); //Traverse the tree using InOrder method for calculating the spaces we need for every node
    PrintTree(p);


    //Print the index with the occurrences.
    cout<<endl<<endl<<"3. Print the index with the occurrences."<<endl;
    WithOcc(p);

    //Search for keywords.
    Search(p);

    return 0;
}

void DataIn(int i)
//Input data from files
{

 for (int i=0; i<=19; i++)   //Different i stands for different pages
    {
        sprintf(tempf,"%d",i+1);
        st2 = tempf;
        fin[i].open(st1+st2,ios::in);
        while(!fin[i].eof())    //When fin[i] reaches eof the page ends
        {
            fin[i].getline(buffer,256,' '); //data input
            Filter(buffer);
            bufferS=buffer; //convert char* to string

                //Traverse the tree, if the entry does not exist, add a node
                //If the entry exists, add element to occurrence[]

                if (page==1 && pos==1)
                //If it's the first word, build a root;
                {
                    p = new NODE;
                    p->data.word = bufferS;
                    p->height = 0;
                }

                p = Insert(p, bufferS, page, pos);

            pos++;
        }
        page++;
    }
}

void Filter(char *c)
//This function is for converting capitals to lower cases and filter symbols
{
    while (*c != '\0')
    {
        if (*c>='A' && *c<='Z')
            *c = *c + 32;
        c++;
        if (*c == '.' || *c == ';' || *c == ',' || *c == ':')
            *c = '\0';
    }
}

void WithOcc(NODE* p)
//Print index and occurrences
{
    int i=0;
    if (p == NULL)
        return;

    WithOcc(p->left);

        cout<<p->data.word<<": ";
    while (p->data.occurrences[i].page != 0)
    {
        {
            cout<<"(";
            cout<<p->data.occurrences[i].page;
            cout<<", ";
            cout<<p->data.occurrences[i].position;
            cout<<")  ";
        }
        i++;
    }
    cout<<endl;

    WithOcc(p->right);
}

void FirstOcc(NODE* p)
//Print the index and the FIRST occurrence
{

    if (p == NULL)
        return;

    FirstOcc(p->left);
    cout<<p->data.word<<": ";
    {
        cout<<"(";
        cout<<p->data.occurrences[0].page;
        cout<<", ";
        cout<<p->data.occurrences[0].position;
        cout<<")  "<<endl;
    }
    FirstOcc(p->right);
}

void InOrder(NODE* p)
//Traverse the tree using InOrder for calculating the spaces we need for every node
{
    if(p == NULL)
        return;
    InOrder(p->left);
    p->distance = distNum;
    distNum++;
    InOrder(p->right);
}

void PreOrder(NODE* p, string s)
//This PreOrder() traverse is for executing the searching task.
{
    extern int foundMark;
    int i = 0;

    if(p == NULL)
        return;

    PreOrder(p->left, s);
    if(p->data.word == s)
    {
        foundMark = 1;
        cout<<"\""<<s<<"\""<<" was found! The occurrences are as follows:"<<endl;
        while (p->data.occurrences[i].page != 0)
        {
            cout<<"(";
            cout<<p->data.occurrences[i].page;
            cout<<", ";
            cout<<p->data.occurrences[i].position;
            cout<<")  ";
            i++;
        }
    }
    PreOrder(p->right, s);
}


//Below are Functions about the queue
NODE* DeQueue()
{
    NODE* temp = nodeQueue[head];
    head++;
    head %= 1024;
    return temp;
}

void EnQueue(NODE* p)
{
   nodeQueue[tail] = p;
   tail++;
   tail %= 1024;
}

int IsEmpty()
{
    return (head == tail);
}
//Above are Funtions about the queue


void PrintTree(NODE* p)
//The function is used to print an AVL tree.
//A queue and functions relating to it are also used for printing.
{
    NODE* lineLast; //It stores the last node of the current line
    NODE* curr;     //It stores the current dequeue&print node
    NODE* nextLast; //It stores the possible last node of next line
    int prevDist = 0;   //It's used to store the PREVIOUS node's distance to the left
    int i;

    EnQueue(p);
    lineLast = p;
    while(!IsEmpty())
    {
        curr = DeQueue();

        for (i=0;i<(curr->distance-prevDist);i++)
            cout<<" ";
        cout<<curr->data.word;

        prevDist = curr->distance;
        if (curr->left != NULL)
        {
            nextLast = curr->left;
            EnQueue(nextLast);
        }
        if (curr->right != NULL)
        {
            nextLast = curr->right;
            EnQueue(nextLast);
        }
        if (curr == lineLast)
        //if the current printing node IS the last one of a line
        //set the nextLast as the lineLast
        //and reset the prevDist variable
        {
            cout<<endl;
            lineLast = nextLast;
            prevDist = 0;
        }
    }
}

void Search(NODE* p)
//This function is to search for given words in the item
//And report their occurrences
{
    extern int foundMark;
    foundMark = 0;
    string tmp;
    while(1)
    {
        cout<<endl<<"4.Type in the word you are looking for:";
        cin>>tmp;
        PreOrder(p, tmp);
        if(foundMark == 0)
            cout<<"\""<<tmp<<"\""<<" was not found!";
        cout<<endl<<"Do you want another search? Y/N:";
        cin>>tmp;
        if (tmp == "Y" || tmp == "y")
            continue;
        else
        {
            cout<<"Goodbye!"<<endl;
            break;
        }

    }
}




