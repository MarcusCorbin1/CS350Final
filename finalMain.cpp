// Includes
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <bitset>
#include <string>
#include <limits>
#include <type_traits>

using namespace std;

void decode(void);

string fileName, concat;
ifstream infile; 

//Main Function
int main(int argc, char *argv[])
{
	// Ask use which file user wants to encode
	cout << "File to open: ";
	cin >> fileName;
	decode();
}

void decode(void)
{
	infile.open(fileName.c_str(), ios::in | ios::binary);
	
	if (infile)
	{
		char *c = new char[0]; // Declaration of c char pointer
		
		while(infile.read(c,7))
		{
			
			bitset<8> a0(c[0]); bitset<8> a1(c[1]); bitset<8> a2(c[2]);		
			bitset<8> a3(c[3]); bitset<8> a4(c[4]); bitset<8> a5(c[5]);
			bitset<8> a6(c[6]);
			
			concat = a0.to_string() + a1.to_string() + 
			a2.to_string() + a3.to_string() + a3.to_string() + 
			a5.to_string() + a6.to_string();
			
			
		}
		
		cout << concat;
		
		//TODO break concat into bits of 7
		
	}

}
