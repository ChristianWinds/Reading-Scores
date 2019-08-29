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
	// * PROGRAMMER'S NOTE: C++ code read line required
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
	calculateFlesch(syllables,
			totalWords,
			sentences);

	return 0;
}

void obtainValues(&syllables,
                  &totalWords,
                  &sentences,
                  &difficultWords)
{
	// Precondition:
	// Postcondition:

	// Initialize a Boolean for presence of a partial word segment at the
	// end of an input file line
	// * PROGRAMMER'S NOTE: The name of this Boolean may need improvement,
	// * and this initialization's placement may require change to a more
	// * relevant location for usage timing
	bool wordPart = false;

	// Store the earliest unread file line
	string currentLine = ;

	
}

calculateFlesch()
{
	// Precondition:
	// Postcondition: The Flesch Readability Index was calculated and
	// returned to this function's caller

	;
}
