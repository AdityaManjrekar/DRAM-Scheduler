#include<iostream>
#include<fstream>
#include<map>
#include<stdlib.h>
#include<assert.h>
#include<string>
#include<locale>
using namespace std;
#define MAX_LENGTH 1024
/*
	Struct
*/
struct InstructionDetails
{
	string instructionType;
	string row;
	string column;
};
/*
 Function Declarations
*/
int readFromFile(map<int,string>&);
int inputDetailsExtraction(const map<int,string> input,map<int,InstructionDetails> &inputDetailsMap);
int cycleTransition(map<string,int>&);
int main()
{
	int flag = 0;
	map<int,string> input;	
	map<int,InstructionDetails> inputDetailsMap;
	map<string,int> latency;
	int programCounter = 0;
	int sizeOfInput = 0;
	std::locale loc;
	flag = readFromFile(input);
	assert(flag==1);
	flag = inputDetailsExtraction(input,inputDetailsMap);	
	assert(flag==1);
	cycleTransition(latency);
	assert(flag==1);
	sizeOfInput = inputDetailsMap.size();
	int activationFlag = 1;
	int preChargeFlag = 0;
	int cycleNumber = 0;
	while(programCounter<sizeOfInput)
	{
		int tempProgramCounter = programCounter;
		InstructionDetails tempInstructionDetails = inputDetailsMap.at(programCounter);
		if(activationFlag==1)
		{
			cycleNumber = 0;
		 	cout<<"A";
		 for (std::string::size_type i=0; i<tempInstructionDetails.row.length(); ++i)
		    std::cout << toupper((tempInstructionDetails.row)[i],loc);
		    cout<<endl;
			cout<<"I11"<<endl;
			cycleNumber = 12;
			activationFlag=0;
		}
		if(tempInstructionDetails.instructionType == "L")
		{
			cout<<"R";
		 for (std::string::size_type i=0; i<tempInstructionDetails.column.length(); ++i)
		    std::cout << toupper((tempInstructionDetails.column)[i],loc);
		    cout<<endl;
			cycleNumber++;
			programCounter++;
			preChargeFlag=1;
		}
		else if(tempInstructionDetails.instructionType == "S")
		{
			cout<<"W";
		 for (std::string::size_type i=0; i<tempInstructionDetails.column.length(); ++i)
		    std::cout << toupper((tempInstructionDetails.column)[i],loc);
		    cout<<endl;
			cycleNumber++;
			programCounter++;
			preChargeFlag=1;
		}
		if(programCounter<sizeOfInput)
		{
			if(inputDetailsMap.at(programCounter).row == inputDetailsMap.at(programCounter-1).row )
			{
				preChargeFlag=0;
				if(inputDetailsMap.at(programCounter).instructionType=="S" && inputDetailsMap.at(programCounter-1).instructionType=="L")
				{
					cycleNumber = cycleNumber+3;
					cout<<"I3"<<endl;
				}
			}
		}
		if(preChargeFlag==1)
		{
			if(inputDetailsMap.at(programCounter-1).instructionType == "L")
			{
				if(cycleNumber+2>30)
					cout<<"I2"<<endl;
				else
					cout<<"I"<<30 - cycleNumber<<endl;
			}
			else
			{
				if(cycleNumber<30)
					cout<<"I"<<30 - cycleNumber<<endl;
			}
			cout<<"P"<<endl;
			if(programCounter<sizeOfInput)
			{
				cout<<"I19"<<endl;
			}
			cycleNumber = 0;
			preChargeFlag=0;
			activationFlag = 1;
		}
	}
}
/*
	Author: ADitya Manjrekar
	Description: 	Reading line by line from the ext file and inserting the lines in the input map
*/
int readFromFile(map<int,string> &input)
{
	char line[MAX_LENGTH]="";
	int inputCounter = 0;
	int flag = 1;
	while(cin>>line)
	{
		input.insert(make_pair(inputCounter,line));
		inputCounter++;
	}
	return flag;
}
/*
	Author: ADitya Manjrekar
	Description: 	extracting the brach address , direction and the destination address	and storting it in the inputDetails struct.
*/
int inputDetailsExtraction(const map<int,string> input,map<int,InstructionDetails> &inputDetailsMap)
{
	int totalNumberOfInputs = input.size();
	int counter =0;
	while (counter<totalNumberOfInputs)
	{
		InstructionDetails temp;
		string tempInput = "";
		tempInput = input.at(counter);
		temp.instructionType = tempInput.substr(0,1);
		temp.row = tempInput.substr(1,5);
		temp.column = tempInput.substr(6,3);
		inputDetailsMap.insert(make_pair(counter,temp));	
		counter++;
	}
	return 1;
}
/*
	Author: ADitya Manjrekar
	Description: 	Storing the latency during transition from each stage
*/
int cycleTransition(map<string,int>& latency)
{
	latency.insert(make_pair("AP",30));
	latency.insert(make_pair("AR",12));
	latency.insert(make_pair("AW",12));
	latency.insert(make_pair("RR",1));
	latency.insert(make_pair("RW",4));
	latency.insert(make_pair("RP",3));
	latency.insert(make_pair("WR",1));
	latency.insert(make_pair("WW",1));
	latency.insert(make_pair("WP",1));
	latency.insert(make_pair("PA",20));
	return 1;
}
