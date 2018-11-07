#include <algorithm>
#include <queue> 
#include <iostream>
#include <vector>
#include <map>
#include <stdio.h>
using namespace std;


//vector<map<int, int> >::iterator p,q;
/*struct cmp{
    bool operator()(const int& a, const int& b){
        (*p).find(a)->second > (*p).find(b)->second;
    }
}; */

int main(int argc, char const *argv[])
{
    int StuNum=0;
    int HosNum=0;
    int maxperson=1;
    int matched=0;
    vector<queue<int> > students;
    queue<int> stuLeft;     
    vector<priority_queue<int, vector<int>, greater<int> > > hospitals;
    vector<map<int, int> > hospref;
    vector<map<int, int> > hospref_rev;


    vector<queue<int> >::iterator stu_ita;
    vector<priority_queue<int, vector<int>, greater<int> > >::iterator hos_ita;
    vector<map<int, int> >::iterator p;
    vector<map<int, int> >::iterator q;

    queue<int> tmp_queue;
    priority_queue<int, vector<int>, greater<int> >  tmp_prio;
    map<int, int> tmp_map;
    int tmp_int, flag;

    FILE* fp=fopen("test1.txt","r");
    fscanf(fp,"%d %d %d\n",&StuNum, &HosNum, &maxperson);
    fscanf(fp,"\n");

    for(int i=0 ; i<StuNum ; i++)
    {
        students.push_back(tmp_queue);
    }
    for(int i=0 ; i<HosNum; i++)
    {
        hospitals.push_back(tmp_prio);
    }
    for(int i=0; i<HosNum ;i++)
    {
        hospref.push_back(tmp_map);
        hospref_rev.push_back(tmp_map);
    }
    for(int i=0; i<StuNum; i++)
    {
        stuLeft.push(i);
    }

    stu_ita=students.begin();
    p=hospref.begin();
    q=hospref_rev.begin();
    for(int i=0 ;i<StuNum;i++)
    {
        
        for(int j=0;j<HosNum;j++)
        {
            fscanf(fp,"%d ",&tmp_int);
            (*(stu_ita+i)).push(tmp_int);
        }
        fscanf(fp,"\n");
    }
    fscanf(fp,"\n");

    for(int i=0; i<HosNum;i++)
    {
        for(int j=0; j<StuNum;j++)
        {
            fscanf(fp,"%d ",&tmp_int);
            (*(p+i)).insert(pair<int,int>(tmp_int,StuNum-j));
            (*(q+i)).insert(pair<int,int>(StuNum-j,tmp_int));

        }
        fscanf(fp,"\n");
    }

    fclose(fp);

    while(stuLeft.size()>0 && matched<maxperson*HosNum){
        

            p=hospref.begin();
            q=hospref_rev.begin();
            
            stu_ita=students.begin();
            hos_ita=hospitals.begin();

            p+=(*(stu_ita+stuLeft.front())).front(); 
            q+=(*(stu_ita+stuLeft.front())).front(); 

            (*((*(stu_ita+stuLeft.front())).front()+hos_ita)).push((*p).find(stuLeft.front())->second);
            std::cout<<stuLeft.front()<<" replaced ";
            flag=0;
            if((*((*(stu_ita+stuLeft.front())).front()+hos_ita)).size()>maxperson){
                stuLeft.push((*q).find((*((*(stu_ita+stuLeft.front())).front()+hos_ita)).top())->second);
                std::cout<<stuLeft.back()<<endl;
                (*((*(stu_ita+stuLeft.front())).front()+hos_ita)).pop();
                matched--;
                flag=1;
                
            }
            if(!flag) std::cout<<"no one"<<endl;
            (*(stu_ita+stuLeft.front())).pop();
            stuLeft.pop();
            matched++;
    }
    std::cout<<"Done"<<endl;
    std::cout<<matched<<" of "<<StuNum<<" students matched"<<endl;
    std::cout<<"Unmatched students: ";
    
    while(!stuLeft.empty())
    {
        flag=2;
        std::cout<<stuLeft.front()<<" ";
        stuLeft.pop();
    }
    if(flag!=2) std::cout<<"none"<<endl;
    
    hos_ita=hospitals.begin();
    q=hospref_rev.begin();
    FILE* fpo=fopen("result1.txt","w");
    for(int i=0 ;i<HosNum; i++)
    {
        
        fprintf(fpo,"hospital %d : ",i);
        while(!(*(hos_ita+i)).empty())
        {
            tmp_int=(*(hos_ita+i)).top();
            fprintf(fpo, "%d ",(*(q+i)).find(tmp_int)->second);
            (*(hos_ita+i)).pop();
        }
        fprintf(fpo, "\n");
    }
    fclose(fpo);
    return 0;
}
