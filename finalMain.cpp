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
void multiply(int Hmat[3][7], int segMat[7][1], int res[3][1], string read);
string binToAscii(string input);
string getFullBinary(void);

// Stream file declarations
ifstream infile; 
ofstream outFile;

// Variable declarations
string fileName, outputName, concat, full, storeThis, strSave;
string outputFile; 
int buffer[7];
int err = 0;
char c;
int r1=3, c1=7, r2=3, c2=1;
string arr[2];


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
	
	cout << "Output file name: ";
	cin >> outputFile;
	
	
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
	//infile.close();
	
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
		
		multiply (Hmatrix, strStore, res, str);
		//cout << endl;
		
		// Error Checking
		if (res[0][0] == 0 && res[1][0] == 0 && res[2][0] == 0)
		{
			//cout << "No Error" << endl;
			string split1 = strSave.substr(first,4);
			//cout << split1 << endl;
			
			storeThis += split1;
			
		}
		else if (res[0][0] == 1 && res[1][0] == 0 && res[2][0] == 0)
		{
			cout << "1st  bit error" << endl;
			cout << "string is: " << str << endl;
			
			string split1 = to_string(((strStore[0][0] + 1) % 2));
			cout << "split1: " << split1 << endl; 
			
			string split2 = str.substr(1,3);
			
			cout << "split2: " << split2 << endl;
			
			string together = split1 + split2;
			cout << "together:  " << together << "\n\n";
			
			storeThis += together;
			
			//cout << storeThis << "\n\n";
			err++;
		}
		else if (res[0][0] == 0 && res[1][0] == 1 && res[2][0] == 0)
		{
			cout << "2nd bit error" << endl;
			cout << "string is: " << str << endl;
			
			string split1 = str.substr(0,1);
			cout << "split1: " << split1 << endl;
			
			string split2 = to_string(((strStore[1][0] + 1) % 2));
			cout << "split2: " << split2 << endl;
			
			string split3 = str.substr(2, 2);
			cout << "split3: " << split3 << endl;
			
			string together = split1 + split2 + split3;
			cout << "together:  " << together << "\n\n";
			
			storeThis += together;
			err++;
		}
		else if (res[0][0] == 1 && res[1][0] == 1 && res[2][0] == 0)
		{
			cout << "3rd bit error" << endl;
			cout << "string is: " << str << endl;
			
			string split1 =  str.substr(0, 2);
			cout << "split1: " << split1 << endl; 
			
			string split2 =  to_string(((strStore[2][0] + 1) % 2));
			cout << "split2: " << split2 << endl; 
			
			string split3 = str.substr(3,1);
			cout << "split3: " << split3 << endl; 
			
			string together = split1 + split2 + split3;
			cout << "together:  " << together << "\n\n";
			
			storeThis += together;
			
			err++;
		}
		else if (res[0][0] == 0 && res[1][0] == 0 && res[2][0] == 1)
		{
			cout << "4th bit error" << endl;
			cout << "string is: " << str << endl;
			
			string split1 = str.substr(0, 3);
			cout << "split1: " << split1 << endl;
			
			string split2 = to_string(((strStore[3][0] + 1) % 2));
			cout << "split2: " << split2 << endl;
			
			string together = split1 + split2;
			cout << "together:  " << together << "\n\n";
			
			storeThis += together;
			
			err++;
		}
		else if (res[0][0] == 1 && res[1][0] == 0 && res[2][0] == 1)
		{
			cout << "5th bit error" << endl;
			
			string split1 = str.substr(0,4);
			//cout << split1 << endl;
			
			storeThis += split1;
			err++;
		}
		else if (res[0][0] == 0 && res[1][0] == 1 && res[2][0] == 1)
		{
			cout << "6th bit error" << endl;
			
			string split1 = str.substr(0,4);
			//cout << split1 << endl;
			
			storeThis += split1;
			err++;
		}
		else if (res[0][0] == 1 && res[1][0] == 1 && res[2][0] == 1)
		{
			cout << "7th bit error" << endl;
			string split1 = str.substr(0,4);
			//cout << split1 << endl;
			
			storeThis += split1;
			err++;
		}
		else
		{
			//cout << "You got an error" << endl;
			err++;
			
		}
		
		//cout << endl;
		
		first = first + 7;
	}
	//cout << "StoreThis: " << storeThis << endl;
}

/** Multiplies two matrices together to get a resultant matrix
*
* @param Hmat 	the H matrix that will be multiplied
* @param segMat 7-bit code block in a 7x1 matrix
* @param res  	result matrix after multiplication of Hmat and segMat
*/
void multiply(int Hmat[3][7], int segMat[7][1], int res[3][1], string read)
{	
	//cout << read << endl;
	//~ //First part of for loop is for rows of result
	for (int i = 0; i < 3; i++)
	{
		//Set result to zero to start
		res[i][0] = 0;
		
		//Increment j for Hmat matrix and segMat matrix
		for (int j = 0; j < 7; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				res[i][j] += Hmat[i][k] * segMat[k][j];
			}
			
		
			//Preform Mod
			res[i][0] = res[i][0] % 2;
		}
		
		//~ //cout << "Result" << i << ": " << res[i][0] << "\n";
	}	
	//~ for(int i=0; i<r1; i++)
         //~ for(int j=0; j<c2; j++) {
            
         //~ }
      //~ for(int i=0; i<r1; i++)
         //~ for(int j=0; j<c2; j++)
            //~ for(int k=0; k<c1; k++) {
               //~ res[i][j]+=Hmat[i][k]*segMat[k][j];
            //~ } 
            
        //~ for(int i=0; i<r1; i++)
		//~ {
			//~ for(int j=0; j<c2; j++)
			//~ {
				//~ int sum=0;
				//~ for(int k=0; k<c1; k++)
				//~ {
					//~ sum = sum + Hmat[i][k] * segMat[k][j];
				//~ }
				//~ res[i][j] = sum % 2;
				//~ //res[i][j] = res[i][j] % 2;
			//~ }
		//cout << "Result" << i << ": " << res[i][0] << "\n";
		//~ }
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



