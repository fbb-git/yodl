#!/usr/bin/perl

$target = $ARGV[0];
$file = $ARGV[1];
$copy = 1;
$recognized = 0;
$closed = 1;
$printed = 0;
$wslines = 0;


open(FILE, "$file");

sub wslines()
{
    return if !$printed;

    while ($wslines)
    {
        print "\n";
        $wslines--;
    }
}

while ($line = <FILE>)
{
    chomp $line;

    if ($line =~ /^<.*$target.*>\s*$/c)
    {
        $copy = 1;
        $closed = 0;
        $recognized = 1;
    }
    elsif ($line =~ /^<>\s*$/c)
    {
        $copy = 1;
        $closed = 1;
        $recognized = 0;
    }
    elsif ($line =~ /^<else>\s*$/c)
    {
        $closed = 0;
        $copy = !$recognized;
    }
    elsif ($line =~ /^<[^>]+>\s*$/c)
    {
        $closed = 0;
        $copy = 0;
    }
    elsif ($copy)
    {
        if ( $line =~ /^\s*$/ )
        {
            if ($printed)
            {            
                $wslines++;
            }
            next;
        }

        wslines();
        print "$line\n";
        $printed = 1;
    }
}

print "\n";
    
if (!$closed)
{
    warn "Maybe no close tag <> in $file\n";
}



