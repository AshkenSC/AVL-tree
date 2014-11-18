#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define OK 1
#define ERROR -1
//#define m 9 //3阶树
#define N 16 //数据元素个数
#define MAX 5 //字符串最大长度＋1

using namespace std;

typedef int KeyType;
const int m = 3;
struct Others  //记录的其它部分
{
    char info[MAX];
};

struct Record
{
    KeyType key; //关键字
    Others others; //其它部分
};

typedef struct BTNode   //with m
{
    //extern int m;
    int keynum; //结点中关键字个数
    BTNode * parent; //指向双亲节点
    struct Node  //结点向量类型
    {
        KeyType key; //关键字向量
        BTNode * ptr; //子树指针向量
        Record * recptr; //记录向量指针
    } node[m + 1]; //key,recptr的0号单元未用
} BTNode, *BTree;

struct Result //B树的查找结果类型
{
    BTNode * pt; //指向找到的结点
    int i; //在节点中关键字序号，1...m
    int tag; //1表示查找成功，0表示查找失败。
};

int InitDSTable(BTree & DT)
{
    DT = NULL;
    return OK;
}//InitDSTable

void DestroyDSTable(BTree & DT)
{
    int i;

    if(DT) //非空树
    {
        for(i = 0; i <= DT->keynum; i++)
        {
            DestroyDSTable(DT->node[i].ptr);
        }

        free(DT);
        DT = NULL;
    }//if
}//DestroyDSTable

int Search(BTree p, KeyType K)
{
    //在p->node[1...keytype].key中查找i,使得p->node[i].key<=K<
    //p->node[i+1].key
    int i = 0, j;

    for(j = 1; j <= p->keynum; j++)
        if(p->node[j].key <= K)
        {
            i = j;
        }

    return i;
}//Search

void Insert(BTree & q, int i, Record * r, BTree ap)
{
    //将r->key、r和ap分别插入到q->key[i+1]、
    //q->recptr[              i+1]和q->ptr[i+1]中
    int j;

    for(j = q->keynum; j > i; j--) //空出q->node[i+1]
    {
        q->node[j + 1] = q->node[j];
    }

    q->node[i + 1].key = r->key;
    q->node[i + 1].ptr = ap; //前加入的结点，还没有儿子结点
    q->node[i + 1].recptr = r;
    q->keynum++;
}//Insert

void NewRoot(BTree & T, Record * r, BTree ap)
{
    // 生成含信息(T,r,ap)的新的根结点*T，原T和ap为子树指针
    BTree p;
    p = (BTree)malloc(sizeof(BTNode));
    p->node[0].ptr = T;
    T = p;

    if(T->node[0].ptr)
    {
        T->node[0].ptr->parent = T;
    }

    T->parent = NULL;
    T->keynum = 1;
    T->node[1].key = r->key;
    T->node[1].recptr = r;
    T->node[1].ptr = ap;

    if(T->node[1].ptr)
    {
        T->node[1].ptr->parent = T;
    }
}//NewRoot

void split(BTree & q, BTree & ap)   //with m
{
    // 将结点q分裂成两个结点，前一半保留，后一半移入新生结点ap
    //extern const int m;
    int i, s = (m + 1) / 2;
    ap = (BTree)malloc(sizeof(BTNode)); //生成新结点ap
    ap->node[0].ptr = q->node[s].ptr; //原来结点中间位置关键字相应指针指向的子树放到

    //新生成结点的0棵子树中去
    for(i = s + 1; i <= m; i++) //后一半移入ap
    {
        ap->node[i - s] = q->node[i];

        if(ap->node[i - s].ptr)
        {
            ap->node[i - s].ptr->parent = ap;
        }
    }//for

    ap->keynum = m - s;
    ap->parent = q->parent;
    q->keynum = s - 1; // q的前一半保留，修改keynum
}//split

void InsertBTree(BTree & T, Record * r, BTree q, int i) //with m
{
    //在m阶B树T上结点*q的key[i]与key[i+1]之间插入关键字K的指针r。若引起
    // 结点过大,则沿双亲链进行必要的结点分裂调整,使T仍是m阶B树。
    //extern int m;
    BTree ap = NULL;
    int finished = false;
    int s;
    Record * rx;
    rx = r;

    while(q && !finished)
    {
        Insert(q, i, rx, ap); //将r->key、r和ap分别插入到q->key[i+1]、

        //q->recptr[i+1]和q->ptr[i+1]中
        if(q->keynum < m)
        {
            finished = true;
        }
        else
        {
            //分裂结点*q
            s = (m + 1) / 2;
            rx = q->node[s].recptr;
            split(q, ap); //将q->key[s+1..m],q->ptr[s..m]和q->recptr[s+1..m]
            //移入新结点*ap
            q = q->parent;

            if(q)
            {
                i = Search(q, rx->key);    //在双亲结点*q中查找rx->key的插入位置
            }
        }//else
    }//while

    if(!finished) //T是空树(参数q初值为NULL)或根结点已分裂为
        //结点*q和*ap
    {
        NewRoot(T, rx, ap);
    }
}//InsertBTree

Result SearchBTree(BTree T, KeyType K)
{
    // 在m阶B树T上查找关键字K，返回结果(pt,i,tag)。若查找成功，则特征值
// tag=1，指针pt所指结点中第i个关键字等于K；否则特征值tag=0，等于K的
// 关键字应插入在指针Pt所指结点中第i和第i+1个关键字之间。
    BTree p = T, q = NULL; //初始化，p指向待查结点，q指向p的双亲
    int found = false;
    int i = 0;
    Result r;

    while(p && !found)
    {
        i = Search(p, K); //p->node[i].key≤K<p->node[i+1].key

        if(i > 0 && p->node[i].key == K)
        {
            found = true;
        }
        else
        {
            q = p;
            p = p->node[i].ptr; //在子树中继续查找
        }//else
    }//while

    r.i = i;

    if(found)
    {
        r.pt = p;
        r.tag = 1;
    }//if
    else
    {
        r.pt = q;
        r.tag = 0;
    }//else

    return r;
}//SearchBTree

void print(BTNode c, int i) // TraverseDSTable()调用的函数
{
    printf("(%d,%s)\n", c.node[i].key, c.node[i].recptr->others.info);
}//print

void TraverseDSTable(BTree DT, void(*Visit)(BTNode, int))
{
    // 初始条件: 动态查找表DT存在，Visit是对结点操作的应用函数
// 操作结果: 按关键字的顺序对DT的每个结点调用函数Visit()一次且至多一次
    int i;

    if(DT) //非空树
    {
        if(DT->node[0].ptr) // 有第0棵子树
        {
            TraverseDSTable(DT->node[0].ptr, Visit);
        }

        for(i = 1; i <= DT->keynum; i++)
        {
            Visit(*DT, i);

            if(DT->node[i].ptr) // 有第i棵子树
            {
                printf("\n\n");
                TraverseDSTable(DT->node[i].ptr, Visit);
            }
        }//for
    }//if
}//TraverseDSTable

void InputBR(BTree & t, Record r[])
{
    Result s;

    for(int i = 0; i < N; i++)
    {
        s = SearchBTree(t, r[i].key);

        if(!s.tag)
        {
            InsertBTree(t, &r[i], s.pt, s.i);
        }
    }
}//InputBR

void UserSearch(BTree t)
{
    int i;
    Result s;
    printf("\n请输入待查找记录的关键字: ");
    scanf("%d", &i);
    s = SearchBTree(t, i);

    if(s.tag)
    {
        print(*(s.pt), s.i);
    }
    else
    {
        printf("没找到");
    }

    printf("\n");
}//UserSearch

void DeleteIt(BTree t, BTNode * dnode, int id)  //with m
{
    //extern int m;
    if(dnode->keynum >= ceil(m / 2))
    {
        dnode->keynum--;
        dnode->node[id].ptr = NULL;
    }//if被删关键字Ki所在结点的关键字数目不小于ceil(m/2)，则只需从结点中删除Ki和相应指针Ai，树的其它部分不变。
    else
        if((dnode->keynum == (ceil(m / 2) - 1)) && ((id + 1) < (m - 1)) && dnode->parent->node[id + 1].ptr->keynum > (ceil(m / 2) - 1))
        {
            for(int i = 1; i < m && dnode->parent->node[i].key < dnode->parent->node[id + 1].ptr->node[1].key; i++)
            {
                dnode->node[i].key = dnode->parent->node[i].key;
            }

            dnode->parent->node[1].key = dnode->parent->node[id + 1].ptr->node[1].key;
            (dnode->parent->node[id + 1].ptr->keynum)--;
        }//else if 被删关键字Ki所在结点的关键字数目等于ceil(m/2)-1，则需调整。本次为与右兄弟调整
        else
            if((dnode->keynum == (ceil(m / 2) - 1)) && ((id - 1) > 0) && dnode->parent->node[id - 1].ptr->keynum > (ceil(m / 2) - 1))
            {
                for(int i = 1; i < m && dnode->parent->node[i].key > dnode->parent->node[id - 1].ptr->node[dnode->parent->node[id - 1].ptr->keynum].key; i++)
                {
                    dnode->node[i].key = dnode->parent->node[i].key;
                }

                dnode->parent->node[1].key = dnode->parent->node[id - 1].ptr->node[dnode->parent->node[id - 1].ptr->keynum].key;
                (dnode->parent->node[id - 1].ptr->keynum)--;
            }//2-else if被删关键字Ki所在结点的关键字数目等于ceil(m/2)-1，则需调整。本次为与左兄弟调整
            else
                if((dnode->keynum == (ceil(m / 2) - 1)) && ((id + 1) < (m - 1)) && dnode->parent->node[id + 1].ptr->keynum == (ceil(m / 2) - 1))
                {
                    do
                    {
                        BTree tmp;
                        tmp = dnode;
                        dnode->parent->node[id + 1].ptr->node[2] = dnode->parent->node[id + 1].ptr->node[1];
                        dnode->parent->node[id + 1].ptr->node[1] = dnode->parent->node[1];
                        dnode->parent->node[id + 1].ptr->keynum++;
                        dnode->parent->node[id + 1].ptr->node[0].ptr = dnode->node[1].ptr;
                        dnode->parent->keynum--;
                        dnode->parent->node[id].ptr = NULL;
                        tmp = dnode;

                        if(dnode->parent->keynum >= (ceil(m / 2) - 1))
                        {
                            dnode->parent->node[1] = dnode->parent->node[2];
                        }

                        dnode = dnode->parent;
                        free(tmp);
                    }
                    while(dnode->keynum < (ceil(m / 2) - 1)); //双亲中keynum<
                }//3-else if被删关键字Ki所在结点和其相邻兄弟结点中的的关键字数目均等于ceil(m/2)-1，本次假设右兄弟存在
                else
                    if((dnode->keynum == (ceil(m / 2) - 1)) && (id - 1) > 0      && dnode->parent->node[id - 1].ptr->keynum == (ceil(m / 2) - 1))
                    {
                        do
                        {
                            BTree tmp;
                            tmp = dnode;
                            dnode->parent->node[id - 1].ptr->node[2] = dnode->parent->node[id - 1].ptr->node[1];
                            dnode->parent->node[id - 1].ptr->node[1] = dnode->parent->node[1];
                            dnode->parent->node[id - 1].ptr->keynum++;
                            dnode->parent->node[id - 1].ptr->node[0].ptr = dnode->node[1].ptr;
                            dnode->parent->keynum--;
                            dnode->parent->node[id].ptr = NULL;
                            tmp = dnode;

                            if(dnode->parent->keynum >= (ceil(m / 2) - 1))
                            {
                                dnode->parent->node[1] = dnode->parent->node[2];
                            }

                            dnode = dnode->parent;
                            free(tmp);
                        }
                        while(dnode->keynum < (ceil(m / 2) - 1)); //双亲中keynum<
                    }//4-else if被删关键字Ki所在结点和其相邻兄弟结点中的的关键字数目均等于ceil(m/2)-1，本次假设左兄弟存在
                    else
                    {
                        printf("Error!");    //出现异常
                    }
}//DeleteIt

void UserDelete(BTree t)
{
    KeyType date;
    Result s;
    printf("Please input the date you want to delete:\n");
    scanf("%d", &date);
    s = SearchBTree(t, date);

    if(!s.tag)
    {
        printf("Search failed,no such date\n");
    }
    else
    {
        DeleteIt(t, s.pt, s.i);
    }
}//UserDelete

int main()
{
    Record r[N] = {{24, "1"}, {45, "2"}, {53, "3"}, {12, "4"}, {37, "5"},
        {50, "6"}, {61, "7"}, {90, "8"}, {100, "9"}, {70, "10"},
        {3, "11"}, {30, "12"}, {26, "13"}, {85, "14"}, {3, "15"},
        {7, "16"}
    };
    BTree t;
    InitDSTable(t);
    InputBR(t, r);
    printf("按关键字的顺序遍历B_树:\n");
    TraverseDSTable(t, print);
    UserSearch(t);
    UserDelete(t);
    TraverseDSTable(t, print);
    DestroyDSTable(t);
    return 0;
}

