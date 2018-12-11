#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
using namespace std;


struct Point{
    double x,y;
};

Point* ps,*temp;

bool cmpx(Point a,Point b){return a.x<=b.x;}  //x坐标升序
bool cmpy(Point a,Point b){return a.y<=b.y;}  //y坐标升序
double dist(Point a,Point b){return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));}  //欧氏距离计算

double mindist(int head,int tail)  //s、e用来表示当前处理的数组中的下标位置
{
    int mid,i,j,num=0;   //mid是数组中间位置下标 ，num存储temp数组标号
    double lrmin;        //点对之间的距离

    if(head==tail) return 1e308;   //只有一个点，则返回极大值
    mid=(head+tail)/2;
    lrmin=min(mindist(head,mid),mindist(mid+1,tail));  //递归求出左右两边的最小距离

    //筛选左右两边的点
    for(i=mid;i>=head&&ps[mid].x-ps[i].x<lrmin;i--){
        temp[num++]=ps[i];
    }

    for(i=mid+1;i<tail&&ps[i].x-ps[mid].x<lrmin;i++)
    {
        temp[num++]=ps[i];
    }
    sort(temp,temp+num,cmpy);
    for(i=0;i<num;i++){
        for(j=i+1;j<num&&temp[j].y-temp[i].y<lrmin;j++){
            lrmin=lrmin>dist(temp[i],temp[j])?min(lrmin,dist(temp[i],temp[j])):lrmin;
        }
    }
    return lrmin;                     //返回最小的点对之间的距离
}

int main()
{
    FILE* fp=fopen("al4_test1.txt","r");

    int n;
    fscanf(fp,"%d\n",&n);
    ps=new Point[n];
    temp=new Point[n];

    for(int i=0;i<n;i++){
        fscanf(fp,"%lf %lf\n",&ps[i].x,&ps[i].y);
    }

    //暴力求解
    double* bftemp=new double[n*(n-1)/2];
    int counter=0;
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            bftemp[counter]=dist(ps[i],ps[j]);
            counter++;
        }
    }
    sort(bftemp,bftemp+n*(n-1)/2);
    cout<<"result using brute-force: "<<bftemp[0]<<endl;
    delete []bftemp;

    sort(ps,ps+n,cmpx);            //按x坐标对ps排序
    double mindis=mindist(0,n);     //分治法计算
    cout<<"minimum distance using divide&conquer: "<<mindis<<endl;
    delete []ps;
    delete []temp;
    fclose(fp);
    return 0;
}
