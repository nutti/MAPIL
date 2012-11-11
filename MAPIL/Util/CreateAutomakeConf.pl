#!/usr/bin/env perl

#########################################################################
#
#	File name	: CreateAutomakeConf.pl
#	Author		: nutti
#	Date		: 2011.8.18 (Thu) 21:04
#	Usage		: CreateAutomakeConf.pl target_dir output_file target_os
#	Brief		: This scripts create configuration file of automake.
#
#########################################################################

use strict;

use File::Find;

my $target_dir = @ARGV[ 0 ];
my $fout_name = @ARGV[ 1 ];
my $target_os = @ARGV[ 2 ];

if( @ARGV != 3 ){
	die "Usage is incorrect.\nUsage : CreateAutomakeConf.pl target_dir output_file target_os\n";
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

if( $target_os eq 'linux' ){
	print FOUT "AM_CPPFLAGS = \@GTK_CFLAGS\@ `pkg-config --cflags openal`\n";
	print FOUT "AM_LOADD = \@GTK_LIBS\@ `pkg-config --libs openal`\n";
}
elsif( $target_os eq 'mac' ){
	print FOUT "AM_CPPFLAGS = \@GTK_CFLAGS\@\n";
	print FOUT "AM_LOADD = \@GTK_LIBS\@ -framework OpenAL\n";
}

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
			$path =~ s/\/Code//;
			print FOUT "\t" . $path . "/";
			print FOUT $_;
			print FOUT " \\" . "\n";
		}
	}
}
