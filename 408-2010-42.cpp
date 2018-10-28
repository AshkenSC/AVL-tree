/*
2010��408ͳ����42��

�轫n��n>1����������ŵ�һά����R�С�
�����һ����ʱ��Ϳռ������涼�����ܸ�Ч���㷨��
��R�б��������ѭ������P��0<P<n����λ�ã�
����R�е������ɣ�x0,x1,��,xn-1���任Ϊ(xp,xp+1,��,xn-1,x0,x1,��,xp-1)��
Ҫ��
��1�������㷨�Ļ������˼�롣
��2���������˼�룬����C��C++��JAVA���������㷨���ؼ�֮������ע�͡�
��3��˵������㷨��ʱ�临�ӶȺͿռ临�Ӷȡ�
*/

#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

const int n = 5;

void ROL(int* a, int p);

int main() {
    int a[n] = {1, 2, 3, 4, 5};

    ROL(a, 2);
    for(int i = 0; i < 5; i++) {
        cout << a[i] << " ";
    }

    return 0;
}

void ROL(int* a, int p) {
    int b[n];
    // copy array a to b;
    for(int i = 0; i < n; i++) {
        b[i] = a[i];
    }
    // move x(p+1) to x(n) to the head
    for(int i = p, j = 0; i < n; i++) {
        b[j++] = a[i];
    }
    // copy x(1) to x(p) to the end
    for(int i = 0, j = n - p; i < p; i++) {
        b[j++] = a[i];
    }
    // copy array b to array a
    for(int i = 0; i < n; i++) {
        a[i] = b[i];
    }
}


