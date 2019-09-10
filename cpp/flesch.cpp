#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

bool testMode = false;
bool printFinalObtainedValues = true;
bool showCalculationValues = true;
void obtainValues(int &totalSyllables,
		  int &totalWords,
		  int &totalSentences,
		  int &difficultWords,
		  string filename);
string getWord(int &currentIndex,
	       string line,
	       bool &endOfLine,
	       bool &endOfSentence,
	       bool &wordRead);
int countSyllables(string word);
bool detectSentenceEnd(char character);
bool detectVowel(char character);
bool detectAlphabetChar(char character);
bool detectNumericChar(char character);
bool detectWordCharacter(char character);
float calculateFlesch(int totalSyllables,
		      int totalWords,
		      int totalSentences);
float calculateFleschKincaid(int totalSyllables,
			     int totalWords,
			     int totalSentences);

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
		obtainValues(syllables,
			     totalWords,
			     sentences,
			     difficultWords,
			     filename);

		if ((testMode) ||
		    (printFinalObtainedValues))
		{
			cout << "main:" << endl;
			cout << "\tTotal counted syllables: " << syllables << endl;
			cout << "\tTotal counted words: " << totalWords << endl;
			cout << "\tTotal countedSentences: " << sentences << endl;
		}

		if ((totalWords > 0) &&
		    (syllables > 0))
		{
		// Calculate the Flesch Readability Index
		if (testMode)
			cout << "main: Calling calculateFlesch" << endl;
		float fleschIndex = calculateFlesch(syllables,
						    totalWords,
						    sentences);

		// Calculate the Flesch-Kincaid Grade Level Index
		if (testMode)
			cout << "main: Calling calculateFleschKincaid" << endl;
		float fleschKincaidIndex = calculateFleschKincaid(syllables,
								  totalWords,
								  sentences);

		// Print the readability scores
		if (testMode)
			cout << "main: Printing Readability Scores" << endl;
		cout << "Flesch Readability Index: " << fleschIndex << endl;
		cout << "Flesch-Kincaid Grade Level Index: " <<
			fleschKincaidIndex << endl;
		cout << "Dale-Chall Readability Score: " << /*daleChallScore << */endl;
		}
		else
		{
			// If no words or no syllables were found in the file,
			// report the absences of words and syllables
			if (!(totalWords > 0))
				cout << "No words found in file." << endl;
			if (!(sentences > 0))
				cout << "No sentences found in file." << endl;

			// State that the readability calculations could not be
			// performed
			cout << "As a result, the readability calculations " <<
				"could not be performed." << endl;
		}
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

					// Create a Boolean to detect whether a word was retrieved
					bool wordRetrieved = false;

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
							      endOfSentence,
							      wordRetrieved);

					// If a word was retrieved, update the
					// total numbers of words and syllables
					if ((wordRetrieved) &&
					    (word != "")) 
					{
						totalWords++;

						// Add the number of syllables
						// in the retrieved word to the
						// syllable total
						totalSyllables += countSyllables(word);
					}

					// Update the number of counted sentences
					if (endOfSentence)
					{
						totalSentences++;
						if ((testMode) ||
						    (true))
						{
							cout << "obtainValues: Incremented totalSentences; totalSentences == " << totalSentences << endl;
						}
					}
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
	       bool &endOfSentence,
	       bool &wordRead)
{
	if (testMode)
		cout << "getWord: Starting" << endl;
	// Precondition:
	// Postcondition: The retrieved word is returned to the function caller,
	// and the currentIndex value is set one beyond the last read index

	// Create a char variable to hold the characters read from the word
	char readCharacter = 'a';

	// From the starting index, locate the first non-whitespace character
	do
	{
		// Read the current character if the current index is within the line
		if ((currentIndex < line.length()) &&
		    (!endOfSentence))
			readCharacter = line.at(currentIndex);

		// If the read character is a sentence-ending punctuation, flag
		// the end of sentence Boolean
		if ((testMode) ||
		    (true))
			cout << "getWord: endOfSentence = detectSentenceEnd(" << readCharacter << ");" << endl;
		if (detectSentenceEnd(readCharacter))
		{
			endOfSentence = true;
			if ((testMode) ||
			    (true))
				cout << "getWord: endOfSentence set to true (first word character)" << endl;
		}
		else if (detectAlphabetChar(readCharacter))
		{
			// Flag the current read characters as a word
			wordRead = true;
		}
		if (testMode)
			cout << "getWord: endOfSentence == " << endOfSentence << endl;

		// * ERROR: detectSentenceEnd not called for first read character; called late [BUGFIX ADDED]
		// *	ERROR: detectSentenceEnd check not performed if first read character is not a space; conversion of while loop to do while loop possible
		// If a word start was not yet found, advance the current index
		// to the next character in the line
		if ((readCharacter == ' ') &&
		    (currentIndex < line.length()))
			currentIndex++;
	} while ((readCharacter == ' ') &&
		 (currentIndex < line.length()) &&
		 (!endOfSentence));

	// Create a word variable to hold the word to return to this function's
	// caller
	string word = "";

	if (endOfSentence)
	{
		if (testMode)
			cout << "getWord: endOfSentence == " << endOfSentence << "; setting word to \"\"." << endl;

		// Set the word read flag to false
		wordRead = false;

		// Set the word string variable to a blank string to indicate
		// no string was retrieved
		word = "";

		// Advance the currentIndex value to the index after the
		// sentence end
		currentIndex++;
	}
	else if (!(currentIndex < line.length()))
	{
		// Flag that the line's end was reached
		endOfLine = true;

		// Set the word read flag to false
		wordRead = false;

		// Place the current index at the end of the line
		currentIndex = line.length() - 1;

		// Set the word string variable to a blank string to indicate
		// no string was retrieved
		word = "";
	}
	else
	{
		// Record the index location of the word beginning
		if ((testMode) &
		    (false))
		{
			cout << "getWord: Assigning currentIndex " << currentIndex << "to wordStartIndex" << endl;
		}
		int wordStartIndex = currentIndex;

		// Create a word end index variable to store the ending index of
		// the word
		int wordEndIndex = 0;

		// Locate the character index after the end of the current word
		while ((readCharacter != ' ') &&
		       (currentIndex < line.length()) &&
		       (!endOfSentence) &&
		       (!endOfLine))
		{
			// Move the current index to the next unread character
			currentIndex++;

			// Stop the word end search if the line end is exceeded
			if (!(currentIndex < line.length()))
				endOfLine = true;
			else
			{
				// Read the current character at the line end
				readCharacter = line.at(currentIndex);

				// Flag the end of sentence flag if
				// sentence-ending punctuation was read
				if (detectSentenceEnd(readCharacter))
				{
					endOfSentence = true;
					if ((testMode) ||
					    (true))
						cout << "getWord: endOfSentence set to true (final word character)" << endl;
				}

				// Ensure that the current set of characters is
				// a word
				if ((!wordRead) &&
				    (!endOfSentence))
				{
					if (detectAlphabetChar(readCharacter))
						wordRead = true;
				}

				// End word index search if the current
				// character is not a word character
				if (!(detectWordCharacter(readCharacter)))
					break;
			}

		}

		// Record the index of the word end
		wordEndIndex = currentIndex - 1;

		// If the current index exceeded the line length, place the
		// index at the final line index
		if (endOfLine)
			currentIndex = line.length() - 1;

		// Update the end of line flag if the end of the received line
		// was reached
		if (currentIndex >= line.length())
			endOfLine = true;

		// Retrieve the found word
		if ((testMode) &&
		    (false))
		{
			cout << "getWord: Retrieving word" << endl;
			cout << "\twordLength = " << wordEndIndex << " - " << wordStartIndex << " + 1" << endl;
		}
		int wordLength = wordEndIndex - wordStartIndex + 1;
		word = line.substr(wordStartIndex, wordLength);
		if ((testMode) ||
		    (true))
			cout << "getWord: Retrieved word: \"" << word << "\"" << endl;
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
	// Precondition: The word received holds only non-whitespace characters,
	// and holds at least one alphabetic character
	// Postcondition:

	// Create an integer variable to track the current read character index
	// in the word
	int currentIndex = 0;

	// Create a char variable to hold each read character of the word
	char readCharacter = '0';

	int syllables = 0;

	// Count each syllable in the word
	while (currentIndex < word.length())
	{
		// Read the current word character
		readCharacter = word.at(currentIndex);

		if (detectVowel(readCharacter))
		{
			// If the current read character is an "e" at the
			// word's end, do not tally the vowel as a syllable
			if (((readCharacter == 'e') ||
			    (readCharacter == 'E')) &&
			    (currentIndex == word.length() - 1))
			{
				// Update the current read index and do not
				// count the vowel as a syllable
				currentIndex++;
			}
			else
			{
				// Find the successive syllables in the word
				while ((detectVowel(readCharacter)) &&
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

	if (testMode)
		cout << "detectSentenceEnd: Starting" << endl;

	if (testMode)
	{
		cout << "detectSentenceEnd: Parameter:" << endl;
		cout << "\tcharacter == '" << character << "'" << endl;
	}

	// Prepare a Boolean variable to flag a sentence end
	bool endOfSentence = false;

	// Flag the endOfSentence Boolean if the received character marks the
	// end of a sentence
	if ((character == '.') ||
	    (character == ':') ||
	    (character == ';') ||
	    (character == '?') ||
	    (character == '!'))
		endOfSentence = true;
	else
		endOfSentence = false;

	// Return the endOfSentence Boolean to this function's caller
	return endOfSentence;
}

bool detectVowel(char character)
{
	// Precondition:
	// Postcondition:

	// Create a Boolean to flag whether the recceived character is a vowel
	bool vowel = false;

	// Flag the vowel Boolean if the received character is a vowel
	if ((character == 'a') ||
	    (character == 'A') ||
	    (character == 'e') ||
	    (character == 'E') ||
	    (character == 'i') ||
	    (character == 'I') ||
	    (character == 'o') ||
	    (character == 'O') ||
	    (character == 'u') ||
	    (character == 'U') ||
	    (character == 'y') ||
	    (character == 'Y'))
		vowel = true;
	else
		vowel = false;

	// Return the vowel Boolean to this function's caller
	return vowel;
}

bool detectAlphabetChar(char character)
{
	// Precondition:
	// Postcondition:

	// Create a Boolean to hold whether the received character is an
	// alphabetic character
	bool isAlphabetic = false;

	// Determine if the received character is an alphabetic character
	if (((character >= 'A') &&
	    (character <= 'Z')) ||
	    ((character >= 'a') &&
	    (character <= 'z')))
		isAlphabetic = true;
	else
		isAlphabetic = false;

	return isAlphabetic;
}

bool detectNumericChar(char character)
{
	// Precondition:
	// Postcondition:

	bool isNumeric = false;

	// Check the character to determine if the received character is a
	// numeric character
	if ((character >= '0') &&
	    (character <= '9'))
		isNumeric = true;
	else
		isNumeric = false;

	return isNumeric;
}

bool detectWordCharacter(char character)
{
	// Precondition:
	// Postcondition:

	bool isWordCharacter = false;

	// Check if the character is alphanumeric or a hyphen to determine if
	// the character is or is not part of a word
	if ((detectAlphabetChar(character)) ||
	    (detectNumericChar(character)) ||
	    (character == '-'))
		isWordCharacter = true;
	else
		isWordCharacter = false;

	return isWordCharacter;
}

float calculateFlesch(int totalSyllables,
		      int totalWords,
		      int totalSentences)
{
	// Precondition:
	// Postcondition: The Flesch Readability Index was calculated and
	// returned to this function's caller

	if (testMode)
	{
		cout << "calculateFlesch: Starting. Parameters: " << endl;
		cout << "\ttotalSyllables == " << totalSyllables << endl;
		cout << "\ttotalWords == " << totalWords << endl;
		cout << "\ttotalSentences == " << totalSentences << endl;
	}

	// * PROGRAMMER'S NOTE: The values of alpha and beta likely require
	// * decimal format; thus, either a float or a double data type may be
	// * necessary for each of the two variables.

	// Calculate the "alpha" value
	if ((testMode) &&
	    (false))
	{
		cout << "calculateFlesch: Calculating alpha" << endl;
	}
	float alpha = (float) totalSyllables / (float) totalWords;
	if (testMode)
		cout << "calculateFlesch: alpha == " << alpha << endl;
	// Calculate the "beta" value
	float beta = (float) totalWords / (float) totalSentences;
	if (testMode)
		cout << "calculateFlesch: beta == " << beta << endl;
	// Calculate the Flesch index
	float fleschIndex = 206.835 - alpha * 84.6 - beta * 1.015;

	return fleschIndex;
}

float calculateFleschKincaid(int totalSyllables,
			     int totalWords,
			     int totalSentences)
{
	// Precondition:
	// Postcondition: The Flesch-Kincaid Readability Index was calculated
	// and returned to this function's caller

	// * PROGRAMMER'S NOTE: The values of alpha and beta likely require
	// * decimal format; thus, either a float or a double data type may be
	// * necessary for each of the two variables.

	// Calculate the "alpha" value
	float alpha = (float) totalSyllables / (float) totalWords;
	if ((testMode) ||
	    (showCalculationValues))
		cout << "calculateFleschKincaid: alpha == " << alpha << endl;

	// Calculate the "beta" value
	float beta = (float) totalWords / (float) totalSentences;
	if ((testMode) ||
	    (showCalculationValues))
		cout << "calculateFleschKincaid: beta == " << beta << endl;

	// Calculate the Flesch-Kincaid Grade Level Index
	float fleschKincaidIndex = alpha * 11.8 + beta * 0.39 - 15.59;

	return fleschKincaidIndex;
}
