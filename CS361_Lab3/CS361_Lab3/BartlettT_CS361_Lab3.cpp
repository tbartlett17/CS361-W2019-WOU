/*****************************************************************
* Name       : Tyler Bartlett
* Course     : CS361-Algorithms, Winter 2019
* Course Time: 1200-1350
* Date       : 02/13/19
* Project    : Lab 3
* Description:
*
* NOTES:
*       Used Resources:
*			Textbook
*			
*
******************************************************************/
#include <iostream>
#include <tuple> //used for holding a pair of ints: min of mcm function and k value that fetched the min
#include <vector>

typedef std::tuple<int, int> i2tuple;


//Dynamic Programming implementation of Multiplication Chain Rule.
void dpMCM()
{


}


void memoMCM()
{


}


void bfsAdjList()
{
	

}


void bfsAdjMatrix()
{


}


int main()
{
	/*
	this array holds dimensions of matricies.
	A1 = 30x4, A2 = 4x8, A3 = 5x10, A4 = 8x5, A5 = 5x10, A6 = 10x25, A7 = 25x15
	*/
	int mcmArr[7] = { 30, 4, 8, 5, 10, 25, 15 };

	std::vector <i2tuple> dpMCM_Table; //
	std::vector <i2tuple> memoMCM_Table;

	return 0;
}