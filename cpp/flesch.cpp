#include <cstdlib>
#include <string>

obtainValues(&syllables,
             &totalWords,
             &sentences,
             &difficultWords);
calculateFlesch();

// * PROGRAMMER NOTE: The parentheses beside main may require text to allow
// * the command line to be an input source.
int main()
{
	// Read the filename of the file to be analyzed
	;

	// Preapare variables for the four values to be recorded while reading
	// the input file
	int syllables = 0;
	int totalWords = 0;
	int sentences = 0;
	int difficultWords = 0;

	// Obtain the values needed for the readability index and score
	// calculations
	// * PROGRAMMER NOTE: Pass-by reference may be required here to
	// * update the multiple calculation variable values, as C++
	// * functions can otherwise return only one value to the functions'
	// * callers.
	obtainValues(syllables,
		     totalWords,
		     sentences,
		     difficultWords);

	// Calculate the Flesch readability index
	calculateFlesch();

	return 0;
}

obtainValues(&syllables,
	     &totalWords,
	     &sentences,
	     &difficultWords)
{
	// Precondition:
	// Postcondition:

}

calculateFlesch()
{
}
