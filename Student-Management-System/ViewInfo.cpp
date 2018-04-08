#include"ViewInfo.h"

void ViewInfo::getHeaderInfo(string path) {
	hide = new int[50];
	header = new string[50];
	headerCode = new string[50];
	Utils::intepretHeader(path, Const::SERVICE_ERROR_MESS, Const::headerInfoTablename, hide, header,headerCode,totalColumn);
}

void ViewInfo::viewInfo(string path, string headerPath, string tableName, string username) {
	getHeaderInfo(headerPath);
	Utils::viewAllRecordStep(path,Const::SERVICE_ERROR_MESS,"*",tableName,"username",username, hide, header);
}

ViewInfo::ViewInfo() {
	string *header = NULL; 
	string *headerCode = NULL;
	int *hide = NULL;
	totalColumn = -1;
}