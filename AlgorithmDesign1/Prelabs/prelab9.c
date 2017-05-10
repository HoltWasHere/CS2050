#include <stdio.h>
#define MAX 100
int length(char *s);
int replace(char *s, int i);
void copy(char *s, char *s2);
int main(void)
{
	char *s, *s2, string[MAX], string2[MAX];
	int i;
	printf("Enter a string:");
	scanf("%s", &string); 
	printf("Input string is %s\n", string);
	printf("Length of the string is %d\n", length(string));
	copy(string, string2); 
	printf("Copy of input string is %s\n", string2);
	printf("Enter a position for the replacement operation(1-%d):", length(string));
	scanf("%d", &i);
	if (replace(string, i)==0)
	printf("Invalid position\n");
	else
	{
		printf("String after replacement operation is %s\n", string);
	}
return 0;
}
int length(char *s)
{
	int i=0;
	while (*s != '\0')
	{
		i++;
		++s;
	}
return i;	
}
int replace(char *s, int i)
{
	if (i>(length(s)))
	return 0;
	else
	{
		*(s+(i+1))='#';
		return 1;
	}
}	
void copy(char *s, char *s2)
{
	while(*s != '\0')
	{
		*s2=*s;
		++s;
		++s2;
	}
}

