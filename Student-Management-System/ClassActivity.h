#ifndef _CLASSACTIVITY_H_
#define _CLASSACTIVITY_H_
#include<fstream>
#include<iostream>
#include<sqlite3.h>
#include<iostream>
#include <experimental/filesystem>
#include"Const.h"
#include"Utils.h"
using namespace std;

class ClassActivity {
private:
public:
	void addNewEmptyClass();
	string getClass(string classname);
	void viewListOfClass();
	void viewAllStudentsOfClass();
};


#endif