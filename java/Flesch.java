import java.util.Scanner;

public class Flesch
{
	public void obtainValues()
	{
		// Precondition:
		// Postcondition:

		// Create an input file stream for the file to analyze;

		String currentLine = "";

		// Open the file to analyze;

		if (/*Analyzed file is open*/)
		{
			// Retrieve the text file's values to prepare for the
			// reading score and index calculations
			while ((/*Analyzed file is not at end of file)) &&
			       (/*Analyzedfile is open*/)
			{
				/*Store the earliest unread file line;*/

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

							totalSyllables += countSyllables(/*Retrieved word*/);
						}
					}
				}
			}
		}
	}

	public int countSyllables(/*Retrieved word*/)
	{
		// Precondition:
		// Postcondition:

		int currentIndex = 0;

		char readCharacter = '0';

		int syllablesCounted = 0;

		while (currentIndex < /* Retrieved word length*/)
		{
			readCharacter = /*Character at current word character index*/;
			if (detectVowel(readCharacter))
			{
				if (((readCharacter == 'e') ||
				    (readCharacter == 'E')) &&
				    (currentIndex == word.length() - 1))
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
					while (detectVowel(readCharacter)) &&
					       (currrentIndex < /*DetectedWordLength*/)
					{
						currentIndex++;
						if (currentIndex < /*Retrieved word length*/)
							readCharacter = /*Word character at currentIndex in word*/;
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

		if (((character >= 'A') &&
		    (character <= 'Z')) ||
		    ((character >= 'a') &&
		    (character <= 'z')))
			isAlphabetic = true;
		else
			isAlphabetic = false;

		return isAlphabetic;
	}

	public static void main (String[] args)
	{
		// Create a Scanner to read the keyboard entered filename of
		// the file to analyze
		Scanner keyboardInput = new Scanner (System.in);

		// Receive keyboard input to receive the filename of the file
		// to analyze
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
