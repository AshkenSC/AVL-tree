/*
NEU 2004-5
��������������,һ������,һ������.
���д�㷨,������������ϲ�Ϊһ����������

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

    return head;
}


