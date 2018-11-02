/*
NEU 2004-5

*/

#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
    int data;
    Node *next;
};

Node* Merge(Node *a, Node *b);

int main() {

    return 0;
}

Node* Merge(Node *a, Node *b) {
    Node *p1 = a, *p2 = b, *head, *p;
    // initialize new head
    if(p1.data < p2.data) {
        head.next = p1;
        p1 = p1.next;
    }
    else {
        head.next = p2;
        p2 = p2.next;
    }
    p = head.next;
    // merge
    while(p1 != nullptr && p2 != nullptr) {
        if(p1.data < p2.data) {
            p.next = p1;
            p1 = p1.next;
        }
        else {
            p.next = p2;
            p2 = p2.next;
        }
    }
    while(p1 != nullptr) {
        p.next = p1;
        p1 = p1.next;
    }
    while(p2 != nullptr) {
        p.next = p2;
        p2 = p2.next;
    }
    // return head of merged list
    p.next = nullptr;
    return head;
}


