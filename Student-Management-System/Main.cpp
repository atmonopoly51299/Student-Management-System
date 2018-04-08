#include"Login.h"
#include"ViewInfo.h"
#include"Student.h"
#include"ClassActivity.h"
int main() {
	//Welcome, login.
	cout << "WELCOME" << endl;
	cout << "LOGIN:" << endl;

	//EX01
	Login login;
	login.login();

	//Ex04
	//After login successfully, user info are accessible in Login.h file by get...() method
	cout << endl<<"CHANGE PASSWORD:" << endl;
	login.changePasswordRuntime();

	//Ex03
	ViewInfo vi;
	//Const::studentDatabaseDirectory or Const::sLDatabaseDirectory depends on person type
	cout << endl << "VIEW INFO:" << endl;
	if(login.getType()==0)vi.viewInfo(login.getPath(), Const::studentDatabaseDirectory + Const::header, login.getTablename(), login.getUsername());
	else vi.viewInfo(login.getPath(), Const::sLDatabaseDirectory + Const::header, login.getTablename(), login.getUsername());

	//Ex06: Import student from csv file: I don't do this because we use SQLite and there is no need to import into array or linked list
	//      just operate directly with the database file


	Student student;

	//Ex07
	cout << endl<<"ADD NEW STUDENT TO A CLASS: " << endl;
	student.addANewStudentToAClass();

	//Ex08, Ex09, Ex10
	cout << endl << "EDIT A STUDENT:" << endl;
	student.editAnExistingStudent();


	ClassActivity classActivity;

	//Ex11:
	cout << endl << "ADD A NEW EMPTY CLASS:" << endl;
	classActivity.addNewEmptyClass();

	//EX12: no filter options available, just show full list of all classes
	cout << endl << "VIEW LIST OF ALL CLASSES:" << endl;
	classActivity.viewListOfClass();

	//Ex13: no filter options available, just show full list of valid student
	cout << endl << "VIEW ALL STUDENTS OF A CLASS:" << endl;
	classActivity.viewAllStudentsOfClass();
	return 0;
}