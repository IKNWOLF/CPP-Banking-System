#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include <iomanip>

class clsDeleteUserScreen:clsScreen
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

	static void ShowDeleteUserScreen() {

		clsScreen::_DrawScreenHeader("\t Delete User Screen:");

		string UserName = "";
		
		cout << "\nEnter UserName : ";

		UserName = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\n User wasnt found! please try another username:";
			UserName = clsInputValidate::ReadString();
		}

		clsUser UserToDelete = clsUser::Find(UserName);

		_PrintUserInfo(UserToDelete);

		char ans = 'n';

		cout << "Are you sure you want to delete? y/n? ";
		cin >> ans;

		if (ans == 'y' || ans == 'Y')
		{
			
			if (UserToDelete.Delete())
			{
				cout << "\nUser deleted successfully";
				_PrintUserInfo(UserToDelete);
			}
			else
			{
				cout << "\nError User was not Deleted!";
			}
		}
	}


};

