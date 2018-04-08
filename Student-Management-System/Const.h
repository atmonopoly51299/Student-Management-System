#ifndef _CONST_H_
#define _CONST_H_
#include<string>
using namespace std;
class Const {
public:
	static string studentDatabaseDirectory;

	static string sLDatabaseDirectory;

	static string classCode;
	static string classCodeTablename;
	
	static string header;
	static string headerInfoTablename;

	static string sLInfo;
	static string sLInfoTablename;

	static string EXT;
	
	static int USERNAME_MIN_CHAR;
	static string DEFAULT_PASSWORD;
	static int PASSWORD_MIN_CHAR;
	static string USER_NOT_FOUND_MESS;
	static string WRONG_PASSWORD_MESS;
	static string SERVICE_ERROR_MESS;
	static string PASSWORD_POLICY;
	static string PASSWORD_VIOLATED_ELERT;
	static string INFO_ALREADY_EXISTED_ELERT;

	static string LOGIN_SUCCESSFULLY;
	static string USER_FOUND_SUCCESSFULLY;
	static string PASSWORD_CHANGED_SUCCESSFULLY;
	static string OPERATION_SUCCESSFULLY;

	static string SQL_CREATE_TABLE;

};
#endif
