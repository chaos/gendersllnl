use ExtUtils::MakeMaker;
use Config;

# Takes a colon-separated list of library paths and returns a cleaner one:
#   o) Removes any leading -L flags (used by the static linker only)
#   o) Removes empty paths
#   o) Removes duplicate paths (keeps first one)
sub cleanup_libpath
{
    my ($libpath) = @_;

    my %seen;
    my @libdirs;
    foreach my $libdir (split /:+/, $libpath) {
        $libdir =~ s/^-L//;
        if (($libdir ne "") && !$seen{$libdir}) {
            push @libdirs, $libdir;
            $seen{$libdir} = 1;
        }
    }

    return join(":", @libdirs);
}

# On AIX, set the compiled-in library path for dynamic libraries to the path
# where the C libraries (gendersllnl and genders) are installed plus the
# default library path.  Otherwise, the library path contains an entry for
# the gendersllnl library in the source directory.
my @new_argv;
foreach (@ARGV) {
    if (my ($libpath) = /^GENDERSLLNL_LIBDIRS=(.*)$/) {
        if ($Config{osname} eq "aix") {
            $libpath = cleanup_libpath($libpath);
            next if ($libpath eq "");
            my $lddlflags = $Config{lddlflags};
            if ($lddlflags !~ s/(-blibpath:)/$1$libpath:/g) {
                $libpath = cleanup_libpath("$libpath:/usr/lib:/lib");
                $lddlflags .= " -blibpath:$libpath";
            }
            push @new_argv, "LDDLFLAGS=$lddlflags";
        }
    }
    else {
        push @new_argv, $_;
    }
}
@ARGV = @new_argv;

# See lib/ExtUtils/MakeMaker.pm for details of how to influence
# the contents of the Makefile that is written.
WriteMakefile(
    'NAME'		=> 'Libgendersllnl',
    'VERSION_FROM'	=> 'Libgendersllnl.pm',
    'PREREQ_PM'		=> {},
    ($] >= 5.005 ?
      (ABSTRACT_FROM => 'Libgendersllnl.pm',
       AUTHOR     => 'Albert Chu <chu11@llnl.gov>') : ()),
);
