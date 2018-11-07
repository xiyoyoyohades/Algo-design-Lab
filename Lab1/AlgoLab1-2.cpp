#include <algorithm>
#include <queue> 
#include <iostream>
#include <vector>
#include <stdio.h>
using namespace std;

struct cmp                     //used in the queue, smaller items get priority
{
	bool operator()(const int& a, const int& b)
	{
		return a > b;
	}
};

struct Slice
{
public:
	int begin, end;
	bool operator<(Slice &x)   //used to sort
	{
		if (begin != x.begin) return this->begin < x.begin;
		else return this->end < x.end;
	}
};

int main()
{
	int const SliceNum = 10;
    int RoomNum = 0;
    int TimeNow;
	Slice slice_array[SliceNum];

	FILE* filein=fopen("test2.txt","r");
	
	for(int i=0; i<SliceNum ; i++){
		fscanf(filein,"%d %d\n", &slice_array[i].begin, &slice_array[i].end);
	}
	fclose(filein);
		

	

	/*
	for (int i = 0; i < SliceNum; i++)  //for test only
	{
		slice_array[i].begin = i;
		slice_array[i].end = i + 10;
	}
	*/

	sort(slice_array, slice_array + SliceNum);

	//for(int i=0; i<SliceNum ; i++){
	//	printf("%d %d\n",slice_array[i].begin, slice_array[i].end);
	//}
	priority_queue <int, vector<int>, cmp  > TimeQueue;
	TimeQueue.push(slice_array[0].end);
	
	for (int i = 0; i < SliceNum; i++)
	{
		TimeNow = TimeQueue.top();
		
		if (slice_array[i].begin >= TimeNow)
		{
			TimeQueue.pop();
			TimeQueue.push(slice_array[i].end);
		}else{ 
			RoomNum++;
			TimeQueue.push(slice_array[i].end);
		}
		//cout<<TimeNow<<" ";
		//cout<<RoomNum<<endl;
	}

	std::cout<<"Total Room Number : "<<RoomNum;
	return 0;
}
