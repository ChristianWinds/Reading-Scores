#!/usr/bin/perl -w
use warnings
use strict

# Code from Beginning Perl,
# https://docs.google.com/viewer?url=https%3A%2F%2Fblob.perl.org%2Fbooks%2Fbeginning-perl%2F3145_Chap06.pdf
# Accessed Thursday, September 26, 2019
open FILE, "twoSentences.txt" or die $!;
my $lineno = 1;

while (<FILE>)
{
	print $lineno++;
	print ": $_";
}
