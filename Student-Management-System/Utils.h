#ifndef _UTILS_H
#define _UTILS_H
#include<fstream>
#include<iostream>
#include<sqlite3.h>
#include<iostream>
#include"Const.h"
using namespace std;
class Utils {
private:
	static int callbackSingle(void *data, int argc, char **argv, char **azColName);
public:
	static string SINGLE_RECORD;
	string *MULTI_RECORD;
	int RECORD_COUNT;
	//static string getString(string path, string error, string selectCol, string table, string conditionCol, string value);
	static string getStringStep(string path, string error, string selectCol, string table, string conditionCol, string value);
	static void viewAllRecordStep(string path, string error, string selectCol, string table, string conditionCol, string value, int*&hide, string *&header);
	static void viewAllRecordStep(string path, string error, string selectCol, string table, string conditionCol, string value, string*&infoHolder, int&cc);
	static void viewAllRecordStepOld(string path, string error, string selectCol, string table, string conditionCol, string value, string *&oldIfo);
	static void intepretHeader(string path, string error, string table, int*&hide, string *&header, string*&headerCode, int&totalColumn);
	static void getInterchange(string path, string error, string table, string *&headerCode, string*&intechange, int&colCount, int&rows);
	static void getOneColumn(string path, string error, string table, string *&holder, int&rows);
	static void getColumnsCout(string path, string error, string table, string classname);
	//void getString(sqlite3*db, string error, int selecColCount, string *selectCol, string table, string WHERE, int &c, string*&holder);
	static void writeRecord(string path, string error, string success, string modifyCol, string modifyValue, string table, string conditionCol, string value);
	static void writeRecord(sqlite3*db, string error, string success, string modifyCol, string modifyValue, string table, string conditionCol, string value);
	static void insertRecord(string path, string error, string success, string QUERY);
	static bool checkUnique(string path, string tablename,string key);
};
#endif