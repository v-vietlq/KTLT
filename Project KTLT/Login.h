#pragma once
#include"Header.h"


User login(vector<User> user)
{
	
	//show mouse to login
	Nocursortype(1);
startLogin:
	erase(3);
	int i = 0;
	string ID, password;
	char key, temp;


	gotoXY(50, 2);
	cout << "ID: ";
	gotoXY(50, 3);
	cout << "Password: ";

	gotoXY(54, 2);
	cin >> ID;
	gotoXY(60, 3);
	

	key = _getch();
	while (key != 13) // enter
	{	
		if (key == 8) // backspace
		{
			password.pop_back();
			gotoXY(60 + --i, 3);
			cout << " ";
			gotoXY(60 + i, 3); // make mouse same on console
			cout << "";
		}
		else
		{
			gotoXY(60 + i++, 3);
			cout << "*";
			password.push_back(key);
			
		}
		key = _getch();
	}
	//new key;
	key = 0;

	int count = 0;
	while (key != 13)
	{
		if (password == getUserPassword(user, ID).password)
		{
			return getUserPassword(user, ID);
		}
		else
		{
			gotoXY(50, 4);
			cout << "Account don't exist.";

			if (_kbhit())
				goto startLogin;
		}
		key = _getch();
	}
	User a;
	a.ID = "N/A";
	a.password = "N/A";
	return a;
}