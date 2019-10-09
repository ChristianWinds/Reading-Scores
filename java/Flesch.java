/* Programmer Name: Christian Winds
 * Course: CSC330 Organization of Programming Languages
 * School Year: 2019-2020 School Year */

import java.util.Scanner;
import java.util.*;
import java.io.File;
import java.lang.Math;
import java.lang.*;

public class Flesch
{
	// Code from GeeksforGeeks,
	// https://www.geeksforgeeks.org/different-ways-reading-text-file-java/
	// Accessed September 24, 2019
	public static void storeDaleChallList(WordVector daleChallVector) throws Exception
	{
		// Precondition: A Dale-Chall List file existed in the location
		// hard-coded into this function, the Dale-Chall List file holds
		// only one word in each file line, and the Dale-Chall vector
		// was empty
		// Postcondition: All Dale-Chall List contents were placed into
		// the Dale-Chall vector as uppercase words and in alphabetical
		// order

		// Code from GeeksforGeeks,
		// https://www.geeksforgeeks.org/different-ways-reading-text-file-java/
		// Accessed September 24, 2019
		File daleChallFile = new File("/pub/pounds/CSC330/dalechall/wordlist1995.txt");
		Scanner daleChallFileScanner = new Scanner(daleChallFile);

		String word = "";

		while (daleChallFileScanner.hasNextLine())
		{
			word = daleChallFileScanner.nextLine();

			// Convert the word to an uppercase word to allow
			// non-case sensitive vector search
			word = word.toUpperCase();

			daleChallVector.wordVector.add(word);
		}
	}

	public static int countSyllables(String word)
	{
		// Precondition:
		// Postcondition:

		int currentIndex = 0;

		char readCharacter = '0';

		int syllables = 0;

		int wordLength = word.length();

		while (currentIndex < wordLength)
		{
			readCharacter = word.charAt(currentIndex);
			if (detectVowel(readCharacter))
			{
				// Determine if the current vowel is a
				// word-ending 'e' to avoid counting a
				// word-ending 'e' as a syllable
				if (!(((readCharacter == 'e') ||
				    (readCharacter == 'E')) &&
				    (currentIndex == wordLength - 1)))
				{
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
		// Precondition: A non-blank character was sent to this function
		// Postcondition: A Boolean value representing whether this
		// function's received character was a vowel was returned to
		// this function's caller

		Boolean isVowel = false;

		// Compare the received character to each vowel to determine
		// whether the received character is a vowel
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
			isVowel = true;
		else
			isVowel = false;

		return isVowel;
	}

	public static boolean detectAlphabetChar(char character)
	{
		// Precondition: A non-blank character was sent to this function
		// Postcondition: A Boolean value representing whether this
		// function's received character was an alphabetic character was
		// returned to this function's caller

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
		// Precondition: A non-blank character was sent to this function
		// Postcondition: A Boolean value representing whether this
		// function's received character was a numeric character was
		// returned to this function's caller

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
		// Precondition: A non-blank character was sent to this function
		// Postcondition: A Boolean value representing whether this
		// function's received character was a valid word character by
		// Flesch Score calculation requirements was returned to this
		// function's caller

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

	public static int calculateFlesch(ReadValueCalcVariables readValueCalcVariables)
	{
		// Precondition: The total numbers of syllables, words, and
		// sentences were counted from a text file, and each of those
		// numbers are not zero
		// Postcondition:

		// Calculate the alpha value to prepare to calculate the Flesch
		// Index
		double alpha = (double) readValueCalcVariables.syllables / (double) readValueCalcVariables.totalWords;

		// Calculate the beta value to prepare to calculate the Flesch
		// Index
		double beta = (double) readValueCalcVariables.totalWords / (double) readValueCalcVariables.sentences;

		double fleschIndexDouble = 206.835 - (alpha * 84.6) - (beta * 1.015);

		// Round the Flesch Index to an integer to complete the Flesch
		// Index's required rounding
		int fleschIndexInt = (int)roundToDecimalPlaces(fleschIndexDouble,
							       0);

		return fleschIndexInt;
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

		double fleschKincaidIndex = (alpha * 11.8) +
					    (beta * 0.39) - 15.59;

		// Round the Flesch-Kincaid Index to one decimal place to
		// complete the Flesch-Kincaid Index's required rounding
		fleschKincaidIndex = roundToDecimalPlaces(fleschKincaidIndex,
							  1);

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

		double daleChallScore = (difficultWordPercent * 0.1579) +
					(beta * 0.0496);

		// Add 3.6365 to the Dale-Chall Score if the difficult word
		// percentage exceeds 5 to complete the required Dale-Chall
		// Score adjustment
		if (difficultWordPercent > 5)
			daleChallScore += 3.6365;

		// Round the Dale-Chall Score to one decimal place to complete
		// the score's needed rounding
		daleChallScore = roundToDecimalPlaces(daleChallScore, 1);

		return daleChallScore;
	}

	// Code from GeeksforGeeks,
	// https://www.geeksforgeeks.org/rounding-floating-point-number-two-decimal-places-c-c/
	// Accessed Wednesday, October 9th, 2019
	public static double roundToDecimalPlaces(double originalNumber,
						  int decimalPlaces)
	{
		// Precondition: The original number sent to this function to be
		// rounded was a valid double value, and the number of decimal
		// places for rounding was zero or greater
		// Postcondition: The original number was rounded to the number
		// of decimal places specified to this function, and the
		// rounding result was returned to this function's caller

		// Multiply the original number by ten to the number of desired
		// decimal places, then add 0.5 to the result to apply the digit
		// changes caused by rounding
		double roundedValue = originalNumber * (Math.pow(10, decimalPlaces)) + 0.5;

		// Typecast the value being rounded into an integer to remove
		// the excess decimal places
		roundedValue = (int)roundedValue;

		// Divide the value being rounded by 10 to the desired number of
		// decimal places to place the correct number of decimal places
		// in the rounded value
		roundedValue = roundedValue / (Math.pow(10, decimalPlaces));

		return roundedValue;
	}

	public static void getWords(String line,
				    WordVector daleChallVector,
				    ReadValueCalcVariables readValueCalcVariables)
	{
		// Precondition:
		// Postcondition:

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

						// If the current character is
						// not a valid word character,
						// set the word retrieval flag
						// to "false" to prepare to stop
						// reading new characters into
						// the current word
						if (!detectWordCharacter(currentCharacter))
						{
							wordEndIndex = currentIndex;
							retrievingWord = false;
						}

						// If the current character is a
						// sentence-ending character,
						// set the word retrieval flag
						// to "false" to prepare to stop
						// reading new characters into
						// the current word
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

					// Search for the word in the Dale-Chall
					// vector to determine whether the word
					// is a difficult word
					boolean wordInVector = daleChallVector.wordVector.contains(word.toUpperCase());

					if (!(wordInVector))
					{
						readValueCalcVariables.difficultWords++;
					}
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
	        // Postcondition: The received word was trimmed up to the word's
	        // last alphanumeric character, and the trimmed word was
	        // returned to this function's caller

	        // Store the word's length for use in locating the word's last
	        // character
	        int wordLength = word.length();

	        if (wordLength > 0)
	        {
	                char lastWordCharacter = word.charAt(wordLength - 1);

	                // Check if the word's last character is not
	                // alphanumeric to decide whether to trim the word
	                while (((!(detectAlphabetChar(lastWordCharacter))) &&
	                       (!(detectNumericChar(lastWordCharacter)))) &&
	                       (wordLength > 0))
	                {
	                        // Trim the word to remove the non-alphanumeric
	                        // character from the word end
	                        word = word.substring(0,
						      wordLength - 2);

	                        // Update the word length and stored last word
	                        // character to check the new last word character
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
		// Precondition: The string this function received was a
		// non-empty string
		// Postcondition: Whether this function's received string was a
		// valid word was returned to this function's caller

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
		// Create a Dale-Chall vector to hold the Dale-Chall Word List
		WordVector daleChallVector = new WordVector();

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
		System.out.print("Enter the name of a file to analyze: ");
		String filename = keyboardInput.nextLine();

		// Code from GeeksforGeeks,
		// https://www.geeksforgeeks.org/different-ways-reading-text-file-java/
		// Accessed September 24, 2019
		File analyzedFile = new File(filename);
		Scanner analyzedFileScanner = new Scanner(analyzedFile);

		// Create an object to store the values needed for the reading
		// score and index calculations
		ReadValueCalcVariables readValueCalcVariables = new ReadValueCalcVariables();

		String line = "";

		// Analyze each file line of the file selected for analysis to
		// obtain the values needed for the reading score and index
		// calculations
		while (analyzedFileScanner.hasNextLine())
		{
			line = analyzedFileScanner.nextLine();

			getWords(line,
				 daleChallVector,
				 readValueCalcVariables);
		}

		/* Test printing */
		System.out.println("Total words: " + readValueCalcVariables.totalWords);
		System.out.println("Syllables: " + readValueCalcVariables.syllables);
		System.out.println("Sentences: " + readValueCalcVariables.sentences);
		System.out.println("Difficult words: " + readValueCalcVariables.difficultWords);

		// Calculate the reading indexes and score only if words
		// and syllables were found in the analyzed file to
		// avoid a division by zero error
		if ((readValueCalcVariables.totalWords > 0) &&
		    (readValueCalcVariables.syllables > 0))
		{
			int fleschIndex = calculateFlesch(readValueCalcVariables);

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
