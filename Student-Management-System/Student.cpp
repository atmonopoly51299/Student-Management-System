#include"Student.h"

Student::Student() {

}

string Student::getClass(string classname) {
	string insertTableName;
	if (classname[classname.length() - 1] >= '1'&&classname[classname.length() - 1] <= '9') {
		insertTableName = classname.substr(2, classname.length() - 3);
	}
	else {
		insertTableName = classname.substr(2, classname.length() - 2);
	}
	return insertTableName;
}

void Student::changeStudentFromClassAtoClassB(string path, string tablename, string username, string newClass, string oldClass) {

	string *oldInfo;
	int c = 0;
	Utils::viewAllRecordStep(path, Const::SERVICE_ERROR_MESS, "*", tablename, "username", username, oldInfo, c);

	//MARK HIM/HER AS In Class Status 'n' in his/her oldClass
	string QUERY = "UPDATE " + tablename + " SET inclass = 'n' WHERE username = " + username;
	Utils::insertRecord(path, Const::SERVICE_ERROR_MESS, Const::OPERATION_SUCCESSFULLY, QUERY);

	//INSERT
	QUERY = "INSERT INTO " + getClass(newClass) + " VALUES (";
	for (int i = 0; i < c; ++i) {
		if(oldInfo[i]==oldClass)QUERY += "'" + newClass + "',";
		else QUERY += "'" + oldInfo[i] + "',";
	}
	QUERY.pop_back();
	QUERY += ")";
	Utils::insertRecord(path, Const::SERVICE_ERROR_MESS, Const::OPERATION_SUCCESSFULLY, QUERY);
}

void Student::editAnExistingStudent() {
	cout << "Input the Student ID: ";
	ViewInfo vii;
	string studentUsername; getline(cin, studentUsername);
	string corPassword, editTableName, path;
	
	do {
		sqlite3 *db;
		path = Const::studentDatabaseDirectory + studentUsername.substr(0, 2) + "/" + studentUsername.substr(0, 2) + Const::EXT;

		int message;
		message = sqlite3_open(path.c_str(), &db);
		if (message) {
			cout << Const::USER_NOT_FOUND_MESS << endl;
			return;
		}

		editTableName = Utils::getStringStep(Const::sLDatabaseDirectory + Const::classCode, Const::USER_NOT_FOUND_MESS, "brief", "class_code", "code", studentUsername.substr(2, 2));
		if (editTableName == "NULL") {
			cout << Const::USER_NOT_FOUND_MESS << endl;
			return;
		}
		corPassword = Utils::getStringStep(path, Const::USER_NOT_FOUND_MESS, "pass", editTableName, "username", studentUsername);

		if (corPassword != "NULL") {
			cout << Const::USER_FOUND_SUCCESSFULLY << endl;
			sqlite3_close(db);
			break;
		}
		else {
			cout << Const::USER_NOT_FOUND_MESS << endl;
		}
		sqlite3_close(db);
		cout << "Retype the Student ID: "; getline(cin, studentUsername);
	} while (corPassword == "NULL");
	cout << "You can start editing the student's info" << endl;

	//UPDATE exercises SET times_answered = times_answered + 1, av_answeringTime = av_answeringTime + ( (av_answeringTime / (times_answered) ) + ?) * (times_answered + 1) WHERE name = ?
	string QUERY = "UPDATE " + editTableName + " SET ";
	vii.getHeaderInfo(Const::studentDatabaseDirectory + Const::header);

	string *oldInformation = new string[vii.totalColumn+1];
	Utils::viewAllRecordStepOld(path, Const::USER_NOT_FOUND_MESS,"*",editTableName,"username", studentUsername,oldInformation);

	cout << "Hit the Enter button to skip the info that you want to keep unchanged" << endl;

	for (int i = 0; i <= vii.totalColumn; ++i) {
		//cout << vii.headerCode[i] << ": " << oldInformation[i] << endl;
		cout << vii.header[i] << endl;
		cout << "Current: " << oldInformation[i] << endl;
		string change;
		cout << "Change into: "; getline(cin, change);

		if (vii.headerCode[i] == "classname"&&change != "") {
			if (getClass(oldInformation[i]) == getClass(change)) {
				QUERY += vii.headerCode[i] + " = '" + change + "',";
				continue;
			}
			string interchangableCode1 = Utils::getStringStep(Const::sLDatabaseDirectory + Const::classCode, Const::SERVICE_ERROR_MESS, "cha", Const::classCodeTablename, "brief", "'"+getClass(oldInformation[i])+ "'");
			string interchangableCode2 = Utils::getStringStep(Const::sLDatabaseDirectory + Const::classCode, Const::SERVICE_ERROR_MESS, "cha", "class_code", "brief", "'"+getClass(change)+"'");
			if (interchangableCode1 != interchangableCode2) {
				--i;
				cout << "Changed infomation violates rules! Not saved" << endl;
				continue;
			}
			else {
				changeStudentFromClassAtoClassB(path, editTableName, studentUsername, change, oldInformation[i]);
				return;
			}
		}
		else if (change != "") {
			QUERY += vii.headerCode[i] + " = '" + change + "',";
		}
	}
	if (QUERY[QUERY.length()-1] == ',') {
		QUERY.pop_back();
		QUERY += " WHERE username = " + studentUsername;

		Utils::insertRecord(path, Const::SERVICE_ERROR_MESS, Const::OPERATION_SUCCESSFULLY, QUERY);	
	}
	else {
		cout << "No changes have been made" << endl;
	}
}

void Student::addANewStudentToAClass() {
	cout << "Which class to add the student? ";
	string classname; getline(cin, classname);
	ViewInfo vi;
	string path = Const::studentDatabaseDirectory + classname.substr(0, 2) + "/" + classname.substr(0, 2) + Const::EXT;
	
	string insertTableName;
	if (classname[classname.length() - 1] >= '1'&&classname[classname.length() - 1] <= '9') {
		insertTableName = classname.substr(2, classname.length() - 3);
	}
	else {
		insertTableName = classname.substr(2, classname.length() - 2);
	}

	vi.getHeaderInfo(Const::studentDatabaseDirectory + Const::header);

	//INSERT INTO tablename (field1, field2, field3) VALUES (value1, value2, value3);
	
	string QUERY = "INSERT INTO " + insertTableName + " (";
	for (int i = 0; i <= vi.totalColumn; ++i) {
		if(i==vi.totalColumn)	QUERY += vi.headerCode[i] + ") ";
		else QUERY += vi.headerCode[i] + ", ";
	}

	QUERY += "VALUES (";
	string get;
	for (int i = 0; i <= vi.totalColumn; ++i) {
		if (vi.headerCode[i] != "pass") {
			if (vi.headerCode[i] == "classname")QUERY += "'"+classname+"'" + ", ";
			else {
				cout << vi.header[i]<<": ";
				getline(cin, get);
				if (i == vi.totalColumn)	QUERY += "'"+get+"'" + ") ";
				else QUERY += "'"+get+"'" + ", ";
			}
		} else QUERY += "'1', ";
	}
	//string QUERY = "INSERT INTO " + insertTableName + " (username) VALUES ('1751035')";
	//cout << QUERY << endl;
	Utils::insertRecord(path, Const::SERVICE_ERROR_MESS, Const::OPERATION_SUCCESSFULLY, QUERY);
}

void Student::importStudentsFromAClass() {
	string path;
	string tableName;
	string subClass;
	cout << "What class do you want to import? ";
	string classname; getline(cin, classname);

	path = Const::studentDatabaseDirectory + classname.substr(0, 2) + "/" + classname.substr(0, 2) + Const::EXT;

	if (classname[classname.length() - 1] >= '1'&&classname[classname.length() - 1] <= '9') {
		tableName = classname.substr(2, classname.length() - 3);
		subClass = classname.substr(classname.length() - 2, 1);
	}
	else {
		tableName = classname.substr(2, classname.length() - 2);
		subClass = "0";
	}
}