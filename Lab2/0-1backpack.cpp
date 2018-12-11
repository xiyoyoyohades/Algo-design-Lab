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

    int* value=new int[good_num+1];// ��ֵ
    int* weight=new int[good_num+1];// ����
    int gain[good_num+1][capacity+1]={0};// ��ʾ�ڱ�������Ϊj������£�ǰi������������ֵ
    memset(gain,0,(good_num+1)*(capacity+1));

    int temp1,temp2;
    value[0]=0; weight[0]=0;
    for(int i=1;i<=good_num;i++){
        fscanf(fp,"%d %d\n",&temp1,&temp2);
        value[i]=temp1;
        weight[i]=temp2;
        //cout<<value[i]<<weight[i]<<endl;
    }


    for (int i = 1; i <= good_num; i++)        //��ѭ��������Ʒ������ȷ��ÿ����Ʒ���ᱻ������
    {

        for (int j = 1; j <= capacity; j++)
        {
            // ���ƹ�ϵʽ
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

    cout << endl << "ѡȡ������ֵ�ǣ�" << gain[good_num][capacity] << endl;
    cout << "ѡȡ����Ʒ��" << endl;
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
