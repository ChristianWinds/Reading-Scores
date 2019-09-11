import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
public class flesch
{
	public static void main (String[] args) throws IOException
	{
		// To avoid an error, analyze an input file only if one filename
		// was entered on the command line
		if ()
		{
			System.out.println("Please enter one filename.");
		}
		else
		{
			String filename = ;

			// Prepare integer variables to store the analyzed file
			// values and calculate the reading scores and indexes
			int syllables = 0;
			int totalWords = 0;
			int sentences = 0;
			int difficultWords = 0;

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
					cout << System.out.println("No words found in file.");
				if (!(sentences > 0))
					cout << System.out.println("No sentences found in file.");

				System.out.println("As a result, the readability calculations could not be performed.");
			}
		}
	}
}
