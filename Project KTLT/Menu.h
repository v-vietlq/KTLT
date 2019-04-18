#pragma once
#include"Header.h"
#include"Login.h"

#define UP 72
#define DOWN 80
#define ENTER 13

#define SIZE_LEVEL_ONE 2
#define SIZE_LEVEL_TWO_STAFF 24
#define SIZE_LEVEL_TWO_LECTURER 9
#define SIZE_LEVEL_TWO_STUDENT 6
#define SIZE_OPTIONS 3

string levelOne[2] = { "Login" , "Exit" };

void menuLevelTwo_Staff(vector<User> &user, vector<Class> &myClass, User userLogin);
void menuLevelTwo_Student(vector<User> &user, vector<Class> &myClass, User userLogin);
void menuLevelTwo_Lecturer(vector<User> &user, vector<Class> &myClass, User userLogin);

void menuLevelOne(vector<User> &user, vector<Class> &myClass)
{
	Nocursortype(0);
	TextColor(11);
	cout << "\t\t\t\t\t Student Management System";
	TextColor(15);

	char key;
	int pointer = 0;

	while (1)
	{
		Nocursortype(0);
		//erase login and exit
		erase(3);
		//print color login or exit
		for (int i = 0; i < 2; i++)
		{
			if (pointer == i)
			{
				//Blue bright
				TextColor(11);
				gotoXY(50, 2 + i);
				cout << levelOne[i];
			}
			else
			{
				//white
				TextColor(15);
				gotoXY(50, 2 + i);
				cout << levelOne[i];
			}
		}

		if (1)
		{
			key = _getch();
			if (key == UP)
			{
				if (pointer > 0)
					pointer--;
				else
					pointer = SIZE_LEVEL_ONE - 1;
			}
			else if (key == DOWN)
			{
				if (pointer < SIZE_LEVEL_ONE - 1)
					pointer++;
				else
					pointer = 0;
			}
			else if (key == ENTER)
			{
				if (pointer == 0)
				{
					erase(3);
					User check = login(user);
					if (check.ID != "N/A")
					{
						if (check.type == staff)
							menuLevelTwo_Staff(user, myClass, check);
						else if (check.type == student)
							menuLevelTwo_Student(user, myClass, check);
						else
							menuLevelTwo_Lecturer(user, myClass, check);
					}
				}
				else
					exit(0);
			}
		}
		//Sleep(100);	
	}
}

string levelTwo_Staff[24] = { "Import students of a class", "Add a new student to a class", "Edit an exsiting student", "Remove a student", "Change students from class A to class B","View list of classes", "View list of students in a class",
					 "Create/update/delete/view academic years (2018-2019), and semesters", "Import courses", "Add a new course", "Edit an existing course", "Remove a course", "Remove a specific student from a course", "Add a specific to a course", "View list of course in the current semester", "View list of students of course", "View attendance list of a course", "Create/update/delete/view all lecturers",
					 "Search and view scoreboard of a course", "Export a scoreboard to csv file",
					 "Search and view attendance list of a course", "Export a attendance list to a csv file",
					 "Options", "Logout" };

string levelTwo_Lecturer[9] = { "View list of courses in the current semester", "View list of students of a course", "View attendance list of a course", "Edit an attendance", "Import scoreboard of a course (midterm, final, lab, bonus) from a csv file", "Edit grade of a student", "View a scoreboard", "Options", "Logout" };
string levelTwo_Student[6] = { "Check-in", "View check-in result", "View schedules", "View his/her scores of a course", "Options", "Logout" };
string Options[3] = { "Change Password", "View Profile", "Back" };


void printFunctionOfUser(string listFunc[], int n, int pointer)
{
	for (int i = 0; i < n; i++)
	{
		if (pointer == i)
		{
			//Blue bright
			TextColor(11);
			gotoXY(20, 2 + i);
			cout << listFunc[i];
		}
		else
		{
			//white
			TextColor(15);
			gotoXY(20, 2 + i);
			cout << listFunc[i];
		}
	}
}

typedef void(*UserType)(User user, vector<Class> myClass, int posClass);

void optionsFunc(vector<User> &userArr, User &user, vector<Class> &myClass, int posClass, UserType func)
{
StartOptions:
	cleanAndPrintTitle();

	char key;
	int pointer = 0;
	erase(9);
	while (1)
	{
		Nocursortype(0);
		//erase login and exit

		//print color login or exit
		printFunctionOfUser(Options, SIZE_OPTIONS, pointer);

		if (1)
		{

			key = _getch();
			if (key == UP)
			{
				if (pointer > 0)
					pointer--;
				else
					pointer = SIZE_OPTIONS - 1;
			}
			else if (key == DOWN)
			{
				if (pointer < SIZE_OPTIONS - 1)
					pointer++;
				else
					pointer = 0;
			}
			else if (key == ENTER)
			{
				if (pointer == 0)
				{
					changePass(userArr, user);
					cleanAndPrintTitle();
				}
				else if (pointer == 1)
				{
					func(user, myClass, posClass);

					gotoXY(40, 9);
					cout << "Press Enter to back!";
					char key = _getch();
					if (key == 13)
						goto StartOptions;
				}
				else if (pointer == 2)
				{
					return;
				}
			}
		}
		//Sleep(100);	
	}
}
void menuLevelTwo_Staff(vector<User> &user, vector<Class> &myClass, User userLogin)
{
StartMenuStaff:

	cleanAndPrintTitle();

	char key;
	int pointer = 0;
	erase(SIZE_LEVEL_TWO_STAFF);
	while (1)
	{
		Nocursortype(0);
		//erase login and exit

		//print color login or exit
		printFunctionOfUser(levelTwo_Staff, SIZE_LEVEL_TWO_STAFF, pointer);

		if (1)
		{
			key = _getch();
			if (key == UP)
			{
				if (pointer > 0)
					pointer--;
				else
					pointer = SIZE_LEVEL_TWO_STAFF - 1;
			}
			else if (key == DOWN)
			{
				if (pointer < SIZE_LEVEL_TWO_STAFF - 1)
					pointer++;
				else
					pointer = 0;
			}
			else if (key == ENTER)
			{
				if (pointer == 0)
				{
					cleanAndPrintTitle();
					Nocursortype(1);
					string path;
					gotoXY(50, 3);
					cout << "Path of file students csv: ";
					cin >> path;


					string className = path.substr(0, path.find('-'));


					if (importStudent(&path[0], myClass, className) == 1)
					{
						gotoXY(50, 5);
						cout << "Success!";

						char key = _getch();
						while (key != 13)
						{
							key = _getch();
						}
						int pos = findPosClass(myClass, className);

						path = path.substr(0, path.find('.'));
						path = path + ".txt";
						saveStudentFile(&path[0], myClass, pos);
						createStudentUser(myClass, pos, user);

					}
					else
					{
						_getch();
					}

					system("cls");
					goto StartMenuStaff;
				}
				else if (pointer == 13)
				{
					cleanAndPrintTitle();
					Nocursortype(1);
					string temp;

					gotoXY(40, 3);
					cout << "Class: ";
					cin >> temp;

					int posClass = findPosClass(myClass, temp);

					if (posClass == -1)
					{
						gotoXY(40, 4);
						cout << "Class don't exist!";

						_getch();
						goto StartMenuStaff;
					}

					gotoXY(40, 4);
					cout << "Course ID you want to add specific student: ";
					cin >> temp;
					int posCourse = findCourse(myClass, posClass, temp);

					gotoXY(40, 4);
					cout << "Specific Student ID: ";
					cin >> temp;

					string className;
					gotoXY(40, 5);
					cout << "Class of student: ";
					cin >> className;
					if (posCourse != -1)
					{
						int posClass1 = findPosClass(myClass, className);
						int posStudent = findStudent(myClass, stoi(temp), posClass1);
						Student stu = myClass[posClass1].stu[posStudent];
						addSpecificStudent(myClass, posClass, posCourse, stu);
					}
					else
					{
						gotoXY(40, 6);
						cout << "Course don't exist!";
					}

					_getch();
					goto StartMenuStaff;
				}
				else if (pointer == 14)
				{
					cleanAndPrintTitle();
					for (int i = 0; i < myClass.size(); i++)
					{
						for (int j = 0; j < myClass[i].cou.size(); j++)
						{
							gotoXY(40, 3 + i);
							cout << myClass[i].cou[i].CourseID << ": " << myClass[i].cou[i].CourseName;
						}
					}
					_getch();
					goto StartMenuStaff;
				}
				else if (pointer == 15)
				{
					cleanAndPrintTitle();
					Nocursortype(1);
					string className, course;

					gotoXY(40, 3);
					cout << "Class: ";
					cin >> className;

					int posClass = findPosClass(myClass, className);

					if (posClass == -1)
					{
						gotoXY(40, 4);
						cout << "Class don't exist!";

						_getch();
						goto StartMenuStaff;
					}

					gotoXY(40, 4);
					cout << "Course ID: ";
					cin >> course;
					int posCourse = findCourse(myClass, posClass, course);
					if (posCourse != -1)
					{
						viewStudentOfCourse(myClass, posClass, posCourse);
					}
					else
					{
						gotoXY(40, 5);
						cout << "Course don't exist!";

					}
					_getch();
					goto StartMenuStaff;
				}
				else if (pointer == 11)
				{
					string className, courseID;
					gotoXY(40, 3);
					cout << "Class: ";
					cin >> className;

					int posClass = findPosClass(myClass, className);
					if (posClass == -1)
					{
						gotoXY(40, 4);
						cout << "Class don't exist!";
						_getch();
						goto StartMenuStaff;
					}

					gotoXY(40, 4);
					cout << "Course ID: ";
					cin >> courseID;
					int posCourse = findCourse(myClass, posClass, courseID);
					if (posCourse != -1)
					{
						removeCourse(myClass, posClass, posCourse);

						className += "-Course.txt";
						saveCourse(&className[0], myClass, posClass);
						_getch();
					}
					else
					{
						gotoXY(40, 5);
						cout << "Course don't exist!";
						_getch();
						goto StartMenuStaff;
					}
				}
				else if (pointer == 12)
				{
					cleanAndPrintTitle();
					Nocursortype(1);
					string temp;
					gotoXY(40, 3);
					cout << "Class: ";
					cin >> temp;

					int posClass = findPosClass(myClass, temp);
					if (posClass == -1)
					{
						gotoXY(40, 4);
						cout << "Class dont't exist!";

						_getch();
						goto StartMenuStaff;
					}

					gotoXY(40, 4);
					cout << "Course ID: ";
					cin >> temp;
					int posCourse = findCourse(myClass, posClass, temp);

					gotoXY(40, 4);
					cout << "Student ID: ";
					cin >> temp;

					if (posCourse != -1)
					{
						removeSpecificStudentFromCourse(myClass, posClass, posCourse, temp);
					}
					else
					{

						gotoXY(40, 5);
						cout << "Course don't exist";
					}

					_getch();
					goto StartMenuStaff;
				}
				else if (pointer == 9)
				{
					cleanAndPrintTitle();
					Nocursortype(1);


					string className;
					gotoXY(40, 3);
					cout << "Class name: ";
					cin >> className;

					int posClass = findPosClass(myClass, className);
					if (posClass == -1)
					{
						gotoXY(40, 5);
						cout << "Class don't exist!";
						_getch();
					}
					else
					{
						addCourse(myClass, posClass);
						className += "-Course.txt";
						saveCourse(&className[0], myClass, posClass);
						createLecturerUser(myClass, posClass, user);
						gotoXY(40, 20);
						cout << "Success!";
					}
					Nocursortype(0);
					system("cls");
					goto StartMenuStaff;
				}
				else if (pointer == 10) // 16 edit course
				{
					cleanAndPrintTitle();
					Nocursortype(1);

					string className, course;
					gotoXY(40, 3);
					cout << "Class: ";
					cin >> className;

					int posClass = findPosClass(myClass, className);

					if (posClass == -1)
					{
						gotoXY(40, 4);
						cout << "Class don't exist!";
						_getch();
						Nocursortype(0);
						goto StartMenuStaff;
					}
					gotoXY(40, 4);
					cout << "Course ID: ";
					cin >> course;

					int posCourse = findCourse(myClass, posClass, course);
					if (posCourse != -1)
					{
						className += "-Course.txt";
						myClass[posClass].cou.erase(myClass[posClass].cou.begin() + posCourse);
						editExistCourse(myClass, posClass, posCourse);
						saveCourse(&className[0], myClass, posClass);
						createLecturerUser(myClass, posClass, user);
						gotoXY(40, 20);
						cout << "Success!";
					}
					else
					{
						gotoXY(40, 4);
						cout << "Course don't exist!";
					}
					Nocursortype(0);
					_getch();
					goto StartMenuStaff;
				}
				else if (pointer == 1)
				{
					Nocursortype(1);
					int k = 3, gender, posClass;
					cleanAndPrintTitle();
					Student newStudent;

					string className;
					gotoXY(40, k++);
					cout << "Class: ";
					cin >> className;

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
						newStudent.gender == Male;
					else
						newStudent.gender == Female;

					posClass = findPosClass(myClass, className);
					newStudent.No = myClass[posClass].stu.size();
					addNewStudent(myClass, newStudent, posClass);
					createStudentUser(myClass, posClass, user);

					Nocursortype(0);
					goto StartMenuStaff;
				}
				else if (pointer == 2)
				{
					Nocursortype(1);
					cleanAndPrintTitle();
					string className, ID;
					gotoXY(40, 3);
					cout << "Class: ";
					cin >> className;
					gotoXY(40, 4);
					cout << "ID: ";
					cin >> ID;


					int posClass = findPosClass(myClass, className);
					int posStudent = findStudent(myClass, stoi(ID), posClass);
					if (posStudent == -1)
					{
						gotoXY(40, 6);
						cout << "Student don't exist!";
						_getch();
						Nocursortype(0);
						goto StartMenuStaff;
					}
					myClass[posClass].stu.erase(myClass[posClass].stu.begin() + posStudent);
					editExistStudent(myClass, posClass, user, posStudent);
					_getch();
					Nocursortype(0);
					goto StartMenuStaff;
				}
				else if (pointer == 3)
				{
					Nocursortype(1);
					cleanAndPrintTitle();

					gotoXY(40, 3);
					string className;
					cout << "Name of class you want to delete student: ";
					cin >> className;
					int posClass = findPosClass(myClass, className);

					if (posClass != -1)
					{
						gotoXY(40, 4);
						string ID;
						cout << "ID of students you want to remove: ";
						cin >> ID;
						gotoXY(0, 0);

						int posStudent;
						for (int i = 0; i < user.size(); i++)
						{
							if (user[i].ID == ID)
								posStudent = i;
						}

						removeStudent(user[posStudent], myClass, posClass, user);
					}
					else
					{
						cout << "Class don't exist!" << endl;
					}

					Nocursortype(0);
					goto StartMenuStaff;
				}
				else if (pointer == 4)
				{
					Nocursortype(1);
					cleanAndPrintTitle();
					string classA, classB, ID;

					gotoXY(40, 3);
					cout << "Class A: ";
					cin >> classA;
					gotoXY(40, 4);
					cout << "Class B: ";
					cin >> classB;
					gotoXY(40, 5);
					cout << "ID: ";
					cin >> ID;

					int posClass1 = findPosClass(myClass, classA);
					int posClass2 = findPosClass(myClass, classB);

					if (posClass1 == -1 || posClass2 == -1)
					{
						cout << "Students don't exist!" << endl;
						system("cls");
						Nocursortype(0);
					}
					changeStudentFromClassA_to_B(myClass, posClass1, posClass2, ID, user);
					_getch();

					system("cls");
					Nocursortype(0);
					goto StartMenuStaff;
				}
				else if (pointer == 5)
				{
					cleanAndPrintTitle();
					viewListClass(myClass);
					_getch();
					goto StartMenuStaff;
				}
				else if (pointer == 6)
				{
					cleanAndPrintTitle();
					gotoXY(40, 2);
					cout << "Class: ";
					string className;
					cin >> className;

					int pos = findPosClass(myClass, className);
					if (pos != -1)
					{
						viewListStudentsInClass(myClass, pos);

					}
					else
					{
						gotoXY(40, 3);
						cout << "Class don't exist!";

					}
					_getch();
					system("cls");
					goto StartMenuStaff;
				}
				else if (pointer == 7)
				{


				}
				else if (pointer == 8)
				{
					cleanAndPrintTitle();
					Nocursortype(1);
					string path;
					gotoXY(50, 3);
					cout << "Path of file course csv: ";
					cin >> path;


					string className = path.substr(0, path.find('-'));

					int pos = findPosClass(myClass, className);
					if (importCourse(&path[0], myClass, pos))
					{
						gotoXY(50, 5);
						cout << "Success!";

						char key = _getch();
						while (key != 13)
						{
							key = _getch();
						}
						path = path.substr(0, path.find('.'));
						path = path + ".txt";
						saveCourse(&path[0], myClass, pos);
						createLecturerUser(myClass, pos, user);
						for (int i = 0; i < myClass[pos].cou.size(); i++)
						{
							myClass[pos].cou[i].stu = myClass[pos].stu;
						}
					}
					else
					{
						_getch();
					}

					system("cls");
					goto StartMenuStaff;
				}
				else if (pointer == 22)
				{
					optionsFunc(user, userLogin, myClass, 0, viewProfileLecturer);
					goto StartMenuStaff;
				}
				else if (pointer == 17)
				{
					cleanAndPrintTitle();
					Nocursortype(1);
					gotoXY(50, 3);
					viewAllLecturer(myClass);
					_getch();
					goto StartMenuStaff;
				}
				else if (pointer == 23)
				{
					system("cls");
					menuLevelOne(user, myClass);
				}
				else if (pointer == 16)
				{
					cleanAndPrintTitle();
					Nocursortype(1);
					string className, course;

					gotoXY(40, 3);
					cout << "Class: ";
					cin >> className;

					int posClass = findPosClass(myClass, className);

					if (posClass == -1)
					{
						gotoXY(40, 4);
						cout << "Class don't exist!";

						_getch();
						goto StartMenuStaff;
					}

					gotoXY(40, 4);
					cout << "Course ID: ";
					cin >> course;
					int posCourse = findCourse(myClass, posClass, course);
					if (posCourse != -1)
					{
						viewAttendance(myClass, posClass, posCourse);
					}
					else
					{
						gotoXY(40, 5);
						cout << "Course don't exist!";

					}
					_getch();
					goto StartMenuStaff;
				}

			}
		}
		//Sleep(100);	
	}
}

void menuLevelTwo_Student(vector<User> &user, vector<Class> &myClass, User userLogin)
{
StartMenuStudent:
	char key;
	int pointer = 0;
	erase(SIZE_LEVEL_TWO_STAFF);
	while (1)
	{
		Nocursortype(0);
		//erase login and exit

		//print color login or exit
		printFunctionOfUser(levelTwo_Student, SIZE_LEVEL_TWO_STUDENT, pointer);

		if (1)
		{

			key = _getch();
			if (key == UP)
			{
				if (pointer > 0)
					pointer--;
				else
					pointer = SIZE_LEVEL_TWO_STUDENT - 1;
			}
			else if (key == DOWN)
			{
				if (pointer < SIZE_LEVEL_TWO_STUDENT - 1)
					pointer++;
				else
					pointer = 0;
			}
			else if (key == ENTER)
			{
				if (pointer == 0)
				{
					cleanAndPrintTitle();
					Nocursortype(1);
					string className, course;

					gotoXY(40, 3);
					cout << "Class: ";
					cin >> className;

					int posClass = findPosClass(myClass, className);

					if (posClass == -1)
					{
						gotoXY(40, 4);
						cout << "Class don't exist!";

						_getch();
						goto StartMenuStudent;
					}

					gotoXY(40, 4);
					cout << "Course ID: ";
					cin >> course;
					int posCourse = findCourse(myClass, posClass, course);
					if (posCourse != -1)
					{
						checkin(myClass, posClass, posCourse, userLogin);
					}
					else
					{
						gotoXY(40, 5);
						cout << "Course don't exist!";

					}
					_getch();
					goto StartMenuStudent;

				}
				else if (pointer == 2)
				{
					cleanAndPrintTitle();
					Nocursortype(1);
					string className, course;

					gotoXY(40, 3);
					cout << "Class: ";
					cin >> className;

					int posClass = findPosClass(myClass, className);

					if (posClass == -1)
					{
						gotoXY(40, 4);
						cout << "Class don't exist!";

						_getch();
						goto StartMenuStudent;
					}
					else
					{
						viewSchedules(myClass, posClass, userLogin);
					}
					_getch();
					system("cls");
					goto StartMenuStudent;
				}
				else if (pointer == 4)
				{

					optionsFunc(user, userLogin, myClass, findPosClass(myClass, userLogin.className), viewProfileStudent);
					goto StartMenuStudent;
				}
				else if (pointer == 5)
				{
					system("cls");
					menuLevelOne(user, myClass);
				}
			}
		}
		//Sleep(100);	
	}
}

void menuLevelTwo_Lecturer(vector<User> &user, vector<Class> &myClass, User userLogin)
{
StartMenuLecturer:
	char key;
	int pointer = 0;
	erase(SIZE_LEVEL_TWO_LECTURER);
	while (1)
	{
		Nocursortype(0);
		//erase login and exit

		//print color login or exit
		printFunctionOfUser(levelTwo_Lecturer, SIZE_LEVEL_TWO_LECTURER, pointer);

		if (1)
		{

			key = _getch();
			if (key == UP)
			{
				if (pointer > 0)
					pointer--;
				else
					pointer = SIZE_LEVEL_TWO_LECTURER - 1;
			}
			else if (key == DOWN)
			{
				if (pointer < SIZE_LEVEL_TWO_LECTURER - 1)
					pointer++;
				else
					pointer = 0;
			}
			else if (key == ENTER)
			{
				if (pointer == 0)
				{
					//func				

				}
				else if (pointer == 1)
				{
					//func..
				}
				else if (pointer == 7)
				{
					optionsFunc(user, userLogin, myClass, 0, viewProfileLecturer);
					goto StartMenuLecturer;
				}
				else if (pointer == 8)
				{
					system("cls");
					menuLevelOne(user, myClass);
				}
				else if (pointer == 4)
				{
					cleanAndPrintTitle();
					Nocursortype(1);
					string className, course;

					gotoXY(40, 3);
					cout << "Class: ";
					cin >> className;

					int posClass = findPosClass(myClass, className);

					if (posClass == -1)
					{
						gotoXY(40, 4);
						cout << "Class don't exist!";

						_getch();
						goto StartMenuLecturer;
					}

					gotoXY(40, 4);
					cout << "Course ID: ";
					cin >> course;
					int posCourse = findCourse(myClass, posClass, course);
					if (posCourse != -1)
					{
						string path;
						gotoXY(40, 5);
						cout << "ScoreBoard path: ";
						cin >> path;
						if (ImportScoreboard(&path[0], myClass, posClass, posCourse) == 1)
						{
							gotoXY(50, 6);
							cout << "Success!";
						}
					}
					else
					{
						gotoXY(40, 5);
						cout << "Course don't exist!";

					}
					_getch();
					system("cls");
					goto StartMenuLecturer;
				}
				else if (pointer == 6)
				{
					cleanAndPrintTitle();
					Nocursortype(1);
					string className, course;

					gotoXY(40, 3);
					cout << "Class: ";
					cin >> className;

					int posClass = findPosClass(myClass, className);

					if (posClass == -1)
					{
						gotoXY(40, 4);
						cout << "Class don't exist!";

						_getch();
						goto StartMenuLecturer;
					}

					gotoXY(40, 4);
					cout << "Course ID: ";
					cin >> course;
					int posCourse = findCourse(myClass, posClass, course);
					if (posCourse != -1)
					{
						viewScoreboard(myClass, posClass, posCourse);
					}
					else
					{
						gotoXY(40, 5);
						cout << "Course don't exist!";

					}
					_getch();
					system("cls");
					goto StartMenuLecturer;
				}
			}
		}
		//Sleep(100);	
	}
}

