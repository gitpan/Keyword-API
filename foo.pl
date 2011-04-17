my $re = qr/^(\S+)(?:\[(.*)\])|(?:\{(.*)\})?$/;
die "bang" if 'D{ "a" : 1 ]' =~ $re;
die "correct" if 'D{ "a" : 1 }' =~ $re;
