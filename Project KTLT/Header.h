#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include<vector>
#include<fstream>
#include<string>
#include<conio.h>
#include"console.h"
#include<Windows.h>
#include <ctime>

//hidden mouse on console
//mode == 0 --> hidden
void cleanAndPrintTitle()
{
	system("cls");
	TextColor(11);
	cout << "\t\t\t\t\t Student Management System";
	TextColor(15);
}

void Nocursortype(int mode)
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = mode;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}
void erase(int rows)
{
	for (int j = 0; j < rows; j++)
	{
		for (int i = 0; i < 50; i++)
		{
			gotoXY(20 + i, 2 + j);
			cout << " ";			
		}
	}
	
}

enum Gender
{
	Male,
	Female
};
struct Date
{
	int day, month, year;
};
struct Time
{
	int hour, minute;
};
struct Student
{
	bool Checkin;
	int No;//stt
	int ID;
	string lastName;
	string firstName;
	Gender gender;
	Date doB;//day of birth
};
struct Scoreboard
{
	int No;
	int ID;
	int Mid;
	int Final;
	int Lab;
	int Bonus;
};
struct Course
{
	int No;
	string CourseID;
	string CourseName;
	string Class;
	string LecturerAccount;
	Date StartDate;
	Date EndDate;
	string DoW;//day of week
	Time startHour;
	Time endHour;
	string Room;
	vector<Student> stu;
	vector<Scoreboard> Sb;
};

enum typeUser
{
	student,
	lecturer,
	staff
};
struct User
{
	string ID;
	string password;	
	string className;
	typeUser type; // check User is student or leader
};

struct Class
{
	string name;
	vector<Student> stu;
	vector<Course> cou;
};



User createUserEmpty()
{
	User temp;
	temp.ID = "N/A";
	temp.password = "N/A";
	return temp;
}
User getUserPassword(vector<User> user, string ID)
{
	for (int i = 0; i < user.size(); i++)
	{
		if (user[i].ID == ID)
			return user[i];
	}

	return createUserEmpty();
}
int findPosClass(vector<Class> myClass, string name)
{
	for (int i = 0; i < myClass.size(); i++)
	{
		if (myClass[i].name == name)
			return i;
	}
	return -1;
}
//posClass is position of array contains students in vector my class
int findStudent(vector<Class> myClass, int id, int posClass)
{
	for (int i = 0; i < myClass[posClass].stu.size(); i++)
	{
		if (id == myClass[posClass].stu[i].ID)
			return i;
	}
	return -1;
}

int findCourse(vector<Class> myClass, int posClass, string course)
{
	for (int i = 0; i < myClass[posClass].cou.size(); i++)
	{
		if (course == myClass[posClass].cou[i].CourseID)
			return i;
	}
	return -1;
}
User findUser(vector<User> user, string ID)
{
	for (int i = 0; i < user.size(); i++)
	{
		if (user[i].ID == ID)
			return user[i];
	}
	return createUserEmpty();
}