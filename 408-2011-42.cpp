/*
2011��408ͳ����42��

һ������ΪL��L��1������������S�����ڵ�L / 2����ΪС����ȥ��С�����1����λ�õ�����ΪS ����λ����
���磬������S1=��11,13,15,17,19������S1 ����λ����15��
�������е���λ���Ǻ���������Ԫ�ص��������е���λ����
���磬��S2=��2,4,6,8,20������S1 ��S2 ����λ����11��
�����������ȳ���������A ��B��
�����һ����ʱ��Ϳռ������涼�����ܸ�Ч���㷨��
�ҳ���������A ��B ����λ����
*/

#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

int FindMid(int* s1, int* s2, int length);

int main() {
    const int length = 5;
    int s1[length] = {1, 3, 9, 12, 19};
    int s2[length] = {2, 4, 6, 9, 20};
    // array input
    /*for(int i = 0; i < 5; i++) {
        cin >> s1[i];
    }
    for(int i = 0; i < 5; i++) {
        cin >> s2[i];
    }*/
    cout << FindMid(s1, s2, length);

    return 0;
}

int FindMid(int* s1, int* s2, int length) {
    int p1 = 0, p2 = 0, num = 0, mid;
    while(num < length) {
        if(s1[p1] < s2[p2]) {
            mid = s1[p1];
            p1++;
            num++;
        }
        else {
            mid = s2[p2];
            p2++;
            num++;
        }
    }
    return mid;
}

