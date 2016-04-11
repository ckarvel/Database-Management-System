/*Carina Vargas*/
/*cv164112*/

#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

int queryOps(char * query, struct database * Database)
{
	/*file variable*/
	FILE *fp;
	
	/*variables*/
	int i;
	int j;
	int floc;
	struct table *table;
	struct attributes *column;
	int count;
	char command[10];
	
	/*open query file*/
	fp = (FILE *)checkedOpen(query, "r");
	
	fseek(fp, 0, SEEK_END); 
	count = ftell(fp);
	rewind(fp);
	
	while(ftell(fp) != count)
	{
		fscanf(fp, "%s", command);
		/*calls to appropriate command function*/
		
		if(strcmp(command, "select") == 0)
		{
			floc = ftell(fp);
			floc = select(query, floc, Database);
			fseek(fp, floc, SEEK_SET);
			puts("");
		}
		else if(strcmp(command, "numRows") == 0)
		{
			floc = ftell(fp);
			floc = numRows(query, floc, Database);
			fseek(fp, floc, SEEK_SET);
			puts("");
		}
		else if(strcmp(command, "rowStat") == 0)
		{
			floc = ftell(fp);
			floc = rowStat(query, floc, Database);
			fseek(fp, floc, SEEK_SET);
			puts("");
		}
		else if(strcmp(command, "numCols") == 0)
		{
			floc = ftell(fp);
			floc = numCols(query, floc, Database);
			fseek(fp, floc, SEEK_SET);
			puts("");
		}
		else if(strcmp(command, "colStat") == 0)
		{
			floc = ftell(fp);
			floc = colStat(query, floc, Database);
			fseek(fp, floc, SEEK_SET);
			puts("");
		}
		else if(strcmp(command, "project") == 0)
		{
			floc = ftell(fp);
			floc = project(query, floc, Database);
			fseek(fp, floc, SEEK_SET);
			puts("");
		}
		else if(strcmp(command, "stop") == 0)
		{
			return 0;
		}
	}
	
	
}