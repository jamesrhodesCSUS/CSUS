#include <stdlib.h>
#include <time.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <stack>
#include <math.h>
using namespace std;

const int MAX_SIZE = 100000000;

// Set this to true if you wish the arrays to be printed.
const bool OUTPUT_DATA = false;

void ReadInput(string& sortAlg, int& size);

void GenerateSortedData(int data[], int size);
void GenerateNearlySortedData(int data[], int size);
void GenerateReverselySortedData(int data[], int size);
void GenerateRandomData(int data[], int size);

void Sort(int data[], int size, string sortAlg, char* dataType);

void InsertionSort(int data[], int size);

void MergeSort(int data[], int lo, int hi);
void Merge(int data[], int lo, int high, int mid);

int QuickSort(int data[], int lo, int hi);
int Quick3Sort(int data[], int lo, int hi, int MaxDepth);
int QuickISort(int data[], int lo, int hi);

void QuickInsertionSort(int data[], int lo, int hi);

int Partition(int data[], int lo, int hi);
int randomizedPartition(int data[], int lo, int hi);

int MedianOf3(int data[], int lo, int hi);

void LibSort(int data[], int size);

void quickSortIterative (int data[], int end);

void Swap(int &x, int &y);

bool IsSorted(int data[], int size);
bool IsSorted(int data[], int start, int end);

void printData(int data[], int size, string title);

bool isReverse(int data[], int size);

void reverseData(int data[], int lo, int hi);

int utilcheck(int data[], int lo, int hi, int MaxDepth);

bool almostSort(int A[], int n);

//Used for builtin quicksort
int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

int main(void)
{
	int size;
	string sortAlg;
	ReadInput(sortAlg, size);
	
	srand (time(NULL));  //Used to seed the random
	
	int * data = new int[size];
	if( data == NULL)
	{
		cout << "\n Memory allocation error." << endl;
		exit(1);
	}
	
	GenerateSortedData(data, size);
	Sort(data, size, sortAlg,"Sorted Data");

	GenerateNearlySortedData(data, size);
	Sort(data, size, sortAlg,"Nearly Sorted Data");
	
	GenerateReverselySortedData(data, size);
	Sort(data, size, sortAlg,"Reversely Sorted Data");
	
	GenerateRandomData(data, size);
	Sort(data, size, sortAlg,"Random Data");
		
	cout << "\nProgram Completed Successfully." << endl;;
	
	delete [] data;
	
	return 0;
}
/********************************************************************/


void ReadInput(string& sortAlg, int& size)
{
	cout << "  I:\tInsertion Sort" << endl;
	cout << "  M:\tMergeSort" << endl;
	cout << "  Q:\tQuickSort" << endl;
	cout << "  L:\tLibSort" << endl;
	cout << "Enter sorting algorithm: ";
	cin >> sortAlg;
	string sortAlgName;
		
	if(sortAlg == "I" || sortAlg == "i")
		sortAlgName = "Insertion Sort";
	else if(sortAlg == "M" || sortAlg == "m")
		sortAlgName = "MergeSort";
	else if(sortAlg == "Q" || sortAlg == "q")
		sortAlgName = "QuickSort";
	else if(sortAlg == "L" || sortAlg == "l")
		sortAlgName = "LibSort";
	else {
		cout << "\nUnrecognized sorting algorithm Code: " << sortAlg << endl;
		exit(1);
	}
	
	cout << "Enter input size: ";
	cin >> size;
	//size = 1000000;
	
	cout << "\nSorting Algorithm: " << sortAlgName;
	cout << "\nInput Size = " << size << endl;
	cout << endl;
}
/******************************************************************************/

void GenerateSortedData(int data[], int size)
{
	int i;
	
	for(i=0; i<size; i++)
		data[i] = i * 3 + 5;
}
/*****************************************************************************/

void GenerateNearlySortedData(int data[], int size)
{
	int i;
	
	GenerateSortedData(data, size);
	
	for(i=0; i<size; i++)
		if(i % 10 == 0)
			if(i+1 < size)
				data[i] = data[i+1] + 7;
}
/*****************************************************************************/

void GenerateReverselySortedData(int data[], int size)
{
	int i;
	
	for(i = 0; i < size; i++)
		data[i] = (size-i) * 2 + 3;
}
/*****************************************************************************/

void GenerateRandomData(int data[], int size)
{
	int i;
	
	for(i = 0; i < size; i++)
		data[i] = rand();
}
/*****************************************************************************/

void Sort(int data[], int size, string sortAlg, char* dataType)
{
	int QDepth;
	//This is used as a safety net
	//So I don't get too deep into my recursive calls
	//This is only used when you have an input size over 5 million or so
	int MaxDepth = floor(2*(log(size)));
	cout << endl << dataType << ":";
		
	if (OUTPUT_DATA)
		printData(data, size, "Data before sorting:");
	
	// Sorting is about to begin ... start the timer!
	clock_t start = clock();
	
	if(sortAlg == "I" || sortAlg == "i")
		InsertionSort(data, size);
	else if(sortAlg == "M" || sortAlg == "m")
		MergeSort(data, 0, size-1);
	else if(sortAlg == "Q" || sortAlg == "q")
	{
	    /************************************************
		*These are my Quick Sorts! Leave one uncommented*
		************************************************/
	    
        //This is for regular QuickSort with random partition
		//QDepth = QuickSort(data, 0, size-1);
		
		//This is for QuickSort with a random partition
		//AND using Insertion for 40 or less items
		//QDepth = QuickISort(data, 0, size-1);
		
		//This is for a 3 way median
		//AND Insertion sort for 40 or less items
		//This is also my BEST one
		//QDepth = utilcheck(data, 0, size-1, MaxDepth);
		
		//This is the build in QuickSort
		qsort(data, size, (sizeof (int)), compare);
		
		//This is my iterative QuickSort
		//quickSortIterative(data, size-1);
		
		/************************************************
		*These are my Quick Sorts! Leave one uncommented*
		************************************************/
	}
	else if(sortAlg == "L" || sortAlg == "l")
		LibSort(data, size);
	else
	{
		cout << "Invalid sorting algorithm!" << endl;
		exit(1);
	}
	
	// Sorting has finished ... stop the timer!
	clock_t end = clock();
 	double elapsed = (((double) (end - start)) / CLOCKS_PER_SEC) * 1000;
	
	if (OUTPUT_DATA)
		printData(data, size, "Data after sorting:");
	
	if (IsSorted(data, size))
    {
		cout << "\nCorrectly sorted " << size << " elements in " << elapsed << "ms";
		if (sortAlg == "Q" || sortAlg == "q"){
		   cout<<endl<<"The largest depth was ";
		   if (QDepth != 0)
		      cout<<QDepth<<endl;
           else
               cout<<"unknown!"<<endl;
	    }
    }
	else
		cout << "ERROR!: INCORRECT SORTING!" << endl;
	cout << "\n-------------------------------------------------------------\n";
}
/*****************************************************************************/

bool IsSorted(int data[], int size)
{
	// Array has one or no element
    if (size == 0 || size == 1)
        return true;
 
    for (int i = 1; i < size; i++) 
        // Unsorted pair found
        if (data[i-1] > data[i])
            return false;
 
    // No unsorted pair found
    return true;
}
/*****************************************************************************/

void InsertionSort(int data[], int size)
{
	int i, key, j;
	for(i=1; i < size; i++)
    {
		key = data[i];
		j = i-1;
		
		while (j >= 0 && data[j] > key)
        {
			data[j+1] = data[j];
			j = j-1;
		}
		data[j+1] = key;
	}
}
/*****************************************************************************/

void MergeSort(int data[], int lo, int hi)
{
	if (lo < hi)
	{
		bool lSorted;
		bool rsorted;
		int mid=lo+(hi-lo)/2;
		if (!IsSorted(data, lo, mid))
			MergeSort(data, lo, mid);
		if (!IsSorted(data, mid+1, hi))
			MergeSort(data, mid+1, hi);
		Merge(data, lo, hi, mid);
	}
}

void Merge(int data[], int lo, int hi, int mid)
{
	int i, j, k;
	int * temp = new int[hi-lo+1];
	i = lo;
	k = 0;
	j = mid + 1;
 
	// Merge the two parts into temp[].
	while (i <= mid && j <= hi)
	{
		if (data[i] < data[j])
		{
			temp[k] = data[i];
			k++;
			i++;
		}
		else
		{
			temp[k] = data[j];
			k++;
			j++;
		}
	}
 
	// Insert all the remaining values from i to mid into temp[].
	while (i <= mid)
	{
		temp[k] = data[i];
		k++;
		i++;
	}
 
	// Insert all the remaining values from j to high into temp[].
	while (j <= hi)
	{
		temp[k] = data[j];
		k++;
		j++;
	}

	// Assign sorted data stored in temp[] to a[].
	for (i = lo; i <= hi; i++)
	{
		data[i] = temp[i-lo];
	}
	
	delete [] temp;
}
/*****************************************************************************/

int QuickSort(int data[], int lo, int hi)
{
	if (lo < hi)
    {
    	int pivot = randomizedPartition(data, lo, hi);
     	int depth1=QuickSort(data, lo, pivot - 1);
        int depth2=QuickSort(data, pivot + 1, hi);
        
        //Used to kep track of Depth
        if (depth1 > depth2)
    	    return (depth1+1);
	    else
	        return (depth2+1);
    }
    //Base Case
    return 0;
}

//Insertion sort just needs the size, this one needs to know
//what part of data to sor (from lo - hi)
int QuickISort(int data[], int lo, int hi)
{
	if (lo < hi)
	{
		if((hi - lo < 45))
			QuickInsertionSort(data, lo, hi+1);
  		else
        {
  			int p = randomizedPartition(data, lo, hi);
  			int depth1 = QuickISort(data, lo, p-1);
  			int depth2 = QuickISort(data, p+1, hi);
  			
  			if (depth1 >= depth2)
    	       return (depth1+1);
            else
	           return (depth2+1);
		}
	}
	return 0;
}

int Quick3Sort(int data[], int lo, int hi, int limit)
{
    //THIS IS USED IF YOU ARE GETTING TOO LARGE OF A DEPTH
   	//This is only used when you have an input size over 5 million or so
    if(limit==0)
    {
        int * begin = &data[lo];
        int * end = &data[hi];
        make_heap(begin, end+1);
        sort_heap(begin, end+1);
        return 0;
    }

    if (lo < hi)
	{
        if((hi - lo) < 45)
    		QuickInsertionSort(data, lo, hi+1);
        else
        {
			int p = MedianOf3(data, lo, hi);
			int depth1, depth2;
			
	     	depth1 = Quick3Sort(data, lo, p-1, limit-1);
			depth2 = Quick3Sort(data, p+1, hi, limit-1);
    		
    		if (depth1 >= depth2)
    	       return (depth1+1);
            else
               return (depth2+1);
    	}
	}
	return 0;
}

void QuickInsertionSort(int data[], int lo, int hi){
	int i, j, val;
	for (i = lo + 1; i < hi; i++)
	{
        val = data[i];
        j = i - 1;
        while (j >= 0 && val < data[j])
        {
            data[j + 1] = data[j];
            j--;
	    }
 		data[j + 1] = val;
   }
}

int randomizedPartition(int data[], int lo, int hi)
{
	int randomIndex = rand() % (hi-lo) + lo;
	Swap(data[hi], data[randomIndex]);
	return Partition(data, lo, hi);
}

int Partition(int data[], int lo, int hi)
{
    //The far right index is always the pivot
	int pivot = data[hi];
    int i = (lo - 1);
 
    for (int j = lo; j <= hi - 1; j++)
        if (data[j] <= pivot)
        {
            i++;
            Swap(data[i], data[j]);
        }
    Swap(data[i + 1], data[hi]);
    return (i + 1);
}

inline
int MedianOf3(int data[], int lo, int hi)
{
    int mid = lo+(hi-lo)/2;

    if (data[lo] > data[mid])
       Swap(data[mid], data[lo]);
    
    if (data[lo] > data[hi])
       Swap(data[lo], data[hi]);
       
    if (data[mid] > data[hi])
       Swap(data[hi], data[mid]);
       
    swap(data[mid], data[hi]);
    return Partition(data, lo, hi);
}
/*****************************************************************************/

void quickSortIterative (int data[], int end)
{
    stack<pair<int, int> > stk;

    // get starting and ending index of given array (vector)
    int start = 0;

    // push array start and end index to the stack
    stk.push(make_pair(start, end));

    // run till stack is not empty
    while (!stk.empty())
    {
        // pop top pair from the list and get sub-array starting 
        // and ending indices
        start = stk.top().first, end = stk.top().second;
        stk.pop();

        // rearrange the elements across pivot
        int pivot = randomizedPartition(data, start, end);

        // push sub-array indices containing elements that are 
        // less than current pivot to stack
        if (pivot - 1 > start)
            stk.push(make_pair(start, pivot - 1));

        // push sub-array indices containing elements that are 
        // more than current pivot to stack
        if (pivot + 1 < end)
            stk.push(make_pair(pivot + 1, end));
    }
}
/*****************************************************************************/

void LibSort(int data[], int size)
{
	sort(data, data+size);
}
/*****************************************************************************/

void Swap(int &x, int &y)
{
	int temp = x;
	x = y;
	y = temp;
}
/*****************************************************************************/

void printData(int data[], int size, string title) {
	int i;

	cout << endl << title << endl;
	for(i=0; i<size; i++)
	{
		cout << data[i] << " ";
		if(i%10 == 9 && size > 10)
			cout << endl;
	}
}

int utilcheck(int data[], int lo, int hi, int MaxDepth)
{
	if (IsSorted(data, hi))
		return 0;
	if (isReverse(data, hi))
	{
		reverseData(data, lo, hi);
		return 0;
	}
	if(almostSort(data, hi))
	{
		InsertionSort(data, hi);
		return 0;
	}

	return Quick3Sort(data, lo, hi, MaxDepth);
}

bool isReverse(int data[], int size)
{
	for (int i = size; i > 0; i--)
    	if (data[i] > data[i-1]){
    		return false;
		}
	return true;
}

void reverseData(int data[], int lo, int hi)
{
    while (lo <= hi)
    {
        Swap(data[lo], data[hi]);
        lo++;
        hi--;
    }
}

bool almostSort(int data[], int n)
{
	int * A = new int[n+1];
	for (int i=0; i<n+1; i++)
		A[i]=data[i];
	
    for (int i = 0; i < n - 1; i++) {
        if (A[i] > A[i + 1]) {
            swap(A[i], A[i + 1]);
        }
    }

    if (IsSorted(A, n))
	{
		delete [] A;
    	return true;
	}
	return false;
}

bool IsSorted(int data[], int start, int end){
	for(int i=start; i<end; i++){
		if (data[i] > data[i+1])
			return false;
	}
	return true;
}
