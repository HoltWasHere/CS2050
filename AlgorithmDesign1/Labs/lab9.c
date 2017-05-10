/*Holt Skinner
 *HASTG2 (Hashtag)
LAB K 
Lab 9
Lorde*/
#include <stdio.h>
#define MAX 100
int length(char *s1);
int replace(char*s1, int i);
void copy(char *s1, char *sc);
void merge(char *s1, char *s2, char *sm);
void reverse(char *s1, char *sr);
int prefix(char *sp1, char *sp2);
int palindrome(char *p);//Bonus prototype//
int main()
{
	char *s1, *sc, *s2, *sm, *sr, *sp1, *sp2, string1[MAX], stringcopy[MAX], string2[MAX], stringmerge[MAX], stringreverse[MAX], stringprefix1[MAX], stringprefix2[MAX];
	int i;//index for replacement//
	printf("\n");
	printf("Enter first string:");
	scanf("%s", &string1);
	printf("\n");
	printf("First string is %s\n", string1);
	printf("Length of the string is %d\n", length(string1));
	copy(string1, stringcopy);//Creates copy of 1st string//
	printf("Copy of input string is %s\n", stringcopy);
	printf("\n");
	printf("Enter a position for the replacement operation(1-%d):", length(string1));
	scanf("%d", &i);
	if (replace(string1, i)==0)
		printf("Invalid position\n");//End if//
	else
		printf("String after replacement operation is %s\n", string1);//End else//
	printf("\n");
	printf("Enter second string:");
	scanf("%s", &string2);//String to be merged with 1st input string//
	printf("\n");
	printf("Second string is %s\n", string2);
	merge(string1, string2, stringmerge);//Merges string1 and string2 into a third string// 
	printf("Merged string is %s\n", stringmerge);
	reverse(stringcopy, stringreverse);
	printf("Reverse of the string %s is %s \n", stringcopy, stringreverse);
	printf("\n");
	printf("Enter a string for the prefix operation:");
	scanf("%s", &stringprefix1);
	printf("Enter a string to check if it is a prefix:");
	scanf("%s", &stringprefix2);
	if (prefix(stringprefix1, stringprefix2)==0)//If it's not a prefix//
		printf("%s is not a prefix of the string %s\n", stringprefix2, stringprefix1);//End if//
	else//If it is a prefix//
		printf("%s is a prefix of the string %s\n",  stringprefix2, stringprefix1);//End else//
	printf("\n");
return 0;
}
int length(char *s1)
{
	int i=0;
	while (*s1 != '\0')//while the character in the string is not null, bump i and bump to next char//
	{
		++i;
		++s1;
	}
return i;
}
int replace(char *s1, int i)
{
	if (i<=0||i>(length(s1)))
		return 0;//End if//
	else
	{
		*(s1+(--i))='#';
		return 1;
	}//End Else
}
void copy(char *s1, char *sc)
{
	while (*s1 != '\0')
	{
		*sc=*s1;//Sets value of current index of s1 to current index of  sc//
		++s1;
		++sc;
	}//End while//
	*sc='\0';
}
void merge(char *s1, char *s2, char *sm)
{
	while (*s1 !='\0')
	{
		*sm=*s1;
		++s1;
		++sm;
	}
	while (*s2 != '\0')
	{
		*sm=*s2;
		++s2;
		++sm;
	}
	*sm='\0';
}
		
void reverse(char *s1, char *sr)
{
	int i;
	for(i=(length(s1)); i>=0; i--)
	{

		*sr=*(s1+(i-1));//Assigns current value (going backwards) of string 1 to the reverse string//
		++sr;//Bump reverse string to next char//
	}
	*sr='\0';
}
int prefix(char *sp1, char *sp2)
{
	while (*sp2 != '\0')
	{
		if (*sp1 != *sp2)
		return 0;
		else
		{
			++sp1;
			++sp2;
		}
	}
return 1;
}
