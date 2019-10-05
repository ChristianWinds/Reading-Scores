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

# Check the word's left to remove non-word characters
if ()

}

sub DetectSentenceEnd
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

sub DetectVowelChar
{
=begin comment
Precondition:
Postcondition:
=cut
	my $character = $_[0];
	my $isvowel = 0;

	# Compare the character to each vowel to check if the character is a vowel
	if (($character eq 'a') or
	    ($character eq 'e') or
	    ($character eq 'i') or
	    ($character eq 'o') or
	    ($character eq 'u') or
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

# Store the Dale-Chall file words to compare the Dale-Chall file words to the analyzed file's words
=begin comment
Code from Perl.com,
https://www.perl.com/article/21/2013/4/21/Read-an-entire-file-into-a-string/
Accessed Monday, September 30, 2019
=cut
open my $dalechallfile, "/pub/pounds/CSC330/dalechall/wordlist1995.txt" or die "Can't open file $!";
my $dale_chall_file_content = do {local $/; <$dalechallfile> };

# Convert the Dale-Chall file words to uppercase to permit non-case sensitive word comparisons to the analyzed file words
$dale_chall_file_content = uc $dale_chall_file_content;

print($dale_chall_file_content ,"\n");

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

# Convert the analyzed file words to uppercase to allow non-case sensitive word comparisons to the Dale-Chall file words
$analyzed_file_content = uc $analyzed_file_content;

print($analyzed_file_content ,"\n");

=begin comment
Code from GeeksforGeeks,
https://www.geeksforgeeks.org/perl-split-function/
Accessed Monday, September 30, 2019
=cut

my @analyzedfilewords = split(' ', $analyzed_file_content);
foreach my $i (@analyzedfilewords)
{
	print "$i\n";
}

my $totalwords = 0;
my $syllables = 0;
my $sentences = 0;
my $difficultwords = 0;

# Analyze each word to obtain the values for the reading value calculations
foreach my $potentialword (@analyzedfilewords)
{
=begin comment
Code from Perl.com,
https://www.perl.com/article/42/2013/10/3/How-to-read-a-string-into-an-array-of-characters-using-split/
Accessed Monday, September 30, 2019
=cut

	# Trim the potential word to evaluate a valid word that may be in the potential word
	my $trimmedword = TrimWord($potentialword);

	my @wordcharacters = split(//, $trimmedword);
	my $readingsyllable = 0;

	# Search the current word to find syllables and sentence end punctuation
	for my $charinword (@wordcharacters)
	{
		# Detect individual and successive vowels to count syllables in the word
		if (DetectVowelChar($charinword))
		{
			if (not($readingsyllable))
			{
				$readingsyllable = 1;
				$syllables++;
			}
		}
		else
		{
			$readingsyllable = 0;
		}

		# Detect sentence-ending punctuation to count the number of sentences
		if (DetectSentenceEnd($charinword))
		{
			$sentences++;
		}
	}

	# Check the Dale-Chall array to determine if the word is a difficult word
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
