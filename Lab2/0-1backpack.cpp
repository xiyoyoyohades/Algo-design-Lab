#include <iostream>
#include <algorithm>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;



int main()
{
    int good_num, capacity;
    FILE* fp=fopen("0-1back.test2","r");
    fscanf(fp,"%d %d\n",&good_num,&capacity);

    int* value=new int[good_num+1];// 价值
    int* weight=new int[good_num+1];// 重量
    int gain[good_num+1][capacity+1]={0};// 表示在背包容量为j的情况下，前i件宝贝的最大价值
    memset(gain,0,(good_num+1)*(capacity+1));

    int temp1,temp2;
    value[0]=0; weight[0]=0;
    for(int i=1;i<=good_num;i++){
        fscanf(fp,"%d %d\n",&temp1,&temp2);
        value[i]=temp1;
        weight[i]=temp2;
        //cout<<value[i]<<weight[i]<<endl;
    }


    for (int i = 1; i <= good_num; i++)        //外循环控制物品数量，确保每个物品都会被遍历到
    {

        for (int j = 1; j <= capacity; j++)
        {
            // 递推关系式
            if (j < weight[i])
            {
                gain[i][j] = gain[i - 1][j];
            }
            else
            {
                gain[i][j] = max(gain[i - 1][j], gain[i - 1][j - weight[i]] + value[i]);
            }
        }
    }

    for (int i = 0; i <= good_num; i++)
    {
        for (int j = 0; j <= capacity; j++)
        {
            printf("%4d ", gain[i][j]);
        }

        cout << endl;
    }

    cout << endl << "选取的最大价值是：" << gain[good_num][capacity] << endl;
    cout << "选取的物品：" << endl;
    int i = good_num, j = capacity;
    while (i)
    {
        if (gain[i][j] == (gain[i - 1][j - weight[i]] + value[i]))
        {
            cout << i << ":" << "weight=" << weight[i] << ", value=" << value[i] << endl;
            j -= weight[i];
        }
        i--;
    }

    return 0;
}
