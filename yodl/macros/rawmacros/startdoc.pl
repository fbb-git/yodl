#!/usr/bin/perl

    # The documentation of the macro in $file is extracted from $file and
    # written to stdout.

$target = "STARTDOC";               # A marker fo the documentation in $file
$file = $ARGV[0];                   # file to process: a raw macro file
$copy = 0;
$printed = 0;

open(FILE, "$file");

while ($line = <FILE>)
{
    chomp $line;

    if ($line =~ /^<$target>\s*$/c)     # start tag found
    {
        $copy = 1;
    }
    elsif ($line =~ /^<>\s*$/c)         # end tag found
    {
        print "\n" if $printed;
        exit 0;
    }
    elsif ($copy)                       # copy a documentation line
    {
        print "$line\n";
        $printed = 1;
    }
}

warn "No close tag <> in $file\n" if $copy;





