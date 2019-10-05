import java.util.Scanner;
import java.util.*;
import java.io.File;
import java.lang.*;

public class Flesch
{
	// Code from GeeksforGeeks,
	// https://www.geeksforgeeks.org/different-ways-reading-text-file-java/
	// Accessed September 24, 2019
	public static void storeDaleChallList(WordVector daleChallVector) throws Exception
	{
		// Code from GeeksforGeeks,
		// https://www.geeksforgeeks.org/different-ways-reading-text-file-java/
		// Accessed September 24, 2019
		File analyzedFile = new File("/pub/pounds/CSC330/dalechall/wordlist1995.txt");
		Scanner analyzedFileScanner = new Scanner(analyzedFile);

		String word = "";

		while (analyzedFileScanner.hasNextLine())
		{
			word = analyzedFileScanner.nextLine();

			// Convert the word to an uppercase word to allow
			// non-case sensitive vector search
			word = word.toUpperCase();

			daleChallVector.wordVector.add(word);
		}

		System.out.println(daleChallVector.wordVector);
	}
/*
	public void insertAlphabetically(DaleChallVector wordVector,
					 String insertionWord)
	{
		// Precondition:
		// Postcondition:

		if (wordVector.daleChallVector.isEmpty())
		{
			wordVector.daleChallVector.add(insertionWord);
		}
		else
		{
			boolean duplicateWord = false;

			// Create index variables to use in finding the midpoint
			// of the word vector
			int currentMinIndex = 0;
			int currentMaxIndex = wordVector.daleChallVector.size() -
					      1;
			int currentMidIndex = currentMaxIndex / 2;

			while ((currentMaxIndex - currentMinIndex >= 0) &&
			       (!(duplicateWord)))
			{
				String currentMiddleIndexWord = wordVector.daleChallVector.get(currentMidIndex);
				if (insertionWord.compareToIgnoreCase(currentMiddleIndexWord) < 0)
				{
					// Update the maximum and middle index
					// values to locate the new search
					// midpoint after the current vector
					// word
					currentMaxIndex = currentMidIndex - 1;
					currentMidIndex = currentMinIndex + (currentMaxIndex - currentMinIndex) / 2;
				}
				else if (insertionWord.compareToIgnoreCase(currentMiddleIndexWord) > 0)
				{
					// Update the minimum and middle index
					// values to locate the new search
					// midpoint after the current vector
					// word
					currentMinIndex = currentMidIndex + 1;
					currentMidIndex = currentMinIndex + (currentMaxIndex - currentMinIndex) / 2;
				}
				else if (insertionWord.equalsIgnoreCase(currentMiddleIndexWord))
				{
					// Flag the word duplicate to avoid
					// adding a duplicate word to the vector
					duplicateWord = true;
				}
			}

			if (!(duplicateWord))
			{
				// Use the currentMidIndex value as an offset to
				// add the insertionWord to the vector in
				// alphabetic order
				wordVector.daleChallVector.add(currentMidIndex,
							       insertionWord);
			}
		}
	}
*/
/*	public boolean findInVector(String searchTerm,
				    DaleChallVector wordVector)
	{
		// Precondition:
		// Postcondition:

		// Search the vector to return whether the vector holds the
		// search term
		return wordVector.contains(searchTerm);
	}
*/
/* DISABLE
 * 	public void obtainValues()
	{
		// Precondition:
		// Postcondition:

		String currentLine = "";

		// Code from GeeksforGeeks,
		// https://www.geeksforgeeks.org/different-ways-reading-text-file-java/
		// Accessed Saturday, September 21, 2019
		*//* Create an input file stream for the file to analyze *//* DISABLE
		File analyzedFile = new File(analyzedFileName);

		*//* Open the file to analyze *//* DISABLE
		Scanner analyzedFileScanner = new Scanner(analyzedFile);

		if (*//*Analyzed file is open*//*analyzedFileScanner.hasNextLine())*/
//		{
			// Retrieve the text file's values to prepare for the
			// reading score and index calculations
//			while /*(*/(analyzedFileScanner.hasNextLine())/* &&
//			       (*//*Analyzedfile is open*//*))*/
/*			{
				currentLine = analyzedFileScanner.nextLine();

*///				if (/*Analyzed file is not at end of file*/analyzedFileScanner.hasNextLine())
/*				{
					int currentLineIndex = 0;

					boolean endOfLine = false;

					while (!(endOfLine))
					{
						boolean endOfSentence = false;
						boolean wordRetrieved = false;	

						// Retrieve the next unread word
						// from the analyzed file to
						// analyze the new word
						String word = getWord();

						// Prevent word and syllable
						// count updates if no word was
						// retrieved to avoid word and
						// syllable miscount
						if ((wordRetrieved) &&
						    (word != ""))
						{
							totalWords++;

							totalSyllables += countSyllables(word);
						}
					}
				}
			}
		}
	}
*/
/*	public String getWord(String line)
	{
		// Precondition:
		// Postcondition: The retrieved word is returned to the function
		// caller, and the currentIndex value is set one beyond the last
		// read index

		int lineLength = line.length();

		// Create a char variable to hold the characters read from the
		// word
		char readCharacter = 'a';

		do
		{
			if ((curentIndex < lineLength) &&
			    (!endOfSentence))
				readCharacter = line.at(currentIndex);

			if (detectSentenceEnd(readCharacter))
			{
				endOfSentence = true;
			}
			else if (detectAlphabetChar(readCharacter))
			{
				wordRead = true;
			}

			if ((readCharacter == ' ') &&
			    (currentIndex < lineLength))
			{
				currentIndex++;
			}
		} while((readCharacter == ' ') &&
			(currentIndex < lineLength) &&
			(!endOfSentence));

		// Create a String variable for the word to return to this
		// function's caller
		String word = "";

		if (endOfSentence)
		{
			// Set the wordRead Boolean and word string to indicate
			// no valid word was read
			wordRead = false;
			word = "";

			// Increment the currentIndex value to allow the program
			// to continue reading after the sentence end
			currentIndex++;
		}
		else if (!(currentIndex < lineLength))
		{

			// Set the wordRead Boolean and word string to indicate
			// no valid word was read
			wordRead = false;
			word = "";

			endOfLine = true;

			// Place the current index value at the line's final
			// character to prevent a line reading error
			currentIndex = lineLength - 1;
		}
		else
		{
			int wordStartIndex = currentIndex;
			int wordEndIndex = 0;

			// Read the remaining line characters to locate the
			// character index after the end of the current word
			while ((readCharacter != ' ') &&
			       (currentIndex < llineLength) &&
			       (!endOfSentence) &&
			       (!endOfLine))
			{
				// Increment the current index to read the next
				// unread character
				currentIndex++;

				if (!(currentIndex < lineLength))
				{
					endOfLine = true;
				}
				else
				{
					readCharacter = line.at(currentIndex);

					if (detectSentenceEnd(readCharacter))
					{
						endOfSentence = true;
					}

					if ((!wordRead) &&
					    (!endOfSentence))
					{
						if (detectAlphabetChar(readCharacter))
						{
							wordRead = true;
						}
					}

					if (!(detectWordCharacter(readCharacter)))
					{
						break;
					}
				}
			}

			wordEndIndex = currentIndex - 1;

			// Increment the current index to avoid counting the
			// same sentence twice
			currentIndex++;

			// If the current index exceeded the line length, place
			// the index at the line's final character to avoid a
			// line read error
			if (endOfLine)
			{
				currentIndex = lineLength - 1;
			}

			if (currentIndex >= lineLength)
			{
				endOfLine = true;
			}

			word = line.substring(wordStartIndex, wordEndIndex + 1);
		}

		//  If the current index is beyond the line end, flag the
		//  end-of-line flag and set the current index to the line's
		//  final character to avoid a line read error
		if (currentIndex >= lineLength)
		{
			endOfLine = true;
			currentIndex = lineLength - 1;
		}

		return word;
	}*/

	public static int countSyllables(String word)
	{
		// Precondition:
		// Postcondition:

		System.out.println("TEST: countSyllables: Starting");

		int currentIndex = 0;

		char readCharacter = '0';

		int syllables = 0;

		int wordLength = word.length();

		while (currentIndex < wordLength)
		{
			System.out.println("TEST: countSyllables: Passed <while (currentIndex < wordLength)>");

			readCharacter = word.charAt(currentIndex);
			if (detectVowel(readCharacter))
			{
				System.out.println("TEST: countSyllables: Passed <if (detectVowel(readCharacter))>");

				// Determine if the current vowel is a
				// word-ending 'e' to avoid counting a
				// word-ending 'e' as a syllable
				if (!(((readCharacter == 'e') ||
				    (readCharacter == 'E')) &&
				    (currentIndex == wordLength - 1)))
				{
					System.out.println("TEST: countSyllables: Passed <if (!(((readCharacter == 'e') || (readCharacter == 'E')) && (currentIndex == wordLength - 1)))>");
					syllables++;

					// Read the successive vowels in the
					// word to find the end of the current
					// syllable
					while ((detectVowel(readCharacter)) &&
					       (currentIndex < wordLength))
					{
						currentIndex++;
						if (currentIndex < wordLength)
							readCharacter = word.charAt(currentIndex);
					}
				}
				else
				{
					// Increment the current index to skip
					// the word-ending 'e' in syllable
					// counting
					currentIndex++;
				}
			}
			else
			{
				currentIndex++;
			}
		}

		// Add one to a syllable count of zero to follow the minimum
		// syllable requirements for words
		if (syllables == 0)
			syllables++;

		System.out.println("TEST: countSyllables: word \"" + word + "\" has " + syllables + "syllables");

		return syllables;
	}

	public static boolean detectSentenceEnd(char character)
	{
		// Precondition:
		// Postcondition: The state of whether the received character
		// was a sentence-ending character was returned to this
		// function's caller

		// Prepare a Boolean variable to flag a sentence end
		boolean endOfSentence = false;

		// Flag the endOfSentence Boolean if the received character
		// marks the end of a sentence
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

	public static boolean detectVowel(char character)
	{
		// Precondition:
		// Postcondition:

		Boolean isVowel = false;

		// Compare the received character to each vowel to deermine
		// whether the received character is a vowel
		if ((character == 'a')||
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
			isVowel = true;
		else
			isVowel = false;

		return isVowel;
	}

	public static boolean detectAlphabetChar(char character)
	{
		// Precondition:
		// Postcondition:

		boolean isAlphabetic = false;

		// Compare the received character to the uppercase and
		// lowercase alphabet characters to determine if the current
		// character is alphabetic
		if (((character >= 'A') &&
		    (character <= 'Z')) ||
		    ((character >= 'a') &&
		    (character <= 'z')))
			isAlphabetic = true;
		else
			isAlphabetic = false;

		return isAlphabetic;
	}

	public static boolean detectNumericChar(char character)
	{
		// Precondition:
		// Postcondition:

		boolean isNumeric = false;

		if ((character >= '0') &&
		    (character <= '9'))
			isNumeric = true;
		else
			isNumeric = false;

		return isNumeric;
	}

	public static boolean detectWordCharacter(char character)
	{
		// Precondition:
		// Postcondition:

		boolean isWordCharacter = false;

		// Check if the character is alphanumeric, a hyphen, or an
		// apostrophe to determine if the character is or is not part of
		// a word
		if ((detectAlphabetChar(character)) ||
		    (detectNumericChar(character)) ||
		    (character == '-') ||
		    (character == '\''))
		{
			isWordCharacter = true;
		}
		else
		{
			isWordCharacter = false;
		}

		return isWordCharacter;
	}

	public static double calculateFlesch(ReadValueCalcVariables readValueCalcVariables)
	{
		// Precondition:
		// Postcondition:

		// Calculate the alpha value to prepare to calculate the Flesch
		// Index
		double alpha = (double) readValueCalcVariables.syllables / (double) readValueCalcVariables.totalWords;

		// Calculate the beta value to prepare to calculate the Flesch
		// Index
		double beta = (double) readValueCalcVariables.totalWords / (double) readValueCalcVariables.sentences;

		double fleschIndex = 206.835 - alpha * 84.6 - beta * 1.015;

		return fleschIndex;
	}

	public static double calculateFleschKincaid(ReadValueCalcVariables readValueCalcVariables)
	{
		// Precondition: The total numbers of syllables, words, and
		// sentences were obtained, and the total numbers of words and
		// sentences are not zero
		// Postcondition: The Flesch-Kincaid Readability Index was
		// calculated and returned to this function's caller

		// Calculate the alpha value to prepare to calculate the
		// Flesch-Kincaid Index
		double alpha = (double) readValueCalcVariables.syllables / (double) readValueCalcVariables.totalWords;

		// Calculate the beta value to prepare to calculate the
		// Flesch-Kincaid Index
		double beta = (double) readValueCalcVariables.totalWords / (double) readValueCalcVariables.sentences;

		double fleschKincaidIndex = alpha * 11.8 + beta * 0.39 - 15.59;

		return fleschKincaidIndex;
	}

	public static double calculateDaleChallScore(ReadValueCalcVariables readValueCalcVariables)
	{
		// Precondition: The numbers of difficult words, total words,
		// and sentences were recorded, and the total numbers of words
		// and sentences are not zero
		// Postcondition: The Dale-Chall Readability Score was
		// calculated and returned to this function's caller

		// Calculate the alpha value to prepare to calculate the
		// Dale-Chall score
		double alpha = (double) readValueCalcVariables.difficultWords / (double) readValueCalcVariables.totalWords;

		// Calculate the beta value to prepare to calculate the
		// Dale-Chall score
		double beta = (double) readValueCalcVariables.totalWords / (double) readValueCalcVariables.sentences;

		// Calculate the percentage of difficult words to prepare to
		// calculate the Dale-Chall Score
		double difficultWordPercent = alpha * 100;

		double daleChallScore = difficultWordPercent * 0.1579 + beta *
				       0.0496;

		// Add 3.6365 to the Dale-Chall Score if the difficult word
		// percentage exceeds 5 to complete the required Dale-Chall
		// Score adjustment
		if (difficultWordPercent > 5)
			daleChallScore += 3.6365;

		return daleChallScore;
	}

	public static void getWords(String line,
				    WordVector daleChallVector,
				    ReadValueCalcVariables readValueCalcVariables)
	{
		int currentIndex = 0;
		int wordStartIndex = 0;
		int wordEndIndex = 0;
		int lineLength = line.length();
		boolean retrievingWord = false;
		String word = "";

		while (currentIndex < lineLength)
		{
			// Store the current word character to check that
			// character
			char currentCharacter = line.charAt(currentIndex);

			// Scan the line for an alphanumeric character to begin
			// retrieving a word
			if (detectAlphabetChar(currentCharacter) ||
			    detectNumericChar(currentCharacter))
			{
				wordStartIndex = currentIndex;
				retrievingWord = true;

				while ((retrievingWord) &&
				       (currentIndex < lineLength))
				{
					// Scan the line for sentence-ending
					// punctuation, another non-word
					// character, or the line end to stop
					// retrieving the word
					currentIndex++;
					if (currentIndex < lineLength)
					{
						// Update the currentCharacter
						// variable to check the new
						// current character
						currentCharacter = line.charAt(currentIndex);

						if (!detectWordCharacter(currentCharacter))
						{
							wordEndIndex = currentIndex;
							retrievingWord = false;
						}

						if (detectSentenceEnd(currentCharacter))
						{
							wordEndIndex = currentIndex;
							retrievingWord = false;
							readValueCalcVariables.sentences++;
						}
					}
					else
					{
						// Regard the line's final
						// character as the word's last
						// character to avoid a string
						// access error
						wordEndIndex = lineLength;
						retrievingWord = false;
					}
				}

				word = line.substring(wordStartIndex, wordEndIndex);
				word = trimWord(word);

				// Check if the retrieved word is a valid word
				// to prevent incorrect word and syllable counts
				if (detectValidWord(word))
				{
					readValueCalcVariables.totalWords++;
					System.out.println("getWords: word == \"" + word + "\"");
					readValueCalcVariables.syllables += countSyllables(word);

					/* Locate the word in the Dale-Chall Vector */
					boolean wordInVector = daleChallVector.wordVector.contains(word.toUpperCase());

					if (!(wordInVector))
					{
						readValueCalcVariables.difficultWords++;
					}

					System.out.println("TEST: getWords: Word \"" + word + "\" in vector: " + wordInVector);
				}
			}
			else if (detectSentenceEnd(currentCharacter))
			{
				readValueCalcVariables.sentences++;
			}

			// Increment the current index to look for another word
			currentIndex++;
		}
	}

	public static String trimWord(String word)
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
	                char lastWordCharacter = word.charAt(wordLength - 1);

	                // Check if the word's last character is not alphanumeric to
	                // decide whether to trim the word
	                while (((!(detectAlphabetChar(lastWordCharacter))) &&
	                       (!(detectNumericChar(lastWordCharacter)))) &&
	                       (wordLength > 0))
	                {
	                        // Trim the word to remove the non-alphanumeric
	                        // character from the word end
	                        word = word.substring(0, wordLength - 2);

	                        // Update the word length and stored last word character
	                        // to check the new last word character
	                        wordLength = word.length();
	                        if (wordLength > 0)
	                        {
	                                lastWordCharacter = word.charAt(wordLength - 1);
	                        }
	                }
	        }

	        return word;
	}

	public static boolean detectValidWord (String word)
	{
		// Precondition:
		// Postcondition:

		// Create variables to track word character indexes
		int currentIndex = 0;
		int wordLength = word.length();

		boolean wordIsValid = false;

		// Check if the word holds an alphabetic character to determine
		// if the word is valid
		while ((!wordIsValid) &&
		       (currentIndex < wordLength))
		{
			char currentCharacter = word.charAt(currentIndex);

			if (detectAlphabetChar(currentCharacter))
			{
				wordIsValid = true;
			}
			else
			{
				wordIsValid = false;
			}

			// Increment the current index to check the next
			// character
			currentIndex++;
		}

		return wordIsValid;
	}

	// Code from GeeksforGeeks,
	// https://www.geeksforgeeks.org/different-ways-reading-text-file-java/
	// Accessed September 24, 2019
	public static void main(String[] args) throws Exception
	{
		/* Create a Dale-Chall vector object */
		WordVector daleChallVector = new WordVector();

		/* Store the Dale-Chall wordlist */
		storeDaleChallList(daleChallVector);

		// Create a Scanner to read the keyboard entered filename of
		// the file to analyze
		// Code from GeeksforGeeks,
		// https://www.geeksforgeeks.org/ways-to-read-input-from-console-in-java/
		// Accessed September 11, 2019
		Scanner keyboardInput = new Scanner (System.in);

		// Receive keyboard input to receive the filename of the file
		// to analyze
		// Code from GeeksforGeeks,
		// https://www.geeksforgeeks.org/ways-to-read-input-from-console-in-java/
		// Accessed September 11, 2019
		String filename = keyboardInput.nextLine();

		// Code from GeeksforGeeks,
		// https://www.geeksforgeeks.org/different-ways-reading-text-file-java/
		// Accessed September 24, 2019
		File analyzedFile = new File(filename);
		Scanner analyzedFileScanner = new Scanner(analyzedFile);

		/* Create an object to store reading score variables */
		ReadValueCalcVariables readValueCalcVariables = new ReadValueCalcVariables();

		String line = "";

		while (analyzedFileScanner.hasNextLine())
		{
			line = analyzedFileScanner.nextLine();

			getWords(line, daleChallVector, readValueCalcVariables);
		}

		/* Create the empty Dale-Chall vector */

//		storeDaleChallList(/* Dale-Chall Vector */);

		// To prepare for the readability index and score
		// calculations, obtain the analyzed file values
/*		obtainFileValues(syllables,
				 totalWords,
				 sentences,
				 difficultWords,
				 filename);
*/
		// Calculate the reading indexes and score only if words
		// and syllables were found in the analyzed file to
		// avoid a division by zero error
		if ((readValueCalcVariables.totalWords > 0) &&
		    (readValueCalcVariables.syllables > 0))
		{
			double fleschIndex = calculateFlesch(readValueCalcVariables);

			double fleschKincaidIndex = calculateFleschKincaid(readValueCalcVariables);

			double daleChallScore = calculateDaleChallScore(readValueCalcVariables);

			System.out.println("Flesch Readability Index: " + fleschIndex);
			System.out.println("Flesch-Kincaid Grade Level Index: " + fleschKincaidIndex);
			System.out.println("Dale-Chall Readability Score: " + daleChallScore);
		}
		else
		{
			if (!(readValueCalcVariables.totalWords > 0))
				System.out.println("No words found in file.");
			if (!(readValueCalcVariables.sentences > 0))
				System.out.println("No sentences found in file.");

			System.out.println("As a result, the readability calculations could not be performed.");
		}
	}
}
