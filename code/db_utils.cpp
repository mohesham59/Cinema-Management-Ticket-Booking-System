#include "db_utils.h"
#include <iostream>

bool executeSQL(sqlite3* db, const string& sql) {
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);

    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

bool querySQL(sqlite3* db, const string& sql, function<void(sqlite3_stmt*)> callback) {
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        callback(stmt);
    }

    sqlite3_finalize(stmt);
    return true;
}
