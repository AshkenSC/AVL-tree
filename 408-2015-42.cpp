/*
2015年408统考第42题

*/

#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
    int data;
    Node *next;
};

const int n = 1000;

void DeleteAbs(Node *head);

int main() {

    return 0;
}

void DeleteAbs(Node *head) {
    int isExisted[n] = {0};
    Node *p = head, *pre, *delNode;
    while(p != nullptr) {
        if(isExisted[abs((*p).data)] == 1) {
            (*pre).next = (*p).next;
            p = (*p).next;
            delNode = p;
            delete(delNode);
        }
        else {
            isExisted[abs((*p).data)] = 1;
            pre = p;
            p = (*p).next;
        }
    }
}

