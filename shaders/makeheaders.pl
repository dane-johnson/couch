use strict;
use warnings;

sub convert {
    my $filename = $1;
    
    my $headerguard = "$filename.h";
    $headerguard =~ tr/a-z./A-Z_/;
    
    my $constname = "$filename";
    $constname =~ tr/./_/;

    open my $fin, '<', $filename;
    open my $fout, '>', "$filename.h";
    
    print $fout "#ifndef $headerguard \n#define $headerguard\nconst char * $constname = \n";

    while(my $line = <$fin>) {
	$line =~ s/\n/\\n/;
	print $fout "\"$line\"\n";
    }

    print $fout ";\n#endif // $headerguard\n";
    close $fin;
    close $fout;
}

opendir DIR, ".";
while (readdir DIR) {
    if (/(.*\.(frag|vert))/) {
	convert;
    }
}
