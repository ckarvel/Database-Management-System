/*Carina Vargas*/
/*cv164112*/

#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

#define STRLENGTH 16

int colStat(char * query, int fbyte, struct database * Database)
{
	/*file variable*/
	FILE *fp;
	
	/*variables*/
	int i;
	int count = 0;
	char tableName[STRLENGTH];
	char columnName[STRLENGTH];
	struct table *t;
	
	/*open query file*/
	fp = (FILE *)checkedOpen(query, "r");
	
	/*location in file after command is scanned in*/
	fseek(fp, fbyte, SEEK_SET);
	
	/*table name*/
	fscanf(fp, " %s", tableName);
	
	/*check if table exists*/
	for(i = 0; i < (Database->numTables); i++)
	{
		if(strcmp((Database->tableArray)[i]->name, tableName) == 0)
		{
			t = (Database->tableArray)[i];
			break;
		}
		else if(i == ((Database->numTables) - 1))
		{
			fprintf(stdout, "Error: Invalid relation -- %s\n", tableName);
			return ftell(fp);
		}
	}
	
	/*column name*/
	fscanf(fp, " %s", columnName);
	
	/*check if column exists*/
	for(i = 0; i < t->numCols; i++)
	{
		if(strcmp(((t->rowArray)[0]->attrArray)[i]->name, columnName) == 0)
		{
			/*prints column type and size*/
			if(strcmp(((t->rowArray)[0]->attrArray)[i]->type, "str") == 0)
			{
				fprintf(stdout, "Attribute type: String\n");
			}
			else if(strcmp(((t->rowArray)[0]->attrArray)[i]->type, "int") == 0)
			{
				fprintf(stdout, "Attribute type: Integer\n");
			}	
			fprintf(stdout, "Attribute size: %d\n", ((t->rowArray)[0]->attrArray)[i]->size);
			count++;
		}
		
		else if(i == ((t->numCols) - 1) && count == 0)
		{
			fprintf(stdout, "Error: Invalid attribute -- %s\n", columnName);
			return ftell(fp);
		}
	}
	count = 0;
	return ftell(fp);
}