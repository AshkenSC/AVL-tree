/*
2011年408统考第42题

一个长度为L（L≥1）的升序序列S，处在第L / 2（若为小数则去掉小数后加1）个位置的数称为S 的中位数。
例如，若序列S1=（11,13,15,17,19），则S1 的中位数是15，
两个序列的中位数是含它们所有元素的升序序列的中位数。
例如，若S2=（2,4,6,8,20），则S1 和S2 的中位数是11。
现在有两个等长升序序列A 和B，
试设计一个在时间和空间两方面都尽可能高效的算法，
找出两个序列A 和B 的中位数。
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

