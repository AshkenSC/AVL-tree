/*
BUPT-1992-2
带头结点且头指针为ha和hb的两线性表A和B 分别表示两个集合。
两表中的元素皆为递增有序。请写一算法求A和B的并集AUB。
要求该并集中的元素仍保持递增有序。
且要利用A和B的原有结点空间。

*/

#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

/*
BUPT-1992-2
带头结点且头指针为ha和hb的两线性表A和B 分别表示两个集合。
两表中的元素皆为递增有序。请写一算法求A和B的并集AUB。
要求该并集中的元素仍保持递增有序。
且要利用A和B的原有结点空间。

*/

#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

typedef int ElemType;

typedef struct LNode {
    ElemType data;
    struct LNode * next;
}LNode, *LinkList;

void unionList(LinkList &l1, LinkList &l2);

int main() {

    return 0;
}

void unionList(LinkList &l1, LinkList &l2) {
    LNode *p = l1 -> next, *p1 = l1, *q = l2 -> next;
    while(p && q) {
        if(p -> data == q -> data) {
        //
            p = p -> next;
            q = q -> next;
            p1 = p1 -> next;
        }else if(p -> data < q -> data) {
            p = p -> next;
            p1 = p1 ->next;
        }else if(p -> data > q -> data) {
            LNode * q1 = q -> next;
            q -> next = p;
            p1 -> next = q;
            p1 = p1 -> next;
            q = q1;
        }
    }
}







