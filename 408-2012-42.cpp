/*
2012年408统考第42题

*/

#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
    char data;
    Node* next;
};

Node* FindCommonSuffix(Node* str1, Node* str2);

int main() {

    return 0;
}

Node* FindCommonSuffix(Node *str1, Node *str2) {
    int len1 = 0, len2 = 0;
    Node *p1 = str1, *p2 = str2, *suffixPtr;
    // get length of 2 strings
    while((*p1).next != nullptr) {
        p1 = (*p1).next;
        len1++;
    }
    while(p2 != nullptr) {
        p2 = (*p2).next;
        len2++;
    }
    // move p1 or p2 until
    // remaining string of s1 is as s2
    if(len1 > len2) {
        for(int i = 0; i < abs(len1 - len2); i++) {
            p1 = (*p1).next;
        }
    }
    else {
        for(int i = 0; i < abs(len1 - len2); i++) {
            p2 = (*p2).next;
        }
    }
    // move p1 and p2 until they reach common suffix
    while(p1 != p2) {
        p1 = (*p1).next;
        p2 = (*p2).next;
    }
    suffixPtr = p1;
    return suffixPtr;
}

