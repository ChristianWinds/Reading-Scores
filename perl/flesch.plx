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
my $file_content = do {local $/; <$fh> };

print($file_content ,"\n");

=begin comment
Code from GeeksforGeeks,
https://www.geeksforgeeks.org/perl-split-function/
Accessed Monday, September 30, 2019
=cut

my @spl = split(' ', $file_content)
foreach my $i (@spl)
{
	print "$i\n"
}
