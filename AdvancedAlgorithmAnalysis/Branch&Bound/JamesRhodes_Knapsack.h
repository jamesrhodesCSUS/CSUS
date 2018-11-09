
//#define KNAPSACK_DEBUG

#define INVALID_VALUE -1
#define NO_SLACK -1

enum UPPER_BOUND { UB1, UB2, UB3, UB4};

class KnapsackInstance
{
private:
	int itemCnt; //Number of items
	int cap; //The capacity
	int* weights;//An array of weights
	int* values;//An array of values

public:
	KnapsackInstance(int itemCnt_);
	~KnapsackInstance();

	void Generate();

	int GetItemCnt();
	int GetItemWeight(int itemNum);
	int GetItemValue(int itemNum);
	int GetCapacity();
	void Print();
};

class KnapsackSolution
{
private:
	bool* isTaken;
	int value;
	int wght;
	int untakenValue;

	KnapsackInstance* inst;


public:
	KnapsackSolution(KnapsackInstance* inst);
	~KnapsackSolution();

	bool operator == (KnapsackSolution& otherSoln);
	
	void TakeItem(int itemNum);
	void DontTakeItem(int itemNum);
	void UndoTakeItem(int itemNum);
	void UndoDontTakeItem(int itemNum);

	int ComputeValue();
	int ComputeFracKS(int itemNum);
	int ComputeFittingItems(int itemNum);

	int GetValue();
	int GetWeight();
	int GetUntakenValue();
	int GetRemainingWeight();

	void Print(std::string str);
	void Copy(KnapsackSolution* otherSoln);
};

// Dynamic programming solver
class KnapsackDPSolver
{
private:
	KnapsackInstance* inst;
	KnapsackSolution* soln;
	
	int **valueTable;
	
	int _row, _column;

public:
	KnapsackDPSolver();
	~KnapsackDPSolver();
	
	void Solve(KnapsackInstance* inst, KnapsackSolution* soln);
	
	void GenerateTable();
	void FindSolution();
	void ConstructSolution();
};


// Brute-force solver
class KnapsackBFSolver
{
protected:
	KnapsackInstance* inst;
	KnapsackSolution* crntSoln;
	KnapsackSolution* bestSoln;

	virtual void FindSolns(int itemNum);
	virtual void CheckCrntSoln();

public:
	KnapsackBFSolver();
	~KnapsackBFSolver();
	virtual void Solve(KnapsackInstance* inst, KnapsackSolution* soln);
};


// Backtracking solver
class KnapsackBTSolver: public KnapsackBFSolver
{
protected:
	void FindSolns(int itemNum);
	
public:
	KnapsackBTSolver();
	~KnapsackBTSolver();
	void Solve(KnapsackInstance* inst, KnapsackSolution* soln);
};

// Branch-and-Bound solver
class KnapsackBBSolver: public KnapsackBFSolver
{
private:
	int totValSum;

protected:
	enum UPPER_BOUND ub;

public:
	KnapsackBBSolver(enum UPPER_BOUND ub_);
	~KnapsackBBSolver();
	void Solve(KnapsackInstance* inst, KnapsackSolution* soln);
	void FindSolutions(int i);
};

