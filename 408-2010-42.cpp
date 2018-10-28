/*
2010年408统考第42题

设将n（n>1）个整数存放到一维数组R中。
试设计一个在时间和空间两方面都尽可能高效的算法，
将R中保存的序列循环左移P（0<P<n）个位置，
即将R中的数据由（x0,x1,…,xn-1）变换为(xp,xp+1,…,xn-1,x0,x1,…,xp-1)。
要求：
（1）给出算法的基本设计思想。
（2）根据设计思想，采用C或C++或JAVA语言描述算法，关键之处给出注释。
（3）说明设计算法的时间复杂度和空间复杂度。
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


