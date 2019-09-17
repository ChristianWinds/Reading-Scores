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

					bool endOfLine = false;

					while (!(endOfLine))
					{
						bool endOfSentence = false;
						bool wordRetrieved = false;
					}

					String word = getWord()
				}
			}
		}
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
