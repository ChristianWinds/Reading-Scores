#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <locale>
using namespace std;

bool testMode = true;
bool printFinalObtainedValues = true;
bool showCalculationValues = true;
bool printActivatingFunctions = true;
bool printFunctionSteps = true;
bool printVariables = true;
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
	// to avoid a file read error
	if (argc != 2)
	{
		cout << "Please enter one filename." << endl;
	}
	else
	{
		vector<string> daleChallVector;
		storeDaleChallList(daleChallVector);
		
		// Access the command line to retrieve the filename needed for
		// file analysis
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
			     daleChallVector,
			     filename);

		if ((totalWords > 0) &&
		    (syllables > 0))
		{
			float fleschIndex = calculateFlesch(syllables,
							    totalWords,
							    sentences);

			float fleschKincaidIndex = calculateFleschKincaid(syllables,
									  totalWords,
									  sentences);

			float daleChallScore = calculateDaleChall(difficultWords,
								  totalWords,
								  sentences);

			cout << "Flesch Readability Index: " <<
				fleschIndex <<
				endl;
			cout << "Flesch-Kincaid Grade Level Index: " <<
				fleschKincaidIndex <<
				endl;
			cout << "Dale-Chall Readability Score: " <<
				daleChallScore <<
				endl;
		}
		else
		{
			// Print an error message to explain why the reading
			// score calculations could not be performed
			if (!(totalWords > 0))
				cout << "No words found in file." << endl;
			if (!(sentences > 0))
				cout << "No sentences found in file." << endl;

			cout << "As a result, the readability calculations " <<
				"could not be performed." << endl;
		}
	}
	
	return 0;
}

void storeDaleChallList(vector<string> &daleChallVector)
{
	// Precondition: A Dale-Chall List file should exist in this function's
	// hard-coded Dale-Chall List file location, and the Dale-Chall vector
	// should be empty
	// Postcondition: The Dale-Chall vector was filled with the Dale-Chall
	// List file's contents

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
}

void insertAlphabetically(vector<string> &wordVector,
			  string insertionWord)
{
	// Precondition: The word to attempt to insert into the vector is not a
	// blank string, and the vector to receive the word is already
	// alphabetically sorted
	// Postcondition: The word received by this function was stored
	// alphabetically into the word vector

	if (wordVector.size() == 0)
	{
		// Place the word at the back of the vector to begin filling
		// the empty vector
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
			// Compare the alphabet order of the word to insert to
			// the current vector word to determine where to place
			// the word to insert, or to decide to not insert the
			// word if the word already exists in the vector
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
				// Flag the word duplicate to avoid adding a
				// duplicate word to the vector
				duplicateWord = true;
			}
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

}

bool findInVector(vector<string> wordVector,
		  string searchTerm)
{
	// Precondition: The word vector was sorted alphabetically
	// Postcondition: A Boolean value representing whether the search term
	// was present in the word vector was returned

	bool foundWord = false;

	// Convert the search term to a capitalized word to allow
	// non-case-sensitive search
	searchTerm = capitalizeWord(searchTerm);

	/* Locate the midpoint of the vector */
	int currentMinIndex = 0;
	int currentMaxIndex = wordVector.size() - 1;
	int currentMidIndex = currentMaxIndex / 2;

	while ((!(foundWord)) &&
	       (currentMaxIndex - currentMinIndex >= 0))
	{
		/* Determine if the current word is alphabetically further or earlier than the current vector word, or else matches the vector word */
		if (searchTerm < wordVector.at(currentMidIndex))
		{
			/* Locate the new search midpoint before the current vector word */
			currentMaxIndex = currentMidIndex - 1;
			currentMidIndex = currentMinIndex + (currentMaxIndex - currentMinIndex) / 2;
		}
		else if (searchTerm > wordVector.at(currentMidIndex))
		{
			/* Locate the new search midpoint after the current vector word */
			currentMinIndex = currentMidIndex + 1;	
			currentMidIndex = currentMinIndex + (currentMaxIndex - currentMinIndex) / 2;
		}
		else if (searchTerm == wordVector.at(currentMidIndex))
		{
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
	// Precondition: The Dale-Chall vector holds all words of a Dale-Chall
	// Word List, the numbers of syllables, total words, sentences, and
	// difficult words are zero, and a valid filename for a file to analyze
	// is stored
	// Postcondition: The numbers of syllables, total words, sentences, and
	// difficult words in the file were stored

	string currentInputFileLine = "";

	// Code from Cplusplus.com,
	// http://www.cplusplus.com/doc/tutorial/files/
	// Accessed Monday, September 2, 2019
	// Create an input file stream for the file to analyze
	ifstream analyzedFile;

	// Open the file to analyze
	analyzedFile.open(filename.c_str());

	if (analyzedFile.is_open())
	{
		// Retrieve the values for the file to analyze
		while ((!(analyzedFile.eof())) &&
		       (analyzedFile.is_open()))
		{
			// Store the earliest unread file line
			getline(analyzedFile,
				currentInputFileLine);

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

					string word = getWord(currentLineIndex,
							      currentInputFileLine,
							      endOfLine,
							      endOfSentence,
							      wordRetrieved);

					if ((wordRetrieved) &&
					    (word != "")) 
					{
						totalWords++;

						totalSyllables += countSyllables(word);

						// Check the word to determine
						// if the word is a difficult
						// word.
						if (!(findInVector(daleChallVector,
								   word)))
						{
							difficultWords++;
						}
					}

					if (endOfSentence)
					{
						totalSentences++;
					}
				}
			}
		}
	}
	else
	{
		cout << "File opening failed." << endl;
	}
}

string getWord(int &currentIndex,
	       string line,
	       bool &endOfLine,
	       bool &endOfSentence,
	       bool &wordRead)
{
	// Precondition: The currentIndex value is within the line string's
	// index range
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
		if (detectSentenceEnd(readCharacter))
		{
			endOfSentence = true;
		}
		else if (detectAlphabetChar(readCharacter))
		{
			wordRead = true;
		}

		// Flag whether the current character is alphanumeric to ensure
		// the retrieved word begins with an alphanumeric character
		if ((detectAlphabetChar(readCharacter)) ||
		    (detectNumericChar(readCharacter)))
		{
			alphanumericCharRead = true;
		}
		else
		{
			alphanumericCharRead = false;
		}

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
		// Set the wordRead Boolean and word string variable to
		// indicate no string was retrieved
		wordRead = false;
		word = "";

		// Advance the currentIndex value to place the index after the
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
	}
	else
	{
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
			// Increment the current index to read the next unread
			// character
			currentIndex++;

			// Stop the word end search if the line end is exceeded
			if (!(currentIndex < lineLength))
				endOfLine = true;
			else
			{
				readCharacter = line.at(currentIndex);

				if (detectSentenceEnd(readCharacter))
				{
					endOfSentence = true;
				}

				// If the current string was not yet validated
				// as a word, check the string to determine
				// whether to count the string as a word
				if ((!wordRead) &&
				    (!endOfSentence))
				{
					if (detectAlphabetChar(readCharacter))
						wordRead = true;
				}

				// If the current character is not a word
				// character, stop attempting to read other
				// characters to retrieve the current word
				if (!(detectWordCharacter(readCharacter)))
					break;
			}

		}

		wordEndIndex = currentIndex - 1;

		// Increment the currentIndex to avoid counting the same
		// sentence twice
		currentIndex++;

		if (currentIndex >= lineLength)
			endOfLine = true;

		// If the current index exceeded the line length, place the
		// index at the end of the line index range to avoid a string
		// index access error
		if (endOfLine)
			currentIndex = lineLength - 1;

		// Calculate the word's length to determine the number of
		// characters to copy from the line string to retrieve the word
		int wordLength = wordEndIndex - wordStartIndex + 1;

		word = line.substr(wordStartIndex, wordLength);

		// Send the word to the trimWord function to remove
		// non-alphanumeric characters from the end of the word
		word = trimWord(word);
	}

	// If the current index is beyond the line end, flag the end-of-line
	// flag and set the current index to the line's final character to
	// prevent errors beyond this function
	if (currentIndex >= lineLength)
	{
		endOfLine = true;
		currentIndex = lineLength - 1;
	}

	return word;
}

string capitalizeWord(string originalWord)
{
	// Precondition: The word sent to this function was not a blank string,
	// and the sent word holds alphabetic characters
	// Postcondition: This function made a string that cpoied the original
	// received word, but with all alphabetic letters capitalized, and
	// returned that string to this function's caller

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
		// decide whether to continue trimming the word
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
	// Precondition: The word received holds only non-whitespace characters,
	// and holds at least one alphabetic character
	// Postcondition: The number of syllables in the word was counted and
	// returned to this function's caller

	int wordLength = word.length();

	// Create an integer variable to track the current read character index
	// in the word
	int currentIndex = 0;

	// Create a char variable to hold each read character of the word
	char readCharacter = '0';

	int syllables = 0;

	while (currentIndex < wordLength)
	{
		readCharacter = word.at(currentIndex);

		if (detectVowel(readCharacter))
		{
			// To follow syllable-tallying rules, if the current
			// read character is an "e" at the word's end, do not
			// tally the vowel as a syllable
			if (((readCharacter == 'e') ||
			    (readCharacter == 'E')) &&
			    (currentIndex == wordLength - 1))
			{
				// Update currentIndex to skip the word-ending
				// "e"
				currentIndex++;
			}
			else
			{
				// Read the current group of one or more
				// successive vowels to count the entire group
				// as one syllable
				while ((detectVowel(readCharacter)) &&
				       (currentIndex < wordLength))
				{
					// Increment currentIndex to prepare to
					// check if the next unread word
					// character is a vowel
					currentIndex++;

					if (currentIndex < wordLength)
					{
						readCharacter = word.at(currentIndex);
					}
				}

				syllables++;
			}
		}
		else
		{
			// Increment currentIndex to prepare to read the word's
			// next character
			currentIndex++;
		}
	}
	
	// To follow syllable-tallying rules, add one to the syllable count if
	// no syllables were detected
	if (syllables == 0)
		syllables++;

	return syllables;
}

bool detectSentenceEnd(char character)
{
	// Precondition: A non-blank character was sent to this function
	// Postcondition: The state of whether the received character was a
	// sentence-ending character was returned to this function's caller

	bool endOfSentence = false;

	// Check the received character to determine if the character marks the
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
	// Precondition: A non-blank character was sent to this function
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
	// Precondition: A non-blank character was sent to this function
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
	// Precondition: A non-blank character was sent to this function
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
	// Precondition: A non-blank character was sent to this function
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
	// Precondition: The numbers of words, sentences, and syllables counted
	// are each greater than zero
	// Postcondition: The Flesch Readability Index was calculated and
	// returned to this function's caller

	// Calculate the alpha value to prepare to calculate the Flesch Index
	float alpha = (float) totalSyllables / (float) totalWords;

	// Calculate the beta value to prepare to calculate the Flesch Index
	float beta = (float) totalWords / (float) totalSentences;

	float fleschIndex = 206.835 - alpha * 84.6 - beta * 1.015;

	return fleschIndex;
}

float calculateFleschKincaid(int totalSyllables,
			     int totalWords,
			     int totalSentences)
{
	// Precondition: The total numbers of syllables, words, and sentences
	// were obtained and are each not zero
	// Postcondition: The Flesch-Kincaid Readability Index was calculated
	// and returned to this function's caller

	// Calculate the alpha value to prepare to calculate the Flesch-Kincaid
	// Index
	float alpha = (float) totalSyllables / (float) totalWords;

	// Calculate the beta value to prepare to calculate the Flesch-Kincaid
	// Index
	float beta = (float) totalWords / (float) totalSentences;

	float fleschKincaidIndex = alpha * 11.8 + beta * 0.39 - 15.59;

	return fleschKincaidIndex;
}

float calculateDaleChall(int difficultWords,
			 int totalWords,
			 int totalSentences)
{
	// Precondition: The numbers of difficult words, total words, and
	// sentences were recorded, and the total number words and the number of
	// sentences are not zero
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
