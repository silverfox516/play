#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 

static int callback(void *NotUsed, int argc, char **argv, char **column_name) {
	int i;
	for (i = 0; i<argc; i++) {
		printf("%s = %s\n", column_name[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

int main(int argc, char* argv[]) {
	sqlite3 *db;
	char *error_message = NULL;
	int rc;
	const char *sql;

	/* Open database */
	rc = sqlite3_open("test.db", &db);
	if (rc < 0) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return rc;
    }
    fprintf(stderr, "Opened database successfully\n");

	/* Create SQL statement */
	sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
		   "VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
		   "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
		   "VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
		   "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
		   "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
		   "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
		   "VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, 0, &error_message);
	if (rc != SQLITE_OK){
		fprintf(stderr, "SQL error: %s\n", error_message);
		sqlite3_free(error_message);
        goto out;
    }
    fprintf(stdout, "Records created successfully\n");

out:
	sqlite3_close(db);
	return rc;
}
