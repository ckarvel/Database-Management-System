/*Carina Vargas*/
/*cv164112*/

#include <stdio.h>
#include<stdlib.h>
#include "prototypes.h"
#include "structures.h"


/*file pointers*/
FILE *fcon;
FILE *fque;


int main(int argc, char *argv[])
{
	/*number of arguments check*/
	if(argc != 3)
	{
		fprintf(stderr, "Error -- Not enough command line arguments\n");
		exit(0);
	}
	
	/*call to function*/
	queryOps(argv[2], initialize (argv[1]));
	
	return 0;
}