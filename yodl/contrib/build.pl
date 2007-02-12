#!/usr/bin/perl

# This script should be run from contrib's parent directory. I.e., you should
# call it as `perl contrib/build.pl'.

use strict;


# Configuration: default values, unless overruled by the environment.
# -------------------------------------------------------------------
my %config = (
	      CC                => 'gcc',
	      CFLAGS            => '-c -Wall -Werror -g',
	      STD_INCLUDE       => '/usr/share/yodl',
	      MAN_DIR           => '/usr/share/man',
	      DOC_DIR           => '/usr/share/doc/yodl',
	      YODL_BIN          => '/usr/bin',
	      STD_CONVERSIONS   => 'html latex man txt xml',
	      MANUAL_FORMATS    => 'html txt pdf ps',
	     );

# Some of the dirs created in the build. Not all of them tho..
my @doc_dirs = ('manual/html', 'manual/latex', 'manual/man', 'manual/pdf',
		'manual/ps', 'manual/txt', 'manual/dvi');

# The manual pages and their sections.
my %man_map = (yodl             => 1,
	       yodlpost         => 1,
	       yodlverbinsert   => 1,
	       yodlconverters   => 1,
	       yodlmanpage      => 7,
	       yodlletter       => 7,
	       yodlmacros       => 7,
	       yodlbuiltins     => 7
          );

# Initialization
# --------------
# The key TOPLEVEL_VERSION is read from the file src/config.h
# to ensure proper version-synchronization. 
open (my $if, "src/config.h")
  or die ("Cannot read the file src/config.h: $!\n");
foreach (<$if>) {
    if ( /#define\s+TOPLEVEL_VERSION\s\"(\S+)\"/) {
	$config{TOPLEVEL_VERSION} = $1;
	print ("Top level version ID: ",
	       $config{TOPLEVEL_VERSION}, "\n");
	last;
    }
}
close ($if);

my $cc = getconf ('CC');
my $cflags = getconf ('CFLAGS');
my $toplevel_version = getconf ('TOPLEVEL_VERSION');
my $std_include = getconf ('STD_INCLUDE');
my $yodl_bin = getconf ('YODL_BIN');
my $std_conversions = getconf ('STD_CONVERSIONS');
my $manual_formats = getconf ('MANUAL_FORMATS');
my $man_dir = getconf ('MAN_DIR');
my $doc_dir = getconf ('DOC_DIR');

$cflags .=
  " -DTOPLEVEL_VERSION=\"$toplevel_version\"" .
  " -DSTD_INCLUDE=\"$std_include\"";

# [KK 2006-03-15] The following isn't necessary anymore. I rewrote
# the sources to use stdlib.h (more POSIX-y anyway)
# $cflags .=
#  " -DNO_MALLOC_H" unless (findheader ('malloc.h'));

# Helpers
# -------

my @_warnings;
sub warning ($) {
    my $msg = shift;
    
    print STDERR ($msg, "\n");
    push (@_warnings, $msg);
}

sub getconf ($) {
    my $var = shift;
    my $val;

    if ($ENV{$var}) {
	$val = $ENV{$var};
    } elsif ($config{$var}) {
	$val = $config{$var};
    } else {
	die ("Configuration for $var could not be obtained!\n");
    }

    $config{$var} = $val;
    return ($val);
}

sub dirtree {
    foreach my $dir (@_) {
	my @subs = split (/\//, $dir);
	for (my $i = 0; $i <= $#subs; $i++) {
	    my $sofar = '';
	    for (my $j = 0; $j <= $i; $j++) {
		$sofar .= $subs[$j];
		$sofar .= '/';
	    }
	    next if (-d $sofar);
	    mkdir ($sofar) or die ("Cannot create dir $sofar: $!\n");
	}
    }
}

sub run ($) {
    my $cmd = shift;
    $cmd =~ s{"}{\\"}g;
    print ("    $cmd\n");
    my $ret = system ($cmd);
    die ("[$cmd] has failed, code $ret\n") if ($ret);
}

sub findbin ($) {
    my $bin = shift;
    foreach my $d (split /:/, $ENV{PATH}) {
	return ("$d/$bin") if (-x "$d/$bin");
    }
    return (undef);
}

sub findheader ($) {
    my $h = shift;
    foreach my $d ('/usr/include', '/usr/local/include') {
	return ("$d/$h") if (-f "$d/$h");
    }
    return (undef);
}

sub newer ($$) {
    my ($a, $b) = @_;

    return (1) unless (-f $b);
    return (1) if ( (stat($a))[9] > (stat($b))[9] );
    return (0);
}

sub sourcecompile ($) {
    my $dir = shift;
    my $headershown = 0;
    
    my @src = glob ("$dir/*.c");
    return if ($#src == -1);

    if (! -d "$dir/o") {
	mkdir ("$dir/o") or die ("Cannot make dir $dir/o: $!\n");
    }
    foreach my $c (@src) {
	my $run = 0;

	my $o = $c;
	$o =~ s{.*/}{};
	$o =~ s{\.c}{.o};
	$o = "$dir/o/$o";

	$run++ if (newer ($c, $o));

	next unless ($run);
    
	print ("Compiling in: $dir\n") unless ($headershown++);
	print ("  $c -> $o\n");

	run ("$cc $cflags $c -o $o");
    }
}

sub collectlibs () {
    my @dirs = glob ('src/*/o');
    my %libmap;

    foreach my $d (@dirs) {
	my @obj = glob ("$d/*.o");
	next if ($#obj == -1);

	my $libname = 'src/libyodlrss.a';
	$libname = 'src/libyodl.a' if ($d =~ m{src/yodl/o});
	$libname = 'src/libyodlpost.a' if ($d =~ m{src/yodlpost/o});

	if (defined ($libmap{$libname})) {
	    my @present = @{ $libmap{$libname} };
	    push (@present, @obj);
	    $libmap{$libname} = [ @present ];
	} else {
	    $libmap{$libname} = [ @obj ];
	}
    }

    foreach my $l (keys (%libmap)) {
	my @obj = @{ $libmap{$l} };
	my @new;

	foreach my $o (@obj) {
	    push (@new, $o) if (newer ($o, $l));
	}
	next if ($#new == -1);
	print ("Library $l: @new\n");
	run ("ar rs $l @new");
	run ("ranlib $l");
    }
}

sub makebinarysimple ($) {
    my $bin = shift;

    my $base = $bin;
    $base =~ s{^yodl}{};
    my $obj = "src/$base/o/$base.o";
    my $dst = "src/bin/$bin";

    if (newer ($obj, $dst)) {
	print ("Creating (simple) binary: $dst\n");
	run ("$cc -o $dst $obj");
    }
}
	
sub makebinarybylibs ($) {
    my $bin = shift;

    my $run = 0;
    $run++ if (newer ("src/lib$bin.a", "src/bin/$bin"));
    $run++ if (newer ('src/libyodlrss.a', "src/bin/$bin"));
    return unless ($run);

    print ("Creating binary: $bin (src/bin/$bin)\n");
    dirtree ("src/bin");
    run ("$cc -o src/bin/$bin -Lsrc -l$bin -lyodlrss");
}

sub makeyodlversion ($) {
    my $versionfile = shift;

    open (my $of, ">$versionfile")
      or die ("Cannot write $versionfile: $!\n");
    print $of ("DEFINESYMBOL(XXyodlVersion)($toplevel_version)\n");
    close ($of);
}

sub patch ($$) {
    my ($inname, $outname) = @_;
    return if (newer ($outname, $inname));
    print ("Patching $inname (-> $outname)\n");

    open (my $if, $inname)
      or die ("Cannot read $inname: $!\n");
    open (my $of, ">$outname")
      or die ("Cannot write $outname: $!\n");
    while (my $line = <$if>) {
	foreach my $k (keys (%config)) {
	    $line =~ s{\@$k\@}{$config{$k}}g;
	}
	print $of ($line);
    }
    close ($if);
    close ($of);
}

sub makestdconversions () {
    foreach my $conv (split (/ +/, $std_conversions)) {
	patch ("macros/in/$conv.in", "macros/yodl/$conv.yo");
    }
}

sub makerawmacros () {
    foreach my $conv (split (/ +/, $std_conversions)) {
	collectrawmacros ("macros/rawmacros/*.raw",
			  "macros/yodl/std.$conv.yo",
			  $conv);
    }
}

sub parserawfile ($$) {
    my ($raw, $target) = @_;
    my $copy = 1;
    my $recognized = 0;
    my $closed = 1;
    my $printed = 0;
    my $wslines = 0;

    my $ret;
    
    open (my $if, $raw)
      or die ("Cannot read raw macro file $raw: $!\n");
    while (my $line = <$if>) {
	chomp ($line);
	if ($line =~ /^<.*$target.*>\s*$/) {
	    $copy = 1;
	    $closed = 0;
	    $recognized = 1;
	} elsif ($line =~ /^<>\s*$/) {
	    $copy = 1;
	    $closed = 1;
	    $recognized = 0;
	} elsif ($line =~ /^<else>\s*$/) {
	    $closed = 0;
	    $copy = !$recognized;
	} elsif ($line =~ /^<[^>]+>\s*$/) {
	    $closed = 0;
	    $copy = 0;
	} elsif ($copy) {
	    if ($line =~ /^\s*$/) {
		$wslines++ if ($printed);
		next;
	    }
	    while ($wslines) {
		$ret .= "\n";
		$wslines--;
	    }
	    $ret .= "$line\n";
	    $printed = 1;
	}
	# print ("$closed [$line]\n");
    }
    close ($if);
    die ("\nNo closing <> in raw macro file $raw\n") unless ($closed);
    return ($ret);
}

sub collectrawmacros ($$$) {
    my ($rawmask, $output, $format) = @_;
    my @rawfiles = glob ($rawmask);
    die ("Failed to list raw files (mask $rawmask)\n")
      if ($#rawfiles == -1);

    my $make = 0;
    foreach my $r (@rawfiles) {
	$make++ if (newer ($r, $output));
    }
    return unless ($make);

    print ("Generating standard macros for format $format ");

    open (my $of, ">$output.tmp")
      or die ("Cannot write $output.tmp: $!\n");
    print $of ("INCWSLEVEL()\n",
	       "DEFINESYMBOL($format)()\n");
    foreach my $r (@rawfiles) {
	print (".");
	print $of (parserawfile ($r, $format));
    }
    print $of ("DECWSLEVEL()\n");
    close ($of);
    patch ("$output.tmp", $output);
    unlink ("$output.tmp");
    print ("\n  Generated.\n");
}

sub makemacrodocs ($) {
    my $dest = shift;
    my @raw  = glob ('macros/rawmacros/*.raw');
    my $make = 0;

    foreach my $r (@raw) {
	$make++ if (newer ($r, $dest));
    }
    return unless ($make);
    print ("Generating raw macros documentation\n");

    open (my $of, ">$dest")
      or die ("Cannot write $dest: $!\n");
    foreach my $r (@raw) {
	open (my $if, $r)
	  or die ("Cannot read $r: $!\n");
	my $active = 0;
	while (my $line = <$if>) {
	    chomp ($line);
	    if ($line =~ /^<STARTDOC>\s*/) {
		$active++;
	    } elsif ($line =~ /^<.*>\s*/) {
		$active = 0;
	    } elsif ($active) {
		print $of ($line, "\n");
	    }
	}
	close ($if);
	die ("Unterminated <STARTDOC> in $r\n") if ($active);
    }
    close ($of);
}

sub build_docformat ($) {
    my $format = shift;

    my $dest = "manual/$format/yodl.$format";

    # Do we need to make it?
    my $make = 0;
    foreach my $yo (glob ('manual/yo/*.yo'),
		    glob ('manual/yo/converters/*.yo'),
		    glob ('manual/yo/intro/*.yo'),
		    glob ('manual/yo/technical/*.yo')) {
	if (newer ($yo, $dest)) {
	    $make++;
	    last;
	}
    }
    return (1) unless ($make);

    # First yodl generation. Must be from within the manual/yo subdir.
    # Applies to output formats latex, html, txt, man.
    if ($format eq 'latex' or $format eq 'html' or
	$format eq 'txt' or $format eq 'man') {
	print ("\nGenerating $format manual ($dest)\n");
	chdir ('manual/yo') or die ("Cannot access manual/yo: $!\n");
	run ("../../src/bin/yodl -DXXMACROPATH=. ".
	     "-I.:../../macros/yodl -oout $format " .
	     "manual");
	if ($format ne 'latex') {
	    run ("../../src/bin/yodlpost out.idx out yodl.$format");
	    run ("mv yodl*$format ../$format/");
	} else {
	    rename ('out', "../$format/yodl.$format")
	      or die ("Cannot move yodl.$format out of manual/yo ",
		      "to manual/$format/yodl.$format: $!\n");
	}

	unlink ('out', 'out.idx')
	  or die ("Cannot unlink temporary files: $!\n");       
    
	chdir ('../..');
	return (1);
    }
    
    # DVI generation. Must occur from manual/latex because
    # ../../macros/yodl/xlatin.tex gets sourced.
    if ($format eq 'dvi') {
	if (! build_docformat ('latex')) {
	    warning ("Cannot generate manual in DVI format.");
	    return (0);
	}
	if (! findbin ('latex')) {
	    warning ("Application `latex' not found. " .
		     "Cannot generate manual in LaTeX format.");
	    return (0);
	}
	chdir ('manual/latex')
	  or die ("Cannot access manual/latex: $!\n");
	run ('latex yodl.latex');
	run ('latex yodl.latex');
	run ('latex yodl.latex');
	chdir ('../..');
	rename ('manual/latex/yodl.dvi', 'manual/dvi/yodl.dvi')
	  or die ("Cannot move yodl.dvi from manual/latex ",
		  "into manual/dvi/: $!\n");
	return (1);
    }

    # Postscript
    if ($format eq 'ps') {
	if (!build_docformat ('dvi')) {
	    warning ("Cannot generate manual in PostScript format.");
	    return (0);
	}
	if (! findbin ('dvips')) {
	    warning ("Application `dvips' not found. " .
		     "Cannot generate manual in PostScript format.");
	    return (0);
	}
	run ('dvips -o manual/ps/yodl.ps manual/dvi/yodl.dvi');
	return (1);
    }

    # PDF
    if ($format eq 'pdf') {
	if (! build_docformat ('latex')) {
	    warning ("Cannot generate manual in PDF format.");
	    return (0);
	}
	# First we try via pdflatex.
	if (findbin ('pdflatex')) {
	    # The pdflatex run must be from manual/latex, 'cuz xlatin1.tex
	    # gets sourced as ../../macros/yodl/xlatin.tex
	    chdir ('manual/latex')
	      or die ("Cannot access manual/latex: $!\n");
	    run ('pdflatex yodl.latex');
	    run ('pdflatex yodl.latex');
	    run ('pdflatex yodl.latex');
	    chdir ('../..');
	    rename ('manual/latex/yodl.pdf', 'manual/pdf/yodl.pdf')
	      or die ("Cannnot move manuals/latex/yodl.pdf to ",
		      "manuals/pdf: $!\n");
	    return (1);
	}

	# We don't seem to have pdflatex. Let's try PS -> ps2pdf.
	if (! make_docformat ('ps')) {
	    warning ("Cannot generate manual in PDF format.");
	    return (0);
	}
	if (! findbin ('ps2pdf')) {
	    warning ("Application `ps2pdf' not found. " .
		     "Cannnot generate manual in PDF format.");
	    return (0);
	}
	run ('ps2pdf manual/ps/yodl.ps manual/pdf/yodl.pdf');
	return (1);
    }

    # All others...
    die ("Manual generation for format `$format' not (yet) implemented!\n");
}
    

sub make_documentation () {
    # Make sure we have the destination dirs.
    dirtree (@doc_dirs);

    # Do all formats.
    foreach my $format (split / +/, $manual_formats) {
	build_docformat ($format);
    }
}

sub make_man () {
    foreach my $page (keys (%man_map)) {
	my $nr = $man_map{$page};
    
	dirtree ("man/$nr");
      
	my $src = "man/$page.in";
	my $yo  = "man/$page.yo";
	my $man = "man/$nr/$page.$nr";

	next if  (newer ($man, $src));
	print ("Generating manpage $man from $src\n");

	patch ($src, $yo);
	chdir ("man") or die ("Cannot access man/: $!\n");
	run ("../src/bin/yodl -DXXMACROPATH=. -I.:../macros/yodl -oout " .
	     "man $page.yo");
	run ("../src/bin/yodlpost out.idx out $nr/$page.$nr");
	unlink ('out', 'out.idx', $yo)
	  or die ("Cannot unlink temporary files: $!\n");
	chdir ('..');
    }
}

sub make_software () {
    # Compilation.
    foreach my $srcdir (glob ("src/*")) {
	next unless (-d $srcdir);
	sourcecompile ($srcdir);
    }

    # Collect into libraries.
    collectlibs ();

    # Create binaries
    makebinarybylibs ('yodl');
    makebinarybylibs ('yodlpost');
    makebinarysimple ('yodlverbinsert');

    # In the macros/yodl dir, create yodlversion.yo
    makeyodlversion ('macros/yodl/yodlversion.yo');

    # Prepare the list of raw macros.
    makemacrodocs('manual/yo/macros/macrolist.yo');

    # Standard conversion macros.
    makestdconversions ();
    makerawmacros ();
}

sub glob_unlink {
    foreach my $mask (@_) {
	foreach my $file (glob ($mask)) {
	    unlink ($file) or die ("Cannot unlink $file: $!\n");
	}
    }
}

sub clean_software () {
    if (-f 'manual/yo/macros/macrolist.yo') {
	unlink ('manual/yo/macros/macrolist.yo')
	  or die ("Cannot unlink manual/yo/macros/macrolist.yo: $!\n");
    }
    
    glob_unlink ('macros/yodl/*.yo',
		 'src/libyodl*',
		 'src/bin/yodl*');
    if (-d 'src/bin') {
	rmdir ('src/bin') or die ("Cannot unlink src/bin: $!\n");
    }
    foreach my $odir (glob ('src/*/o')) {
	next unless (-d $odir);
	glob_unlink ("$odir/*.o");
	rmdir ($odir) or die ("Cannot unlink $odir: $!\n");
    }
}

sub clean_documentation () {
    foreach my $d (@doc_dirs) {
	next unless (-d $d);
	glob_unlink ("$d/*");
	rmdir ("$d") or die ("Cannot unlink dir $d: $!\n");
    }
}

sub clean_man () {
    foreach my $nr (values (%man_map)) {
	my $dir = "man/$nr";
	next unless (-d $dir);
	glob_unlink ("$dir/*");
	rmdir ($dir) or die ("Cannot unlink dir $dir: $!\n");
    }
    foreach my $f (glob ("man/*.yo")) {
	unlink ($f) or die ("Cannot unlink $f: $!\n");
    }
}

sub make () {
    make_software();
    make_man();
    make_documentation();
}

sub clean () {
    clean_software();
    clean_man();
    clean_documentation();
}

my $_install_depth = 0;
sub install ($$) {
    my ($a, $dst) = @_;

    die ("Install depth exceeded (error in build.pl script)\n")
      if ($_install_depth++ > 100);

    if (! -d $dst) {
	print ("Creating install directory `$dst'\n");
	dirtree ($dst);
    }

    if (-f $a and newer ($a, $dst)) {
	print ("Installing file $a -> $dst/$a\n");
	if (-x $a) {
	    run ("install -s $a $dst");
	} else {
	    run ("cp $a $dst");
	}
    } elsif (-d $a) {
	print ("Installing directory $a/ -> $dst/\n");
	run ("(cd $a; tar --exclude .svn --exclude CVS -c -f - .) | " .
	     "(cd $dst; tar xf -)");
    } else {
	my @list = glob ($a);
	die ("Installation failure, $a fails to yield a list\n")
	  if ($#list == -1);
	foreach my $l (@list) {
	    install ($l, $dst);
	}
    }

    $_install_depth--;
}

sub install_software() {
    make_software();
    install ('src/bin/yodl*', $yodl_bin);
    install ('macros/yodl',   $std_include);
}

sub install_man () {
    make_man();
    foreach my $nr (values (%man_map)) {
	install ("man/$nr", "$man_dir/man$nr");
    }
}

sub install_documentation () {
    make_documentation();
    foreach my $format (split (/ +/, $manual_formats)) {
	install ("manual/$format/*", $doc_dir);
    }
}
    

# Main starts here
# ----------------

select (STDERR); $| = 1;
select (STDOUT); $| = 1;

my $selector = $ARGV[0];

if ($selector eq 'make-software') {
    make_software();
} elsif ($selector eq 'make-man') {
    make_man();
} elsif ($selector eq 'make-documentation') {
    make_documentation();
} elsif ($selector eq 'make') {
    make_software(); make_man(); make_documentation();
} elsif ($selector eq 'install-software') {
    install_software();
} elsif ($selector eq 'install-man') {
    install_man();
} elsif ($selector eq 'install-documentation') {
    install_documentation();
} elsif ($selector eq 'install') {
    install_software(); install_man(); install_documentation();
} elsif ($selector eq 'clean-software') {
    clean_software();
} elsif ($selector eq 'clean-man') {
    clean_man();
} elsif ($selector eq 'clean-documentation') {
    clean_documentation();
} elsif ($selector eq 'clean') {
    clean_software(); clean_man(); clean_documentation();
} else {
    die <<"ENDUSAGE";

You must supply an argument:
    
  make-software         - build the software locally
  make-man              - build the manpages (`software' required)
  make-documentation    - build the docs (`software' required)
  make                  - the three above

  install-software      - install software to $yodl_bin
  install-man           - install manpages to $man_dir
  install-documentation - install docs to $doc_dir
  install               - the three above

  clean-software        - clean up from target `make-software'
  clean-man             - clean up from target `make-man'
  clean-documentation   - clean up from target `make-documentation'
  clean                 - the three above

ENDUSAGE

}

# Show collected warnings.
if ($#_warnings > -1) {
    print STDERR ("\nWARNINGS:\n");
    foreach my $w (@_warnings) {
	print STDERR ("  $w\n");
    }
}
    
