#ifndef _LOGIN_H
#define _LOGIN_H
#include<fstream>
#include<iostream>
#include<sqlite3.h>
#include<iostream>
#include"Const.h"
#include"Utils.h"
using namespace std;
class Login {
private:
	int stt;
	string username;
	string password;
	string path;
	string tableName;
	int personType;

	int foundUser();
	int matchPassword();
public:
	void login();
	int getSTT();
	int getType();
	string getPath();
	string getUsername();
	string getPassword();
	string getTablename();
	void changePasswordInit();
	void changePasswordRuntime();
};
#endif