#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsUser.h"
#include "Global.h"
#include "clsMainMenuScreen.h"
class clsLoginScreen: clsScreen
{
private:
		
	static bool _Login() {
		bool LoginFailed = false;

		short LoginTrials = 3;

		string Username, password;

		do
		{

			if (LoginFailed)
			{
				cout << "\nInvalid Username or Password!";
				cout << "\nYou have " << --LoginTrials << " trials to login.";

				if (LoginTrials == 0)
				{
					cout << "\nYou have used all 3 login trials.\n";
					return false;
				}
			}

			cout << "\nEnter Username :";
			Username = clsInputValidate::ReadString();
			cout << "\nEnter Password :";
			password = clsInputValidate::ReadString();

			CurrentUser = clsUser::Find(Username, password);

			LoginFailed = CurrentUser.IsEmpty();

		} while (LoginFailed);

		CurrentUser.RegisterLogin();

		clsMainMenuScreen::ShowMainMenu();

		return true;
	}
public:

	static bool ShowLoginScreen() {
		clsScreen::_DrawScreenHeader("\t\tLogin Screen");

		return _Login();
	}


};

