/*****************************************************************
* Name       : Tyler Bartlett
* Course     : CS361-Algorithms, Winter 2019
* Course Time: 1200-1350
* Date       : 01/14/19
* Project    : Lab 1
* Description: 
*				
* NOTES: 
*       Used Resources: Textbook
*                       Mike
*
******************************************************************/
#include <iostream>
#include <fstream> 
#include <string>
#include <vector>
#include <ctime>
#define DATA_FILE "lab1_data.txt" //name of file to read from
#define DATA_FILE_LN_CNT 10000000 //number of lines in said file
#define NUM_RUNS 3 //number of times to run prorgram

using namespace std; 

//a function to print out vector<int> contents
int vectorPrinter(vector<int>& arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr.at(i) << '\n';
    }
    cout << '\n';

    return 0;
}

//Swap two elements of an array
int swap(vector<int>& arr, int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;

    return 0;
}

//read the input fine into a vector<int>
int readFileToArray(vector<int>& arr, int numLinesToRead)
{
    ifstream infile; // create a file object
    infile.open (DATA_FILE);

    string line; // for reading lines in from file
    int intFromLine; // int to hold converted line string
    int numLinesRead = 1; //start reading at line 1 of file
    double sum = 0;

    //if the file is open, read it into the array 
    if (infile.is_open())
    {
        while(getline(infile, line) && numLinesRead <= numLinesToRead)
        {
            //skip blank lines
            if (line.size() != 0)
            {
                intFromLine = stoi (line); // stoi converts string to int
                arr.push_back(intFromLine); // push_back adds element to next available spot in vector
                sum += intFromLine;
            }
            numLinesRead++;
        }
    }
    infile.close();
    cout << fixed << "sum from file is: " << sum << '\n'; 

    return 0;
}

//the helper function to actually reassemble the array
int mergeHelper(vector<int>& arr, int startIndex, int midIndex, int endIndex)
{
    int num1 = midIndex - startIndex; //length of subarray of arr from startIndex to midIndex
    int num2 = endIndex - midIndex; //length of subarray from midIndex to endIndex

    vector<int> left; // array to hold 'left side' values after the splitting and reassembly
    left.reserve(DATA_FILE_LN_CNT/2);
    vector<int> right; // array to hold 'left side' values after the splitting and reassembly
    right.reserve(DATA_FILE_LN_CNT/2);

    //cout << "num1 = " << num1 << '\n';
    //cout << "num2 = " << num2 << '\n';

    //copy subarray arr[startIndex..midIndex] into 'left side' arr
    for (int i = 0; i <= num1; i++)
    {
        left.push_back(arr[startIndex + i]);
    }
    //copy subarray arr[midIndex+1..endIndex] into 'right side' arr
    for (int j = 1; j <= num2; j++)
    {
        right.push_back(arr[midIndex + j]);
    }

    //setting left and right [numX + 1] to a large number to correct for comparison logic in reassemly 
    left.push_back(9999999);
    right.push_back(9999999);    

    //shrink array capacities to array actual sizes
    left.shrink_to_fit();
    right.shrink_to_fit();

    // begin reassembling the array in sorted order
    int i = 0;
    int j = 0;
    for (int k = startIndex; k <= endIndex; k++)
    {
        if (left[i] <= right[j])
        {
            arr[k] = left[i];
            i++;
        }
        else
        {
            arr[k] = right[j];
            j++;
        }
    } 

    return 0;
}

//recursive function to merge sort an array.
int auxMergeSort(vector<int>& arr, int startIndex, int endIndex)
{
    if (startIndex < endIndex)
    {
        int mid = (startIndex + endIndex)/2; //get the middleIndex
        
        auxMergeSort(arr, startIndex, mid); //break array in half from startIndex to midIndex
        auxMergeSort(arr, (mid+1), endIndex); //break array in half from midIndex to endIndex
        mergeHelper(arr, startIndex, mid, endIndex); //sort the array 
    }

    return 0;
}

//this is equivalent to the partition function from the textbook psuedo code
int qsHelper(vector<int>& arr, int startIndex, int endIndex)
{
    int x = arr[endIndex]; //the pivot for quick sort
    int i = startIndex-1;
    
    for (int j = startIndex; j < endIndex; j++)
    {
        //if value is less than the pivot
        if (arr[j] <= x)
        {
            i++;
            swap(arr, i, j);
        }
    }

    swap(arr, i+1, endIndex);//swap the pivot

    return i+1;
}

//equivalent to quick sort psuedo code from textbook
int auxQuickSort (vector<int>& arr, int startIndex, int endIndex)
{
    if (startIndex < endIndex)
    {
        int q = qsHelper(arr, startIndex, endIndex);
        auxQuickSort (arr, startIndex, q-1); //sort from startIndex to q
        auxQuickSort (arr, q+1, endIndex); //sort from q to endIndex
    }

    return 0;
}

//iteratinvely check if array is sorted in ascending order.
//this function breaks at 100,000 data values
bool flgIsSorted(vector<int>& arr)
{
    if (arr.size() == 1)
    {
        cout << "arr is sorted! \n";
        return true;
    }
    else
    {
        //two half arrays to compare arr against
        vector<int> sortedArrHalf1;
        vector<int> sortedArrHalf2;
        sortedArrHalf1.reserve(arr.size());
        sortedArrHalf2.reserve(arr.size());

        //values to check later to determine if sorted array is ascending or descending order
        int lastEleHalf1;
        int firstEleHalf2;

        bool setFirstEleHalf2 = true;

        //copy array data over into both half arrays
        for (int i = 0; i < arr.size(); i++)
        {
            if (i < arr.size()/2)
            {
                sortedArrHalf1.push_back(arr[i]);
                lastEleHalf1 = arr[i];
            }
            else
            {
                sortedArrHalf2.push_back(arr[i]);
                
                if (setFirstEleHalf2 == true)
                {
                    firstEleHalf2 = arr[i];
                    setFirstEleHalf2 = false;
                }
            }
        }

        //shrink array capacities to array actual sizes
        sortedArrHalf1.shrink_to_fit();
        sortedArrHalf2.shrink_to_fit();

        //sort the two half arrays to compare passed in array against
        auxQuickSort(sortedArrHalf1, 0, sortedArrHalf1.size()-1);
        auxQuickSort(sortedArrHalf2, 0, sortedArrHalf2.size()-1);

        //check that arr passed into this function is sorted by comparing against the first half
        for (int i = 0; i < sortedArrHalf1.size(); i++)
        {            
            if (sortedArrHalf1[i] != arr[i])
            {
                cout << "arr half1 not sorted \n";
                return false;
            }
        }

        //to fix logic in comparisons of 2nd half against second half of arr
        int evenOddAdjuster = 0;
        if (arr.size()%2 != 0)
        {
            evenOddAdjuster++;
        }

        //check that arr passed into this function is sorted by comparing against the second half
        for (int i = 0; i < sortedArrHalf2.size(); i++)
        {
            if (sortedArrHalf2[i] != arr[i+ sortedArrHalf2.size()-evenOddAdjuster])
            {
                cout << "arr half2 not sorted \n";
                return false;
            }
        }

        //arr passed in not sorted if first ele of 2nd half < last ele of 1st half
        if (firstEleHalf2 < lastEleHalf1)
        {
           cout << "arr is not sorted! \n";
            return false;
        }
        else
        {
           cout << "arr is sorted! \n";
            return true;
        }
    }

    //this statement should not be reached, but is here as a last catch just in case
    cout << "arr is not sorted!_last \n";
    return false;
}

//iteratively check if array is sorted in ascending order
bool flgIsSorted2(vector<int>& arr)
{
    //array size one is sorted
    if (arr.size() == 1)
    {
        cout << "arr is sorted! \n";
        return true;
    }
    //array size greater than 1
    else
    {
        for (int i = 0; i < arr.size()-1; i++)
        {
            //checks that arr[i] is less than the next value
            if (arr[i] > arr[i+1])
            {
                cout << "arr is not sorted! \n";
                return false;
            }
        }
    }

    cout << "arr is sorted! \n";
    return true;
}


int main()
{
    //components of time
    //time calculation: time = (float)(end - start) / CLOCKS_PER_SEC
    srand(time(NULL));
	clock_t start, end;
	float algoRunTime = 0;

    int numLinesToRead = 10000000;

    //run the program NUM_RUNS times and print time taken to execute file read, 
    for (int i = 1; i <= NUM_RUNS; i++)
    {
        /* setup array containers to store data from read from file */
        vector<int> dataFileArr; //a dynamic array
        vector<int> dataFileArrCopy; //a copy vector to run on the second sort function
        dataFileArr.reserve(DATA_FILE_LN_CNT); //sets capacity of vector
        dataFileArrCopy.reserve(DATA_FILE_LN_CNT);

        /* print out run number (1-3) inclusive */
        cout << "run " << i << ": \n"; 

        /* read file into vector and time function duration */
        start = clock();
        readFileToArray(dataFileArr, numLinesToRead);
        end = clock();
        algoRunTime = (float)(end - start) / CLOCKS_PER_SEC;
        cout << "time to complete File read: " << algoRunTime << '\n';
        //cout << "data read in from file:\n";
        //vectorPrinter(dataFileArr);

        /* copy dataFileArr */
        dataFileArrCopy = dataFileArr;

        /* clean up vector memory usage */
        dataFileArr.shrink_to_fit(); //shrink array capacity to array actual size (number of data points in vector)
        dataFileArrCopy.shrink_to_fit();

        /* recursive merge sort vector and time function duration */
        // start = clock();
        // auxMergeSort(dataFileArr, 0, dataFileArr.size()-1);
        // end = clock();
        // algoRunTime = (float)(end - start) / CLOCKS_PER_SEC;
        // cout << "time to complete merge sort: " << algoRunTime << '\n';
        // cout << "Array after merge sort:\n";
        // vectorPrinter(dataFileArr);

        /* check if array is sorted and time function duration */
        // start = clock();
        // flgIsSorted2(dataFileArr);
        // end = clock();
        // algoRunTime = (float)(end - start) / CLOCKS_PER_SEC;
        // cout << "time to complete sort check: " << algoRunTime << '\n';

        /* recursively quick sort vector and time function duration */
        start = clock();
        auxQuickSort(dataFileArrCopy, 0, dataFileArr.size()-1);
        end = clock();
        algoRunTime = (float)(end - start) / CLOCKS_PER_SEC;
        cout << "time to complete quick sort: " << algoRunTime << '\n';
        //cout << "Array after quick sort:\n";
        //vectorPrinter(dataFileArrCopy);

        /* check if array is sorted and time function duration */
        start = clock();
        flgIsSorted2(dataFileArr);
        end = clock();
        algoRunTime = (float)(end - start) / CLOCKS_PER_SEC;
        cout << "time to complete sort check: " << algoRunTime << "\n\n";
    }


    cout << "done! \n";
    return 0;
}
