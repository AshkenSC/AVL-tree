/*
BUPT-1992-2
��ͷ�����ͷָ��Ϊha��hb�������Ա�A��B �ֱ��ʾ�������ϡ�
�����е�Ԫ�ؽ�Ϊ����������дһ�㷨��A��B�Ĳ���AUB��
Ҫ��ò����е�Ԫ���Ա��ֵ�������
��Ҫ����A��B��ԭ�н��ռ䡣

*/

#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

/*
BUPT-1992-2
��ͷ�����ͷָ��Ϊha��hb�������Ա�A��B �ֱ��ʾ�������ϡ�
�����е�Ԫ�ؽ�Ϊ����������дһ�㷨��A��B�Ĳ���AUB��
Ҫ��ò����е�Ԫ���Ա��ֵ�������
��Ҫ����A��B��ԭ�н��ռ䡣

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







