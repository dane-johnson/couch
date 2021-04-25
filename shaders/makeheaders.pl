use strict;
use warnings;
use File::Basename;

my ($filename, $outfilename) = @ARGV;

my $headerguard = basename $outfilename;
$headerguard =~ tr/a-z./A-Z_/;

my $constname = basename "$filename";
$constname =~ tr/./_/;

open(my $fin, '<', $filename) or die("Couldn't find $filename");
open my $fout, '>', $outfilename;

print $fout "#ifndef $headerguard \n#define $headerguard\nconst char * $constname = \n";

while(my $line = <$fin>) {
    $line =~ s/(\r?\n)/\\n/;
    print $fout "\"$line\"\n";
}

print $fout ";\n#endif // $headerguard\n";
close $fin;
close $fout;
print "Generated $outfilename\n";

