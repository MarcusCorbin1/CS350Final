/**
 * @file finalMain.cpp
 *
 * @brief This is a program that take the input of a .enc file
 *
 * @author  Marcus Corbin
 * Contact: marcus.corbin@mnsu.edu
 *
 */

// Includes
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <bitset>
#include <string>
#include <sstream>


using namespace std;

// Function Prototypes
void decode(string strSave);
void multiply(int Hmat[3][7], int segMat[7][1], int res[3][1]);
string binToAscii(string input);
string getFullBinary(void);


string fileName, concat, full;
string outputFile = "result.txt"; 
ifstream infile; 
ofstream outFile;

int buffer[7];
int modBuff[3];
int err = 0;
char c;
string arr[2];

string storeThis, strSave;


// Given H Matrix that will be multiplied with 7-bit sequence
int Hmatrix[3][7] = {{0,0,0,1,1,1,1},
					 {0,1,1,0,0,1,1},
					 {1,0,1,0,1,0,1}};

int res[3][1]; //Stored Matrix (after multiplication)

//Main Function
int main(int argc, char *argv[])
{
	// Ask use which file user wants to encode
	cout << "File to open: ";
	cin >> fileName;
	
	// Set .enc file to a large string
	strSave = getFullBinary();
	cout << strSave << "\n\n";
	
	// Decode the .enc file
	decode(strSave);
	
	cout << endl; // Just another 
	
	cout << "# of errors = " << err << endl;
	
	string finalString = binToAscii(storeThis); 
	cout << "\nFinal output: " << endl;
	cout << finalString << endl;
	outFile << finalString;
	
	
	outFile.close();
	
	
}


/** Decodes the .enc file 
*
* If no verbosity is specified, inherit from parent
*
* @param strSave a binary string from the .enc file
*/
void decode(string strSave)
{
	
	outFile.open(outputFile.c_str(), ios::out | ios::binary);
	
	int lengthBin = strSave.size();
	cout << "Length " << lengthBin << "\n\n";
	
	
	
	int first = 0;
	
	// Split the strSave into 7 bit chunks
	for (int cnt = 0; cnt < lengthBin; cnt = cnt + 7)
	{
		string str = strSave.substr(first, 7);
		
		
		//cout << str << endl;
		
		int strStore[7][1];
		int k = 0;
		
		// Convert the string to a 1x7 Matrix
		for (int a = 0; a < 7; a++)
		{
			for (int b = 0; b < 1; b++)
			{
				strStore[a][b] = str[k]-48; // Minus 48 to get 0 or 1
				k++;
			}
		}
		
		
		// Error Checking
		if (res[0][0] == 0 && res[1][0] == 0 && res[2][0] == 0)
		{
			//cout << "No Error" << endl;
			string split1 = strSave.substr(first,4);
			//cout << split1 << endl;
			
			storeThis += split1;
			
			//outFile << split1;
			
		}
		else
		{
			//cout << "You got an error" << endl;
			err++;
			
		}
		
		multiply (Hmatrix, strStore, res);
		
		//cout << endl;
		
		first = first + 7;
	}
}

/** Multiplies two matrices together to get a resultant matrix
*
* @param Hmat 	the H matrix that will be multiplied
* @param segMat 7-bit code block in a 7x1 matrix
* @param res  	result matrix after multiplication of Hmat and segMat
*/
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
		//cout << "Result" << i << ": " << res[i][0] << "\n";
		//modBuff[i] = res[i][0];
	}
} 

/** Convert final binary output string to ASCII.
*
* @param input the input string that will be converted to ASCII.
*/
string binToAscii(string input)
{
	stringstream sstream(input);
	string output;
	
	while(sstream.good())
    {
        bitset<8> bits;
        sstream >> bits;
        char c = char(bits.to_ulong());
        output += c;
    }
    
    return output;
}

/** Translates the .enc file into a large string.

* @return full the full string that will be thrown into the decoder.
*/
string getFullBinary()
{
	infile.open(fileName.c_str(), ios::in | ios::binary);

	string full;	
	while (infile.get(c))
	{
		for (int i = 7; i >= 0; i--)
		{
			full += to_string(((c >> i) & 1));
		}
	}

	
	return full;
}



