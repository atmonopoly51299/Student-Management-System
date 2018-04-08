#include"Utils.h"

string Utils::SINGLE_RECORD = "NULL";

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	for (i = 0; i<argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

bool Utils::checkUnique(string path, string tablename, string key) {
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;

	rc = sqlite3_open(path.c_str(), &db);

	if (rc) {
		return false;
	}

	string QUERY = "SELECT * FROM " + tablename+" WHERE classname = "+key;
	rc = sqlite3_exec(db, QUERY.c_str(), callback, 0, &zErrMsg);

	if (rc != SQLITE_OK) {
		if (rc == SQLITE_CONSTRAINT_UNIQUE) {
			cout << Const::INFO_ALREADY_EXISTED_ELERT << endl;
			sqlite3_free(zErrMsg);
			return false;
		}
		sqlite3_free(zErrMsg);
		return true;
	}
	else return false;
	sqlite3_close(db);
}



void Utils::insertRecord(string path, string error, string success, string QUERY) {

	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;

	rc = sqlite3_open(path.c_str(), &db);

	if (rc) {
		cout << error << endl;
		return;
	}

	rc = sqlite3_exec(db, QUERY.c_str(), callback, 0, &zErrMsg);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Records created successfully\n");
	}
	sqlite3_close(db);
}

/*void Utils::insertRecord(string path, string error, string success, string QUERY) {

	sqlite3 *db;

	int message;
	message = sqlite3_open(path.c_str(), &db);

	if (message) {
		cout << error << endl;
		return;
	}

	sqlite3_stmt *stmt;
	char* errMsg = NULL;
	int rc = sqlite3_prepare_v2(db, QUERY.c_str(), -1, &stmt, NULL);
	//int rc = sqlite3_exec(db, QUERY.c_str(), NULL, NULL, &errMsg);

	cout << rc << endl;
	if (rc != SQLITE_OK) {
		cout << error << endl;
		return;
	}

	rc = sqlite3_step(stmt);
	cout << rc << endl;
	if (rc != SQLITE_DONE && rc != SQLITE_ROW) {
		cout << error << endl;
		sqlite3_finalize(stmt);
		return;
	}

	cout << success << endl;

	sqlite3_finalize(stmt);
	sqlite3_close(db);
}*/

void Utils::writeRecord(string path, string error, string success, string modifyCol, string modifyValue, string table, string conditionCol, string value) {
	sqlite3 *db;

	int message;
	message = sqlite3_open(path.c_str(), &db);

	if (message) {
		cout << error << endl;
		return;
	}

	sqlite3_stmt *stmt;
	string QUERY = "UPDATE " + table + " SET " + modifyCol + " = '" + modifyValue + "' WHERE " + conditionCol + " = '" + value+"'";

	int rc = sqlite3_prepare_v2(db, QUERY.c_str(), -1, &stmt, NULL);

	if (rc != SQLITE_OK) {
		cout << error << endl;
		return;
	}

	rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE && rc != SQLITE_ROW) {
		cout << error << endl;
		sqlite3_finalize(stmt);
		return;
	}

	cout << success << endl;
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

//void writeRecord(sqlite3*db, string error, string modifyCol, string modifyValue, string table, string conditionCol, string value)

/*static int callbackMulti(void *data, int argc, char **argv, char **azColName) {
	RECORD_COUNT = argc;
	MULTI_RECORD = new string[argc];
	for (int i=0; i < argc; ++i) {
		MULTI_RECORD[i] = argv[i];
	}
	return 0;
}*/

/*int Utils::callbackSingle(void *data, int argc, char **argv, char **azColName) {
	cout << "COUNT "<<argc << endl;
	if (argc == 0)SINGLE_RECORD = "NULL";
	else SINGLE_RECORD = argv[0]? argv[0]:"NULL";
	cout << "RECORD " << SINGLE_RECORD << endl;
	return 0;
}*/

/*void getString(sqlite3*db, string error, int selecColCount,string *selectCol, string table, string WHERE, int &c, string*&holder) {
	int message;
	string QUERY = "SELECT ";
	for (int i = 0; i < selecColCount; ++i)if(i==selecColCount-1)QUERY += selectCol[i]; else QUERY += selectCol[i] + ",";
	QUERY += " FROM " + table + " WHERE " + WHERE;

	//Execute SQL statement
	int data = 0;
	char *zErrMsg = 0;
	message = sqlite3_exec(db, QUERY.c_str(), callbackMulti, (void*)data, &zErrMsg);

	if (message != SQLITE_OK) {
		cout << Const::SERVICE_ERROR_MESS << endl;
		sqlite3_free(zErrMsg);
	}

	c = RECORD_COUNT;
	holder = MULTI_RECORD;
	
	delete[]MULTI_RECORD;
	sqlite3_close(db);
}*/

/*string Utils::getString(string path, string error, string selectCol, string table, string conditionCol, string value) {
	sqlite3 *db;

	int message;
	message = sqlite3_open(path.c_str(), &db);

	if (message) {
		cout << error << endl;
		return 0;
	}

	string QUERY = "SELECT " + selectCol + " FROM " + table + " WHERE " + conditionCol + " = " + value;

	//Execute SQL statement
	const char* data = 0;
	char *zErrMsg = 0;
	message = sqlite3_exec(db, QUERY.c_str(), callbackSingle, (void*)data, &zErrMsg);
	cout << "MESS" << message << endl;
	if (message) {
		cout << error << endl;
		sqlite3_free(zErrMsg);
	}

	sqlite3_close(db);
	return SINGLE_RECORD;
}*/

void Utils::getColumnsCout(string path, string error, string table, string classname) {
	sqlite3 *db;

	int message;
	message = sqlite3_open(path.c_str(), &db);

	if (message) {
		cout << error << endl;
		return;
	}

	sqlite3_stmt *stmt;
	string QUERY = "SELECT * FROM " + table +" WHERE classname = '"+classname+"'";

	int rc = sqlite3_prepare_v2(db, QUERY.c_str(), -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		cout << error << endl;
		return;
	}
	int *hide = new int[50];
	string *header = new string[50];
	string *headerCode = new string[50];
	int totalColumn = -1;

	Utils::intepretHeader(Const::studentDatabaseDirectory + Const::header, Const::SERVICE_ERROR_MESS, Const::headerInfoTablename, hide, header, headerCode, totalColumn);
	
	cout << endl;
	int id = -1;
	while (true) {
		rc = sqlite3_step(stmt);
		if (rc == SQLITE_DONE) {
			sqlite3_finalize(stmt);
			return;
		}
		else if (sqlite3_column_type(stmt, 0) == SQLITE_NULL) {
			sqlite3_finalize(stmt);
			return;
		}
		else {
			if (rc == SQLITE_ROW) {
				for (int i = 0; i < totalColumn; ++i) {
					cout << header[i] << ": ";
					cout << string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, i))) << endl;
				}
				cout << endl;
			}
			else {
				break;
			}
		}
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

void Utils::getOneColumn(string path, string error, string table, string *&holder, int&rows) {
	sqlite3 *db;

	int message;
	message = sqlite3_open(path.c_str(), &db);

	if (message) {
		cout << error << endl;
		return;
	}

	sqlite3_stmt *stmt;
	string QUERY = "SELECT * FROM " + table;

	int rc = sqlite3_prepare_v2(db, QUERY.c_str(), -1, &stmt, NULL);

	if (rc != SQLITE_OK) {
		cout << error << endl;
		return;
	}

	while (true) {
		rc = sqlite3_step(stmt);
		if (rc == SQLITE_DONE) {
			sqlite3_finalize(stmt);
			return;
		}
		else if (sqlite3_column_type(stmt, 0) == SQLITE_NULL) {
			sqlite3_finalize(stmt);
			return;
		}
		else {
			if (rc == SQLITE_ROW) {
				holder[++rows] = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
			}
			else {
				break;
			}
		}
	}
	++rows;

	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

void Utils::getInterchange(string path, string error, string table, string *&headerCode, string*&intechange, int&colCount, int&rows) {
	sqlite3 *db;

	int message;
	message = sqlite3_open(path.c_str(), &db);

	if (message) {
		cout << error << endl;
		return;
	}

	sqlite3_stmt *stmt;
	string QUERY = "SELECT * FROM " + table;

	int rc = sqlite3_prepare_v2(db, QUERY.c_str(), -1, &stmt, NULL);

	if (rc != SQLITE_OK) {
		cout << error << endl;
		return;
	}

	while (true) {
		rc = sqlite3_step(stmt);
		if (rc == SQLITE_DONE) {
			sqlite3_finalize(stmt);
			return;
		}
		else if (sqlite3_column_type(stmt, 0) == SQLITE_NULL) {
			sqlite3_finalize(stmt);
			return;
		}
		else {
			if (rc == SQLITE_ROW) {
				if (colCount == 0)colCount = sqlite3_column_count(stmt);
				headerCode[++rows] = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
				intechange[rows] = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
			}
			else {
				break;
			}
		}
	}
	++rows;

	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

void Utils::intepretHeader(string path, string error, string table, int*&hide, string *&header, string*&headerCode, int&totalColumn) {

	sqlite3 *db;

	int message;
	message = sqlite3_open(path.c_str(), &db);

	if (message) {
		cout << error << endl;
		return;
	}

	sqlite3_stmt *stmt;
	string QUERY = "SELECT * FROM " + table;

	int rc = sqlite3_prepare_v2(db, QUERY.c_str(), -1, &stmt, NULL);

	if (rc != SQLITE_OK) {
		cout << error << endl;
		return;
	}

	while (true) {
		rc = sqlite3_step(stmt);
		if (rc == SQLITE_DONE) {
			sqlite3_finalize(stmt);
			return;
		}
		else if (sqlite3_column_type(stmt, 0) == SQLITE_NULL) {
			sqlite3_finalize(stmt);
			return;
		}
		else {
			if (rc == SQLITE_ROW) {
				headerCode[++totalColumn] = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
				hide[totalColumn] = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)))[0] - 48;
				header[totalColumn] = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
			}
			else {
				break;
			}
		}
	}
	++totalColumn;

	sqlite3_finalize(stmt);
	sqlite3_close(db);
}


void Utils::viewAllRecordStepOld(string path, string error, string selectCol, string table, string conditionCol, string value, string *&oldIfo) {
	sqlite3 *db;

	int message;
	message = sqlite3_open(path.c_str(), &db);

	if (message) {
		cout << error << endl;
		return;
	}

	sqlite3_stmt *stmt;
	string QUERY = "SELECT " + selectCol + " FROM " + table + " WHERE " + conditionCol + " = " + value;

	int rc = sqlite3_prepare_v2(db, QUERY.c_str(), -1, &stmt, NULL);

	if (rc != SQLITE_OK) {
		cout << error << endl;
		return;
	}

	rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE && rc != SQLITE_ROW) {
		cout << error << endl;
		sqlite3_finalize(stmt);
		return;
	}

	if (rc == SQLITE_DONE) // no result
		return;
	else if (sqlite3_column_type(stmt, 0) == SQLITE_NULL) // result is NULL
		return;
	else {
		//result existed:
		int c = sqlite3_column_count(stmt);
		for (int i = 0; i < c; ++i) {
			//cout << header[i] << ": " << string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, i))) << endl;
			oldIfo[i] = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
		}
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

void Utils::viewAllRecordStep(string path, string error, string selectCol, string table, string conditionCol, string value, string*&infoHolder, int&cc) {
	sqlite3 *db;

	int message;
	message = sqlite3_open(path.c_str(), &db);

	if (message) {
		cout << error << endl;
		return;
	}

	sqlite3_stmt *stmt;
	string QUERY = "SELECT " + selectCol + " FROM " + table + " WHERE " + conditionCol + " = " + value;

	int rc = sqlite3_prepare_v2(db, QUERY.c_str(), -1, &stmt, NULL);

	if (rc != SQLITE_OK) {
		cout << error << endl;
		return;
	}

	rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE && rc != SQLITE_ROW) {
		cout << error << endl;
		sqlite3_finalize(stmt);
		return;
	}

	if (rc == SQLITE_DONE) // no result
		return;
	else if (sqlite3_column_type(stmt, 0) == SQLITE_NULL) // result is NULL
		return;
	else {
		//result existed:
		int c = sqlite3_column_count(stmt);
		infoHolder = new string[c];
		cc = c;
		for (int i = 0; i < c; ++i) {
			infoHolder[i] = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, i)));
		}
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

void Utils::viewAllRecordStep(string path, string error, string selectCol, string table, string conditionCol, string value, int*&hide, string *&header) {
	sqlite3 *db;

	int message;
	message = sqlite3_open(path.c_str(), &db);

	if (message) {
		cout << error << endl;
		return;
	}

	sqlite3_stmt *stmt;
	string QUERY = "SELECT " + selectCol + " FROM " + table + " WHERE " + conditionCol + " = " + "'"+value+ "'";

	int rc = sqlite3_prepare_v2(db, QUERY.c_str(), -1, &stmt, NULL);

	if (rc != SQLITE_OK) {
		cout << error << endl;
		return;
	}

	rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE && rc != SQLITE_ROW) {
		cout << error << endl;
		sqlite3_finalize(stmt);
		return;
	}

	if (rc == SQLITE_DONE) // no result
		return;
	else if (sqlite3_column_type(stmt, 0) == SQLITE_NULL) // result is NULL
		return;
	else { 
		//result existed:
		int c = sqlite3_column_count(stmt);
		for (int i = 0; i < c; ++i) {
			if (!hide[i]) {
				cout << header[i] << ": " << string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, i))) << endl;
			}
		}
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

string Utils::getStringStep(string path, string error, string selectCol, string table, string conditionCol, string value) {
	sqlite3 *db;

	int message; 
	message = sqlite3_open(path.c_str(), &db);

	if (message) {
		cout << error << endl;
		return 0;
	}

	sqlite3_stmt *stmt;
	string QUERY = "SELECT " + selectCol + " FROM " + table + " WHERE " + conditionCol + " = " + value;
	int rc = sqlite3_prepare_v2(db, QUERY.c_str(), -1, &stmt, NULL);


	if (rc != SQLITE_OK) {
		cout << error << endl;
		return "NULL";
	}

	rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE && rc != SQLITE_ROW) {
		cout << error << endl;
		sqlite3_finalize(stmt);
		return "NULL";
	}

	if (rc == SQLITE_DONE) // no result
		return "NULL";
	else if (sqlite3_column_type(stmt, 0) == SQLITE_NULL) // result is NULL
		return "NULL";
	else { // some valid result
		SINGLE_RECORD = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return SINGLE_RECORD;
}