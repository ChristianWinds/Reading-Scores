#!/usr/bin/perl -w
use warnings;
use strict;

=begin comment
Code from Perl.com,
https://www.perl.com/article/21/2013/4/21/Read-an-entire-file-into-a-string/
Accessed Monday, September 30, 2019
=cut
open my $dalechallfile, "/pub/pounds/CSC330/dalechall/wordlist1995.txt" or die "Can't open file $!";
my $dale_chall_file_content = do {local $/; <$dalechallfile> };

print($dale_chall_file_content ,"\n");

my @dalechallwordsarray = split(' ', $dale_chall_file_content);

=begin comment
Code from Perl.com,
https://www.perl.com/article/21/2013/4/21/Read-an-entire-file-into-a-string/
Accessed Monday, September 30, 2019
=cut

open my $fh, '<', 'twoSentences.txt' or die "Can't open file $!";
my $analyzed_file_content = do {local $/; <$fh> };

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
	my @wordcharacters = split(//, $potentialword);
	my $readingsyllable = 0;

	for my $charinword (@wordcharacters)
	{
		if (($charinword eq 'a') or
		    ($charinword eq 'e') or
		    ($charinword eq 'i') or
		    ($charinword eq 'o') or
		    ($charinword eq 'u') or
		    ($charinword eq 'y'))
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

		if (($charinword eq '.') or
		    ($charinword eq ':') or
		    ($charinword eq ';') or
		    ($charinword eq '?') or
		    ($charinword eq '!'))
		{
			$sentences++;
		}
	}
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
