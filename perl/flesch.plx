#!/usr/bin/perl -w
use warnings;
use strict;

=begin comment
Code from Beginning Perl,
https://docs.google.com/viewer?url=https%3A%2F%2Fblob.perl.org%2Fbooks%2Fbeginning-perl%2F3145_Chap06.pdf
Accessed Thursday, September 26, 2019
=cut
open FILE, "/pub/pounds/CSC330/dalechall/wordlist1995.txt" or die $!;
my $linenoa = 1;

while (<FILE>)
{
	print $linenoa++;
	print ": $_";
}

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
	}
	$totalwords++;
}

print "Total words: $totalwords\n";
print "Syllables: $syllables\n";
