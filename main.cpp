/* CS 210 Assignment 7
Shicheng Ai #200356891
*/

#include <iostream>
#include <fstream>
#include "main.h"

using namespace std;

int foundMark = 0;  //If Search() finds a matched item, it will be set to 1.
string st1 = "D:\\data\\";
string st2;
char tempf[10];
char buffer[256];
string bufferS; //convert from char to string

//Pointer variables for use
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
    cout<<"2.1 PreOrder Traverse: "<<endl;
    PreOrder(p);
    cout<<endl<<"2.2 InOrder Traverse: "<<endl;
    InOrder(p);
    cout<<endl<<"2.3 PostOrder Traverse: "<<endl;
    PostOrder(p);

    //Print the index with the occurrences.
    cout<<endl<<endl<<"3. Print the index with the occurrences."<<endl;
    WithOcc(p);

    //Search for keywords.
    Search(p);

    return 0;
}

void DataIn(int i)
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
//Convert capitals to lower cases and filter symbols
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

void PreOrder(NODE* p)
{
    if(p == NULL)
        return;

    cout<<p->data.word<<"  ";
    PreOrder(p->left);
    PreOrder(p->right);
}

void InOrder(NODE* p)
{
    if(p == NULL)
        return;
    InOrder(p->left);
    cout<<p->data.word<<"  ";
    InOrder(p->right);
}

void PreOrder(NODE* p, string s)
//Use this reloaded PreOrder() function to execute the searching task.
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

void PostOrder(NODE* p)
{
    if(p == NULL)
        return;
    PostOrder(p->left);
    PostOrder(p->right);
    cout<<p->data.word<<"  ";
}

void Search(NODE* p)
{
    extern int foundMark;
    foundMark = 0;
    string tmp;
    while(1)
    {
        cout<<endl<<"4.Type in what you are looking for:";
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




