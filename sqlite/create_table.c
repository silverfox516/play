#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 

static int callback(void *not_used, int argc, char **argv, char **column_name) {
	int i;
	for(i = 0; i<argc; i++) {
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

    fprintf(stdout, "Opened database successfully\n");

	/* Create SQL statement */
	sql = "CREATE TABLE COMPANY("  \
		   "ID INT PRIMARY KEY     NOT NULL," \
		   "NAME           TEXT    NOT NULL," \
		   "AGE            INT     NOT NULL," \
		   "ADDRESS        CHAR(50)," \
		   "SALARY         REAL );";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, 0, &error_message);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", error_message);
		sqlite3_free(error_message);
        goto out;
    }

    fprintf(stdout, "Table created successfully\n");

out:
	sqlite3_close(db);
	return rc;
}
