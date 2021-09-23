#!/usr/bin/perl

for my $dir (@ARGV)
{
    print "$0: opendir on $dir\n";
    opendir(DIR, $dir) || die "$0: could not open $dir: $!\n";
    @dirlist = readdir(DIR);
    print "$0: found $#dirlist elements in $dir\n";
    print "$0: closdir on $dir\n";
    closedir(DIR);
}

exit 0;
