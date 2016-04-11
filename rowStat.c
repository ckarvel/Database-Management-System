/*Carina Vargas*/
/*cv164112*/

#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

#define STRLENGTH 16

int rowStat(char * query, int fbyte, struct database * Database)
{
	/*file variable*/
	FILE *fp;
	
	/*variables*/
	int i;
	int count = 0;
	char tableName[STRLENGTH];
	struct table *t;
	
	/*open query file*/
	fp = (FILE *)checkedOpen(query, "r");
	
	/*location in file after command is scanned in*/
	fseek(fp, fbyte, SEEK_SET);
	
	/*table name*/
	fscanf(fp, " %s", tableName);
	
	/*check if table exists*/
	for(i = 0; i < Database->numTables; i++)
	{
		/*prints out the row size of the table*/
		if(strcmp((Database->tableArray)[i]->name, tableName) == 0)
		{
			t = (Database->tableArray)[i];
			fprintf(stdout, "%d\n", t->rowSize);
			count++;
			break;
		}
		else if(i == ((Database->numTables) - 1) && count == 0)
		{
			fprintf(stdout, "Error: Invalid relation -- %s\n", tableName);
			return ftell(fp);
		}
	}
	
	return ftell(fp);
}
	