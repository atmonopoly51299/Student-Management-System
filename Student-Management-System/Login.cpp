#include"Login.h"


void Login::changePasswordRuntime() {
	cout << "Your current password: ";
	string dumbPass; getline(cin, dumbPass);

	while (dumbPass != getPassword()) {
		cout << Const::WRONG_PASSWORD_MESS << endl;
		cout << "Retype current password: ";
		getline(cin, dumbPass);
	}
	changePasswordInit();
}

void Login::changePasswordInit() {
	cout << Const::PASSWORD_POLICY << endl;
	cout << "New Password: ";
	getline(cin, password);
	while ((int)password.length() < Const::PASSWORD_MIN_CHAR) {
		cout << Const::PASSWORD_VIOLATED_ELERT << endl << "Retype new password: ";
		getline(cin, password);
	}
	Utils::writeRecord(getPath(), Const::SERVICE_ERROR_MESS, Const::PASSWORD_CHANGED_SUCCESSFULLY, "pass", getPassword(), getTablename(), "username", getUsername());
}

int Login::foundUser() {

	//initial checking:
	if ((int)getUsername().length() < Const::USERNAME_MIN_CHAR) {
		cout << Const::USER_NOT_FOUND_MESS << endl;
		return -1;
	}

	int message;
	string corPassword;

	string type = getUsername().substr(0, 1);
	if (type[0] >= '1'&&type[0] <= '9') {
		sqlite3 *db;
		personType = 0;
		path = Const::studentDatabaseDirectory + getUsername().substr(0, 2) + "/" + getUsername().substr(0, 2) + Const::EXT;

		message = sqlite3_open(path.c_str(), &db);
		if (message) {
			cout << Const::USER_NOT_FOUND_MESS << endl;
			return -1;
		}

		tableName = Utils::getStringStep(Const::sLDatabaseDirectory + Const::classCode, Const::USER_NOT_FOUND_MESS, "brief", "class_code", "code", getUsername().substr(2, 2));
		if (tableName == "NULL") {
			cout << Const::USER_NOT_FOUND_MESS << endl;
			return -1;
		}

		sqlite3_close(db);
	}
	else if (type[0] >= 'a'&&type[0] <= 'z') {
		sqlite3 *db;
		personType = 1;
		path = Const::sLDatabaseDirectory + Const::sLInfo;

		message = sqlite3_open(path.c_str(), &db);
		if (message) {
			cout << Const::USER_NOT_FOUND_MESS << endl;
			return -1;
		}
		tableName = Const::sLInfoTablename;
		sqlite3_close(db);
	}

	//get password (for comfirmation if user want to change password);

	corPassword = Utils::getStringStep(path, Const::USER_NOT_FOUND_MESS, "pass", tableName, "username", "'"+username+ "'");

	if (corPassword == "NULL") {
		cout << Const::USER_NOT_FOUND_MESS << endl;
		return -1;
	} else if (corPassword != password) {
		cout << Const::WRONG_PASSWORD_MESS << endl;
		return -1;
	} 

	if (personType == 1) {
		string t = Utils::getStringStep(path, Const::SERVICE_ERROR_MESS, "type", tableName, "username", "'" + username + "'");
		personType = t[0] - 48;
		cout << personType << endl;
	}

	cout << Const::LOGIN_SUCCESSFULLY << endl;
	return personType;
}

void Login::login() {
	do {
		cout << "Username: ";
		getline(cin, username);

		cout << "Password: ";
		getline(cin, password);

		if (getUsername()[0] != ' '&&getPassword()[0] != ' '&&foundUser()>-1)break;
	} while (1);

	if (password.length() == 1 && password[0] == Const::DEFAULT_PASSWORD[0]) {
		cout << "Please change your password" << endl;
		changePasswordInit();
	}
}
int Login::getSTT() {
	return stt;
}
string Login::getUsername() {
	return username;
}
string Login::getPassword() {
	return password;
}
int Login::getType() {
	return personType;
}
string Login::getPath() {
	return path;
}
string Login::getTablename() {
	return tableName;
}