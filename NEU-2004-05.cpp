/*
NEU 2004-5
设有两个单链表,一个升序,一个降序.
设编写算法,将这两个链表合并为一个有序链表

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
    // suppose list a is reversed
    // reverse list a
    Node *head;
    Node *pre = a, *p = (*a).next, *q = p;
    while(p != nullptr) {
        p = (*p).next;
        (*q).next = pre;
        pre = q;
        q = p;
    }
    (*a).next = nullptr;
    a = pre;

    // TODO: merge a and b
    // 1.
    Node *r;
    p = a; q = b;
    if((*p).data < (*q).data) {
        head = p;
        p = (*p).next;
    }
    else {
        head = q;
        q = (*q).next;
    }
    r = head;
    // 2.
    while(p != nullptr && q != nullptr) {
        if((*p).data < (*q).data) {
            (*r).next = p;
            r = p;
            p = (*p).next;
        }
        else {
            (*r).next = q;
            r = q;
            q = (*q).next;
        }
    }
    // 3.
    if(p != nullptr) {
        (*r).next = p;
    }
    else {
        (*r).next = q;
    }

    return head;
}


