/*Carina Vargas*/
/*cv164112*/

struct database * initialize(char *);
int queryOps(char *, struct database *);
FILE * checkedOpen(char *, char *);
void checkpoint();
int select(char *, int, struct database *);
int numRows(char *, int, struct database *);
int rowStat(char *, int, struct database *);
int	numCols(char *, int, struct database *);
int colStat(char *, int, struct database *);
int project(char *, int, struct database *);