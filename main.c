#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMEL(x) (sizeof(x) / sizeof(x[0]))
#define SIZEL(x) (sizeof(x[0]))

enum{
	BufSiz = 512 ,
} ;

char *argv0;
char hexchrs[] = "0123456789ABCDEF" ;

void
usage(void)
{
	fprintf(stderr, "usage: %s [buffer_size]\n", argv0);
	exit(1);
}

char *
c2h(char *hex, char c)
{
	hex[0] = hexchrs[(int)c / 16] ;
	hex[1]	= hexchrs[(int)c % 16] ;
	return hex ;
}

void
fwritehex(FILE *f, char *b, char n)
{
	int i;
	char h[2];

	for( ; n ; --n){
		fwrite(c2h(h, *b), sizeof(h), 1, f);
		++b;
	}
}

int main(int argc, char *argv[])
{
	char *buf;
	int n;
	int bufsiz = BufSiz ;

	argv0 = argv[0] ;

	if(argc==2){
		bufsiz = atoi(argv[1]) ;
		if(!bufsiz)
			usage();
	}

	buf = malloc(bufsiz) ;

	do{
		n = fread(buf, SIZEL(buf), bufsiz, stdin) ;
		fwritehex(stdout, buf, n);
	}while( n == bufsiz );

	return 0 ;
}

