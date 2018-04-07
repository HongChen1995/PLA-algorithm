#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define DEMENSION 5
double weight[DEMENSION];
int Size=0;// the size of trainingset
int step=0;//record the times of updata

struct data // to reserve every row of data
{
	double  feature[DEMENSION];
	int lable;
};

vector<data>trainingset;//create a dynamic array

int sign(double* weight, double* feature)
{
	int i;
	double sum=0;
	for(i=0;i<DEMENSION;i++) sum+=weight[i]*feature[i];
	if(sum>0)return +1;// defualt  sign(0)=-1
	else return -1;
}

void updata(double* weigth, struct data errorsample)
{
	int i,y=errorsample.lable;
	for(i=0;i<DEMENSION;i++)  weight[i]=weight[i]+y*errorsample.feature[i]; //updata the weight w(i+1)=w(i)+y*x
}

void PLA()
{
	int index=0;//the index of data that is being classified
	while(index!=Size-1)// keep going until classify all the data correctly
	{
		if(trainingset[index].lable==sign(weight,trainingset[index].feature)) index++;//continue to next data
		else//updata the weight w(i+1)=w(i)+y*x
		{
			updata(weight,trainingset[index]);
			step++;
		}
	}
	cout<<"total steps:"<<step<<endl;
}



void GetData(ifstream &TrainData)//read the trainingdata from file
{
	while(!TrainData.eof())//if not reach the end of file
	{
		data OneRecord;
		OneRecord.feature[0]=1;
		int i;
		for(i=1;i<DEMENSION;i++) TrainData>>OneRecord.feature[i];
		TrainData>>OneRecord.lable;
		trainingset.push_back(OneRecord);
	}
	TrainData.close();
	Size=trainingset.size();
}

void main()
{
	int i;
	ifstream TrainData("data.txt");
	if(! TrainData) cout<<"file can't be opened!"<<endl;
	else GetData(TrainData);//read the training data into vector
	for(i=0;i<DEMENSION;i++) weight[i]=0.0;//initialize the weight
	PLA();
}
