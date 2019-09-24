#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <locale>
using namespace std;

bool testMode = false;
bool printFinalObtainedValues = false;
bool showCalculationValues = false;
bool printActivatingFunctions = false;
bool printFunctionSteps = false;
bool printVariables = false;
void storeDaleChallList(vector<string> &daleChallVector);
void insertAlphabetically(vector<string> &wordVector,
                          string insertionWord);
void obtainValues(int &totalSyllables,
		  int &totalWords,
		  int &totalSentences,
		  int &difficultWords,
		  vector<string> daleChallVector,
		  string filename);
string getWord(int &currentIndex,
	       string line,
	       bool &endOfLine,
	       bool &endOfSentence,
	       bool &wordRead);
string capitalizeWord(string originalWord);
string trimWord(string word);
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
float calculateDaleChall(int difficultWords,
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
		vector<string> daleChallVector;
		if ((testMode) ||
		    (printActivatingFunctions))
		{
			cout << "main: Calling storeDaleChallList(daleChallVector)" << endl;
		}
		storeDaleChallList(daleChallVector);
		if (testMode)
		{
			cout << "main: Dale-Chall vector size after storeDaleChallList call == " << daleChallVector.size() << endl;
		}
		
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
		if ((testMode) ||
		    (printActivatingFunctions))
		{
			cout << "main: Calling obtainValues(syllables, totalWords, sentences, difficultWords, daleChallVector, filename)" << endl;
		}
		obtainValues(syllables,
			     totalWords,
			     sentences,
			     difficultWords,
			     daleChallVector,
			     filename);

		if ((testMode) ||
		    (printFinalObtainedValues))
		{
			cout << "main:" << endl;
			cout << "\tTotal counted syllables: " << syllables << endl;
			cout << "\tTotal counted words: " << totalWords << endl;
			cout << "\tTotal counted sentences: " << sentences << endl;
		}

		if ((totalWords > 0) &&
		    (syllables > 0))
		{
		if (testMode)
			cout << "main: Calling calculateFlesch" << endl;
		float fleschIndex = calculateFlesch(syllables,
						    totalWords,
						    sentences);

		if (testMode)
			cout << "main: Calling calculateFleschKincaid" << endl;
		float fleschKincaidIndex = calculateFleschKincaid(syllables,
								  totalWords,
								  sentences);

		float daleChallScore = calculateDaleChall(difficultWords,
							  totalWords,
							  sentences);

		// Print the readability scores
		if (testMode)
			cout << "main: Printing Readability Scores" << endl;
		cout << "Flesch Readability Index: " << fleschIndex << endl;
		cout << "Flesch-Kincaid Grade Level Index: " <<
			fleschKincaidIndex << endl;
		cout << "Dale-Chall Readability Score: " <<
			daleChallScore <<
			endl;
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

void storeDaleChallList(vector<string> &daleChallVector)
{
	// Precondition:
	// Postcondition:

	if ((testMode) ||
	    (printActivatingFunctions))
	{
		cout << "storeDaleChallList: Starting" << endl;
	}

	// Open the Dale-Chall List file to begin storing the list's words in a
	// vector
	// Code from Cplusplus.com,
	// http://www.cplusplus.com/doc/tutorial/files/
	// Accessed Monday, September 2, 2019
	ifstream daleChallFile;
	daleChallFile.open("/pub/pounds/CSC330/dalechall/wordlist1995.txt");

	if (daleChallFile.is_open())
	{
		while ((!(daleChallFile.eof())) &&
		       (daleChallFile.is_open()))
		{
			// Retrieve the next unread Dale-Chall file line to
			// retrieve the line's word
			string currentWord = "";
			getline(daleChallFile,
				currentWord);

			// Check if the current word is a blank string to avoid
			// placing a blank string into the Dale-Chall vector
			if (currentWord != "")
			{
				// Capitalize the current word to prepare later
				// non-case sensitive vector searches
				currentWord = capitalizeWord(currentWord);

				if ((testMode) ||
				    (printActivatingFunctions))
				{
					cout << "storeDaleChallList: Calling insertAlphabetically(daleChallVector, currentWord)" << endl;
				}

				insertAlphabetically(daleChallVector,
						     currentWord);
			}
		}

		daleChallFile.close();
	}
	else
	{
		cout << "The Dale-Chall wordlist file could not be opened." <<
			endl;
	}

	if (testMode)
	{
		cout << "storeDaleChallList: Dale-Chall List size at function end == " << daleChallVector.size() << endl;
	}
}

void insertAlphabetically(vector<string> &wordVector,
			  string insertionWord)
{
	// Precondition: The word to attempt to insert into the vector is not a
	// blank word, and the vector to receive the word is already
	// alphabetically sorted
	// Postcondition:

	if (testMode)
	{
		cout << "insertAlphabetically: Dale-Chall vector size at function start == " << wordVector.size() << endl;
	}

	if (wordVector.size() == 0)
	{
		wordVector.push_back(insertionWord);
	}
	else
	{
		bool duplicateWord = false;

		// Create index variables to use in finding the midpoint of the
		// word vector
		int currentMinIndex = 0;
		int currentMaxIndex = wordVector.size() - 1;
		int currentMidIndex = currentMaxIndex / 2;

		while ((currentMaxIndex - currentMinIndex >= 0) &&
		       (!(duplicateWord)))
		{
			if (testMode)
			{
				cout << "insertAlphabetically: while loop: currentMaxIndex{" << currentMaxIndex << "} - currentMinIndex{" << currentMinIndex << "} == " << currentMaxIndex - currentMinIndex << endl;
			}

			if (testMode)
			{
				cout << "insertAlphabetically: while loop: insertionWord == \"" << insertionWord << "\"; wordVector.at(currentMidIndex{" << currentMidIndex << "}) == \"" << wordVector.at(currentMidIndex) << "\"" << endl;
			}

			/* Determine if the current word is alphabetically further or earlier than the current vector word, or else matches the vector word */
			if (insertionWord < wordVector.at(currentMidIndex))
			{
				// Update the maximum and middle index values to
				// locate the new search midpoint before the
				// current vector word
				currentMaxIndex = currentMidIndex - 1;
				currentMidIndex = currentMinIndex + (currentMaxIndex - currentMinIndex) / 2;
			}
			else if (insertionWord > wordVector.at(currentMidIndex))
			{
				// Update the minimum and middle index values to
				// locate the new search midpoint after the
				// current vector word
				currentMinIndex = currentMidIndex + 1;	
				currentMidIndex = currentMinIndex + (currentMaxIndex - currentMinIndex) / 2;
			}
			else if (insertionWord == wordVector.at(currentMidIndex))
			{
				if (testMode)
				{
					cout << "insertAlphabetically: while loop: else if branch: Duplicate word detected" << endl;
				}

				// Flag the word duplicate to avoid adding a
				// duplicate word to the vector
				duplicateWord = true;
			}
		}

		if (testMode)
		{
			cout << "insertAlphabetically: Progressed beyond while loop" << endl;
		}

		if (!(duplicateWord))
		{
			// Create and use an iterator to place the word to
			// insert into the vector in alphabetical order
			// Code from Cplusplus.com,
			// http://www.cplusplus.com/reference/vector/vector/insert/
			// Accesed Friday, September 20th, 2019
			vector<string>::iterator wordVectorIterator;
			wordVectorIterator = wordVector.begin();
			wordVector.insert(wordVectorIterator + currentMidIndex,
					  insertionWord);
		}
	}

	if (testMode)
	{
		cout << "insertAlphabetically: Dale-Chall vector size at function end == " << wordVector.size() << endl;
	}
}

bool findInVector(vector<string> wordVector,
		  string searchTerm)
{
	// Precondition:
	// Postcondition:

	if ((testMode) ||
	    (printActivatingFunctions))
	{
		cout << "findInVector: Starting" << endl;
	}

	bool foundWord = false;

	// Convert the search term to a capitalized word to allow
	// non-case-sensitive search
	searchTerm = capitalizeWord(searchTerm);

	/* Locate the midpoint of the vector */
	int currentMinIndex = 0;
	int currentMaxIndex = wordVector.size() - 1;
	if ((testMode) ||
	    (printVariables))
	{
		cout << "findInVector: currentMaxIndex == " << currentMaxIndex << endl;
	}
	int currentMidIndex = currentMaxIndex / 2;

	if ((testMode) ||
	    (printFunctionSteps))
	{
		cout << "findInVector: Attempting to begin while loop" << endl;
	}

	while ((!(foundWord)) &&
	       (currentMaxIndex - currentMinIndex >= 0))
	{
		/* Determine if the current word is alphabetically further or earlier than the current vector word, or else matches the vector word */
		if (testMode)
		{
			cout << "findInVector: Current vector middle == \"" << wordVector.at(currentMidIndex) << "\"" << endl;
			cout << "              searchTerm == \"" << searchTerm << "\"" << endl;
		}
		if (searchTerm < wordVector.at(currentMidIndex))
		{
			/* Locate the new search midpoint before the current vector word */
			currentMaxIndex = currentMidIndex - 1;
			if ((testMode) ||
			    (printVariables))
			{
				cout << "findInVector: currentMaxIndex == " << currentMaxIndex << endl;
			}
			currentMidIndex = currentMinIndex + (currentMaxIndex - currentMinIndex) / 2;
			if ((testMode) ||
			    (printVariables))
			{
				cout << "findInVector: currentMidIndex == " << currentMidIndex << endl;
			}
		}
		else if (searchTerm > wordVector.at(currentMidIndex))
		{
			/* Locate the new search midpoint after the current vector word */
			currentMinIndex = currentMidIndex + 1;	
			if ((testMode) ||
			    (printVariables))
			{
				cout << "findInVector: currentMinIndex == " << currentMinIndex << endl;
			}
			currentMidIndex = currentMinIndex + (currentMaxIndex - currentMinIndex) / 2;
			if ((testMode) ||
			    (printVariables))
			{
				cout << "findInVector: currentMidIndex == " << currentMidIndex << endl;
			}
		}
		else if (searchTerm == wordVector.at(currentMidIndex))
		{
			if ((testMode) ||
			    (printFunctionSteps))
			{
				cout << "findInVector: Word found; setting foundWord to true" << endl;
			}
			foundWord = true;
		}
	}

	return foundWord;
}

void obtainValues(int &totalSyllables,
		  int &totalWords,
		  int &totalSentences,
		  int &difficultWords,
		  vector<string> daleChallVector,
		  string filename)
{
	if (testMode)
		cout << "obtainValues: Starting" << endl;
	// Precondition: The Dale-Chall vector holds all words of a Dale-Chall
	// Word List
	// Postcondition:

	// Initialize a Boolean for presence of a partial word segment at the
	// end of an input file line
	/*bool wordPart = false;*/

	string currentInputFileLine = "";

	// Code from Cplusplus.com,
	// http://www.cplusplus.com/doc/tutorial/files/
	// Accessed Monday, September 2, 2019
	// Create an input file stream for the file to analyze
	ifstream analyzedFile;

	// Open the file to analyze
	analyzedFile.open(filename.c_str());

	if (testMode)
		cout << "obtainValues: Opened file: " << filename.c_str() << endl;

	if (analyzedFile.is_open())
	{
		// Retrieve the values for the file to analyze
		while ((!(analyzedFile.eof())) &&
		       (analyzedFile.is_open()))
		{
			if (testMode)
				cout << "obtainValues: analyzedFile.eof == " << analyzedFile.eof() << endl;
			// Store the earliest unread file line
			getline(analyzedFile,
				currentInputFileLine);

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
						cout << "\t currentInputFileLine == " << currentInputFileLine << endl;
						cout << "\t endOfLine == " << endOfLine << endl;
					}
					if (testMode)
						cout << "obtainValues: Calling getWord" << endl;
					string word = getWord(currentLineIndex,
							      currentInputFileLine,
							      endOfLine,
							      endOfSentence,
							      wordRetrieved);

					if ((wordRetrieved) &&
					    (word != "")) 
					{
						totalWords++;

						// Add the number of syllables
						// in the retrieved word to the
						// syllable total
						totalSyllables += countSyllables(word);

						/* Check the word to determine if the word is a difficult word.*/
						if ((testMode) ||
						    (printActivatingFunctions))
						{
							cout << "obtainValues: Calling findInVector(daleChallVector, word)" << endl;
						}

						if (!(findInVector(daleChallVector,
								   word)))
						{
							if ((testMode) ||
							    (true))
							{
								cout << "obtainValues: Difficult word found: \"" << word << "\"" << endl;
							}
							difficultWords++;
						}
					}

					// Update the number of counted sentences
					if (endOfSentence)
					{
						totalSentences++;
						if (testMode)
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

	int lineLength = line.length();

	// Create an alphanumeric character detection Boolean to prevent
	// non-alphanumeric characters from beginning a word
	bool alphanumericCharRead = false;

	// Create a char variable to hold the characters read from the word
	char readCharacter = 'a';

	// From the starting index, locate the first alphanumeric character to
	// identify the first character of the word to retrieve
	do
	{
		if ((currentIndex < lineLength) &&
		    (!endOfSentence))
			readCharacter = line.at(currentIndex);

		// If the read character is a sentence-ending punctuation, flag
		// the end of sentence Boolean
		if (testMode)
			cout << "getWord: endOfSentence = detectSentenceEnd(" << readCharacter << ");" << endl;

		if (detectSentenceEnd(readCharacter))
		{
			endOfSentence = true;
			if (testMode)
				cout << "getWord: endOfSentence set to true (first word character)" << endl;
		}
		else if (detectAlphabetChar(readCharacter))
		{
			wordRead = true;
		}

		if ((testMode) ||
		    (true))
		{
			cout << "getWord: Checking for alphanumeric word start" << endl;
		}

		// Flag whether the current character is alphanumeric to ensure
		// the retrieved word begins with an alphanumeric character
		if ((detectAlphabetChar(readCharacter)) ||
		    (detectNumericChar(readCharacter)))
		{
			if ((testMode) ||
			    (true))
			{
				cout << "getWord: Alphanumeric word start found" << endl;
			}

			alphanumericCharRead = true;
		}
		else
		{
			alphanumericCharRead = false;
		}

		if (testMode)
			cout << "getWord: endOfSentence == " << endOfSentence << endl;

		// * ERROR: detectSentenceEnd not called for first read character; called late [BUGFIX ADDED]
		// *	ERROR: detectSentenceEnd check not performed if first read character is not a space; conversion of while loop to do while loop possible
		// If an alphanumeric word start was not yet found, advance the
		// current index to the next character in the line to locate an
		// alphnumeric word start
		if (((readCharacter == ' ') ||
		    (!(alphanumericCharRead))) &&
		    (currentIndex < lineLength))
			currentIndex++;
	} while (((readCharacter == ' ') ||
		 (!(alphanumericCharRead))) &&
		 (currentIndex < lineLength) &&
		 (!endOfSentence));

	// Create a word variable to hold the word to return to this function's
	// caller
	string word = "";

	if (endOfSentence)
	{
		if (testMode)
			cout << "getWord: endOfSentence == " << endOfSentence << "; setting word to \"\"." << endl;

		// Set the wordRead Boolean and word string variable to
		// indicate no string was retrieved
		wordRead = false;
		word = "";

		// Advance the currentIndex value to the index after the
		// sentence end
		currentIndex++;
	}
	else if (!(currentIndex < lineLength))
	{
		// Set the wordRead Boolean and word string variable to
		// indicate no string was retrieved
		wordRead = false;
		word = "";

		endOfLine = true;

		// Place the current index at the line's final character to
		// prevent a line reading error
		currentIndex = lineLength - 1;

		// Set the word string variable to a blank string to indicate
		// no string was retrieved
	}
	else
	{
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
		       (currentIndex < lineLength) &&
		       (!endOfSentence) &&
		       (!endOfLine))
		{
			// Move the current index to the next unread character
			currentIndex++;

			// Stop the word end search if the line end is exceeded
			if (!(currentIndex < lineLength))
				endOfLine = true;
			else
			{
				readCharacter = line.at(currentIndex);

				// Flag the end of sentence flag if
				// sentence-ending punctuation was read
				if (detectSentenceEnd(readCharacter))
				{
					endOfSentence = true;
					if (testMode)
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

		// Increment the currentIndex to avoid counting the same
		// sentence twice
		currentIndex++;

		// If the current index exceeded the line length, place the
		// index at the final line index
		if (endOfLine)
			currentIndex = lineLength - 1;

		// Update the end of line flag if the end of the received line
		// was reached
		if (currentIndex >= lineLength)
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

		// Send the word to the trimWord function to remove
		// non-alphanumeric characters from the end of the word
		word = trimWord(word);

		if (testMode)
			cout << "getWord: Retrieved word: \"" << word << "\"" << endl;
	}

	// If the current index is beyond the line end, flag the end-of-line
	// flag and set the current index to the line's final character to
	// prevent errors beyond this function
	if (currentIndex >= lineLength)
	{
		endOfLine = true;
		currentIndex = lineLength - 1;
	}

	if (testMode)
		cout << "getWord: After this iteration's endOfSentence flag, the line index's character is '" << line.at(currentIndex) << "'" << endl;
	// Return the retrieved word to the function caller
	if (testMode)
		cout << "getWord: Returning " << word << " to function caller" << endl;
	return word;
}

string capitalizeWord(string originalWord)
{
	// Precondition:
	// Postcondition:

	// Code from Cplusplus.com,
	// http://www.cplusplus.com/reference/locale/toupper/
	// Accessed Friday, September 20th, 2019
	locale loc;

	// Create a string variable with an empty string to hold the upcoming
	// capitalized word
	string capitalizedWord = "";

	for (string::size_type i = 0; i < originalWord.length(); ++i)
	{
		capitalizedWord += toupper(originalWord[i], loc); 
	}

	return capitalizedWord;
}

string trimWord(string word)
{
	// Precondition: The received word holds at least one alphanumeric
	// character
	// Postcondition: The received word was shortened up to the word's last
	// alphanumeric character, and the word was returned to this function's
	// caller

	// Store the word's length for use in locating the word's last character
	int wordLength = word.length();

	if (wordLength > 0)
	{
		char lastWordCharacter = word.at(wordLength - 1);

		// Check if the word's last character is not alphanumeric to
		// decide whether to trim the word
		while (((!(detectAlphabetChar(lastWordCharacter))) &&
		       (!(detectNumericChar(lastWordCharacter)))) &&
		       (wordLength > 0))
		{
			// Trim the word to remove the non-alphanumeric
			// character from the word end
			word = word.substr(0, wordLength - 1);

			// Update the word length and stored last word character
			// to check the new last word character
			wordLength = word.length();
			if (wordLength > 0)
			{
				lastWordCharacter = word.at(wordLength - 1);
			}
		}
	}

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

	int wordLength = word.length();

	// Create an integer variable to track the current read character index
	// in the word
	int currentIndex = 0;

	// Create a char variable to hold each read character of the word
	char readCharacter = '0';

	int syllables = 0;

	// Count each syllable in the word
	while (currentIndex < wordLength)
	{
		// Read the current word character
		readCharacter = word.at(currentIndex);

		if (detectVowel(readCharacter))
		{
			// If the current read character is an "e" at the
			// word's end, do not tally the vowel as a syllable
			if (((readCharacter == 'e') ||
			    (readCharacter == 'E')) &&
			    (currentIndex == wordLength - 1))
			{
				// Update the current read index and do not
				// count the vowel as a syllable
				currentIndex++;
			}
			else
			{
				// Find the successive syllables in the word
				while ((detectVowel(readCharacter)) &&
				       (currentIndex < wordLength))
				{
					// Read the next unread character of the
					// word if unread characters remain
					currentIndex++;
					if (currentIndex < wordLength)
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

bool detectSentenceEnd(char character)
{
	// Precondition:
	// Postcondition: The state of whether the received character was a
	// sentence-ending character was returned to this function's caller

	if (testMode)
		cout << "detectSentenceEnd: Starting" << endl;

	if (testMode)
	{
		cout << "detectSentenceEnd: Parameter:" << endl;
		cout << "\tcharacter == '" << character << "'" << endl;
	}

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

	// Check if the character is alphanumeric, a hyphen, or an apostrophe to
	// determine if the character is or is not part of a word
	if ((detectAlphabetChar(character)) ||
	    (detectNumericChar(character)) ||
	    (character == '-') ||
	    (character == '\''))
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

	// Calculate the alpha value to prepare to calculate the Flesch Index
	if ((testMode) &&
	    (false))
	{
		cout << "calculateFlesch: Calculating alpha" << endl;
	}
	float alpha = (float) totalSyllables / (float) totalWords;
	if (testMode)
		cout << "calculateFlesch: alpha == " << alpha << endl;
	// Calculate the beta value to prepare to calculate the Flesch Index
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
	// Precondition: The total numbers of syllables, words, and sentences
	// were obtained, and the total numbers of words and sentences are not
	// zero
	// Postcondition: The Flesch-Kincaid Readability Index was calculated
	// and returned to this function's caller

	// Calculate the alpha value to prepare to calculate the Flesch-Kincaid
	// Index
	float alpha = (float) totalSyllables / (float) totalWords;
	if ((testMode) ||
	    (showCalculationValues))
		cout << "calculateFleschKincaid: alpha == " << alpha << endl;

	// Calculate the beta value to prepare to calculate the Flesch-Kincaid
	// Index
	float beta = (float) totalWords / (float) totalSentences;
	if ((testMode) ||
	    (showCalculationValues))
		cout << "calculateFleschKincaid: beta == " << beta << endl;

	float fleschKincaidIndex = alpha * 11.8 + beta * 0.39 - 15.59;

	return fleschKincaidIndex;
}

float calculateDaleChall(int difficultWords,
			 int totalWords,
			 int totalSentences)
{
	// Precondition: The numbers of difficult words, total words, and
	// sentences were recorded, and the total numbers of words and sentences
	// are not zero
	// Postcondition: The Dale-Chall Readability Score was calculated and
	// returned to this function's caller

	// Calculate the alpha value to prepare to calculate the Dale-Chall
	// score
	float alpha = (float) difficultWords / (float) totalWords;

	// Calculate the beta value to prepare to calculate the Dale-Chall
	// score
	float beta = (float) totalWords / (float) totalSentences;

	// Calculate the percentage of difficult words to prepare to calculate
	// the Dale-Chall Score
	float difficultWordPercent = alpha * 100;

	float daleChallScore = difficultWordPercent * 0.1579 + beta * 0.0496;

	// Add 3.6365 to the Dale-Chall Score if the difficult word percentage
	// exceeds 5 to complete the required Dale-Chall Score adjustment
	if (difficultWordPercent > 5)
		daleChallScore += 3.6365;

	return daleChallScore;
}
