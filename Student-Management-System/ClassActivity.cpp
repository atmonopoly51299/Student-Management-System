#include"ClassActivity.h"


string ClassActivity::getClass(string classname) {
	string insertTableName;
	if (classname[classname.length() - 1] >= '1'&&classname[classname.length() - 1] <= '9') {
		insertTableName = classname.substr(2, classname.length() - 3);
	}
	else {
		insertTableName = classname.substr(2, classname.length() - 2);
	}
	return insertTableName;
}


void ClassActivity::viewAllStudentsOfClass() {
	cout << "Input class name: ";
	string classname;
	getline(cin, classname);

	//vd 17BBB2

	//check if this CLASSCODE exist
	while (!Utils::checkUnique(Const::sLDatabaseDirectory + Const::classCode, "total_class", classname)) {
		cout << "Re-input new class name (or hit number 0 to quit): "; getline(cin, classname);
		if (classname == "0")return;
	}

	Utils::getColumnsCout(Const::studentDatabaseDirectory + classname.substr(0,2)+ "/"+ classname.substr(0,2)+Const::EXT, Const::SERVICE_ERROR_MESS, getClass(classname), classname);
}

void ClassActivity::viewListOfClass() {
	cout << "List of all classes: " << endl;
	string *listOfClasses = new string[250];
	int c=-1;
	Utils::getOneColumn(Const::sLDatabaseDirectory + Const::classCode, Const::SERVICE_ERROR_MESS, "total_class", listOfClasses, c);
	for (int i = 0; i <= c; ++i) {
		cout << listOfClasses[i] << endl;
	}
}

void ClassActivity::addNewEmptyClass() {
	cout << "New class name to add: ";
	string classname;
	getline(cin, classname);

	//vd 17BBB2

	//check if this CLASSCODE exist,CLASSCODE is unique so if violated, means user input existing class, ask for re-input or quit
	//insert into class_code.db in the table TOTAL_CLASS
	while (!Utils::checkUnique(Const::sLDatabaseDirectory + Const::classCode, "total_class", classname)) {
		cout << "Re-input new class name (or hit number 0 to quit): "; getline(cin, classname);
		if (classname == "0")return;
	}
	
	string QUERY = "INSERT INTO total_class VALUES ('" + classname + "')";
	Utils::insertRecord(Const::sLDatabaseDirectory + Const::classCode, Const::SERVICE_ERROR_MESS, "update the general database: " + Const::OPERATION_SUCCESSFULLY, QUERY);

	//classcode and its interchane code:
	string *classcodes = new string [250];//our school should not reach this capacity
	string *interchange = new string[250];
	int colCount=0, rowsCount = -1;
	Utils::getInterchange(Const::sLDatabaseDirectory + Const::classCode, Const::SERVICE_ERROR_MESS, Const::classCodeTablename, classcodes, interchange, colCount, rowsCount);

	//subclass->class code already existed, update the general database is enough. Done
	string cl = getClass(classname);
	for (int i = 0; i < rowsCount; ++i) {
		if (cl == classcodes[i]) {
			cout << "Class code existed.\nOperation finished" << endl;
			return;
		}
	}

	//okay, not a subclass, register this new class code
	//insert into class_code.db the new CLASSCODE: code, brief, full, cha: 53 CLC Chat luong cao 14
	QUERY = "INSERT INTO class_code VALUES (";
	string head[] = { "Code","Brief","Full name of class","Interchangable" };
	string tmp;
	string brief;
	for (int i = 0; i < colCount; ++i) {
		cout << head[i] << ": ";
		if (i == 0) {
			getline(cin, tmp);
			QUERY += "'" + tmp + "',";
		}
		else if (i == 1) {
			cout << getClass(classname) << endl;
			QUERY += "'" + getClass(classname) + "',";
		}
		else if (i==2) {
			getline(cin, tmp);
			QUERY += "'" + tmp + "',";
		}
		else if(i==3) {
			cout << "Reference:" << endl;
			for (int j = 0; j <= rowsCount; ++j) {
				cout << classcodes[j] << ": " << interchange[j] << endl;
			}
			getline(cin, tmp);
			QUERY += "'" + tmp + "',";
		}
	}
	QUERY.pop_back();
	QUERY += ")";

	Utils::insertRecord(Const::sLDatabaseDirectory + Const::classCode, Const::SERVICE_ERROR_MESS, "generate class code: " + Const::OPERATION_SUCCESSFULLY, QUERY);
	
	//part of SQLite COMMAND is stored in Const::SQL_COMMAND
	if (experimental::filesystem::exists(Const::studentDatabaseDirectory + classname.substr(0, 2))) {
		//create new table in existing database
		QUERY = "CREATE TABLE " + cl + Const::SQL_CREATE_TABLE;
		string path = Const::studentDatabaseDirectory + classname.substr(0, 2) + "/" + classname.substr(0, 2) + Const::EXT;
		Utils::insertRecord(path, Const::SERVICE_ERROR_MESS, Const::OPERATION_SUCCESSFULLY, QUERY);
		return;
	}
	else {
		//create new directory
		experimental::filesystem::create_directories(Const::studentDatabaseDirectory + classname.substr(0, 2));
		ofstream out;
		out.open(Const::studentDatabaseDirectory + classname.substr(0, 2) + "/" + classname.substr(0, 2) + Const::EXT);
		QUERY = "CREATE TABLE " + cl + Const::SQL_CREATE_TABLE;
		Utils::insertRecord(Const::studentDatabaseDirectory + classname.substr(0, 2) + "/" + classname.substr(0, 2) + Const::EXT, Const::SERVICE_ERROR_MESS, Const::OPERATION_SUCCESSFULLY, QUERY);
		return;
	}

	

}