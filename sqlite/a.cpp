#include <iostream>
#include <string>
#include <sqlite3.h>
#include <unistd.h>

#define DB_NAME "testdb"

//#define SEEK

template<typename T>
struct SingleIntListCbData
{
	T *values;
	size_t &count;
};

template<typename T>
int getCallback(void *data, int argc, char **argv, char **azColName)
{
	SingleIntListCbData<T> *cbData = (SingleIntListCbData<T> *)data;

	cbData->values[cbData->count++] = strtoul(argv[0], NULL, 0);

	return 0;
}

template<typename T>
class SingleIntListDb
{
public:
	int ins(sqlite3 *db, T val);
	int del(sqlite3 *db, T val);
	int get(sqlite3 *db, T *val, size_t &count);
	int clr(sqlite3 *db);

	SingleIntListDb(const char *table, const char *col) : mTable(table), mCol(col) {
		static_assert(std::is_arithmetic<T>::value, "T must be numeric");
	}

private:

	std::string mTable;
	std::string mCol;
};

template<typename T>
int SingleIntListDb<T>::ins(sqlite3 *db, T val)
{
    char *query;
    char *errmsg;
    int rc;

    query = sqlite3_mprintf("INSERT INTO %s VALUES (%d);", mTable.c_str(), val);

    rc = sqlite3_exec(db, query, 0, 0, &errmsg);
    if(SQLITE_OK != rc) {
        std::cout << "SQL " << query << " error: " << errmsg << std::endl;
        sqlite3_free(errmsg);
    } else {
        std::cout << "SQL " << query << " done" << std::endl;
    }
    sqlite3_free(query);

    return rc;
}

template<typename T>
int SingleIntListDb<T>::del(sqlite3 *db, T val)
{
    char *query;
    char *errmsg;
    int rc;

    query = sqlite3_mprintf(
			"DELETE from %s where (%s=%d);", mTable.c_str(), mCol.c_str(), val);

    rc = sqlite3_exec(db, query, 0, 0, &errmsg);
    if(SQLITE_OK != rc) {
        std::cout << "SQL " << query << " error: " << errmsg << std::endl;
        sqlite3_free(errmsg);
    } else {
        std::cout << "SQL " << query << " done" << std::endl;
    }
    sqlite3_free(query);

    return rc;
}

template<typename T>
int SingleIntListDb<T>::get(sqlite3 *db, T *val, size_t &count)
{
    char *query;
    char *errmsg;
    int rc;

	query = sqlite3_mprintf("SELECT %s from %s;", mCol.c_str(), mTable.c_str());

	SingleIntListCbData<T> cbData = {
		.values = val,
		.count = count,
	};

	int cnt = 0;
    rc = sqlite3_exec(db, query, getCallback<T>, (void *)&cbData, &errmsg);
    if(SQLITE_OK != rc) {
        std::cout << "SQL " << query << " error: " << errmsg << std::endl;
        sqlite3_free(errmsg);
    } else {
        std::cout << "SQL " << query << " done" << std::endl;
    }
    sqlite3_free(query);

    return rc;
}

template<typename T>
int SingleIntListDb<T>::clr(sqlite3 *db)
{
    char *query;
    char *errmsg;
    int rc;

    query = sqlite3_mprintf(
			"DELETE from %s;", mTable.c_str());

    rc = sqlite3_exec(db, query, 0, 0, &errmsg);
    if(SQLITE_OK != rc) {
        std::cout << "SQL " << query << " error: " << errmsg << std::endl;
        sqlite3_free(errmsg);
    } else {
        std::cout << "SQL " << query << " done" << std::endl;
    }
    sqlite3_free(query);

    return rc;
}

void openSxmInfoDB(sqlite3 **ppDb) {
    bool needInitialize = false;
    int rc;

    if ( access(DB_NAME, F_OK) == -1 ) {
        needInitialize = true;
    }

    rc = sqlite3_open(DB_NAME, &(*ppDb));
    if(rc != SQLITE_OK)
    {
		std::cout << "Can't open database: " << sqlite3_errmsg(*ppDb) << std::endl;
    }
    else
    {
        std::cout << "Opened database successfully" << std::endl;
    }

    if(needInitialize) {
    	char *errmsg;
        rc = sqlite3_exec(*ppDb, "CREATE TABLE IF NOT EXISTS 'SEEK' ('id' INTEGER KEY NOT NULL DEFAULT 0, 'tmi' INTEGER NOT NULL DEFAULT 0, 'info' TEXT, 'enabled' INTEGER NOT NULL DEFAULT 1, UNIQUE(id,tmi));", 0, 0, &errmsg);
        sqlite3_free(errmsg);

        rc = sqlite3_exec(*ppDb, "CREATE TABLE IF NOT EXISTS 'LOCK' ('sid' INTEGER NOT NULL DEFAULT 0 UNIQUE);", 0, 0, &errmsg);
        sqlite3_free(errmsg);

        rc = sqlite3_exec(*ppDb, "CREATE TABLE IF NOT EXISTS 'SKIP' ('sid' INTEGER NOT NULL DEFAULT 0 UNIQUE);", 0, 0, &errmsg);
        sqlite3_free(errmsg);
    }
}

void closeSxmInfoDB(sqlite3 *db) {
    int rc = sqlite3_close(db);
    std::cout << "sqlite3_close(" << (db) << ") : " << rc << std::endl;
}

int seekInsert(sqlite3 *db, uint32_t id, int tmi, const char *info, int enable = 1)
{
    char *query;
    char *errmsg;
    int rc;

    query = sqlite3_mprintf(
			"INSERT INTO SEEK VALUES (%d, %u, %Q, %d);", id, tmi, info, enable);

    rc = sqlite3_exec(db, query, 0, 0, &errmsg);
    if(SQLITE_OK != rc) {
        std::cout << "SQL " << query << " error: " << errmsg << std::endl;
        sqlite3_free(errmsg);
    } else {
        std::cout << "SQL " << query << " done" << std::endl;
    }
    sqlite3_free(query);

    return rc;
}

int seekDelete(sqlite3 *db, uint32_t id, int tmi)
{
    char *query;
    char *errmsg;
    int rc;

    query = sqlite3_mprintf(
			"DELETE from SEEK where (id=%u AND tmi=%d);", id, tmi);

    rc = sqlite3_exec(db, query, 0, 0, &errmsg);
    if(SQLITE_OK != rc) {
        std::cout << "SQL " << query << " error: " << errmsg << std::endl;
        sqlite3_free(errmsg);
    } else {
        std::cout << "SQL " << query << " done" << std::endl;
    }
    sqlite3_free(query);

    return rc;
}

int seekEnable(sqlite3 *db, uint32_t id, int tmi, int enable)
{
    char *query;
    char *errmsg;
    int rc;

    query = sqlite3_mprintf(
			"UPDATE SEEK set enabled = %d where (id=%u AND tmi=%d);", enable, id, tmi);

    rc = sqlite3_exec(db, query, 0, 0, &errmsg);
    if(SQLITE_OK != rc) {
        std::cout << "SQL " << query << " error: " << errmsg << std::endl;
        sqlite3_free(errmsg);
    } else {
        std::cout << "SQL " << query << " done" << std::endl;
    }
    sqlite3_free(query);

    return rc;
}

int countCallback(void *data, int argc, char **argv, char **azColName)
{
	std::cout << "go" << std::endl;
	for (int i = 0; i < argc; i++) {
		std::cout << "CNT CB, " << azColName[i] << ": " << argv[i] << std::endl;
		*(int *)data = atoi(argv[0]);
	}
	return 0;
}

int seekCount(sqlite3 *db, int &count, int tmi = -1)
{
    char *query;
    char *errmsg;
    int rc;

	if (-1 == tmi) {
		query = sqlite3_mprintf("SELECT COUNT(*) from SEEK;");
	} else {
		query = sqlite3_mprintf("SELECT COUNT(*) from SEEK where tmi=%d;", tmi);
	}

    rc = sqlite3_exec(db, query, countCallback, (void *)&count, &errmsg);
    if(SQLITE_OK != rc) {
        std::cout << "SQL " << query << " error: " << errmsg << std::endl;
        sqlite3_free(errmsg);
    } else {
        std::cout << "SQL " << query << " done" << std::endl;
    }
    sqlite3_free(query);

    return rc;
}

int getIdsCallback(void *data, int argc, char **argv, char **azColName)
{
	int *count = (int *)data;

	std::cout << "go" << std::endl;
	for (int i = 0; i < argc; i++) {
		std::cout << "ID CB, " << azColName[i] << ": " << argv[i] << std::endl;
		std::cout << ++(*count) << std::endl;
	}
	return 0;
}

int seekGetIds(sqlite3 *db, int tmi, int enabledOnly = 1)
{
    char *query;
    char *errmsg;
    int rc;

	if (enabledOnly) {
		query = sqlite3_mprintf("SELECT id from SEEK where (tmi=%d AND enabled=1);", tmi);
	} else {
		query = sqlite3_mprintf("SELECT id from SEEK where tmi=%d;", tmi);
	}

	int count = 0;
    rc = sqlite3_exec(db, query, getIdsCallback, (void *)&count, &errmsg);
    if(SQLITE_OK != rc) {
        std::cout << "SQL " << query << " error: " << errmsg << std::endl;
        sqlite3_free(errmsg);
    } else {
        std::cout << "SQL " << query << " done" << std::endl;
    }
    sqlite3_free(query);

    return rc;
}

int seekClear(sqlite3 *db)
{
    char *query;
    char *errmsg;
    int rc;

    query = sqlite3_mprintf(
			"DELETE from SEEK;");

    rc = sqlite3_exec(db, query, 0, 0, &errmsg);
    if(SQLITE_OK != rc) {
        std::cout << "SQL " << query << " error: " << errmsg << std::endl;
        sqlite3_free(errmsg);
    } else {
        std::cout << "SQL " << query << " done" << std::endl;
    }
    sqlite3_free(query);

    return rc;
}

int main()
{
	sqlite3 *db = NULL;
	openSxmInfoDB(&db);

#ifdef SEEK
	seekInsert(db, 1, 0, "1aaa");
	seekInsert(db, 2, 0, "2aaa");
	seekInsert(db, 3, 0, "3aaa");
	seekInsert(db, 1, 0, "1aaa");
	seekInsert(db, 1, 1, "1aaa");
	seekInsert(db, 1, 1, "1aaa");
	seekInsert(db, 5, 2, "5aaa");
	seekInsert(db, 6, 4, "6aaa");
	seekInsert(db, 7, 3, "7aaa");

	int count = 0;
	seekCount(db, count);
	std::cout << ",,," << count << std::endl;

	seekDelete(db, 5, 3);
	seekDelete(db, 5, 2);

	seekCount(db, count, 0);
	std::cout << ",,," << count << std::endl;

	seekEnable(db, 1, 0, 0);

	seekGetIds(db, 0);
	seekGetIds(db, 1, 0);
	seekGetIds(db, 3, 0);
	seekGetIds(db, 4, 0);
#endif

	SingleIntListDb<uint32_t> lock("LOCK", "sid");
	lock.ins(db, 5);
	lock.ins(db, 6);
	lock.ins(db, 7);
	lock.ins(db, 8);

	uint32_t values[100];
	size_t count = 0;

	lock.get(db, values, count);
	
	for (int i = 0; i < count; ++i) {
		std::cout << values[i] << std::endl;
	}

	closeSxmInfoDB(db);
	return 0;
}
