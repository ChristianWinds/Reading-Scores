// Code from GeeksforGeeks,
// https://www.geeksforgeeks.org/ways-to-read-input-from-console-in-java/
// Accessed September 11, 2019
import java.util.Scanner;
import java.lang.*;

public class Flesch
{
	public void storeDaleChallList()
	{
	}

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

	public boolean findInVector(String searchTerm,
				    DaleChallVector wordVector)
	{
		// Precondition:
		// Postcondition:

		// Search the vector to return whether the vector holds the
		// search term
		return wordVector.contains(searchTerm);
	}

	public void obtainValues()
	{
		// Precondition:
		// Postcondition:

		String currentLine = "";

		// Code from GeeksforGeeks,
		// https://www.geeksforgeeks.org/different-ways-reading-text-file-java/
		// Accessed Saturday, September 21, 2019
		/* Create an input file stream for the file to analyze */
		File analyzedFile = new File(analyzedFileName);

		/* Open the file to analyze */
		Scanner analyzedFileScanner = new Scanner(analyzedFile);

		if (/*Analyzed file is open*/)
		{
			// Retrieve the text file's values to prepare for the
			// reading score and index calculations
			while ((analyzedFileScanner.hasNextLine()) &&
			       (/*Analyzedfile is open*/))
			{
				currentLine = analyzedFileScanner.nextLine();

				if (/*Analyzed file is not at end of file*/)
				{
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

	public string getWord()
	{
	}

	public int countSyllables(String word)
	{
		// Precondition:
		// Postcondition:

		int currentIndex = 0;

		char readCharacter = '0';

		int syllablesCounted = 0;

		int wordLength = word.length();

		while (currentIndex < wordLength)
		{
			readCharacter = word.charAt(currentIndex);
			if (detectVowel(readCharacter))
			{
				if (((readCharacter == 'e') ||
				    (readCharacter == 'E')) &&
				    (currentIndex == wordLength - 1))
				{
					// Update the current index to not count
					// the word-ending "e" as a syllable
					currentIndex++;
				}
				else
				{
					// Read the successive vowels in the
					// word to find the end of the current
					// syllable
					while ((detectVowel(readCharacter)) &&
					       (currrentIndex < wordLength))
					{
						currentIndex++;
						if (currentIndex < wordLength)
							readCharacter = word.charAt(currentIndex);
					}
				}
			}
			else
			{
				currentIndex++;
			}
		}

		// Add one to a syllable count of zero to follow the minimum
		// syllale requirements for words
		if (syllables == 0)
			syllables++;

		return syllables;
	}

	public boolean detectSentenceEnd()
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

	public boolean detectVowel(char character)
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

	public boolean detectAlphabetChar(char character)
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

	public boolean detectNumericChar(char character)
	{
		// Precondition:
		// Postcondition:

		bool isNumeric = false;

		if ((character >= '0') &&
		    (character <= '9'))
			isNumeric = true;
		else
			isNumeric = false;

		return isNumeric;
	}

	public float calculateFlesch(int totalSyllables,
				     int totalWords,
				     int totalSentences)
	{
		// Precondition:
		// Postcondition:

		float alpha = (float ) totalSyllables / (float) totalWords;

		float beta = (float) totalWords / (float) totalSentences;

		float fleschIndex = 206.835 - alpha * 84.6 - beta * 1.015;

		return fleschIndex;
	}
	

	public float calculateFleschKincaid(int totalSyllables,
					    int totalWords,
					    int totalSentences)
	{
		// Precondition: The total numbers of syllables, words, and
		// sentences were obtained, and the total numbers of words and
		// sentences are not zero
		// Postcondition: The Flesch-Kincaid Readability Index was
		// calculated and returned to this function's caller

		// Calculate the alpha value to prepare to calculate the
		// Flesch-Kincaid Index
		float alpha = (float) totalSyllables / (float) totalWords;

		// Calculate the beta value to prepare to calculate the
		// Flesch-Kincaid Index
		float beta = (float) totalWords / (float) totalSentences;

		float fleschKincaidIndex = alpha * 11.8 + beta * 0.39 - 15.59;

		return fleschKincaidIndex;
	}

	public float calculateDaleChall(int difficultWords,
					int totalWords,
					int totalSentences)
	{
		// Precondition: The numbers of difficult words, total words,
		// and sentences were recorded, and the total numbers of words
		// and sentences are not zero
		// Postcondition: The Dale-Chall Readability Score was
		// calculated and returned to this function's caller

		// Calculate the alpha value to prepare to calculate the
		// Dale-Chall score
		float alpha = (float) difficultWords / (float) totalWords;

		// Calculate the beta value to prepare to calculate the
		// Dale-Chall score
		float beta = (float) totalWords / (float) totalSentences;

		// Calculate the percentage of difficult words to prepare to
		// calculate the Dale-Chall Score
		float difficultWordPercent = alpha * 100;

		float daleChallScore = difficultWordPercent * 0.1579 + beta *
				       0.0496;

		// Add 3.6365 to the Dale-Chall Score if the difficult word
		// percentage exceeds 5 to complete the required Dale-Chall
		// Score adjustment
		if (difficultWordPercent > 5)
			daleChallScore += 3.6365;

		return daleChallScore;
	}

	public static void main(String[] args)
	{
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

		// Prepare integer variables to store the analyzed file
		// values and calculate the reading scores and indexes
		ReadingValueCalculationVariables calculationVariables = new ReadingValueCalculationVariables();

		// To prepare for the readability index and score
		// calculations, obtain the analyzed file values
		obtainFileValues(syllables,
				 totalWords,
				 sentences,
				 difficultWords,
				 filename);

		// Calculate the reading indexes and score only if words
		// and syllables were found in the analyzed file to
		// avoid a division by zero error
		if ((totalWords > 0) &&
		    (syllables > 0))
		{
			float fleschIndex = calculateFlesch(syllables,
							    totalWords,
							    sentences);

			float fleschKincaidIndex = calculateFleschKincaid(syllables,
									  totalWords,
									  sentences);

			System.out.println("Flesch Readability Index: " + fleschIndex);
			System.out.println("Flesch-Kincaid Grade Level Index: " + fleschKincaidIndex);
		}
		else
		{
			if (!(totalWords > 0))
				System.out.println("No words found in file.");
			if (!(sentences > 0))
				System.out.println("No sentences found in file.");

			System.out.println("As a result, the readability calculations could not be performed.");
		}
	}
}
