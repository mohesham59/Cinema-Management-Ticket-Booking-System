
#ifndef DB_UTILS_H
#define DB_UTILS_H
#include <functional>
#include "sqlite3.h"
#include <string>
using namespace std;

bool executeSQL(sqlite3* db, const std::string& sql);

bool querySQL(sqlite3* db, const string& sql, function<void(sqlite3_stmt*)> callback);

#endif
