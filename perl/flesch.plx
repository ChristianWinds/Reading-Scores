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
Code from Beginning Perl,
https://docs.google.com/viewer?url=https%3A%2F%2Fblob.perl.org%2Fbooks%2Fbeginning-perl%2F3145_Chap06.pdf
Accessed Thursday, September 26, 2019
=cut

open FILE, "twoSentences.txt" or die $!;
my $linenob = 1;

while (<FILE>)
{
	print $linenob++;
	print ": $_";
}
