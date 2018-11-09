#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/timeb.h>
#include <string.h>
#include <string>
#include <iostream>
#include <algorithm>
#include "JamesRhodes_Knapsack.h"

#define TIMEB struct timeb
#define FTIME ftime
#define UDT_TIME long
#define MAX_SIZE_TO_PRINT 25

UDT_TIME gRefTime = 0;

UDT_TIME GetMilliSecondTime(TIMEB timeBuf);
void SetTime(void);
UDT_TIME GetTime(void);

int main(int argc, char* argv[])
{
	srand (time(NULL));
	UDT_TIME time, BFTime;
    float speedup;
	int itemCnt;
	KnapsackInstance* inst; //a Knapsack instance object
	KnapsackDPSolver DPSolver; //dynamic programming solver
	KnapsackBFSolver BFSolver; //brute-force solver
	KnapsackBTSolver BTSolver; //backtracking solver
	KnapsackBBSolver BBSolver1(UB1); //branch-and-bound solver with UB1
	KnapsackBBSolver BBSolver2(UB2); //branch-and-bound solver with UB2
	KnapsackBBSolver BBSolver3(UB3); //branch-and-bound solver with UB3
	KnapsackSolution *DPSoln, *BFSoln, *BTSoln, *BBSoln1, *BBSoln2, *BBSoln3;

	//Use only with command line
	/*
    if(argc != 2) {
        printf("Invalid Number of command-line arguments\n");
	    exit(1);
    }
    */
    //itemCnt = atoi(argv[1]);
    itemCnt = 25;
    if(itemCnt < 1) {
        printf("Invalid number of items\n");
        exit(1);
    }

	inst = new KnapsackInstance(itemCnt);
	DPSoln = new KnapsackSolution(inst);
	BFSoln = new KnapsackSolution(inst);
	BTSoln = new KnapsackSolution(inst);
	BBSoln1 = new KnapsackSolution(inst);
	BBSoln2 = new KnapsackSolution(inst);
	BBSoln3 = new KnapsackSolution(inst);
	
	inst->Generate();
	inst->Print();

	SetTime();
	DPSolver.Solve(inst,DPSoln);
	time = GetTime();
	printf("\n\nSolved using dynamic programming (DP) in %ld ms. Optimal value = %d",time, DPSoln->GetValue());
	if(itemCnt <= MAX_SIZE_TO_PRINT)
		DPSoln->Print("Dynamic Programming Solution");


	SetTime();
	BFSolver.Solve(inst,BFSoln);
	BFTime = time = GetTime();
	printf("\n\nSolved using brute-force enumeration (BF) in %ld ms. Optimal value = %d",time, BFSoln->GetValue());
	if(itemCnt <= MAX_SIZE_TO_PRINT)
		BFSoln->Print("Brute-Force Solution");
	if(*DPSoln == *BFSoln)
		printf("\nSUCCESS: DP and BF solutions match");
	else
		printf("\nERROR: DP and BF solutions mismatch");
		

	SetTime();
	BTSolver.Solve(inst,BTSoln);
	time = GetTime();
	printf("\n\nSolved using backtracking (BT) in %ld ms. Optimal value = %d",time, BTSoln->GetValue());
	if(itemCnt <= MAX_SIZE_TO_PRINT)
		BTSoln->Print("Backtracking Solution");

	if(*BFSoln == *BTSoln)
		printf("\nSUCCESS: BF and BT solutions match");
	else
		printf("\nERROR: BF and BT solutions mismatch");
    speedup = time==0? 0 : 100.0*(BFTime-time)/(float)BFTime;
	printf("\nSpeedup of BT relative to BF is %.2f%c",speedup,'%');

	SetTime();
	BBSolver1.Solve(inst,BBSoln1);
	time = GetTime();
	printf("\n\nSolved using branch-and-bound (BB) with UB1 in %ld ms. Optimal value = %d",time, BBSoln1->GetValue());
	if(itemCnt <= MAX_SIZE_TO_PRINT)
		BBSoln1->Print("BB-UB1 Solution");

	if(*BFSoln == *BBSoln1)
		printf("\nSUCCESS: BF and BB-UB1 solutions match");
	else
		printf("\nERROR: BF and BB-UB1 solutions mismatch");
    speedup = time==0? 0 : 100.0*(BFTime-time)/(float)BFTime;
	printf("\nSpeedup of BB-UB1 relative to BF is %.2f%c",speedup,'%');

	SetTime();
	BBSolver2.Solve(inst,BBSoln2);
	time = GetTime();
	printf("\n\nSolved using branch-and-bound (BB) with UB2 in %ld ms. Optimal value = %d",time, BBSoln2->GetValue());
	if(itemCnt <= MAX_SIZE_TO_PRINT)
		BBSoln2->Print("BB-UB2 Solution");

	if(*BFSoln == *BBSoln2)
		printf("\nSUCCESS: BF and BB-UB2 solutions match");
	else
		printf("\nERROR: BF and BB-UB2 solutions mismatch");
    speedup = time==0? 0 : 100.0*(BFTime-time)/(float)BFTime;
	printf("\nSpeedup of BB-UB2 relative to BF is %.2f%c",speedup,'%');


	SetTime();
	BBSolver3.Solve(inst,BBSoln3);
	time = GetTime();
	printf("\n\nSolved using branch-and-bound (BB) with UB3 in %ld ms. Optimal value = %d",time, BBSoln3->GetValue());
	if(itemCnt <= MAX_SIZE_TO_PRINT)
		BBSoln3->Print("BB-UB3 Solution");

	if(*BFSoln == *BBSoln3)
		printf("\nSUCCESS: BF and BB-UB3 solutions match");
	else
		printf("\nERROR: BF and BB-UB3 solutions mismatch");
    speedup = time==0? 0 : 100.0*(BFTime-time)/(float)BFTime;
	printf("\nSpeedup of BB-UB3 relative to BF is %.2f%c",speedup,'%');
	
	delete inst;
	delete DPSoln;
	delete BFSoln;
	delete BTSoln;
	delete BBSoln1;
	delete BBSoln2;
	delete BBSoln3;

	printf("\n\nProgram Completed Successfully\n");

	return 0;
}
/********************************************************************/

KnapsackInstance::KnapsackInstance(int itemCnt_)
{
	itemCnt = itemCnt_;

	weights = new int[itemCnt+1];
	values = new int[itemCnt+1];
	cap = 0;
}
/********************************************************************/
	
KnapsackInstance::~KnapsackInstance()
{
	delete [] weights;
	delete [] values;
}
/********************************************************************/

void KnapsackInstance::Generate()
{
    int i, wghtSum;  
        
    weights[0] = 0;
    values[0] = 0;
        
    wghtSum = 0;
    for(i=1; i<=itemCnt; i++)
    {
        weights[i] = rand()%100 + 1;
        wghtSum += weights[i]; 
    }
    
    std::sort(weights+1, weights+itemCnt+1, std::less<int>());

    for(i=1; i<=itemCnt; i++)
    {
    	values[i] = weights[i] + 10;
	}
    cap = wghtSum/2;
}
/********************************************************************/

int KnapsackInstance::GetItemCnt()
{
	return itemCnt;
}
/********************************************************************/

int KnapsackInstance::GetItemWeight(int itemNum)
{
	return weights[itemNum];
}
/********************************************************************/

int KnapsackInstance::GetItemValue(int itemNum)
{
	return values[itemNum];
}
/********************************************************************/

int KnapsackInstance::GetCapacity()
{
	return cap;
}
/********************************************************************/

void KnapsackInstance::Print()
{
	int i;

	printf("Number of items = %d, Capacity = %d\n",itemCnt, cap);
	printf("Weights: ");
	for(i=1; i<=itemCnt; i++)
	{
		printf("%d ",weights[i]);
	}
	printf("\nValues: ");
	for(i=1; i<=itemCnt; i++)
	{
		printf("%d ",values[i]);
	}
	printf("\n");
}
/*****************************************************************************/

KnapsackSolution::KnapsackSolution(KnapsackInstance* inst_)
{
	int i, itemCnt = inst_->GetItemCnt();

	inst = inst_;
	isTaken = new bool[itemCnt+1];
	value = INVALID_VALUE;
	wght = 0;

	for(i=1; i<=itemCnt; i++)
	{
		isTaken[i] = false;
	}
}
/********************************************************************/

KnapsackSolution::~KnapsackSolution()
{
	delete [] isTaken;
}
/********************************************************************/

bool KnapsackSolution::operator== (KnapsackSolution& otherSoln)
{
	return value == otherSoln.value;
}
/********************************************************************/

void KnapsackSolution::TakeItem(int itemNum)
{
	if (value == INVALID_VALUE)
		value = 0;

	isTaken[itemNum] = true;
	wght += inst->GetItemWeight(itemNum);
	value += inst->GetItemValue(itemNum);
}
/********************************************************************/
	
void KnapsackSolution::DontTakeItem(int itemNum)
{
 	int remainingWeight = inst->GetItemWeight(itemNum);

	isTaken[itemNum] = false;
	untakenValue += inst->GetItemValue(itemNum);

}
/********************************************************************/

void KnapsackSolution::UndoTakeItem(int itemNum)
{
	wght-=inst->GetItemWeight(itemNum);
	value-=inst->GetItemValue(itemNum);
	
	if (value == 0)
		value = INVALID_VALUE;
}

void KnapsackSolution::UndoDontTakeItem(int itemNum)
{
	untakenValue -= inst->GetItemValue(itemNum);
}
/********************************************************************/

int KnapsackSolution::ComputeValue()
{
	int i, itemCnt = inst->GetItemCnt(), weight = 0;

	value = 0;
	for(i=1; i<=itemCnt; i++)
	{
		if(isTaken[i] == true)
		{
			weight += inst->GetItemWeight(i);
			if(weight > inst->GetCapacity())
			{
				value = INVALID_VALUE;
				break;
			}
			value += inst->GetItemValue(i);
		}
	}
	return value;
}

int KnapsackSolution::ComputeFittingItems(int itemNum)
{
	int i, itemCnt = inst->GetItemCnt(), UBValue=0;
	int remainingWeight = inst->GetCapacity()-wght;
	for (i = itemNum; i<=itemCnt; i++)
	{
		if (inst->GetItemWeight(i) <= remainingWeight)
			UBValue += inst->GetItemValue(i);
	}
	return UBValue;
}

int KnapsackSolution::ComputeFracKS(int itemNum)
{
	int i, itemCnt = inst->GetItemCnt(), remainingWeight = inst->GetCapacity()-wght;
	int fracValue=0;
	for(i = itemNum; i<=itemCnt; i++)
	{
		if (inst->GetItemWeight(i) <= remainingWeight)
		{
			fracValue += inst->GetItemValue(i);
			remainingWeight -= inst->GetItemWeight(i);
		}
		else
		{
			fracValue += (inst->GetItemValue(i) * remainingWeight) / inst->GetItemWeight(i);
			break;
		}
	}
	return fracValue;
}
/********************************************************************/

int KnapsackSolution::GetValue()
{
	return value;
}

int KnapsackSolution::GetWeight()
{
	return wght;
}

int KnapsackSolution::GetUntakenValue()
{
	return untakenValue;
}

int KnapsackSolution::GetRemainingWeight()
{
	return inst->GetCapacity()-wght;
}
/********************************************************************/

void KnapsackSolution::Copy(KnapsackSolution* otherSoln)
{
	int i, itemCnt = inst->GetItemCnt();

	for(i=1; i<=itemCnt; i++)
	{
		isTaken[i] = otherSoln->isTaken[i];
	}
	value = otherSoln->value;
}
/********************************************************************/

void KnapsackSolution::Print(std::string title)
{
	int i, itemCnt = inst->GetItemCnt();

	printf("\n%s: ",title.c_str());
	for(i=1; i<=itemCnt; i++)
	{
		if(isTaken[i] == true)
			printf("%d ",i);
	}
	printf("\nValue = %d\n",value);
}
/*****************************************************************************/

KnapsackBFSolver::KnapsackBFSolver()
{
	crntSoln = NULL;
}
/********************************************************************/

KnapsackBFSolver::~KnapsackBFSolver()
{
	if(crntSoln != NULL)
		delete crntSoln;
}
/********************************************************************/

void KnapsackBFSolver::Solve(KnapsackInstance* inst_, KnapsackSolution* soln_)
{
	inst = inst_;	
	bestSoln = soln_;
	crntSoln = new KnapsackSolution(inst);
	FindSolns(1);
}
/********************************************************************/

void KnapsackBFSolver::FindSolns(int itemNum)
{
	int itemCnt = inst->GetItemCnt();

	if(itemNum == itemCnt + 1)
	{
		CheckCrntSoln();
		return;
	}
	crntSoln->DontTakeItem(itemNum);
	FindSolns(itemNum+1);
	crntSoln->TakeItem(itemNum);
	FindSolns(itemNum+1);

}
/********************************************************************/

void KnapsackBFSolver::CheckCrntSoln()
{
	int crntVal = crntSoln->ComputeValue();

#ifdef KNAPSACK_DEBUG
	printf("\nChecking solution ");
	crntSoln->Print(" ");
#endif

	if(crntVal == INVALID_VALUE)
		return;

	if(bestSoln->GetValue() == INVALID_VALUE) //The first solution is initially the best solution
		bestSoln->Copy(crntSoln);
	else
	{
		if(crntVal > bestSoln->GetValue())
   			bestSoln->Copy(crntSoln);
	}
}

KnapsackDPSolver::KnapsackDPSolver()
{
	soln = NULL;
}

KnapsackDPSolver::~KnapsackDPSolver()
{
	for(int i = 0; i < inst->GetCapacity(); ++i)
    	delete [] valueTable[i];
	delete [] valueTable;
}

void KnapsackDPSolver::Solve(KnapsackInstance* inst_, KnapsackSolution* soln_)
{
	inst = inst_;
	soln = soln_;
	
	//The plus one is used to make sure that we include row 0
	//If cap == 5, we need 6 spots, 0 through 5
	_row = inst->GetItemCnt() + 1;
	_column = inst->GetCapacity() + 1;
	
	GenerateTable();
	FindSolution();
}

void KnapsackDPSolver::GenerateTable()
{
	// Create a dynamic array of pointers
    valueTable = new int* [_row];

    // Create a row for every pointer
    for (int i=0; i<_row; ++i)
       valueTable[i] = new int[_column];

	//Initialize first row and column = to 0;
	for(int i=0; i<_row; i++)
		valueTable[i][0] = 0;

	for(int i=0; i<_column; i++)
		valueTable[0][i] = 0;
}

void KnapsackDPSolver::FindSolution()
{
	for (int i = 1; i < _row; i++)
		for (int j = 1; j < _column; j++)
			if (j < inst->GetItemWeight(i))
				valueTable[i][j] = valueTable[i-1][j];
			else
				if (valueTable[i-1][j] > (valueTable[i-1][j-(inst->GetItemWeight(i))] + inst->GetItemValue(i)))
					valueTable[i][j] = valueTable[i-1][j];
				else
					valueTable[i][j] = (valueTable[i-1][j-(inst->GetItemWeight(i))] + inst->GetItemValue(i));
	
	ConstructSolution();
	
#ifdef KNAPSACK_DEBUG
	for (int i=0; i<_column; i++)
	{
		for(int j=0; j<_row; j++)
			std::cout<<"  "<<valueTable[j][i]<<"  ";
	std::cout<<std::endl;
	}
#endif
}

void KnapsackDPSolver::ConstructSolution()
{
	int i = _row - 1;
	int j = _column - 1;
	while (i>0 && j>0)
		if (valueTable[i][j] != valueTable[i-1][j])
		{
			soln->TakeItem(i);
			j -= inst->GetItemWeight(i);
			--i;
		}
		else
		   --i;
}
/*****************************************************************************/

KnapsackBTSolver::KnapsackBTSolver()
{
	crntSoln = NULL;
}
/********************************************************************/

KnapsackBTSolver::~KnapsackBTSolver()
{

}
/********************************************************************/

void KnapsackBTSolver::Solve(KnapsackInstance* inst_, KnapsackSolution* soln_)
{
	inst = inst_;
	bestSoln = soln_;
	crntSoln = new KnapsackSolution(inst);
	FindSolns(1);
}
/*****************************************************************************/

void KnapsackBTSolver::FindSolns(int itemNum)
{
	if (crntSoln->GetWeight() > inst->GetCapacity())
		return;

	if(itemNum == inst->GetItemCnt() + 1)
	{
		if(crntSoln->GetValue() > bestSoln->GetValue())
			bestSoln->Copy(crntSoln);
		return;
	}
	
	crntSoln->DontTakeItem(itemNum);
	FindSolns(itemNum+1);
	
	crntSoln->TakeItem(itemNum);
	FindSolns(itemNum+1);
	
	crntSoln->UndoTakeItem(itemNum);
}
/********************************************************************/

KnapsackBBSolver::KnapsackBBSolver(enum UPPER_BOUND ub_)
{
	ub = ub_;
	totValSum = 0;
}
/********************************************************************/

KnapsackBBSolver::~KnapsackBBSolver()
{

}
/********************************************************************/

void KnapsackBBSolver::Solve(KnapsackInstance* inst_, KnapsackSolution* soln_)
{
	inst = inst_;
	bestSoln = soln_;
	crntSoln = new KnapsackSolution(inst);
	
	for (int i=0; i<=inst->GetItemCnt(); i++)
		totValSum += inst->GetItemValue(i);

	FindSolutions(1);
}

void KnapsackBBSolver::FindSolutions(int i)
{
	if (crntSoln->GetWeight() > inst->GetCapacity())
		return;
		
	if (i == inst->GetItemCnt() +1)
	{
		if(crntSoln->GetValue() > bestSoln->GetValue())
			bestSoln->Copy(crntSoln);
		return;
	}
	
	if (ub == UB1)
	{
		if (totValSum - crntSoln->GetUntakenValue() <= bestSoln->GetValue())
			return;
	}
	else if (ub == UB2)
	{
		if (crntSoln->GetValue() + crntSoln->ComputeFittingItems(i) <= bestSoln->GetValue())
			return;
	}
	else
	{
		if (crntSoln->GetValue() + crntSoln->ComputeFracKS(i) <= bestSoln->GetValue())
			return;
	}

	crntSoln->DontTakeItem(i);
	FindSolutions(i+1);
	crntSoln->UndoDontTakeItem(i);

	crntSoln->TakeItem(i);
	FindSolutions(i+1);
	crntSoln->UndoTakeItem(i);
}
/*****************************************************************************/

UDT_TIME GetCurrentTime(void)
{
	UDT_TIME crntTime=0;

	TIMEB timeBuf;
	FTIME(&timeBuf);
    crntTime = GetMilliSecondTime(timeBuf);

	return crntTime;
}
/********************************************************************/

void SetTime(void)
{
	gRefTime = GetCurrentTime();
}
/********************************************************************/

UDT_TIME GetTime(void)
{
	UDT_TIME crntTime = GetCurrentTime();

	return (crntTime - gRefTime);
}
/********************************************************************/

UDT_TIME GetMilliSecondTime(TIMEB timeBuf)
{
	UDT_TIME mliScndTime;

	mliScndTime = timeBuf.time;
	mliScndTime *= 1000;
	mliScndTime += timeBuf.millitm;
	return mliScndTime;
}
/*****************************************************************************/




