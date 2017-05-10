#include <stdio.h>
#include <stdlib.h>
int load_data(char*, int*, float*);
void print_data(int*, float*, int);
int main(int argc, char** argv)
{
	if (argc !=3)
	{
		printf("\nInsufficient Parameters\n");
		return 0;
	}
	int n=atoi(argv[2]);
	int *acn;
	float *amt;
	acn=malloc(sizeof(int)*n);
	amt=malloc(sizeof(float)*n);
	int size=load_data(argv[1], acn, amt);
	if(size==0)
	{
		printf("\n Unable to open the input file \n");
	}
	print_data(acn, amt, size);
	free(acn);
	free(amt);
return 0;
}
int load_data(char *input, int *acn, float *amt)
{
	int i=0;
	FILE* file=fopen("input.txt", "r");
	if(file==NULL)
	{
		return 0;
	}
	int size;
	fscanf(file, "%d", &size);
	for(i=0; i<size; i++)
	{
		fscanf(file, "%d", acn);
		fscanf(file, "%f", amt);
		acn++;
		amt++;
	}
	fclose(file);
	return size;
}
void print_data(int *acn, float *amt, int size)
{
	int i;
	printf("Account No.	Amount\n");
	for(i=0; i<size; i++)
	{
		printf("%d\t\t", *acn);
		printf("%.2f\n", *amt);
		acn++;
		amt++;
	}
}
