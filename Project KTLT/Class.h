#include"Header.h"

void readAccountFile(const char* path, vector<User> &user)
{
	ifstream fin(path, ios::in);
	user.clear();
	User tempUser;

	string temp;
	getline(fin, temp);
	int pos;
	while (!fin.eof())
	{
		getline(fin, temp);
		pos = temp.find(" ");
		tempUser.ID = temp.substr(0, pos);
		temp.erase(0, pos + 1);

		pos = temp.find(" ");
		tempUser.password = temp.substr(0, pos);
		temp.erase(0, pos + 1);

		if (temp == "0")
			tempUser.type = student;
		else if (temp == "1")
			tempUser.type = lecturer;
		else if (temp == "2")
			tempUser.type = staff;
		user.push_back(tempUser);
	}
	fin.close();
}
int importStudent(const char* path, vector<Class> &myClass, string className)
{
	ifstream fin(path, ios::in);
	if (!fin)
	{
		gotoXY(50, 4);
		cout << "File not found!";
		return 0;
	}
	string temp = string(path);
	temp = temp.substr(0, temp.find('-'));
	getline(fin, temp);
	int pos;
	Student student;
	vector<Student> studentArray;
	Class classTemp;
	classTemp.name = className;
	while (!fin.eof())
	{
		getline(fin, temp);

		//get No
		pos = temp.find(',');
		student.No = stoi(temp.substr(0, pos));
		temp.erase(0, pos + 1);

		//get ID
		pos = temp.find(',');
		student.ID = stoi(temp.substr(0, pos));
		temp.erase(0, pos + 1);

		//get last name
		pos = temp.find(',');
		student.lastName = temp.substr(0, pos);
		temp.erase(0, pos + 1);

		//get first name
		pos = temp.find(',');
		student.firstName = temp.substr(0, pos);
		temp.erase(0, pos + 1);

		//get gender
		pos = temp.find(',');
		string _gender = temp.substr(0, pos);
		student.gender = _gender == "Male" ? Male : Female;
		temp.erase(0, pos + 1);

		//get dob
		pos = temp.find('-');
		student.doB.year = stoi(temp.substr(0, pos));
		temp.erase(0, pos + 1);
		pos = temp.find('-');
		student.doB.month = stoi(temp.substr(0, pos));
		temp.erase(0, pos + 1);
		pos = temp.find('-');
		student.doB.day = stoi(temp.substr(0, pos));


		classTemp.stu.push_back(student);
		//myClass[posClass].stu.push_back(student);
	}
	myClass.push_back(classTemp);
	fin.close();
	return 1;
}
void saveStudentFile(const char* path, vector<Class> &myClass, int posClass)
{
	ofstream fout;
	fout.open(path, ios::out);
	for (int i = 0; i < myClass[posClass].stu.size(); i++)
	{
		fout << myClass[posClass].stu[i].No << "," << myClass[posClass].stu[i].ID << "," << myClass[posClass].stu[i].lastName << "," << myClass[posClass].stu[i].firstName << ",";
		if (myClass[posClass].stu[i].gender == 0)
			fout << "Male" << ",";
		else
			fout << "Female" << ",";
		fout << myClass[posClass].stu[i].doB.year << "-" << myClass[posClass].stu[i].doB.month << "-" << myClass[posClass].stu[i].doB.day << endl;
	}
	fout.close();
}

int importCourse(const char* path, vector<Class> &myClass, int posClass)
{
	ifstream fin;
	fin.open(path, ios::in);

	if (!fin)
	{
		cout << "file not found";
		return 0;
	}
	string temp;
	getline(fin, temp);
	int pos;
	Course m_course;
	while (!fin.eof())
	{
		getline(fin, temp);

		// get No
		pos = temp.find(',');
		m_course.No = stoi(temp.substr(0, pos));
		temp.erase(0, pos + 1);

		// get course ID
		pos = temp.find(',');
		m_course.CourseID = temp.substr(0, pos);
		temp.erase(0, pos + 1);

		// get Course Name
		pos = temp.find(',');
		m_course.CourseName = temp.substr(0, pos);
		temp.erase(0, pos + 1);

		// get Class
		pos = temp.find(',');
		m_course.Class = temp.substr(0, pos);
		temp.erase(0, pos + 1);

		// get LetureAcount
		pos = temp.find(',');
		m_course.LecturerAccount = temp.substr(0, pos);
		temp.erase(0, pos + 1);

		// get start Date
		pos = temp.find('-');
		m_course.StartDate.year = stoi(temp.substr(0, pos));
		temp.erase(0, pos + 1);
		pos = temp.find('-');
		m_course.StartDate.month = stoi(temp.substr(0, pos));
		temp.erase(0, pos + 1);
		pos = temp.find(',');
		m_course.StartDate.day = stoi(temp.substr(0, pos));
		temp.erase(0, pos + 1);

		// get end Date
		pos = temp.find('-');
		m_course.EndDate.year = stoi(temp.substr(0, pos));
		temp.erase(0, pos + 1);
		pos = temp.find('-');
		m_course.EndDate.month = stoi(temp.substr(0, pos));
		temp.erase(0, pos + 1);
		pos = temp.find(',');
		m_course.EndDate.day = stoi(temp.substr(0, pos));
		temp.erase(0, pos + 1);

		// get Date of Week
		pos = temp.find(',');
		m_course.DoW = temp.substr(0, pos);
		temp.erase(0, pos + 1);

		// get Start Hour
		pos = temp.find(':');
		m_course.startHour.hour = stoi(temp.substr(0, pos));
		temp.erase(0, pos + 1);
		pos = temp.find(',');
		m_course.startHour.minute = stoi(temp.substr(0, pos));
		temp.erase(0, pos + 1);


		// get End Hour
		pos = temp.find(':');
		m_course.endHour.hour = stoi(temp.substr(0, pos));
		temp.erase(0, pos + 1);
		pos = temp.find(',');
		m_course.endHour.minute = stoi(temp.substr(0, pos));
		temp.erase(0, pos + 1);


		// get Room
		m_course.Room = temp;
		// Push courses
		myClass[posClass].cou.push_back(m_course);

	}
	fin.close();
	return 1;
}
void saveCourse(const char* path, vector<Class> myClass, int posClass)
{
	ofstream fout;
	fout.open(path, ios::out);
	if (!fout)
	{
		cout << "file not found";
		return;
	}
	fout << "No,Course ID,Course Name,Class,LectureAccount,StartDate,EndDate,Day of week,Start hour,End hour,Room" << endl;
	for (int i = 0; i < myClass[posClass].cou.size(); i++)
	{
		fout << myClass[posClass].cou[i].No << "," << myClass[posClass].cou[i].CourseID << "," << myClass[posClass].cou[i].CourseName << "," << myClass[posClass].cou[i].Class << "," << myClass[posClass].cou[i].LecturerAccount << ",";
		fout << myClass[posClass].cou[i].StartDate.year << "-" << myClass[posClass].cou[i].StartDate.month << "-" << myClass[posClass].cou[i].StartDate.day << ",";
		fout << myClass[posClass].cou[i].EndDate.year << "-" << myClass[posClass].cou[i].EndDate.month << "-" << myClass[posClass].cou[i].EndDate.day << ",";
		fout << myClass[posClass].cou[i].DoW << ",";
		fout << myClass[posClass].cou[i].startHour.hour << ":" << myClass[posClass].cou[i].startHour.minute << "," << myClass[posClass].cou[i].endHour.hour << ":" << myClass[posClass].cou[i].endHour.minute << ",";
		fout << myClass[posClass].cou[i].Room << endl;
	}
	fout.close();
}


void createStudentUser(vector<Class> myClass, int posClass, vector<User> &user)
{
	User temp;
	for (int i = 0; i < myClass[posClass].stu.size(); i++)
	{
		temp.ID = to_string(myClass[posClass].stu[i].ID);
		temp.password = to_string(myClass[posClass].stu[i].doB.day) + to_string(myClass[posClass].stu[i].doB.month) + to_string(myClass[posClass].stu[i].doB.year);
		temp.type = student;
		user.push_back(temp);
	}

}

void createLecturerUser(vector<Class> myClass, int posClass, vector<User> &user)
{
	User temp;
	for (int i = 0; i < myClass[posClass].cou.size(); i++)
	{
		temp.ID = myClass[posClass].cou[i].LecturerAccount;
		temp.password = "admin123";
		temp.type = lecturer;
		user.push_back(temp);
	}
}

void createStaff(vector<User> &user)
{
	User temp;
	temp.ID = "Staff";
	temp.password = "staff";
	temp.type = staff;
	user.push_back(temp);
}
void saveStudentAccount(const char* path, vector<User> user)
{
	ofstream fout(path, ios::out);

	fout << "ID Password Mode" << endl;
	for (int i = 0; i < user.size(); i++)
	{
		fout << user[i].ID << " " << user[i].password << " " << user[i].type << endl;
	}
	fout.close();
}

void viewProfileStudent(User user, vector<Class> myClass, int posClass)
{
	system("cls");
	TextColor(11);
	cout << "\t\t\t\t\t Student Management System";
	TextColor(15);

	for (int i = 0; i < myClass[posClass].stu.size(); i++)
	{
		if (stoi(user.ID) == myClass[posClass].stu[i].ID)
		{
			gotoXY(40, 3);
			cout << "User: " << myClass[posClass].stu[i].ID;
			gotoXY(40, 4);
			cout << "PassWord: " << user.password;
			gotoXY(40, 5);
			cout << "Full name: " << myClass[posClass].stu[i].lastName << " " << myClass[posClass].stu[i].firstName;
			gotoXY(40, 6);
			cout << "DoB: " << myClass[posClass].stu[i].doB.day << "-" << myClass[posClass].stu[i].doB.month << "-" << myClass[posClass].stu[i].doB.year;
			if (myClass[posClass].stu[i].gender == 0)
			{
				gotoXY(40, 7);
				cout << "Gender: Male" << endl;
			}
			else
			{
				gotoXY(40, 7);
				cout << "Gender: Female" << endl;
			}
		}
	}
}
void viewProfileLecturer(User user, vector<Class> myClass, int posClass)
{
	system("cls");
	TextColor(11);
	cout << "\t\t\t\t\t Student Management System";
	TextColor(15);

	gotoXY(40, 3);
	cout << "User: " << user.ID;
	gotoXY(40, 4);
	cout << "PassWord: " << user.password;
}


void changePass(vector<User> &user, User &userLogin)
{
	Nocursortype(1);
startChange:
	erase(3);
	int i = 0;
	string new_password, confirm;
	char key, temp;



	// new pass
	gotoXY(40, 2);
	cout << "You must change password in the first login" << endl;
	gotoXY(50, 3);
	cout << "New password: ";
	gotoXY(65, 3);

	key = _getch();
	while (key != 13) // enter
	{
		if (key == 8) // backspace
		{
			new_password.pop_back();
			gotoXY(65 + --i, 3);
			cout << " ";
			gotoXY(65 + i, 3); // make mouse same on console
			cout << "";
		}
		else
		{
			gotoXY(65 + i++, 3);
			cout << "*";
			new_password.push_back(key);

		}
		key = _getch();
	}


	//confirm

	gotoXY(50, 4);
	cout << "Confirm: ";

	gotoXY(65, 4);
	i = 0;
	key = _getch();
	while (key != 13) // enter
	{
		if (key == 8) // backspace
		{
			confirm.pop_back();
			gotoXY(65 + --i, 4);
			cout << " ";
			gotoXY(65 + i, 4); // make mouse same on console
			cout << "";
		}
		else
		{
			gotoXY(65 + i++, 4);
			cout << "*";
			confirm.push_back(key);

		}
		key = _getch();
	}

	//new key;
	key = 0;
	User tempUser;
	int j;
	for (j = 0; j < user.size(); j++)
	{
		if (user[j].ID == userLogin.ID)
		{
			tempUser = user[j];
			break;
		}
	}

	int count = 0;

	Nocursortype(0);
	if (new_password.compare(confirm) == 0) // check new pass = confirm ?
	{
		if (new_password.compare(tempUser.password) != 0) // check new pass = old pass ?
		{
			tempUser.password = new_password;
		}
		else
		{
			gotoXY(45, 6);
			cout << "The old password is not the same password";
			goto startChange;
		}
		gotoXY(45, 6);
		cout << "          Successfull                ";
		//gotoXY(63 + i, 6);
	}
	else
	{
		gotoXY(45, 6);
		cout << " Confirm password does not match           ";
		gotoXY(78, 6);
		goto startChange;
	}
	key = _getch();

	user[j] = tempUser;
	userLogin = tempUser;

	saveStudentAccount("Account.txt", user);
}


void removeStudent(User user, vector<Class> &myClass, int posClass, vector<User> &userArr)
{
	for (int i = 0; i < myClass[posClass].stu.size(); i++)
	{
		if (stoi(user.ID) == myClass[posClass].stu[i].ID)
		{
			myClass[posClass].stu.erase(myClass[posClass].stu.begin() + i);
		}
	}

	for (int i = 0; i < userArr.size(); i++)
	{
		if (user.ID == userArr[i].ID)
			userArr.erase(userArr.begin() + i);
	}

	for (int i = 0; i < myClass[posClass].stu.size(); i++)
	{
		myClass[posClass].stu[i].No = i + 1;
	}

	string file = myClass[posClass].name + "-Students.txt";
	saveStudentFile(&file[0], myClass, posClass);
}

void viewListClass(vector<Class> myClass)
{
	for (int i = 0; i < myClass.size(); i++)
	{
		gotoXY(50, 3 + i);
		cout << myClass[i].name;
	}
}
void viewListStudentsInClass(vector<Class> myClass, int posClass)
{
	int j = 3;
	for (int i = 0; i < myClass[posClass].stu.size(); i++)
	{
		gotoXY(40, j++);
		cout << " No: " << myClass[posClass].stu[i].No;
		gotoXY(40, j++);
		cout << "ID: " << myClass[posClass].stu[i].ID;
		gotoXY(40, j++);
		cout << "Full name: " << myClass[posClass].stu[i].lastName << " " << myClass[posClass].stu[i].firstName;
		gotoXY(40, j++);
		cout << "DoB: " << myClass[posClass].stu[i].doB.day << "-" << myClass[posClass].stu[i].doB.month << "-" << myClass[posClass].stu[i].doB.year;
		gotoXY(40, j++);

		cout << "Gender: " << (myClass[posClass].stu[i].gender == 0 ? "Male" : "Female");
	}
}

void addNewStudent(vector<Class> &myClass, Student newStudent, int posClass)
{
	myClass[posClass].stu.push_back(newStudent);
}



void changeStudentFromClassA_to_B(vector<Class> &myClass, int posClass1, int posClass2, string ID, vector<User> &user)
{
	Student temp = myClass[posClass1].stu[findStudent(myClass, stoi(ID), posClass1)];
	removeStudent(findUser(user, ID), myClass, posClass1, user);
	addNewStudent(myClass, temp, posClass2);
}

void editExistStudent(vector<Class> &myClass, int posClass, vector<User> &user, int posStudent)
{
	Student newStudent;
	int gender, k = 5;

	gotoXY(40, k++);
	cout << "ID: ";
	cin >> newStudent.ID;

	gotoXY(40, k++);
	cout << "Last name: ";
	cin.ignore();
	getline(cin, newStudent.lastName);

	gotoXY(40, k++);
	cout << "First name: ";
	cin.ignore();
	getline(cin, newStudent.firstName);

	gotoXY(40, k++);
	cout << "Day of birth: ";
	gotoXY(45, k++);
	cout << "Day: ";
	cin >> newStudent.doB.day;
	gotoXY(45, k++);
	cout << "Month: ";
	cin >> newStudent.doB.month;
	gotoXY(45, k++);
	cout << "Year: ";
	cin >> newStudent.doB.year;

	gotoXY(40, k++);
	cout << "Gender(Male: 1, Female: 2): ";
	cin >> gender;
	if (gender == 1)
		newStudent.gender = Male;
	else
		newStudent.gender = Female;

	myClass[posClass].stu.push_back(newStudent);
	createStudentUser(myClass, posClass, user);
	for (int i = 0; i < myClass[posClass].stu.size(); i++)
	{
		myClass[posClass].stu[i].No = i + 1;
	}
}

void addCourse(vector<Class> &myClass, int posClass)
{
	Course temp;
	int k = 4;
	temp.No = myClass[posClass].cou.size();
	temp.Class = myClass[posClass].name;

	gotoXY(40, k++);
	cout << "Course ID: ";
	cin >> temp.CourseID;

	gotoXY(40, k++);
	cout << "Course name: ";
	cin >> temp.CourseName;

	gotoXY(40, k++);
	cout << "Lecturer Account: ";
	cin >> temp.LecturerAccount;

	gotoXY(40, k++);
	cout << "Start Date";
	gotoXY(45, k++);
	cout << "Day: ";
	cin >> temp.StartDate.day;
	gotoXY(45, k++);
	cout << "Month: ";
	cin >> temp.StartDate.month;
	gotoXY(45, k++);
	cout << "Year: ";
	cin >> temp.StartDate.year;

	gotoXY(40, k++);
	cout << "End Date";
	gotoXY(45, k++);
	cout << "Day: ";
	cin >> temp.EndDate.day;
	gotoXY(45, k++);
	cout << "Month: ";
	cin >> temp.EndDate.month;
	gotoXY(45, k++);
	cout << "Year: ";
	cin >> temp.EndDate.year;

	gotoXY(40, k++);
	cout << "Day of week: ";
	cin >> temp.DoW;

	gotoXY(40, k++);
	cout << "Start hour";
	gotoXY(45, k++);
	cout << "Hour: ";
	cin >> temp.startHour.hour;
	gotoXY(45, k++);
	cout << "Minutes: ";
	cin >> temp.startHour.minute;

	gotoXY(40, k++);
	cout << "End hour";
	gotoXY(45, k++);
	cout << "Hour: ";
	cin >> temp.endHour.hour;
	gotoXY(45, k++);
	cout << "Minutes: ";
	cin >> temp.endHour.minute;

	gotoXY(40, k++);
	cout << "Room: ";
	cin >> temp.Room;

	myClass[posClass].cou.push_back(temp);

	//assignment stu into stu of course to build vector member of that course
	for (int i = 0; i < myClass[posClass].cou.size(); i++)
	{
		myClass[posClass].cou[i].stu = myClass[posClass].stu;
	}
}


void editExistCourse(vector<Class> &myClass, int posClass, int posCourse)
{
	int k = 5;
	Course temp;
	gotoXY(40, k++);
	cout << "Course ID: ";
	cin >> temp.CourseID;

	gotoXY(40, k++);
	cout << "Course name: ";
	cin >> temp.CourseName;

	gotoXY(40, k++);
	cout << "Class: ";
	cin >> temp.Class;

	gotoXY(40, k++);
	cout << "Lecturer Account: ";
	cin >> temp.LecturerAccount;

	gotoXY(40, k++);
	cout << "Start Date";
	gotoXY(45, k++);
	cout << "Day: ";
	cin >> temp.StartDate.day;
	gotoXY(45, k++);
	cout << "Month: ";
	cin >> temp.StartDate.month;
	gotoXY(45, k++);
	cout << "Year: ";
	cin >> temp.StartDate.year;

	gotoXY(40, k++);
	cout << "End Date";
	gotoXY(45, k++);
	cout << "Day: ";
	cin >> temp.EndDate.day;
	gotoXY(45, k++);
	cout << "Month: ";
	cin >> temp.EndDate.month;
	gotoXY(45, k++);
	cout << "Year: ";
	cin >> temp.EndDate.year;

	gotoXY(40, k++);
	cout << "Day of week: ";
	cin >> temp.DoW;

	gotoXY(40, k++);
	cout << "Start hour";
	gotoXY(45, k++);
	cout << "Hour: ";
	cin >> temp.startHour.hour;
	gotoXY(45, k++);
	cout << "Minutes: ";
	cin >> temp.startHour.minute;

	gotoXY(40, k++);
	cout << "End hour";
	gotoXY(45, k++);
	cout << "Hour: ";
	cin >> temp.endHour.hour;
	gotoXY(45, k++);
	cout << "Minutes: ";
	cin >> temp.endHour.minute;

	gotoXY(40, k++);
	cout << "Room: ";
	cin >> temp.Room;

	temp.stu = myClass[posClass].stu;
	for (int i = 0; i < myClass[posClass].cou.size(); i++)
	{
		myClass[posClass].cou[i].No = i + 1;
	}
	myClass[posClass].cou.push_back(temp);
}

void removeCourse(vector<Class> &myClass, int posClass, int posCourse)
{
	myClass[posClass].cou.erase(myClass[posClass].cou.begin() + posCourse);
	for (int i = 0; i < myClass[posClass].cou.size(); i++)
	{
		myClass[posClass].cou[i].No = i + 1;
	}
}

void removeSpecificStudentFromCourse(vector<Class> &myClass, int posClass, int posCourse, string ID)
{
	for (int i = 0; i < myClass[posClass].cou[posCourse].stu.size(); i++)
	{
		if (stoi(ID) == myClass[posClass].cou[posCourse].stu[i].ID)
			myClass[posClass].cou[posCourse].stu.erase(myClass[posClass].cou[posCourse].stu.begin() + i);
	}
}

void addSpecificStudent(vector<Class> &myClass, int posClass, int posCourse, Student stu)
{
	myClass[posClass].cou[posCourse].stu.push_back(stu);
}

void viewStudentOfCourse(vector<Class> myClass, int posClass, int posCourse)
{
	for (int i = 0; i < myClass[posClass].cou[posCourse].stu.size(); i++)
	{
		gotoXY(40, 5 + i);
		cout << myClass[posClass].cou[posCourse].stu[i].ID << "-" << myClass[posClass].cou[posCourse].stu[i].lastName << " " << myClass[posClass].cou[posCourse].stu[i].firstName;
	}
	//cout << 1;

}

// view all lecturer --function 23
void viewAllLecturer(vector<Class> myClass)
{
	int pos = 0;
	for (int i = 0; i < myClass.size(); i++)
	{
		for (int j = 0; j < myClass[i].cou.size(); j++)
		{
			gotoXY(40, 5 + pos);
			cout << myClass[i].cou[j].LecturerAccount;
			pos++;
		}
	}
}

//  check in students-function 35
void checkin(vector<Class> &myClass, int &posClass, int &posCourse, User &userLogin)
{
	time_t now = time(0);
	tm *ltm = localtime(&now);

	for (int i = 0; i < myClass[posClass].cou[posCourse].stu.size(); i++)
	{
		if (stoi(userLogin.ID) == myClass[posClass].cou[posCourse].stu[i].ID)
		{
			if ( ltm->tm_hour >= myClass[posClass].cou[posCourse].startHour.hour && ltm->tm_hour <= myClass[posClass].cou[posCourse].endHour.hour)
			{
				myClass[posClass].cou[posCourse].stu[i].Checkin = true;
				
			}
			else if (ltm->tm_hour == myClass[posClass].cou[posCourse].endHour.hour)
			{
				if ((1 + ltm->tm_min) <= myClass[posClass].cou[posCourse].endHour.minute)
					myClass[posClass].cou[posCourse].stu[i].Checkin = true;

			}
		}
	}
	gotoXY(40, 5);
	cout << "Sucess!";
}

// function 30
void viewAttendance(vector<Class> myClass, int posClass, int posCourse)
{

	for (int i = 0; i < myClass[posClass].cou[posCourse].stu.size(); i++)
	{
		if (myClass[posClass].cou[posCourse].stu[i].Checkin == true)
			cout << myClass[posClass].cou[posCourse].stu[i].lastName << " " << myClass[posClass].cou[posCourse].stu[i].firstName << endl;
	}
}

// function 32
int ImportScoreboard(const char *path, vector<Class> &myClass, int &posClass, int &posCourse)
{
	ifstream fin;
	fin.open(path);

	if (!fin)
	{
		cout << "file not found";
		return 0;
	}
	string temp;
	getline(fin, temp);
	int pos;
	Scoreboard m_Sb;
	while (!fin.eof())
	{
		getline(fin, temp);

		// get No
		pos = temp.find(',');
		m_Sb.No = stoi(temp.substr(0, pos));
		temp.erase(0, pos + 1);

		// get Scoreboard ID
		pos = temp.find(',');
		m_Sb.ID = stoi(temp.substr(0, pos));
		temp.erase(0, pos + 1);

		// get ScoreBoad Mid
		pos = temp.find(',');
		m_Sb.Mid = stoi(temp.substr(0, pos));
		temp.erase(0, pos + 1);

		// get ScoreBoard Final
		pos = temp.find(',');
		m_Sb.Final = stoi(temp.substr(0, pos));
		temp.erase(0, pos + 1);

		// get Lab
		pos = temp.find(',');
		m_Sb.Lab = stoi(temp.substr(0, pos));
		temp.erase(0, pos + 1);


		// get Bonus
		pos = temp.find(',');
		m_Sb.Bonus = stoi(temp.substr(0, pos));
		temp.erase(0, pos + 1);


		// Push courses
		myClass[posClass].cou[posCourse].Sb.push_back(m_Sb);
	}
	fin.close();
	return 1;
}

// function 34 view scoreboard

void viewScoreboard(vector<Class> myClass, int posClass, int posCourse)
{
	for (int i = 0; i < myClass[posClass].cou[posCourse].Sb.size(); i++)
	{
		gotoXY(40, 5 + i);
		cout << myClass[posClass].cou[posCourse].Sb[i].ID << "\t";
		cout << "Mid: " << myClass[posClass].cou[posCourse].Sb[i].Mid << "\t";
		cout << "Final: " << myClass[posClass].cou[posCourse].Sb[i].Final << "\t";
		cout << "Lab: " << myClass[posClass].cou[posCourse].Sb[i].Lab << "\t";
		cout << "Bonus: " << myClass[posClass].cou[posCourse].Sb[i].Bonus << "\n";
	}
}


// function 37 - viewSchedules
void viewSchedules(vector<Class> myClass, int posClass, User &userLogin)
{
	for (int i = 0; i < myClass[posClass].cou.size(); i++)
	{
		gotoXY(40, 5 + i);
		cout << myClass[posClass].cou[i].CourseName << "\t";
		cout << myClass[posClass].cou[i].DoW << "\t";
		cout << myClass[posClass].cou[i].startHour.hour << ":" << myClass[posClass].cou[i].startHour.minute << "-";
		cout << myClass[posClass].cou[i].endHour.hour << ":" << myClass[posClass].cou[i].endHour.minute << "\t";
		cout << myClass[posClass].cou[i].Room;
	}
}