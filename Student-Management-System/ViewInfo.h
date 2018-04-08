#ifndef _VIEWINFO_H
#define _VIEWINFO_H
#include<fstream>
#include<iostream>
#include<sqlite3.h>
#include<iostream>
#include"Const.h"
#include"Utils.h"
using namespace std;
class ViewInfo {
private:
public:
	string *header;
	string *headerCode;
	int *hide;
	int totalColumn;
	ViewInfo();
	void getHeaderInfo(string path);
	void viewInfo(string path, string headerPath, string tableName, string username);
};
#endif