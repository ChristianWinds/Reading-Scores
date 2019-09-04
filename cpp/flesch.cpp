// * A MESSAGE TO THE READER: All "PROGRAMMER'S NOTE" comments are intended to
// * be removed (or reworked into regular comments if helpful) before the final
// * submission of both this program and future Organization of Programming
// * Languages programs.

// * PROGRAMMER'S NOTE: Current Goal (8/29/2019): Read a text file
#include <cstdlib>
// * PROGRAMMER'S NOTE: iostream may be a testing-only item. Removal in the
// * final program build depends upon desired testing content to retain.
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

// * PROGRAMMER'S NOTE: This global Boolean was created to test features and
// * values of the prgram. If safe, this boolean may remain in the final program
// * build unlesss otherwise desired by Dr. Pounds.
/*bool testMode = true;*/
/* DISABLE
string readLine();
*/
void obtainValues(&syllables,
		  &totalWords,
		  &sentences,
		  &difficultWords);
/* DISABLE
float calculateFlesch();
*/

// * PROGRAMMER NOTE: The parentheses beside main may require text to allow
// * the command line to be an input source. [OK]
int main(int argc, char* argv[])
{
	// Run the program only if one filename was entered on the command line
/*	if (argc != 2)
	{
		// Ask the user to enter a filename
		cout << "Please enter one filename." << endl;
	}
	else
	{*/
		// Read the filename of the file to be analyzed
		// * PROGRAMMER'S NOTE: C++ code read line required [OK]
		/*string filename = argv[1];*/

		// ** TEST
/*		if (testMode)
		{
			cout << " ** Filename read: " << filename << endl;
		} */

		// * PROGRAMMER'S NOTE: The below code is intended to test file
		// reading
		// * PROGRAMMER'S NOTE: The filename string variable likely
		// * requires conversion to a c string for success [CODE
		// * PLACED]
		string line = "TEST";
		cout << line << endl;
/*		char * filenameCstr = new char [filename.length() + 1];*/
/*		strcpy (filenameCstr, filename.c_str());*/
		ifstream analyzedFile/*("minisample.txt")*/;
		// Open file
		// * PROGRAMER'S NOTE: Derived from OneNote C++ programming
		// * notes
		analyzedFile.open(filename.c_str());
		// Print content from the input file if the input file
		// successfully opens
		if (analyzedFile.is_open())
		{
			// ** TEST
			/*if (testMode)
			{
				cout << "analyzedFile.is_open() == true" << endl;
			}*/
			// * PROGRAMMER'S NOTE: File reading is [SUCCESS] if
			// * getline command is NOT in "while" statement.
			/*while (*/getline(analyzedFile, line)/*)*/;
			/*{*/
				// ** TEST
				cout << "Print read line." << endl;
				/*cin >> line;*/
/*				if (testMode)
				{
					cout << "getline branch entered" << endl;
				}*/
				// Print the read line
				cout << "line: " << line << '\n';
			/*}*/
			analyzedFile.close();
		}
		else
		{
			cout << "File opening failed.";
		}

		// * PROGRAMMER'S NOTE: place final program algorithm below this
		// * line.
		// Retrieve the filename needed for file analysis
		string filename = argv[1];

		// Preapare variables for the four values to be recorded while
		// reading the input file
		int syllables = 0;
		int totalWords = 0;
		int sentences = 0;
		int difficultWords = 0;

		// Obtain the values needed for the readability index and score
		// calculations
		// * PROGRAMMER NOTE: Pass-by reference may be required here to
		// * update the multiple calculation variable values, as C++
		// * functions can otherwise return only one value to the
		// functions' callers.
		obtainValues(syllables,
			     totalWords,
			     sentences,
			     difficultWords);
/*
		// Calculate the Flesch readability index
		calculateFlesch(syllables,
				totalWords,
				sentences);
*/
/*	}*/
	
	return 0;
}


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
	// * PROGRAMMER'S NOTE (8/3/2019): Disabled to continue main program
	// * development
	/*bool wordPart = false;*/

	string currentLine = "";

	// Store the earliest unread file line
	// * PROGRAMMER'S NOTE: Code line [SUCCESSFUL]	
	getline(analyzedFile, currentLine);

	// Retrieve the next unread word from the line
	getWord();

	
}

string getWord(int currentIndex, string line)
{
	// Precondition:
	// Postcondition:

	char readCharacter = 'NULL';

	// From the starting index, locate the first non-whitespace character
	readCharacter = line.at(currentIndex);
	while ((readCharacter == ' ') && (currentIndex < line.length()))
	{
		// Check the next character in the line
		currentIndex++;
		readCharacter = line.at(currentIndex);
	}
	int wordStartIndex = currentIndex;

	// Locate the end of the current word
	int wordEndIndex = -1;
	if (currentIndex + 1 < line.length())
	{
		// Check the remaining line characters to find the word's end
		currentIndex++;
		readCharacter = line.at(currentIndex);
		while ((readCharacter != ' ') && (currentIndex < line.length()))
		{
			// Check the next character in the line
			currentIndex++;
			if (currentIndex < line.length())
				readCharacter = line.at(currentIndex);
		}

		// Store the index of the word end
		// * PROGRAMMER'S NOTE: The word index storage code below should
		// * function regardless of whether a space was detected or the
		// * line's end was reached
		wordEndIndex = currentIndex - 1;
	}
	else if (currentIndex + 1 == line.length())
	{
		// Regard the line's final character as the end of the word
		wordEndIndex = currentIndex;
	}

	// Retrieve the found word
	int wordLength = wordEndIndex - wordStartIndex + 1;
	string word = line.substr(wordStartIndex, wordLength);

	// Return the retrieved word to the function caller
	return word;
}
/*
float calculateFlesch()
{
	// Precondition:
	// Postcondition: The Flesch Readability Index was calculated and
	// returned to this function's caller

	// * PROGRAMMER'S NOTE: The values of alpha and beta likely require
	// * decimal format; thus, either a float or a double data type may be
	// * necessary for each of the two variables.

	// Calculate the "alpha" value
	float alpha = ;

	// Calculate the "beta" value
	float beta = ;

	return fleschIndex;
}
*/
