#!/usr/bin/perl
use strict;
use warnings;

use Algorithm::FastPermute ('permute');
use Text::Aspell;

my $arg = shift or die "takes one arg";
my @arg = split(//,$arg);
my $speller = Text::Aspell->new;

permute {
	if ($speller->check(join("",@arg))) {
		#print "@arg\n";
		for (@arg) {
			print $_;
		}
		print "\n";
	}
} @arg;
