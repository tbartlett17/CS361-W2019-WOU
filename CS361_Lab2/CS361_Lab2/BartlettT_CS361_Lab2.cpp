/*****************************************************************
* Name       : Tyler Bartlett
* Course     : CS361-Algorithms, Winter 2019
* Course Time: 1200-1350
* Date       : 01/28/19
* Project    : Lab 2
* Description:
*
* NOTES:
*       Used Resources:
*			https://www.geeksforgeeks.org/radix-sort/
*			https://www.techiedelight.com/count-sort-cpp-java-implementation/
*			https://www.geeksforgeeks.org/bucket-sort-2/
*			Textbook
*
******************************************************************/
#include <iostream>
#include <fstream> 
#include <string>
#include <vector>
#include <ctime> //time function run times
#include <map> //for count sort
#include <algorithm> //for use in bucket sort
#define DATA_FILE "lab3_data.txt" //name of file to read from (the file for this lab is called lab3 data for some reason)
#define DATA_FILE_LN_CNT 10000000 //number of lines in said file
#define NUM_RUNS 1 //number of times to run prorgram
#define NUM_LINES_TO_READ 1000000 //number of lines to read from input file

//a function to print out vector<int> contents
int vectorPrinter(std::vector<int>& arr)
{
	for (int i = 0; i < arr.size(); i++)
	{
		std::cout << arr.at(i) << '\n';
	}
	std::cout << '\n';

	return 0;
}

//a function to print out vector<int> contents backwards
int vectorPrinterReversed(std::vector<int>& arr)
{
	for (int i = arr.size()-1; i >= 0; i--)
	{
		std::cout << arr.at(i) << '\n';
	}
	std::cout << '\n';

	return 0;
}


//iteratively check if array is sorted in ascending order
bool flgIsSorted(std::vector<int>& arr)
{
	//array size one is sorted
	if (arr.size() == 1)
	{
		std::cout << "arr is sorted! \n";
		return true;
	}
	//array size greater than 1
	else
	{
		for (int i = 0; i < arr.size() - 1; i++)
		{
			//checks that arr[i] is less than the next value
			if (arr[i] > arr[i + 1])
			{
				std::cout << "arr is not sorted! \n";
				return false;
			}
		}
	}

	std::cout << "arr is sorted! \n";
	return true;
}


//read the input fine into a vector<int>
int readFileToArray(std::vector<int>& arr)
{
	std::ifstream infile; // create a file object
	infile.open(DATA_FILE);

	std::string line; // for reading lines in from file
	int intFromLine; // int to hold converted line string
	int numLinesRead = 1; //start reading at line 1 of file
	double sum = 0;

	//if the file is open, read it into the array 
	if (infile.is_open())
	{
		while (getline(infile, line) && numLinesRead <= NUM_LINES_TO_READ)
		{
			//skip blank lines
			if (line.size() != 0)
			{
				intFromLine = stoi(line); // stoi converts string to int
				arr.push_back(intFromLine); // push_back adds element to next available spot in vector
				sum += intFromLine;
			}
			numLinesRead++;
		}
	}
	infile.close();
	//std::cout << std::fixed << "sum from file is: " << sum << '\n';

	return 0;
}


//finds the largest number in arr
int getMax(std::vector<int>& arr)
{
	int maxValue = 0;
	for (int i = 0; i < arr.size() - 1; i++)
	{
		if (maxValue < arr[i])
		{
			maxValue = arr[i];
		}
	}

	return maxValue;
}


//radixSort Helper (Count Sort)
int countSort(std::vector<int>& arr)
{
	// create an empty map to store frequency of array elements
	std::map<int, int> freq;

	// store distinct values in the input array as key and 
	// their respective counts as values
	for (int i = 0; i < arr.size(); i++) {
		freq[arr.at(i)]++;
	}

	// traverse the map and overwrite the input array with sorted elements
	// (map will iterate based on the sorted order of keys)
	int i = 0;
	for (auto it : freq) {
		while (it.second--) {
			arr[i++] = it.first;
		}
	}

	return 0;
}


//a function to radix sort arr implementing a stable sort (count sort in this case)
int radixSort(std::vector<int>& arr)
{
	int max = getMax(arr); //largest num in arr

	// Do counting sort for every digit. Note that instead 
	// of passing digit number, exp is passed. exp is 10^i 
	// where i is current digit number 
	for (int exp = 1; max / exp > 0; exp *= 10)
	{
		countSort(arr);
	}
		
	return 0;
}


//a function to bucket sort input arr
//tried implementing a modified version of the geek for geek bucket sort
//does not work. did not fix due to time
int bucketSort(std::vector<int>& arr)
{
	std::vector<int> bucketArr[sizeof(arr) / sizeof(int)];
	//bucketArr.reserve(arr.size());
	int bucketIndex = 0; //index in bucketArr

	//put array elements in different buckets
	for (int i = 0; i < arr.size() - 1; i++)
	{
		bucketIndex = arr.size() * arr[i];
		bucketArr[bucketIndex].push_back(arr[i]);
	}

	//Sort individual buckets
	for (int i = 0; i < arr.size()-1; i++) 
	{
		sort(bucketArr[i].begin(), bucketArr[i].end());
	} 

	//Concatenate all buckets into arr[] 
    int index = 0; 
    for (int i = 0; i < arr.size()-1; i++)
	{
		for (int j = 0; j < bucketArr[i].size(); j++)
		{
			arr[index++] = bucketArr[i][j]; 
		}
	}
          

	return 0;
}

//helper function for merge sort
int mergeHelper(std::vector<int>& arr, int startIndex, int midIndex, int endIndex)
{
    int num1 = midIndex - startIndex; //length of subarray of arr from startIndex to midIndex
    int num2 = endIndex - midIndex; //length of subarray from midIndex to endIndex

    std::vector<int> left; // array to hold 'left side' values after the splitting and reassembly
    left.reserve(DATA_FILE_LN_CNT/2);
    std::vector<int> right; // array to hold 'left side' values after the splitting and reassembly
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
int auxMergeSort(std::vector<int>& arr, int startIndex, int endIndex)
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


int main()
{
	//components of time
	//time calculation: time = (float)(end - start) / CLOCKS_PER_SEC
	srand(time(NULL));
	clock_t start, end;
	float algoRunTime = 0;


	//run the program NUM_RUNS times and print time taken to execute file read, 
	for (int i = 1; i <= NUM_RUNS; i++)
	{
		/* setup array containers to store data from read from file */
		std::vector<int> dataFileArr; //a dynamic array
		std::vector<int> dataFileArrCopy; //a copy vector to run on the second sort function
		dataFileArr.reserve(DATA_FILE_LN_CNT); //sets capacity of vector
		dataFileArrCopy.reserve(DATA_FILE_LN_CNT);

		/* print out run number (1-3) inclusive */
		std::cout << "=================== run " << i << " =================== \n";

		/* read file into vector and time function duration */
		std::cout << "Reading data from file... ";
		start = clock();
		readFileToArray(dataFileArr);
		end = clock();
		std::cout << "done!\n";
		algoRunTime = (float)(end - start) / CLOCKS_PER_SEC;
		std::cout << "time taken: " << algoRunTime << "\n\n";
		// std::cout << "data read in from file:\n";
		// vectorPrinter(dataFileArr);

		/* copy dataFileArr */
		dataFileArrCopy = dataFileArr;

		/* clean up vector memory usage */
		dataFileArr.shrink_to_fit(); //shrink array capacity to array actual size (number of data points in vector)
		dataFileArrCopy.shrink_to_fit();

		/* Radix Sort data and time function duration */
		std::cout << "Performing radix sort... ";
		start = clock();
		radixSort(dataFileArr);
		end = clock();
		std::cout << "done!\n";
		algoRunTime = (float)(end - start) / CLOCKS_PER_SEC;
		std::cout << "time taken: " << algoRunTime << "\n\n";
		// std::cout << "(reverse) Array after radix sort:\n";
		// vectorPrinterReversed(dataFileArr);

		/* check if array is sorted and time function duration */
		std::cout << "checking if array is sorted...\n";
		start = clock();
		flgIsSorted(dataFileArr);
		end = clock();
		algoRunTime = (float)(end - start) / CLOCKS_PER_SEC;
		std::cout << "time taken: " << algoRunTime << "\n\n";

		/* Bucket Sort data and time function duration */
		// std::cout << "Performing bucket sort... ";
		// start = clock();
		// //bucketSort(dataFileArr);
		// end = clock();
		// std::cout << "done!\n";
		// algoRunTime = (float)(end - start) / CLOCKS_PER_SEC;
		// std::cout << "time taken: " << algoRunTime << "\n\n";
		// std::cout << "Array after radix sort:\n";
		// vectorPrinter(dataFileArr);

		/* recursive merge sort vector and time function duration */
		std::cout << "Performing merge sort... ";
        start = clock();
        auxMergeSort(dataFileArrCopy, 0, dataFileArr.size()-1);
        end = clock();
		std::cout << "done!\n";
        algoRunTime = (float)(end - start) / CLOCKS_PER_SEC;
        std::cout << "time taken: " << algoRunTime << "\n\n";
        // std::cout << "Array after merge sort:\n";
        // vectorPrinter(dataFileArr);

		/* check if array is sorted and time function duration */
		std::cout << "checking if array is sorted...\n";
		start = clock();
		flgIsSorted(dataFileArr);
		end = clock();
		algoRunTime = (float)(end - start) / CLOCKS_PER_SEC;
		std::cout << "time taken: " << algoRunTime << "\n\n";





		std::cout << "=============================================\n\n";
	}

	//system("pause");
	return 0;
}
