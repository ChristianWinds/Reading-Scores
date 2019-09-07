// * A MESSAGE TO THE READER: All "PROGRAMMER'S NOTE" comments are intended to
// * be removed (or reworked into regular comments if helpful) before the final
// * submission of both this program and future Organization of Programming
// * Languages programs.

// * PROGRAMMER'S NOTE: Current Goal (8/29/2019): Read a text file [SUCCESSFUL]
// * PROGRAMMER'S NOTE: Current Goal (9/4/2019): Count the number of syllables
// * 	- PROGRAMMER'S NOTE: Subgoal (9/4/2019): Add special word end "e"
// *	  counting rule to algorithm [RUNNING; UNEVALUATED]
// * PROGRAMMER'S NOTE: Current Goal (9/5/2019): Refine word and syllable detection
// *	- Potential issue (9/5/2019): Detection of period and comma-separated numbers
// *	  (e.g., 1,299; 1.7)
// *	- Error (9/4/2019) - Line index not updating properly [CORRECTED]
// *	- Error (9/4/2019) - Text read becomes out of range at line end
// *	  [CORRECTED]
// *	- Error (9/4/2019) - Program hangs with multi-line file [CORRECTED]
// *		- (9/4/2019) Likely related to ending "e" syllable count
// *		  behavior;  program hangs on word "line" [CORRECTED]
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
		  int &totalSentences,
		  int &difficultWords,
		  string filename);
string getWord(int &currentIndex,
	       string line,
	       bool &endOfLine,
	       bool &endOfSentence);
int countSyllables(string word);
bool detectSentenceEnd(char character);
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
		  int &totalSentences,
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
			if (testMode)
				cout << "obtainValues: analyzedFile.eof == " << analyzedFile.eof() << endl;
			// Store the earliest unread file line
			// * PROGRAMMER'S NOTE: Code line [SUCCESSFUL]	
			getline(analyzedFile, currentLine);

			if (testMode)
				cout << "obtainValues: analyzedFile.eof == " << analyzedFile.eof() << endl;
			if (!(analyzedFile.eof()))
			{
				// Create an integer variable to hold the
				// current line's current index
				int currentLineIndex = 0;

				// Create a Boolean to detect the end of the
				// current line
				bool endOfLine = false;

				// Read each word of the current line
				while (!(endOfLine))
				{
					// Create a Boolean to detect if a
					// sentence end was reached
					bool endOfSentence = false;

					// Retrieve the next unread word from
					// the line
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
							      endOfLine,
							      endOfSentence);

					// If a word was retrieved, update the
					// total numbers of words and syllables
					if (word != "")
					{
						totalWords++;

						// Add the number of syllables
						// in the retrieved word to the
						// syllable total
						totalSyllables += countSyllables(word);
					}

					// Update the number of counted sentences
					if (endOfSentence)
						totalSentences++;
				}
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
	       bool &endOfLine,
	       bool &endOfSentence)
{
	if (testMode)
		cout << "getWord: Starting" << endl;
	// Precondition:
	// Postcondition: The retrieved word is returned to the function caller,
	// and the currentIndex value is set one beyond the last read index

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

		// If the read character is a sentence-ending punctuation, flag
		// the end of sentence Boolean
		endOfSentence = detectSentenceEnd(readCharacter);
	}

	// Create a word variable to hold the word to return to this function's
	// caller
	string word = "";

	if (endOfSentence)
	{
		// Set the word string variable to a blank string to indicate
		// no string was retrieved
		word = "";
	}
	else if (!(currentIndex < line.length())
	{
	}
	else
	{
		// Record the index location of the word beginning
		int wordStartIndex = currentIndex;

		// Create a word end index variable to store the ending index of
		// the word
		int wordEndIndex = -1;

		// Locate the character index after the end of the current word
		while ((readCharacter != ' ') &&
		       (currentIndex < line.length()) &&
		       (!endOfSentence) &&
		       (!endOfLine))
		{
			currentIndex++;

			// Stop the word end search if the line end is exceeded
			if (!(currentIndex < line.length())
				endOfLine = true;
			else
			{
				// Read the current character at the line end
				readCharacter = line.at(currentIndex);

				// Flag the end of sentence flag if
				// sentence-ending punctuation was read
				if (detectSentenceEnd(readCharacter))
					endOfSentence = true;
			}

		}

		// Record the index of the word end
		wordEndIndex = currentIndex - 1;

		// If the current index exceeded the line length, place the
		// index at the final line index
		if (endOfLine)
			currentIndex = line.length() - 1;

		/* DISABLE FOR SIMPLIFICATION
		if (currentIndex + 1 < line.length())
		{
			// Check the remaining line characters to find the
			// word's end
			currentIndex++;
			readCharacter = line.at(currentIndex);
			while ((readCharacter != ' ') &&
			       (currentIndex < line.length()) &&
			       (!endOfSentence))
			{
				// Determine if a sentence end was reached


				// Check the next character in the line
				currentIndex++;
				if (currentIndex < line.length())
					readCharacter = line.at(currentIndex);
				else
				{
					// Flag that the end of the text line was
					// reached
					endOfLine = true;
				}
			}

			// Store the index of the word end
			// * PROGRAMMER'S NOTE: The word index storage code
			// * below should function regardless of whether a space
			// * was detected or the line's end was reached
			wordEndIndex = currentIndex - 1;
		}
		else if (currentIndex + 1 == line.length())
		{
			// Flag the end of line Boolean
			endOfLine = true;

			// Regard the line's final character as the end of the word
			wordEndIndex = currentIndex;
		}
		*/

		// Update the end of line flag if the end of the received line was reached
		if (currentIndex >= line.length())
			endOfLine = true;

		// Retrieve the found word
		int wordLength = wordEndIndex - wordStartIndex + 1;
		word = line.substr(wordStartIndex, wordLength);
	}

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
			// If the current read character is not an "e" at the
			// word's end, tally the current word syllable
			if ((readCharacter == 'e') &&
			    (currentIndex == word.length() - 1))
			{
				// Update the current read index
				currentIndex++;
			}
			else
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
					// Read the next unread character of the
					// word if unread characters remain
					currentIndex++;
					if (currentIndex < word.length())
						readCharacter = word.at(currentIndex);
				}

				// Increment the number of found syllables
				syllables++;
			}
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

	if (testMode)
	{
		cout << "countSyllables: Syllables counted in word \""
		     << word << "\" == " << syllables << endl;
	}

	// Return the number of detected syllables to the function's caller
	return syllables;
}

bool detectSentenceEnd (char character)
{
	// Precondition:
	// Postcondition:

	// Prepare a Boolean variable to flag a sentence end
	bool endOfSentence = false;

	// Flag the endOfSentence Boolean if the received character marks the
	// end of a sentence
	if ((readCharacter == '.') ||
	    (readCharacter == ':') ||
	    (readCharacter == ';') ||
	    (readCharacter == '?') ||
	    (readCharacter == '!'))
		endOfSentence = true;
	else
		endOfSentence = false;

	// Return the endOfSentence Boolean to this function's caller
	return endOfSentence;
}

bool detectVowel()
{
	// Precondition:
	// Postcondition:

	// Create a Boolean to flag whether the recceived character is a vowel
	bool vowel = false;

	// Flag the vowel Boolean if the received character is a vowel
	
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
