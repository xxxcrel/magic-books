#include<stdio.h>
#include"disjset.h"

//基于方便，从1开始计数
void InitializeSet(DisjSet S)
{
    for (int i = NumSets; i > 0; --i)
        S[i] = -1;
}
//下面两个SetUnion算法传进去的Root1和Root2都假设为一个集合的根
//Union-by-size
void SetUnion(DisjSet S, SetType Root1, SetType Root2)
{
    if(S[Root2] < S[Root1])//Root1的数目小于Root2(注意负数的比较eg:-3 < -2)
    {
        //增加Root2的数目，并更新Root1的父节点为Root2
        S[Root2] = S[Root1] + S[Root2];
        S[Root1] = Root2;
    }
    else
    {
        //当大于等于时
        S[Root1] = S[Root1] + S[Root2];
        S[Root2] = Root1;
    }
}
//Union-by-height
// void SetUnion(DisjSet S, SetType Root1, SetType Root2)
// {
//     if(S[Root2] < S[Root1])//Root2比Root1更深(eg:-5 < -3)
//         S[Root1] = Root2;//无需更新高度与Union-by-Size不一样
//     else
//     {
//         //只有当相等的时候才需要更新高度
//         /*Root1  Root2
//             5      8           5 <----8
//            / \    / \--union->/ \    / \
//          4    2  3   9       4   2  3   9*/
//         if(S[Root1] == S[Root2])
//             --S[Root1];//eg:-4 - 1 = -5
//         S[Root2] = Root1;
//     }
// }
//压缩路径的写法
SetType Find(DisjSet S, ElementType X)
{
    if(S[X] <= 0)//小于等于0表示已经找到了根
        return X;
    else
        return S[X] = Find(S, S[X]);//递归的将当前元素直接指向当前集合的根
}

void PrintSet(DisjSet S)
{
    for (SetType i = 1; i < NumSets; ++i)
        printf("%4d", i);
    printf("\n");
    for (int i = 1; i < NumSets; ++i)
            printf("%4d", S[i]);
    printf("\n");
}