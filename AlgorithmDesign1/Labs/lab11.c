//Holt Skinner
//HASTG2 (Hashtag)
//Lab K
//Merry Christmas!!!
#include <stdio.h>
#include <stdlib.h>
int load_data(char*, int*, float*);
void print_data(int*, float*, int);
int search_account(int*, int, int);
int highest_amount(float*, int);
void write_data(char*, int*, float*, int);
int main(int argc, char** argv)
{
	if(argc!=4)//If the user doesn't enter enough arguments, show error and quit
	{
		printf("\nInsufficient Arguments\n");
		return 0;
	}
	int n=atoi(argv[2]);
	int *acn=malloc(sizeof(int)*n);
	float *amt=malloc(sizeof(int)*n);
	int size=load_data(argv[1], acn, amt);
	int searchfor;
	int search;
	if(size==0)//If theres a file error, end program
	{
		printf("\nUnable to open the input file\n");
		return 0;
	}
	print_data(acn, amt, size);
	write_data(argv[3], acn, amt, size);//Send data to file
	printf("\nEnter the account that you want to search:");//Ask for account to search
	scanf("%d", &searchfor);
	search=search_account(acn, size, searchfor);//assign searchindex to index of the account that was searched for
	if(search==-1)//if the account diesn't exist
	{
		printf("\nAccount number %d is not present\n", searchfor);
	}
	else//If it does exist
	{
		printf("\nAccount number %d has $%.2f in it.\n", searchfor, *(amt+search));
	}
	int maxindex=highest_amount(amt, size);//Save the index of the maximum value
	printf("\nThe highest amount is $%.2f in the account number %d.\n", *(amt+maxindex), *(acn+maxindex));
	free(acn);
	free(amt);
return 0;	
}
int load_data(char* input, int* acn, float* amt)
{
	int i=0;
	int size;
	FILE* file=fopen(input, "r");
	if(file==NULL)
	{
		return 0;
	}
	fscanf(file, "%d", &size);
	for(i=0; i<size; i++)
	{
		fscanf(file, "%d", acn+i);
		fscanf(file, "%f", amt+i);
	}	
	fclose(file);
	return size;
}
void print_data(int* acn, float* amt, int size)
{
	int i;
	printf("Account No.\tAmount\n");
	for(i=0; i<size; i++)
	{
		printf("%d\t\t", *(acn+i));
		printf("%.2f\n", *(amt+i));
	}
}	
int search_account(int* acn, int size, int searchfor)
{
	int i;
	for(i=0; i<size; i++)
	{
		if(searchfor==*(acn+i))
		return i;
	}
return -1;
}
int highest_amount(float* amt, int size)
{
	int i, j=0;
	float max=0;
	for (i=0; i<size; i++)
	{
		if(*(amt+i)>max)
		{
			max=*(amt+i);
			j=i;
		}
	}
return j;
}
void write_data(char* output, int* acn, float* amt, int size)
{
	int i=0;
	FILE* out=fopen("output.txt", "w");
	for (i=0; i<size; i++)
	{
		fprintf(out, " %d", *(acn+i));
		fprintf(out, " %.2f\n", *(amt+i));
	}
	fclose(out);
}
