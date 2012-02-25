#!/usr/bin/perl

#########################################################################
#
#	File name	: svn_deleter.pl
#	Author		: nutti
#	Date		: 2011.8.21 (Sun) 10:25
#	Usage		: svn_deleter.pl target_dir
#	Brief		: Delete files related to svn.
#
#########################################################################

use strict;

use File::Find;
use File::Path;

my $target_dir = @ARGV[ 0 ];

if( @ARGV != 1 ){
	die "Usage is incorrect.\nUsage : svn_deleter.pl target_dir\n";
}

unless( -e $target_dir ){
	die $target_dir . " isn't exist.\n";
}

my @dir = ( $target_dir );
my @del_list;

find( \&del, @dir );



foreach( @del_list ){
	print $_ . "\n";
	rmtree( $_ );
}

sub del
{
	if( $_ =~ /\.svn/ ){
		if( -d $_ ){
			my $path = $File::Find::dir . "/" . $_;
			push( @del_list, $path );
		}
	}
}