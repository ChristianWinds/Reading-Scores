// * A MESSAGE TO THE READER: All "PROGRAMMER'S NOTE" comments are intended to
// * be removed (or reworked into regular comments if helpful) before the final
// * submission of both this program and future Organization of Programming
// * Languages programs.

// * PROGRAMMER'S NOTE: Current Goal (8/29/2019): Read a text file [SUCCESSFUL]
// * PROGRAMMER'S NOTE: Current Goal (9/4/2019): Count the number of syllables
// * in a text file
// *	- Error (9/4/2019) - Line index not updating properly
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
bool testMode = true;
/* DISABLE
string readLine();
*/
void obtainValues(int &totalSyllables,
		  int &totalWords,
		  int &sentences,
		  int &difficultWords,
		  string filename);
string getWord(int &currentIndex,
	       string line,
	       bool &endOfLine);
int countSyllables(string word);
/* DISABLE
float calculateFlesch();
*/

// * PROGRAMMER NOTE: The parentheses beside main may require text to allow
// * the command line to be an input source. [OK]
int main(int argc, char* argv[])
{
	// Run the program only if one filename was entered on the command line
	if (argc != 2)
	{
		// Ask the user to enter a filename
		cout << "Please enter one filename." << endl;
	}
	else
	{
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
			     difficultWords,
			     filename);
/*
		// Calculate the Flesch readability index
		calculateFlesch(syllables,
				totalWords,
				sentences);
*/
	}
	
	return 0;
}

void obtainValues(int &totalSyllables,
		  int &totalWords,
		  int &sentences,
		  int &difficultWords,
		  string filename)
{
	if (testMode)
		cout << "obtainValues: Starting" << endl;
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

	// Create an input file stream for the file to analyze
	ifstream analyzedFile;

	// Create a string variable to hold the current read line
	string currentLine = "";

	// Open the file to analyze
	analyzedFile.open(filename.c_str());

	if (analyzedFile.is_open())
	{
		// Retrieve the values for the file to analyze
		while ((!(analyzedFile.eof())) &&
		       (analyzedFile.is_open()))
		{
			// Store the earliest unread file line
			// * PROGRAMMER'S NOTE: Code line [SUCCESSFUL]	
			getline(analyzedFile, currentLine);

			// Create an integer variable to hold the current line's
			// current index
			int currentLineIndex = 0;

			// Create a Boolean to detect the end of the current
			// line
			bool endOfLine = false;

			// Read each word of the current line
			while (!(endOfLine))
			{
				// Retrieve the next unread word from the line
				if (testMode)
				{
					cout << "obtainValues: getWord call upcoming. Parameters:" << endl;
					cout << "\t currentLineIndex == " << currentLineIndex << endl;
					cout << "\t currentLine == " << currentLine << endl;
					cout << "\t endOfLine == " << endOfLine << endl;
				}
				if (testMode)
					cout << "obtainValues: Calling getWord" << endl;
				string word = getWord(currentLineIndex,
						      currentLine,
						      endOfLine);

				// Increment the number of words
				totalWords++;

				// Determine the number of syllables in the
				// retrieved word
				int wordSyllables = countSyllables(word);

				// Add the word's number of syllables to the
				// syllable total
				totalSyllables += wordSyllables;
			}
		}
	}
	else
	{
		// Report that the file opening attempt failed
		cout << "File opening failed." << endl;
	}
}

string getWord(int &currentIndex,
	       string line,
	       bool &endOfLine)
{
	if (testMode)
		cout << "getWord: Starting" << endl;
	// Precondition:
	// Postcondition: The retrieved word is returned to the function caller

	// Create a char variable to hold the characters read from the word
	char readCharacter = 'a';

	// From the starting index, locate the first non-whitespace character
	readCharacter = line.at(currentIndex);
	while ((readCharacter == ' ') &&
	       (currentIndex < line.length()))
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
		while ((readCharacter != ' ') &&
		       (currentIndex < line.length()))
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
		// Flag the end of line Boolean
		endOfLine = true;

		// Regard the line's final character as the end of the word
		wordEndIndex = currentIndex;
	}

	// Retrieve the found word
	int wordLength = wordEndIndex - wordStartIndex + 1;
	string word = line.substr(wordStartIndex, wordLength);

	// Return the retrieved word to the function caller
	if (testMode)
		cout << "getWord: Returning " << word << " to function caller" << endl;
	return word;
}

int countSyllables(string word)
{
	if (testMode)
		cout << "countSyllables: Starting" << endl;
	if (testMode)
		cout << "countSyllables: Parameter: word == " << word << endl;
	// Precondition: The word received holds only non-whitespace characters
	// Postcondition:

	// Create an integer variable to track the current read character index
	// in the word
	int currentIndex = 0;

	// Create a char variable to hold each read character of the word
	char readCharacter = 'a';

	// Create a variable to hold the number of syllables in the word
	int syllables = 0;

	// Count each syllable in the word
	while (currentIndex < word.length())
	{
		// Read the current word character
		readCharacter = word.at(currentIndex);

		if ((readCharacter == 'a') ||
		    (readCharacter == 'e') ||
		    (readCharacter == 'i') ||
		    (readCharacter == 'o') ||
		    (readCharacter == 'u') ||
		    (readCharacter == 'y'))
		{
			// Find the successive syllables in the word
			while (((readCharacter == 'a') ||
			       (readCharacter == 'e') ||
		               (readCharacter == 'i') ||
			       (readCharacter == 'o') ||
			       (readCharacter == 'u') ||
			       (readCharacter == 'y')) &&
			       (currentIndex < word.length()))
			{
				// Read the next unread character of the word
				// if unread characters remain
				currentIndex++;
				if (currentIndex < word.length())
					readCharacter = word.at(currentIndex);
			}

			// Increment the number of found syllables
			syllables++;
		}
		else
		{
			// Prepare to read the word's next character
			currentIndex++;
		}
	}
	
	// Add one to the syllable count if no syllables were detected
	if (syllables == 0)
		syllables++;

	// Return the number of detected syllables to the function's caller
	return syllables;
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
