// Includes
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <bitset>
#include <string>
#include <sstream>

using namespace std;

void multiply(int Hmat[3][7], int segMat[7][1], int res[3][1]);

string fileName;
ifstream infile;

string concat; 

int Hmatrix[3][7] = {{0,0,0,1,1,1,1},
					 {0,1,1,0,0,1,1},
					 {1,0,1,0,1,0,1}};
					 
int res[3][1]; //Stored Matrix (after multiplication)

int main(int argc, char *argv[])
{
	string str = "0101101";
	
	int strStore[7][1];
	int k = 0;
		
	// Convert the string to a 1x7 Matrix
	for (int a = 0; a < 7; a++)
	{
		for (int b = 0; b < 1; b++)
		{
			cin >> 
			strStore[a][b] = str[k]; // Minus 48 to get 0 or 1
			k++;
		}
	}
	
	multiply (Hmatrix, strStore, res);
}

void multiply(int Hmat[3][7], int segMat[7][1], int res[3][1])
{	
	//First part of for loop is for rows of result
	for (int i = 0; i < 3; i++)
	{
		//Set result to zero to start
		res[i][0] = 0;
		
		//Increment j for Hmat matrix and segMat matrix
		for (int j = 0; j < 7; j++)
		{
			res[i][0] += Hmat[i][j] * segMat[j][0];
		
			//Preform Mod
			res[i][0] = res[i][0] % 2;
		}
		cout << "Result" << i << ": " << res[i][0] << "\n";
	}
} 
