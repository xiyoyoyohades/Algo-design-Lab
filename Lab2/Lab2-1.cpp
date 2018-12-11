#include <iostream>
#include <algorithm>

#define MAXLEN 31
#define BLANK 1
#define DISMATCH 30

using namespace std;

int penalty[MAXLEN+1][MAXLEN+1];
string str1, str2;
int len=0;
char* result1=nullptr, * result2=nullptr;

void Reverse(int i, int j) {
	if (!j||!i){
	    if(i&&!j) {
            result1[len]=str1[i-1];
            result2[len]='-';
            len++;
            return Reverse(i-1,0);
        }else if(!i&&j){
            result1[len]='-';
            result2[len]=str2[j-1];
            len++;
            return Reverse(0,j-1);
        }
	    else return;
	}
	if (penalty[i][j] == penalty[i - 1][j] + BLANK) {
		result1[len]=str1[i-1];
		result2[len]='-';
		len++;
		return Reverse(i - 1, j);
	}else if (penalty[i][j] == penalty[i][j - 1] + BLANK) {
		result1[len]='-';
		result2[len]=str2[j-1];
		len++;
		return Reverse(i , j - 1);
	}else {
		result1[len]=str1[i-1];
		result2[len]=str2[j-1];
		len++;
		return Reverse(i - 1, j - 1);
	}
}
int main()
{
	cin>>str1;
	cin>>str2;
	int length1 = str1.length();
	int length2 = str2.length();
	result1=new char[length1+length2];
	result2=new char[length1+length2];

	for (int i = 0; i <= length1; i++)
	{
		for (int j = 0; j <= length2; j++)
		{
		    if(j&&i){
                penalty[i][j]= min(penalty[i - 1][j - 1] + (str1[i-1] == str2[j-1] ? 0 : DISMATCH), min(penalty[i][j - 1] + BLANK, penalty[i - 1][j] + BLANK));
		    }else if(j&&!i)
		    {
		        penalty[0][j]=penalty[0][j-1]+BLANK;
		    }else if(!j&&i){
                penalty[i][0]=penalty[i-1][0]+BLANK;
		    }else{
		        penalty[i][j]=0;
		    }

		}
	}

	cout <<endl<< "minimum penalty: "<<penalty[length1][length2] << endl<<endl<<"match result: "<<endl;
	/*
	for(int i=0;i<=length1;i++){
        for(int j=0;j<=length2;j++){
            cout<<penalty[i][j]<<" ";
        }
        cout<<endl;
	}
	*/
	Reverse(length1, length2);
	for(int i=len-1;i>=0;i--){
        cout<<result1[i];
	}cout<<endl;
	for(int i=len-1;i>=0;i--){
        cout<<result2[i];
	}cout<<endl;
	delete []result1;
	delete []result2;

	return 0;
}
