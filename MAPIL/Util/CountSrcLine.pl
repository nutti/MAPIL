#!/usr/bin/perl

#########################################################################
#
#	File name	: count_src_line.pl
#	Author		: nutti
#	Date		: 2011.9.23 (Fri) 11:30
#	Usage		: count_src_line.pl target_dir
#	Brief		: Count number of source line.
#
#########################################################################

use strict;

use File::Find;
use File::Path;

my $target_dir = @ARGV[ 0 ];

if( @ARGV != 1 ){
	die "Usage is incorrect.\nUsage : count_src_line.pl target_dir\n";
}

unless( -e $target_dir ){
	die $target_dir . " isn't exist.\n";
}

my @dir = ( $target_dir );
my @count_list;

find( \&count, @dir );

my $all_line = 0;

foreach( @count_list ){
	print $_ . " : ";
	open( FIN, $_ ) or die "Can't open $_\n";
	my @buf = <FIN>;
	my $line = @buf;
	print $line . "\n";
	$all_line += $line;
}

print "\n" . "All Line : " . "$all_line\n";

sub count
{
	unless( $_ =~ /\.svn/ ){
		unless( -d $_ ){
			my $path = $File::Find::dir . "/" . $_;
			push( @count_list, $path );
		}
	}
}