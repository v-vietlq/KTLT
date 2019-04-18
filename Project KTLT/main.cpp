#include"Class.h"
#include"Menu.h"


int main()
{
	vector<Class> myClass;
	vector<Student> stu;
	vector<User> user;
	vector<Course> course;
	
	User temp;
	temp.className = "N/A";
	temp.ID = "Staff";
	temp.password = "staff";
	temp.type = staff;
	user.push_back(temp);
	/*importStudent("18CLC6-Students.csv", myClass);
	//importCourse("18CLC6-Course.csv", myClass);
	//createStudentUser(myClass, user);
	//createLecturerUser(myClass, user);
	//createStaff(user);
	//saveStudentAccount("18CLC6-Account.txt", user);*/
	
	//viewAllLectuture(myClass);
	menuLevelOne(user, myClass);

	return 0;
}
