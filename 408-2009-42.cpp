/*
2009��408ͳ����42�� 

��֪һ�����б�ͷ���ĵ��������ṹΪ����data, link��
���������ֻ������ͷָ��list���ڲ��ı������ǰ���£������һ�������ܸ�Ч���㷨
���������е�����k��λ���ϵĽ�㣨kΪ����������
�����ҳɹ����㷨����ý���data���ֵ��������1��
����ֻ����0��Ҫ��

1�������㷨�Ļ������˼�롣
2�������㷨����ϸʵ�ֲ��衣
3���������˼���ʵ�ֲ��裬���ó���������������㷨��ʹ��C��C++��Java����ʵ�֣����ؼ�֮���������Ҫע�͡�
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

