// * A MESSAGE TO THE READER: All "PROGRAMMER'S NOTE" comments are intended to
// * be removed (or reworked into regular comments if helpful) before the final
// * submission of both this program and future Organization of Programming
// * Languages programs.

// * PROGRAMMER'S NOTE: Current Goal (8/29/2019): Read a text file
#include <cstdlib>
// * PROGRAMMER'S NOTE: iostream may be a testing-only item. Removal in the
// * final program build depends upon desired testing content to retain.
#include <iostream>
#include <string>
using namespace std;

// * PROGRAMMER'S NOTE: This global Boolean was created to test features and
// * values of the prgram. If safe, this boolean may remain in the final program
// * build unlesss otherwise desired by Dr. Pounds.
bool testMode = true;

/* DISABLE
string readLine();
void obtainValues(&syllables,
             &totalWords,
             &sentences,
             &difficultWords);
float calculateFlesch();
*/

// * PROGRAMMER NOTE: The parentheses beside main may require text to allow
// * the command line to be an input source. [OK]
int main(int argc, char* argv[])
{
	// Read the filename of the file to be analyzed
	// * PROGRAMMER'S NOTE: C++ code read line required [OK]
	string filename = argv[1];

	// ** TEST
	if (testMode)
	{
		cout << " ** Filename read: " << filename << endl;
	}

	// * PROGRAMMER'S NOTE: The below code is intended to test file reading.
	// * PROGRAMMER'S NOTE: The filename string variable likely requires
	// * conversion to a c string for success [CODE PLACED]
	string line;
	ifstream analyzedFile ((string) (filename).c_str);
	// Print content from the input fle if the input file successfully opens
	if (analyzedFile.is_open())
	{
		while (getline(analyzedFile, line));
		{
			// Print the read line
			cout << line << endl;
		}
		analyzedFile.close();
	}
	else
	{
		cout << "File opening failed." << endl;
	}

/* DISABLE
	// Preapare variables for the four values to be recorded while reading
	// the input file
	int syllables = 0;
	int totalWords = 0;
	int sentences = 0;
	int difficultWords = 0;

	// Obtain the values needed for the readability index and score
	// calculations
	// * PROGRAMMER NOTE: Pass-by reference may be required here to
	// * update the multiple calculation variable values, as C++
	// * functions can otherwise return only one value to the functions'
	// * callers.
	obtainValues(syllables,
		     totalWords,
		     sentences,
		     difficultWords);

	// Calculate the Flesch readability index
	calculateFlesch(syllables,
			totalWords,
			sentences);
*/
	return 0;
}

/* DISABLE
void obtainValues(&syllables,
                  &totalWords,
                  &sentences,
                  &difficultWords)
{
	// Precondition:
	// Postcondition:

	// Initialize a Boolean for presence of a partial word segment at the
	// end of an input file line
	// * PROGRAMMER'S NOTE: The name of this Boolean may need improvement,
	// * and this initialization's placement may require change to a more
	// * relevant location for usage timing
	bool wordPart = false;

	// Store the earliest unread file line
	string currentLine = ;

	
}

float calculateFlesch()
{
	// Precondition:
	// Postcondition: The Flesch Readability Index was calculated and
	// returned to this function's caller

	// * PROGRAMMER'S NOTE: The values of alpha and beta likely require
	// * decimal format; thus, either a flot or a double data type may be
	// * necessary for each of the two variables.

	// Calculate the "alpha" value
	float alpha = ;

	// Calculate the "beta" value
	float beta = ;

	return fleschIndex;
}
*/
