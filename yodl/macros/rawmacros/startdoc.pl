#!/usr/bin/perl

$target = "STARTDOC";
$file = $ARGV[0];
$copy = 0;
$printed = 0;

open(FILE, "$file");

while ($line = <FILE>)
{
    chomp $line;

    if ($line =~ /^<$target>\s*$/c)
    {
        $copy = 1;
    }
    elsif ($line =~ /^<>\s*$/c)
    {
        print "\n" if $printed;
        exit 0;
    }
    elsif ($copy)
    {
        print "$line\n";
        $printed = 1;
    }
}

warn "No close tag <> in $file\n" if $copy;





