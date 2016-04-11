/*Carina Vargas*/
/*cv164112*/

#include<stdio.h>
#include<stdlib.h>

FILE * checkedOpen(char * name, char * mode)
{
	FILE * file = fopen(name, mode);
	if(file == NULL)
	{
		fprintf(stderr, "Cannot open %s\n", name);
		exit(0);
	}
	
	else
	{
		return file;
	}
}

void checkpoint()
{
	printf("%s \t %d \n", __FILE__, __LINE__);
	fflush(stdout);
}