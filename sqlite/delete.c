#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 

static int callback(void *data, int argc, char **argv, char **column_name) {
	int i;

	fprintf(stderr, "%s: ", (const char *)data);
	for (i = 0; i<argc; i++) {
		printf("%s = %s\n", conumn_name[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");

	return 0;
}

int main(int argc, char* argv[]) {
	sqlite3 *db;
	char *error_message = NULL;
	int rc;
	const char *sql;
	const char *data = "Callback function called";

	/* Open database */
	rc = sqlite3_open("test.db", &db);
	if (rc < 0) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return rc;
    }
    fprintf(stderr, "Opened database successfully\n");

	/* Create merged SQL statement */
	sql = "DELETE from COMPANY where ID=2; " \
		   "SELECT * from COMPANY";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, (void*)data, &error_message);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", error_message);
		sqlite3_free(error_message);
        goto out;
    }
    fprintf(stdout, "Operation done successfully\n");

out:
	sqlite3_close(db);
	return rc;
}
