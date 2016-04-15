/*Carina Vargas*/
/*cv164112*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

#define DATA ".data"
#define TABLE ".table"
#define STRLEN 16
#define TABLELEN 10

struct database * initialize(char * config)
{
	/*variables*/
	FILE *finp;
	FILE **fdata;
	FILE **ftable;
	
	char **string;
	char **data;
	char **table;
	char ***columnName;
	char ***columnType;
	
	int integer = 0;
	int i;
	int j;
	int k;
	int count = 0;
	int sum = 0;
	int add[10][10];
	int bytesize[10];
	
	struct database *Database;
	
	/*open files*/
	finp = (FILE *)checkedOpen(config, "r"); 
	
	/*allocating space for temporary strings*/
	string = (char **)malloc(sizeof(char*) * TABLELEN);
	data = (char **)malloc(sizeof(char) * TABLELEN);
	table = (char **)malloc(sizeof(char) * TABLELEN);
	for(i = 0; i < TABLELEN; i++)
	{
		string[i] = (char *)malloc(sizeof(char) * STRLEN);
		data[i] = (char *)malloc(sizeof(char) * (STRLEN + 10)); //to take into account ".data"
		table[i] = (char *)malloc(sizeof(char) * (STRLEN + 10)); //to take into account ".table"
	}
	
	/*allocating space for database*/
	Database = (struct database *)malloc(sizeof(struct database));

	/*storing number of tables*/
	fscanf(finp, "%d", &integer);
	Database->numTables = integer;
	
	/*allocating space for table*/
	Database->tableArray = (struct table **)malloc(sizeof(struct table *) * Database->numTables);
	for(i = 0; i < Database->numTables; i++)
	{
		((Database->tableArray)[i]) = (struct table *)malloc(sizeof(struct table));
	}
	
	/*allocating space for table name*/
	for(i = 0; i < Database->numTables; i++)
	{
		((Database->tableArray)[i])->name = (char *)malloc(sizeof(char) * STRLEN);
	}
	
	/*reading table names*/
	for(i = 0; i < Database->numTables; i++)
	{
		fscanf(finp, "%s", string[i]);
		((Database->tableArray)[i])->name = string[i];
		
		/*concatenating .data*/
		strcpy(data[i], string[i]);
		strcat(data[i], DATA);
		
		/*concatenating .table*/
		strcpy(table[i], string[i]);
		strcat(table[i], TABLE);
	}
	
	/*allocating space for file pointers*/
	fdata = (FILE **)malloc(sizeof(FILE *) * Database->numTables);
	ftable = (FILE **)malloc(sizeof(FILE *) * Database->numTables);
	for(i = 0; i < Database->numTables; i++)
	{
		fdata[i] = (FILE *)malloc(sizeof(FILE));
		ftable[i] = (FILE *)malloc(sizeof(FILE));
	}
	
	/*opening files*/
	for(i = 0; i < Database->numTables; i++)
	{
		fdata[i] = (FILE *)checkedOpen(data[i], "r");
		ftable[i] = (FILE *)checkedOpen(table[i], "r");
	}
	
	/*storing number of columns for each table*/
	for(i = 0; i < Database->numTables; i++)
	{
		fscanf(ftable[i], "%d", &integer);
		((Database->tableArray)[i])->numCols = integer;
	}
	
	/*allocating space for temporary string*/
	columnName = (char ***)malloc(sizeof(char **) * Database->numTables);
	columnType = (char ***)malloc(sizeof(char **) * Database->numTables);
	for(i = 0; i < Database->numTables; i++)
	{
		columnName[i] = (char **)malloc(sizeof(char*) * TABLELEN);
		columnType[i] = (char **)malloc(sizeof(char*) * TABLELEN);
		for(j =0; j < TABLELEN; j++)
		{
			columnName[i][j] = (char *)malloc(sizeof(char) * STRLEN);
			columnType[i][j] = (char *)malloc(sizeof(char) * 4);
		}
	}
	
	/*storing column name, type, size*/
	for(i = 0; i < Database->numTables; i++)
	{
		for(j = 0; j < ((Database->tableArray)[i])->numCols; j++)
		{
			fscanf(ftable[i], "%s %s %d", columnName[i][j], columnType[i][j], &add[i][j]);
		}
	}
	
	/*to get row size*/
	for(i = 0; i < Database->numTables; i++)
	{
		for(j = 0; j < ((Database->tableArray)[i])->numCols; j++)
		{
			sum += add[i][j];
			count++;
			if(count == ((Database->tableArray)[i])->numCols)
			{
				((Database->tableArray)[i])->rowSize = sum;
				sum = 0; 
				count = 0;
			}
		}
	}
	
	/*to get number of rows*/
	for(i = 0; i < Database->numTables; i++)
	{
		fseek(fdata[i], 0, SEEK_END);
		bytesize[i] = ftell(fdata[i]);
		((Database->tableArray)[i])->numRows = (bytesize[i]) / (((Database->tableArray)[i])->rowSize);
		rewind(fdata[i]);
	}
	
	/*allocating space for row array*/
	for(i = 0; i < Database->numTables; i++)
	{
		((Database->tableArray)[i])->rowArray = (struct row **)malloc(sizeof(struct row *) * ((Database->tableArray)[i])->numRows);
		for(j=0; j < ((Database->tableArray)[i])->numRows; j++)
		{
			(((Database->tableArray)[i])->rowArray)[j] = (struct row *)malloc(sizeof(struct row));
		}
	}
	
	/*allocating space for attribute array*/
	for(i = 0; i < Database->numTables; i++)
	{
		for(k = 0; k < ((Database->tableArray)[i])->numRows; k++)
		{
			((((Database->tableArray)[i])->rowArray)[k])->attrArray = (struct attributes **)malloc(sizeof(struct attributes *) * (((Database->tableArray)[i])->numCols));
			for(j=0; j < ((Database->tableArray)[i])->numCols; j++)
			{
				(((((Database->tableArray)[i])->rowArray)[k])->attrArray)[j] = (struct attributes *)malloc(sizeof(struct attributes));
			}
		}
	}
	
	/*allocating space for column name and type*/
	for(i = 0; i < Database->numTables; i++)
	{
		for(k = 0; k < ((Database->tableArray)[i])->numRows; k++)
		{
			for(j = 0; j < ((Database->tableArray)[i])->numCols; j++)
			{
				((((((Database->tableArray)[i])->rowArray)[k])->attrArray)[j])->name = (char *)malloc(sizeof(char) * STRLEN);
				((((((Database->tableArray)[i])->rowArray)[k])->attrArray)[j])->type = (char *)malloc(sizeof(char) * 4);
			}
		}
	}
	
	/*filling in column names and types*/
	for(i = 0; i < Database->numTables; i++)
	{
		for(k =0; k < ((Database->tableArray)[i])->numRows; k++)
		{
			for(j = 0; j < ((Database->tableArray)[i])->numCols; j++)
			{
				((((((Database->tableArray)[i])->rowArray)[k])->attrArray)[j])->name = columnName[i][j];
				((((((Database->tableArray)[i])->rowArray)[k])->attrArray)[j])->type = columnType[i][j];
				((((((Database->tableArray)[i])->rowArray)[k])->attrArray)[j])->size = add[i][j];
			}
		}
	}

	/*allocating space for string data name*/
	for(i = 0; i < Database->numTables; i++)
	{
		for(k =0; k < ((Database->tableArray)[i])->numRows; k++)
		{
			for(j = 0; j < ((Database->tableArray)[i])->numCols; j++)
			{
				((((((Database->tableArray)[i])->rowArray)[k])->attrArray)[j])->strdata = (char *)malloc(sizeof(char) * 50);
			}
		}
	}

	/*reading in from binary*/
	for(i = 0; i < Database->numTables; i++)
	{
		for(k = 0; k < ((Database->tableArray)[i])->numRows; k++)
		{
			for(j = 0; j < ((Database->tableArray)[i])->numCols; j++)
			{
				if(strcmp((((((((Database->tableArray)[i])->rowArray)[k])->attrArray)[j])->type), "str") == 0)
				{
					fread((((((((Database->tableArray)[i])->rowArray)[k])->attrArray)[j])->strdata), ((((((Database->tableArray)[i])->rowArray)[k])->attrArray)[j])->size, 1, fdata[i]);
				}
				
				else if(strcmp((((((((Database->tableArray)[i])->rowArray)[k])->attrArray)[j])->type), "int") == 0)
				{
					fread(&(((((((Database->tableArray)[i])->rowArray)[k])->attrArray)[j])->intdata), ((((((Database->tableArray)[i])->rowArray)[k])->attrArray)[j])->size, 1, fdata[i]);
				}
			}
		}
	}
	
	/*close all files*/
	fclose(finp);
	for(i = 0; i < Database->numTables; i++)
	{
		fclose(fdata[i]);
		fclose(ftable[i]);
	}
	
	return Database; 
}