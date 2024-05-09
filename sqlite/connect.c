#include <stdio.h>
#include <sqlite3.h> 

int main(int argc, char* argv[]) {
	sqlite3 *db;
	int rc;

	rc = sqlite3_open("test.db", &db);
	if (rc < 0) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return rc;
    }
    fprintf(stderr, "Opened database successfully\n");

	sqlite3_close(db);
    return rc;
}
