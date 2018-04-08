#ifndef _STUDENT_H_
#define _STUDENT_H_
#include<fstream>
#include<iostream>
#include<sqlite3.h>
#include<iostream>
#include"Const.h"
#include"Utils.h"
#include"ViewInfo.h"
using namespace std;

class Student {
private:
	//ViewInfo vi;
	string getClass(string classname);
public:
	Student();
	void importStudentsFromAClass();
	void addANewStudentToAClass();
	void editAnExistingStudent();
	void changeStudentFromClassAtoClassB(string path, string tablename, string username, string newClass, string oldClass);
};


#endif