// Includes
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <bitset>
#include <string>
#include <sstream>

using namespace std;

string fileName;
ifstream infile;

string concat; 

int main(int argc, char *argv[])
{
	cout << "FileName : ";
	cin >> fileName;
	
	ifstream infile(fileName, ios::binary | ios::in);
	char c;
	while (infile.get(c))
	{
		for (int i = 7; i >= 0; i--) // or (int i = 0; i < 8; i++)  if you want reverse bit order in bytes
		{
			concat += to_string(((c >> i) & 1));
		}
	}
	
	cout << concat << endl;
}
