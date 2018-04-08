#include"Const.h"
string Const::studentDatabaseDirectory = "database/student/";
string Const::sLDatabaseDirectory = "database/sl/";

string Const::classCode = "class_code.db";
string Const::classCodeTablename = "class_code";

string Const::header = "header.db";
string Const::headerInfoTablename = "info";

string Const::sLInfo = "sl.db";
string Const::sLInfoTablename = "sl";

string Const::EXT = ".db";
int Const::USERNAME_MIN_CHAR = 2;
string Const::DEFAULT_PASSWORD = "1";
int Const::PASSWORD_MIN_CHAR = 6;
string Const::USER_NOT_FOUND_MESS = "Sorry, user not found!";
string Const::WRONG_PASSWORD_MESS = "Sorry, wrong password!";
string Const::SERVICE_ERROR_MESS = "Sorry, our service encountered an error!";
string Const::PASSWORD_POLICY = "Policy: password must be at least 6 characters!";
string Const::PASSWORD_VIOLATED_ELERT = "Inputted password violated the policy, please read it carefully!";
string Const::INFO_ALREADY_EXISTED_ELERT = "Info already existed!";

string Const::LOGIN_SUCCESSFULLY = "Login successfully!";
string Const::USER_FOUND_SUCCESSFULLY = "User found!";
string Const::PASSWORD_CHANGED_SUCCESSFULLY = "Password changed successfully!";
string Const::OPERATION_SUCCESSFULLY = "Operation successfully!";

string Const::SQL_CREATE_TABLE = "(username	TEXT UNIQUE, pass	text NOT NULL, surname	text NOT NULL,name	text NOT NULL,dob	TEXT NOT NULL,gender	TEXT NOT NULL,classname	text NOT NULL,term	text NOT NULL,status	text NOT NULL,idcard	text NOT NULL,nationality	text NOT NULL,ethnic	text NOT NULL,peradd	text NOT NULL,curadd	text NOT NULL,email	text NOT NULL,phone	text NOT NULL,agribank	text NOT NULL,genemail	text NOT NULL,unionist	text NOT NULL,inclass	TEXT DEFAULT 'y')";


