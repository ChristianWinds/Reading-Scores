#!/usr/bin/perl -w
use warnings;
use strict;

sub TrimWord
{
=begin comment
Precondition:
Postcondition:
=cut
	my $word = $_[0];
	my $wordlength = length $word;
	my $firstwordcharacter = '';

	# Retrieve the word's first character only if the word has a length more than zero to avoid an error
	if ($wordlength > 0)
	{
		$firstwordcharacter = substr($word, 0, 1);
	}

	# Check the word's left to remove non-word characters
	while (($wordlength > 0) and
	       (not (DetectAlphabetChar($firstwordcharacter))))
	{
		$word = substr($word, 1);
		$wordlength = length $word;

		# Retrieve the word's first character only if the word has a length more than zero to avoid an error
		if ($wordlength > 0)
		{
			$firstwordcharacter = substr($word, 0, 1);
		}
	}

	my $lastwordcharacter = '';

	# Retrieve the word's last character only if the word has a length more
	# than zero to avoid an error
	if ($wordlength > 0)
	{
		$lastwordcharacter = substr($word, -1);
	}

	# Check the word's right to remove non-word characters
	while (($wordlength > 0) and
	       (not (DetectAlphanumericChar($lastwordcharacter))))
	{
		$word = substr($word, 0, $wordlength - 1);
		$wordlength = length $word;

		# Retrieve the word's last character only if the word has a
		# length more than zero to avoid an error
		if ($wordlength > 0)
		{
			$lastwordcharacter = substr($word, -1);
		}
	}

	return $word
}

sub CountSentenceEndsInString
{
=begin comment
Precondition:
Postcondition:
=cut

	my $string = $_[0];

=begin comment
Code from Perl.com,
https://www.perl.com/article/42/2013/10/3/How-to-read-a-string-into-an-array-of-characters-using-split/
Accessed Monday, September 30, 2019
=cut

	my @stringcharacters = split(//, $string);
	my $sentences = 0;

	# Check each word character to tally the number of sentence-end
	# punctuation characters in the word
	for my $charinword (@stringcharacters)
	{
		if (DetectSentenceEndChar($charinword))
		{
			$sentences++;
		}
	}

	return $sentences;
}

sub DetectSentenceEndChar
{
=begin comment
Precondition:
Postcondition:
=cut
	my $character = $_[0];
	my $issentenceend = 0;

	# Check if the character is sentence-ending punctuation to flag a sentence end	
	if (($character eq '.') or
	    ($character eq ':') or
	    ($character eq ';') or
	    ($character eq '?') or
	    ($character eq '!'))
	{
		$issentenceend = 1;
	}
	else
	{
		$issentenceend = 0;
	}

	return $issentenceend;
}

sub DetectAlphabetChar
{
=begin comment
Precondition: A non-empty character was sent to this subroutine
Postcondition: 
=cut

	my $character = $_[0];
	my $isalphabetic = 0;

	# Check the character to determine if the character is alphabetic
	if ((($character ge 'A') and
	    ($character le 'Z')) or
	    (($character ge 'a') and
	    ($character le 'z')))
	{
		$isalphabetic = 1;
	}
	else
	{
		$isalphabetic = 0;
	}

# 	print "DetectAlphabetChar: Result for \"$character\": $isalphabetic\n";

	return $isalphabetic;
}

sub DetectVowelChar
{
=begin comment
Precondition: A non-empty character was sent to this subroutine
Postcondition: A 1 was sent to this subroutine's caller if the character this
subroutine received was a vowel; otherwise, a 0 was sent to this subroutine's
caller
=cut
	my $character = $_[0];
	my $isvowel = 0;

	# Compare the character to each vowel to check if the character is a vowel
	if (($character eq 'A') or
	    ($character eq 'a') or
	    ($character eq 'E') or
	    ($character eq 'e') or
	    ($character eq 'I') or
	    ($character eq 'i') or
	    ($character eq 'O') or
	    ($character eq 'o') or
	    ($character eq 'U') or
	    ($character eq 'u') or
	    ($character eq 'Y') or
	    ($character eq 'y'))
	{
		$isvowel = 1;
	}
	else
	{
		$isvowel = 0;
	}

	return $isvowel;
}

sub DetectNumericChar
{
=begin comment
Precondition:
Postcondition:
=cut

	my $character = $_[0];
	my $isnumeric = 0;

	# Check the character to determine if the character is numeric
	if (($character ge '0') and
	    ($character le '9'))
	{
		$isnumeric = 1;
	}
	else
	{
		$isnumeric = 0;
	}

	return $isnumeric;
}

sub DetectAlphanumericChar
{
=begin comment
Precondition:
Postcondition:
=cut

	my $character = $_[0];
	my $isalphanumeric = 0;

	# Check the character to determine if the character is alphanumeric
	if ((DetectAlphabetChar($character)) or
	    (DetectNumericChar($character)))
	{
		$isalphanumeric = 1;
	}
	else
	{
		$isalphanumeric = 0;
	}

	return $isalphanumeric;
}

sub CalculateFlesch
{
=begin comment
Precondition: An analyzed text file's numbers of syllables, words, and sentences
were obtained, and each of the numbers were greater than zero
Postcondition: The Flesch Score of the analyzed file was returned to this
subroutine's caller
=cut

	my $syllables = $_[0];
	my $words = $_[1];
	my $sentences = $_[2];

	# Calculate the alpha and beta values to prepare to use alpha and beta in the Flesch calculation
	my $alpha = $syllables / $words;
	my $beta = $words / $sentences;

	my $fleschindex = 206.835 - ($alpha * 84.6) - ($beta * 1.015);

	return $fleschindex;
}

sub CalculateFleschKincaid
{
=begin comment
Precondition: An analyzed text file's numbers of syllables, words, and sentences
were obtained, and each of the numbers were greater than zero
Postcondition: The Flesch-Kincaid Score of the analyzed file was returned to
this subroutine's caller
=cut
	my $syllables = $_[0];
	my $words = $_[1];
	my $sentences = $_[2];

	# Calculate the alpha and beta values to prepare to use alpha and beta in the Flesch-Kincaid calculation
	my $alpha = $syllables / $words;
	my $beta = $words / $sentences;

	my $fleschkincaidindex = ($alpha * 11.8) + ($beta * 0.39) - 15.59;

	return $fleschkincaidindex;
}

sub CalculateDaleChallScore
{
=begin comment
Precondition: An analyzed text file's numbers of difficult words, total words,
and sentences were tallied, and the numbers of total words and sentences were
greater than zero
Postcondition: The Dale-Chall Index of the analyzed file was returned to this
subroutine's caller
=cut

	my $difficultwords = $_[0];
	my $totalwords = $_[1];
	my $sentences = $_[2];

	# Calculate the alpha and beta values to prepare to use alpha and beta in the Dale-Chall calculation
	my $alpha = $difficultwords / $totalwords;
	my $beta = $totalwords / $sentences;

	my $difficultwordpercentage = $alpha * 100;

	my $dalechallscore = ($difficultwordpercentage * 0.1579) +
			     ($beta * 0.0496);

	# If the difficult word percentage is more than 5, increase the
	# Dale-Chall Score by 3.6365 to fulfill the associated Dale-Chall
	# calculation step
	if ($difficultwordpercentage > 5)
	{
		$dalechallscore += 3.6365;
	}

	# Round the Dale-Chall Score to one decimal place to fulfill the
	# required score rounding
	$dalechallscore = sprintf("%.1f", $dalechallscore);

	return $dalechallscore;
}

# Store the Dale-Chall file words to compare the Dale-Chall file words to the
# analyzed file's words
=begin comment
Code from Perl.com,
https://www.perl.com/article/21/2013/4/21/Read-an-entire-file-into-a-string/
Accessed Monday, September 30, 2019
=cut
open my $dalechallfile, "/pub/pounds/CSC330/dalechall/wordlist1995.txt" or die "Can't open file $!";
my $dale_chall_file_content = do {local $/; <$dalechallfile> };

# Convert the Dale-Chall file words to uppercase to permit non-case sensitive
# word comparisons to the analyzed file words
$dale_chall_file_content = uc $dale_chall_file_content;

my @dalechallwordsarray = split(' ', $dale_chall_file_content);

=begin comment
Code from Perl.com,
https://www.perl.com/article/21/2013/4/21/Read-an-entire-file-into-a-string/
Accessed Monday, September 30, 2019
and from Perl Tutorial,
https://www.perltutorial.org/perl-read-file/
Accessed Monday, September 30, 2019
and from Perl Maven,
https://perlmaven.com/read-from-stdin
Accessed Monday, September 30, 2019
=cut
print "Enter filename: ";
my $analyzedfilename = <STDIN>;
chomp $analyzedfilename;
open my $fh, '<', $analyzedfilename or die "Can't open file $!";
my $analyzed_file_content = do {local $/; <$fh> };

# Convert the analyzed file words to uppercase to allow non-case sensitive word
# comparisons to the Dale-Chall file words
$analyzed_file_content = uc $analyzed_file_content;

=begin comment
Code from GeeksforGeeks,
https://www.geeksforgeeks.org/perl-split-function/
Accessed Monday, September 30, 2019
=cut

my @analyzedfilewords = split(' ', $analyzed_file_content);

my $totalwords = 0;
my $syllables = 0;
my $sentences = 0;
my $difficultwords = 0;

# Analyze each word to obtain the values for the reading value calculations
foreach my $potentialword (@analyzedfilewords)
{
	# Scan the potential word to add the word's number of sentence ending
	# punctuation characters to the total sentence count
	$sentences += CountSentenceEndsInString($potentialword);	

	# Trim the potential word to evaluate a valid word that may be in the
	# potential word
	my $trimmedword = TrimWord($potentialword);

=begin comment
Code from Perl.com,
https://www.perl.com/article/42/2013/10/3/How-to-read-a-string-into-an-array-of-characters-using-split/
Accessed Monday, September 30, 2019
=cut
	my @wordcharacters = split(//, $trimmedword);
	my $readingsyllable = 0;

	# Create a variable for tracking if an "e" was read to avoid counting a
	# word-ending "e" as a syllable
	my $possibleendingeread = 0;

	# Search the current word to find syllables
	for my $charinword (@wordcharacters)
	{
		# If a letter "e" was read in the previous for loop iteration,
		# increment the number of syllables, as the previous "e" was not
		# at the word end
		if (($possibleendingeread) and
		    (not ($readingsyllable)))
		{
			$readingsyllable = 1;
			$syllables++;
			$possibleendingeread = 0;
		}

		# Detect individual and successive vowels to count syllables in
		# the word
		if (DetectVowelChar($charinword))
		{
			# If a syllable is not currently flagged as being read,
			# check whether this vowel is an "e" to avoid counting a
			# word-ending "e" as a syllable
			if ((not($readingsyllable)) and
			    (not (($charinword eq 'e') or
			    ($character eq 'E'))))
			{
				$readingsyllable = 1;
				$syllables++;
			}
			elsif ((not($readingsyllable)) and
			       (($charinword eq 'e') or
			       ($character eq 'E')))
			{
				# Flag that a word-ending "e" may have been read
				# to prepare to determine whether the "e" is a
				# word-ending "e" that should not be tallied as
				# a syllable
				$possibleendingeread = 1;
			}
		}
		else
		{
			$readingsyllable = 0;
		}
	}

	# Check the Dale-Chall array to determine if the word is a difficult
	# word
=begin comment
Code from alvin alexander,
https://alvinalexander.com/perl/perl-array-contains-grep-search-how-test
Accessed Monday, September 30, 2019
=cut
	if (not (grep { $_ eq $potentialword } @dalechallwordsarray ))
	{
		$difficultwords++;
	}

	$totalwords++;
}

print "Total words: $totalwords\n";
print "Syllables: $syllables\n";
print "Sentences: $sentences\n";
print "Difficult Words: $difficultwords\n";

my $fleschindex = CalculateFlesch($syllables,
				  $totalwords,
				  $sentences);
my $fleschkincaidindex = CalculateFleschKincaid($syllables,
						$totalwords,
						$sentences);
my $dalechallscore = CalculateDaleChallScore($difficultwords,
					     $totalwords,
					     $sentences);

print "Flesch Readability Index: $fleschindex\n";
print "Flesch-Kincaid Grade Level Index: $fleschkincaidindex\n";
print "Dale-Chall Readability Score: $dalechallscore\n";
