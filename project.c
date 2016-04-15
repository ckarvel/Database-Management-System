/*Carina Vargas*/
/*cv164112*/

#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

#define STRLENGTH 16

int project(char * query, int fbyte, struct database * Database)
{
	/*file variable*/
	FILE *fp;
	
	/*variables*/
	int i;
	int k;
	int j;
	int x;
	int q;
	int count = 0;
	char tableName[STRLENGTH];
	char columnName[STRLENGTH];
	struct table *t;
	struct attributes *a;
	
	/*open query file*/
	fp = (FILE *)checkedOpen(query, "r");
	
	/*location in file after command is scanned in*/
	fseek(fp, fbyte, SEEK_SET);
	
	/*table name*/
	fscanf(fp, " %s", tableName);
	
	/*check if table exists*/
	for(i = 0; i < Database->numTables; i++)
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
	
	char **charray;
	charray = (char **)malloc(sizeof(char *) * t->numRows);
	for(i = 0; i < t->numRows; i++)
	{
		charray[i] = (char *)malloc(sizeof(char) * STRLENGTH);
	}
	
	int iarray[t->numRows];

	/*column name*/
	fscanf(fp, " %s", columnName);
			
	/*check if column exists*/
	for(i = 0; i < t->numCols; i++)
	{
		if(strcmp(((t->rowArray)[0]->attrArray)[i]->name, columnName) == 0)
		{
			a = ((t->rowArray)[0]->attrArray)[i];
			/*string type*/
			if(strcmp(a->type, "str") == 0)
			{	
				/*will print only unique attributes of the array*/
				for(k = 0; k < t->numRows; k++)
				{
					for(q = 0; q < k; q++)
					{
						if(strcmp(((t->rowArray)[k]->attrArray)[i]->strdata, ((t->rowArray)[q]->attrArray)[i]->strdata) == 0)
						{
							break;
						}
					}
						
					if (k == q)
					{
						fprintf(stdout, "%s\n", ((t->rowArray)[k]->attrArray)[i]->strdata);
					}
				}
			}
			/*integer type*/
			else if(strcmp(a->type, "int") == 0)
			{
				for(k = 0; k < t->numRows; k++)
				{
					for(q = 0; q < k; q++)
					{
						if(((t->rowArray)[k]->attrArray)[i]->intdata == ((t->rowArray)[q]->attrArray)[i]->intdata)
						{
							break;
						}
					}
									  
					if (k == q)
					{
						printf("%d\n", ((t->rowArray)[k]->attrArray)[i]->intdata);
					}
				}
			}
			count++;
		}

		else if(i == ((t->numCols) - 1) && count == 0)
		{
			fprintf(stdout, "Error: Invalid attribute -- %s\n", columnName);
			return ftell(fp);
		}
	}
	
	return ftell(fp);
}