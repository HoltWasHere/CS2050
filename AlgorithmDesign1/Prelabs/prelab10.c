#include <stdio.h>
#include <stdlib.h>
int length(char *s);
char* copy(char *s);
char* reverse(char *s);
void clear(char *s);
int main(int argc, char **argv)
{
	if(argc<2)
	{
		printf("\nNot enough parameters\n");
		return 0;
	}
	char *x=argv[1];
	int len=length(x);
	char *y=malloc(sizeof(char)*len);
	y=copy(x);
	printf("\n Input string is %s", x);
	printf("\n Length of the string is %d", len);
	printf("\n Copy of the string is %s", y);

	char *rev=reverse(x);
	printf("\n Reverse of the string %s is %s \n", x, rev);

	clear(y);
	clear(rev);
return 0;
}
int length(char *s)
{
	char *hold=s;
	int i=0;
	while (*s != '\0')
	{
		++i;
		++s;
	}
	s=hold;
return i;
}	
char* copy(char *s)
{
	char *sc=malloc(sizeof(char)*length(s));
	while (*s != '\0')
        {
		*sc=*s;//Sets value of current index of s1 to current index of sc//
		++s;
		++sc;
        }
	*sc='\0';
return sc;
}
char* reverse(char *s)
{
	int i;
	char *sr=malloc(sizeof(char)*length(s));
	for (i=(length(s)); i>0; i--)
	{
		*sr=*(s+(i-1));
		++sr;
	}
	*sr='\0';
return sr;
}
void clear(char *s)
{
free(s);
}
