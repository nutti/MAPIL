#!/usr/bin/perl

#########################################################################
#
#	File name	: create_automake_conf.pl
#	Author		: nutti
#	Date		: 2011.8.18 (Thu) 21:04
#	Usage		: create_automake_conf.pl target_dir output_file
#	Brief		: This scripts create configuration file of automake.
#
#########################################################################

use strict;

use File::Find;

my $target_dir = @ARGV[ 0 ];
my $fout_name = @ARGV[ 1 ];

if( @ARGV != 2 ){
	die "Usage is incorrect.\nUsage : create_automake_conf.pl target_dir output_file\n";
}

unless( -e $target_dir ){
	die $target_dir . " isn'ty exists.\n";
}

if( -e $fout_name ){
	die $fout_name . " is already exists.\n";
}
else{
	open FOUT, ">$fout_name" or die "Failed to open output file.\n";
}

print FOUT "AM_CPPFLAGS = \@GTK_CFLAGS\@ `pkg-config --cflags openal`\n";
print FOUT "AM_LOADD = \@GTK_LIBS\@ `pkg-config --libs openal`\n";
print FOUT "nobase_include_HEADERS = \\\n";

$target_dir =~ s#\\#/#;

my @dir = ( $target_dir . "/Include" );

find( \&dump, @dir );

print FOUT "lib_LIBRARIES = libmapil.a\n";
print FOUT "libmapil_a_SOURCES = \\\n";

@dir = ( $target_dir . "/Src" );

find( \&dump, @dir );

print FOUT "\n";

close FOUT;

sub dump
{
	unless( $File::Find::dir =~ /\.svn/ || $_ =~ /\.svn/ || $_ =~ /^\.{1,2}$/ ){
		unless( -d $_ ){
			my $path = $File::Find::dir;
			$path =~ s/\/code//;
			print FOUT "\t" . $path . "/";
			print FOUT $_;
			print FOUT " \\" . "\n";
		}
	}
}
