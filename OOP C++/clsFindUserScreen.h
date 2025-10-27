#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include <iomanip>

class clsFindUserScreen:clsScreen
{
private:

	static void _PrintUserInfo(clsUser User) {
		cout << "\nUser Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << User.FirstName;
		cout << "\nLastName    : " << User.LastName;
		cout << "\nFull Name   : " << User.FullName();
		cout << "\nEmail       : " << User.Email;
		cout << "\nPhone       : " << User.Phone;
		cout << "\nUser Name   : " << User.UserName;
		cout << "\nPassword    : " << User.Password;
		cout << "\nPermissions : " << User.Permissions;
		cout << "\n___________________\n";
	}

public:

	static void ShowFindUserScreen() {

		clsScreen::_DrawScreenHeader("\t Find User Screen");

		string UserName = "";

		cout << "\nEnter UserName: ";

		UserName = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\n User wasnt found! please try another username:";
			UserName = clsInputValidate::ReadString();
		}

		clsUser UserToUpdate = clsUser::Find(UserName);

		_PrintUserInfo(UserToUpdate);
	}
};

