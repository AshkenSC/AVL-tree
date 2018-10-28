/*
2009年408统考第42题 

已知一个带有表头结点的单链表，结点结构为：（data, link）
假设该链表只给出了头指针list。在不改变链表的前提下，请设计一个尽可能高效的算法
查找链表中倒数第k个位置上的结点（k为正整数）。
若查找成功，算法输出该结点的data域的值，并返回1；
否则，只返回0。要求：

1）描述算法的基本设计思想。
2）描述算法的详细实现步骤。
3）根据设计思想和实现步骤，采用程序设计语言描述算法（使用C、C++或Java语言实现），关键之处请给出简要注释。
*/

#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
    int data;
    Node* link;
};

int FindReverseK(Node* head, int k);

int main() {
	
    return 0;
}

int FindReverseK(Node* head, int k) {
    Node* p = head;
    Node* q = head;

    // check linked list length, if <k, return 0;
    int length;
    for(length = 0; p != nullptr; length++) {
        p = p -> link;
    }
    if(length < k) {
        return 0;
    }
    // if list is long enough, find the k-th node
    for(int i = 1; i <= k; i++) {
        p = p -> link;
        q = q -> link;
    }
    for(; q -> link != nullptr; q = q -> link);
    cout << p -> data;
    return 1;
}

