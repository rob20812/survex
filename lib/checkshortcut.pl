#!/usr/bin/perl -w
require 5.008;
use bytes;
use strict;

my %menu = ();
my $srcdir = $ENV{'srcdir'} || '';
$srcdir .= '/' if $srcdir;

open I, "<$srcdir../src/mainfrm.cc" or die $!;
while (<I>) {
    m!(\w+)->Append[A-Za-z]*\(.*\(/\*.*?\*/(\d+)! && push @{$menu{$1}}, $2;
}
close I;

#for (sort keys %menu) { print "$_:".join("|", @{$menu{$_}})."\n" }

my $exitcode = 0;
for my $lang (@ARGV) {
    $lang =~ s/\.msg$//; # allow en or en.msg
    my $hdr = "Lang $lang:\n";
    # .msg files could be in srcdir or build directory when building outside
    # the source tree
    open L, "<$srcdir$lang.msg" or open L, "<$lang.msg" or die $!;
    my $buf;
    read L, $buf, 20;
    read L, $buf, 999999;
    close L;
    my @msg = split /\0/, $buf;
    for my $menu (sort keys %menu) {
	my %sc = ();
	my $bad = 0;
	for (@{$menu{$menu}}) {
            my ($acc) = ($msg[$_] =~ /\&(.)/);
	    if (!defined $acc) {
		print "Lang $lang : message $_ '$msg[$_]' has no shortcut\n";
	    } else {
		$acc = lc $acc;
		if (exists $sc{$acc}) {
		    if (defined $hdr) {
			print $hdr;
			$hdr = undef;
		    }
		    print "Menu $menu : '$msg[$sc{$acc}]' and '$msg[$_]' both use shortcut '$acc'\n";
		    $bad = 1;
		} else {
		    $sc{$acc} = $_;
		}
	    }
	}
	if ($bad) {
	    print "Unused letters: ", grep {!exists $sc{$_}} ('a' .. 'z'), "\n";
	    $exitcode = 1;
	}
    }
    print "\n" unless defined $hdr;
}
exit $exitcode;
