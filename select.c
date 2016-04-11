/*Carina Vargas*/
/*cv164112*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "structures.h"

#define STRLENGTH 16

int select(char * query, int fbyte, struct database * Database)
{
	/*file variable*/
	FILE *fp;
	
	/*variables*/
	int i;
	int k;
	int j;
	int length;
	int count = 0;
	char tableName[STRLENGTH];
	char columnName[STRLENGTH];
	char cmp[3];
	char fstring[STRLENGTH];
	char finteger[STRLENGTH];
	int fint;
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
			fscanf(fp, " %s", cmp);
			
			/*if column is of string type*/
			if(strcmp(((t->rowArray)[0]->attrArray)[i]->type, "str") == 0)
			{
				fscanf(fp, " %s", fstring);
				
				/*checks if value is a digit which would be an error*/
				if(fstring[0] >= '0' && fstring[0] <= '9')
				{
					fprintf(stdout, "Error:  Wrong type of value for attribute %s\n", columnName);
					return ftell(fp);
				}
				
				
				length = strlen(fstring);
				
				if(strcmp(cmp, "==") == 0)
				{
					/*will print all rows with attribute*/
					for(k = 0; k < t->numRows; k++)
					{
						/*compares database string with the input (removes " " from input)*/
						if(strncmp(((t->rowArray)[k]->attrArray)[i]->strdata, (fstring + 1), (length - 2)) == 0)
						{
							for(j = 0; j < t->numCols; j++)
							{
								/*will print all rows that satisfies condition*/
								if(strcmp(((t->rowArray)[k]->attrArray)[j]->type, "str") == 0)
								{
									fprintf(stdout, "%s\t", ((t->rowArray)[k]->attrArray)[j]->strdata);
								}
								else if(strcmp(((t->rowArray)[k]->attrArray)[j]->type, "int") == 0)
								{
									fprintf(stdout, "%d\t", ((t->rowArray)[k]->attrArray)[j]->intdata);
								}
							}
							puts("");
							count++;
						}
						else if(k == ((t->numRows) - 1) && count == 0)
						{
							fprintf(stdout, "No tuples satisfy the specified condition.\n");
							return ftell(fp);
						}
					}
					puts("");
					count = 0;
				}
				else if(strcmp(cmp, "!=") == 0)
				{
					/*will print all rows without attribute*/
					for(k = 0; k < t->numRows; k++)
					{
						if(strncmp(((t->rowArray)[k]->attrArray)[i]->strdata, (fstring + 1), (length - 2)) != 0)
						{
							for(j = 0; j < t->numCols; j++)
							{
								if(strcmp(((t->rowArray)[k]->attrArray)[j]->type, "str") == 0)
								{
									fprintf(stdout, "%s\t", ((t->rowArray)[k]->attrArray)[j]->strdata);
								}
								else if(strcmp(((t->rowArray)[k]->attrArray)[j]->type, "int") == 0)
								{
									fprintf(stdout, "%d\t", ((t->rowArray)[k]->attrArray)[j]->intdata);
								}
							}
							puts("");
							count++;
						}
						else if(k == ((t->numRows) - 1) && count == 0)
						{
							fprintf(stdout, "No tuples satisfy the specified condition.\n");
							return ftell(fp);
						}
					}
					puts("");
					count = 0;
				}
				else
				{
					fprintf(stdout, "Wrong comparison value for attribute %s\n", columnName);
					return ftell(fp);
				}
			}
			
			/*if column is of type integer*/
			else if(strcmp(((t->rowArray)[0]->attrArray)[i]->type, "int") == 0)
			{
				fscanf(fp, " %s", &finteger); 
				
				if(!(finteger[0] >= '0' && finteger[0] <= '9'))
				{
					fprintf(stdout, "Error:  Wrong type of value for attribute %s\n", columnName);
					return ftell(fp);
				}
				
				fint = atoi(finteger);
				
				/*equal*/
				if(strcmp(cmp, "==") == 0)
				{
					/*will print all rows with attribute*/
					for(k = 0; k < t->numRows; k++)
					{
						if(((t->rowArray)[k]->attrArray)[i]->intdata == fint)
						{
							for(j = 0; j < t->numCols; j++)
							{
								if(strcmp(((t->rowArray)[k]->attrArray)[j]->type, "str") == 0)
								{
									fprintf(stdout, "%s\t", ((t->rowArray)[k]->attrArray)[j]->strdata);
								}
								else if(strcmp(((t->rowArray)[k]->attrArray)[j]->type, "int") == 0)
								{
									fprintf(stdout, "%d\t", ((t->rowArray)[k]->attrArray)[j]->intdata);
								}
							}
							puts("");
							count++;
						}
						else if(k == ((t->numRows) - 1) && count == 0)
						{
							fprintf(stdout, "No tuples satisfy the specified condition.\n");
							return ftell(fp);
						}
					}
					puts("");
					count = 0;
				}
				
				/*not equal*/
				else if(strcmp(cmp, "!=") == 0)
				{
					/*will print all rows without attribute*/
					for(k = 0; k < t->numRows; k++)
					{
						if(((t->rowArray)[k]->attrArray)[i]->intdata != fint)
						{
							for(j = 0; j < t->numCols; j++)
							{
								if(strcmp(((t->rowArray)[k]->attrArray)[j]->type, "str") == 0)
								{
									fprintf(stdout, "%s\t", ((t->rowArray)[k]->attrArray)[j]->strdata);
								}
								else if(strcmp(((t->rowArray)[k]->attrArray)[j]->type, "int") == 0)
								{
									fprintf(stdout, "%d\t", ((t->rowArray)[k]->attrArray)[j]->intdata);
								}
							}
							puts("");
							count++;
						}
						
						else if(k == ((t->numRows) - 1) && count == 0)
						{
							fprintf(stdout, "No tuples satisfy the specified condition.\n");
							return ftell(fp);
						}
					}
					puts("");
					count = 0;
				}
				
				/*less than or equal to*/			
				else if(strcmp(cmp, "<=") == 0)
				{
					/*will print all rows less than or equal to attribute*/
					for(k = 0; k < t->numRows; k++)
					{
						if(((t->rowArray)[k]->attrArray)[i]->intdata <= fint)
						{
							for(j = 0; j < t->numCols; j++)
							{
								if(strcmp(((t->rowArray)[k]->attrArray)[j]->type, "str") == 0)
								{
									fprintf(stdout, "%s\t", ((t->rowArray)[k]->attrArray)[j]->strdata);
								}
								else if(strcmp(((t->rowArray)[k]->attrArray)[j]->type, "int") == 0)
								{
									fprintf(stdout, "%d\t", ((t->rowArray)[k]->attrArray)[j]->intdata);
								}
							}
							puts("");
							count++;
						}
						
						else if(k == ((t->numRows) - 1) && count == 0)
						{
							fprintf(stdout, "No tuples satisfy the specified condition.\n");
							return ftell(fp);
						}
					}
					puts("");
					count = 0;
				}
				
				/*greater than or equal to*/
				else if(strcmp(cmp, ">=") == 0)
				{
					/*will print all rows greater than or equal to attribute*/
					for(k = 0; k < t->numRows; k++)
					{
						if(((t->rowArray)[k]->attrArray)[i]->intdata >= fint)
						{
							for(j = 0; j < t->numCols; j++)
							{
								if(strcmp(((t->rowArray)[k]->attrArray)[j]->type, "str") == 0)
								{
									fprintf(stdout, "%s\t", ((t->rowArray)[k]->attrArray)[j]->strdata);
								}
								else if(strcmp(((t->rowArray)[k]->attrArray)[j]->type, "int") == 0)
								{
									fprintf(stdout, "%d\t", ((t->rowArray)[k]->attrArray)[j]->intdata);
								}
							}
							puts("");
							count++;
						}
						
						else if(k == ((t->numRows) - 1) && count == 0)
						{
							fprintf(stdout, "No tuples satisfy the specified condition.\n");
							return ftell(fp);
						}
					}
					puts("");
					count = 0;
				}
				
				/*greater than*/
				else if(strcmp(cmp, ">") == 0)
				{
					/*will print all rows greater than attribute*/
					for(k = 0; k < t->numRows; k++)
					{
						if(((t->rowArray)[k]->attrArray)[i]->intdata > fint)
						{
							for(j = 0; j < t->numCols; j++)
							{
								if(strcmp(((t->rowArray)[k]->attrArray)[j]->type, "str") == 0)
								{
									fprintf(stdout, "%s\t", ((t->rowArray)[k]->attrArray)[j]->strdata);
								}
								else if(strcmp(((t->rowArray)[k]->attrArray)[j]->type, "int") == 0)
								{
									fprintf(stdout, "%d\t", ((t->rowArray)[k]->attrArray)[j]->intdata);
								}
							}
							puts("");
							count++;
						}
						
						else if(k == ((t->numRows) - 1) && count == 0)
						{
							fprintf(stdout, "No tuples satisfy the specified condition.\n");
							return ftell(fp);
						}
					}
					puts("");
					count = 0;					
				}
				
				/*less than*/
				else if(strcmp(cmp, "<") == 0)
				{
					/*will print all rows less than attribute*/
					for(k = 0; k < t->numRows; k++)
					{
						if(((t->rowArray)[k]->attrArray)[i]->intdata < fint)
						{
							for(j = 0; j < t->numCols; j++)
							{
								if(strcmp(((t->rowArray)[k]->attrArray)[j]->type, "str") == 0)
								{
									fprintf(stdout, "%s\t", ((t->rowArray)[k]->attrArray)[j]->strdata);
								}
								else if(strcmp(((t->rowArray)[k]->attrArray)[j]->type, "int") == 0)
								{
									fprintf(stdout, "%d\t", ((t->rowArray)[k]->attrArray)[j]->intdata);
								}
							}
							puts("");
							count++;
						}
						
						else if(k == ((t->numRows) - 1) && count == 0)
						{
							fprintf(stdout, "No tuples satisfy the specified condition.\n");
							return ftell(fp);
						}
					}
					puts("");
					count = 0;
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