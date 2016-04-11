/*Carina Vargas*/
/*cv164112*/

struct database{
	int numTables;
	struct table **tableArray;
};

struct table{
	int numRows;
	int numCols;
	int rowSize;
	char *name;
	struct row **rowArray;
};

struct row{
	struct attributes **attrArray;
};

struct attributes{
	char *name;
	int size;
	char *type;
	int intdata; 
	char *strdata;
};