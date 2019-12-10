// Includes
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <bitset>
#include <string>


using namespace std;

void decode(void);
void multiply(int Hmat[3][7], int segMat[7][1], int res[3][1]);

string fileName, concat;
ifstream infile; 

int buffer[7];
int modBuff[3];
int err = 0;


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
	decode();
	
	cout << endl;
	
	cout << "# of errors = " << err << endl;
	
	//~ // Print H matrix								 
	//~ for (int i = 0; i < 3; i++)
	//~ {
		//~ for (int j = 0; j < 7; j++)
		//~ cout << Hmatrix[i][j] << " ";
		//~ cout << endl;
	//~ }
}

void decode(void)
{
	infile.open(fileName.c_str(), ios::in | ios::binary);
	
	if (infile)
	{
		char *c = new char[0]; // Declaration of c char pointer
		
		while(infile.read(c,14))
		{
			//Set binary values 0-13 from .enc file
			bitset<8> a0(c[0]); bitset<8> a1(c[1]); bitset<8> a2(c[2]);		
			bitset<8> a3(c[3]); bitset<8> a4(c[4]); bitset<8> a5(c[5]);
			bitset<8> a6(c[6]); bitset<8> a7(c[7]); bitset<8> a8(c[8]);
			bitset<8> a9(c[9]); bitset<8> a10(c[10]);
			bitset<8> a11(c[11]); bitset<8> a12(c[12]); 
			bitset<8> a13(c[13]); 
			
			// Concatenate the bitset together
			concat = a0.to_string() + a1.to_string() + 
			a2.to_string() + a3.to_string() + a3.to_string() + 
			a5.to_string() + a6.to_string() + a7.to_string() + 
			a8.to_string() + a9.to_string() + a10.to_string() +
			a11.to_string() + a12.to_string() + a13.to_string(); 
			
			cout << concat << "\n" <<endl;
			
			string s[16];
			int j = 0;
			
			for (int i = 0; i < 16; i++)
			{
				string str = concat.substr(j, 7);
				s[i] = concat.substr(j, 7);
				
				// TODO possibly do matrix multiplication in this 
				// for loop
				
				
				//~ for (int i = 0; i < 7; i++)
				//~ {
					//~ buffer[i] = str[i]-'0';
				//~ }
				
				//~ cout << buffer[0];
				//~ cout << buffer[1];
				//~ cout << buffer[2];
				//~ cout << buffer[3];
				//~ cout << buffer[4];
				//~ cout << buffer[5];
				//~ cout << buffer[6]<< endl;
				
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
				
				multiply (Hmatrix, strStore, res);
				
				// Error Checking
				if (res[0][0] == 0 && res[1][0] == 0 && res[2][0] == 0)
				{
					string firstPart = concat.substr(j, 4);
					j = j+4;
					string secondPart = concat.substr(j, 4);
					
					cout << firstPart << "\n";
					cout << secondPart << "\n\n";
					
				}
				else
				{
					cout << "You got an error" << endl;
					err++;
					
				}
							
				//~ // Test to print out matrix
				//~ cout << "Test Matrix" << endl;
				
				
				//~ for (int c = 0; c < 7; c++)
				//~ {
					//~ for (int d = 0; d < 1; d++)
					//~ {
						//~ if (strStore[c][d] == '\0')
							//~ break;
						//~ cout << strStore[c][d];
					//~ }
					//~ cout << endl; 
				//~ }
				
				//~ cout << endl;
				
				
				//~ cout << "Result Matrix \n";
				//~ for (int i = 0; i < 3; i++)
				//~ {
					//~ for (int j = 0; j < 1; j++)
					//~ cout << res[i][j] << " ";
					//~ cout << "\n";
				//~ }
				
				//~ cout << endl;
				
				
				//j = j + 7;
			}
			
			//Test print values of store
			for (int k = 0; k < 16; k++)
			{
				cout << s[k] << endl;
			}		
		}
	}
	else
	{
		cout << "No file found, please run program again" << endl;
		main(0, 0);
	}
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
		//cout << "Result" << i << ": " << res[i][0] << "\n";
		//modBuff[i] = res[i][0];
	}
	
	
	
	
	

} 


