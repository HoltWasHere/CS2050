//Holt Skinner
//HASTG2 (Hashtag)
//Homework 4
#include <stdio.h>
#include <stdlib.h>
int load_data(char*, int*, float*);
void print_data(int*, float*, int);
int update_data(char*, int*, float*, int);
int highest_amount(float*, int);
int lowest_amount(float*, int);
float average_amount(float*, int);
void write_data(char*, int*, float*, int, int, int, float);
int main(int argc, char** argv)
{
	if (argc !=5)//If the user doesn't enter enough arguments show error and quit//
	{		
		printf("\nInsufficient Arguments\n");
		return 0;
	}
	int n=atoi(argv[2]);
	int *acn=malloc(sizeof(int)*n);
	float *amt=malloc(sizeof(float)*n);
	int size=load_data(argv[1], acn, amt);
	if(size==0)//If there's a file error, display error and quit
	{
		printf("\n Unable to open the input file \n");
		return 0;
	}
	print_data(acn, amt, size);
	if(update_data(argv[3], acn, amt, size)==0)
	{
		printf("Unable to read the update file\n");
		return 0;
	}
	printf("\nUpdated account information\n");
	print_data(acn, amt, size);
	int maxindex=highest_amount(amt, size);
	int minindex=lowest_amount(amt, size);
	float average=average_amount(amt, size);
	printf("\nThe highest amount is $%.2f in the account number %d.", *(amt+maxindex), *(acn+maxindex));
	printf("\nThe lowest amount is $%.2f in the account number %d.", *(amt+minindex), *(acn+minindex));
	printf("\nThe average amount is $%.2f\n.", average);
	write_data(*(argv+4), acn, amt, size, maxindex, minindex, average);
	free(acn);
	free(amt);
return 0;
}
int load_data(char* input, int* acn, float* amt)
{
	int i=0;
	int size;
	int *acnhold=acn;//Saves starting pointer address
	float *amthold=amt;
	FILE* file=fopen(input, "r");
	if(file==NULL)
	{
		return 0;
	}
	fscanf(file, "%d", &size);
	for(i=0; i<size; i++)
	{
		fscanf(file, "%d", acn);
		fscanf(file, "%f", amt);
		acn++;
		amt++;
	}
	fclose(file);
	acn=acnhold;
	amt=amthold;//Puts original address back in original
	return size;
}
void print_data(int* acn, float* amt, int size)
{
	int i;
	int *acnhold=acn;
	float *amthold=amt;
	printf("Account No.\tAmount\n");
	for(i=0; i<size; i++)
	{
		printf("%d\t\t", *acn);
		printf("%.2f\n", *amt);
		acn++;
		amt++;
	}
	acn=acnhold;
	amt=amthold;
}
int update_data(char* inFile, int* acn, float* amt, int size)
{
	int i, j, holdn, updatesize;
	float holdm;
	FILE* update=fopen(inFile, "r");
	if(update==NULL)
	{
		return 0;
	}
	fscanf(update, "%d", &updatesize);//Takes off first number
	for(i=0; i<updatesize; i++)//Cycles through update file
	{
		fscanf(update, "%d %f", &holdn, &holdm);
			for(j=0; j<size; j++)//Cycles through original file	
			{
				if(holdn==*(acn+j))
				{
					*(amt+j)=*(amt+j)+holdm;//Updates amount value
				}
							
			}
	}
	fclose(update);
return 1;
}
int highest_amount(float* amt, int size)
{
	int i, j=0;
	float max=0;
	for (i=0; i<size; i++)
	{
		if(*amt>max)
		{
			max=*amt;
			j=i;
		}
		++amt;
	}
return j;
}
int lowest_amount(float* amt, int size)
{
	int i, j=0;
	float min=100000;
	for (i=0; i<size; i++)
	{
		if(*amt<min)
		{
			min=*amt;
			j=i;
		}
		++amt;
	}
return j;
}
float average_amount(float* amt, int size)
{
	int i;
	float sum=0, average=0;
	for (i=0; i<size; i++)
	{
		sum+=*amt;
		++amt;
	}
	average=sum/size;
return average;
}
void write_data(char* output, int* acn, float* amt, int size, int maxindex, int minindex, float average)
{
	int i=0;
	int *holdacn=acn;//Save starting index to pointers
	float *holdamt=amt;
	FILE* out=fopen("output.txt", "w");
	for (i=0; i<size; i++)
	{
		fprintf(out, " %d", *acn);
		fprintf(out, " %.2f\n", *amt);
		acn++;
		amt++;
	}
	acn=holdacn;//Reassign beginning index to pointers
	amt=holdamt;
	fprintf(out, "\nThe highest amount is $%.2f in the account number %d.\n", *(amt+maxindex), *(acn+maxindex));
	fprintf(out, "The lowest amount is $%.2f in the account number %d.\n", *(amt+minindex), *(acn+minindex));
	fprintf(out, "The average amount is $%.2f.", average);
	fclose(out);
}
