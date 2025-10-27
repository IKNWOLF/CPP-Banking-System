#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include <iomanip>

class clsAddNewUserScreen : clsScreen
{

private:

	static void _ReadUserInfo(clsUser& User) {

		cout << "\nEnter FirstName:";
		User.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter LastName:";
		User.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email:";
		User.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone:";
		User.Phone = clsInputValidate::ReadString();

		cout << "\nEnter Password:";
		User.Password = clsInputValidate::ReadString();

		cout << "\nEnter Permissions:";
		User.Permissions = _ReadPermissionsToSet();

	}

	static void _printUserInfo(clsUser User) {

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

	static int _ReadPermissionsToSet() {

		int permissions = 0;

		char ans = 'n';

		cout << "\nDo you want to give full access to User ?y/n? ";
		cin >> ans;

		if (ans == 'y'|| ans == 'Y')
		{
			return -1;
		}

		cout << "\nDo you want to give access to: ";

		cout << "\nShow Client List? y/n ? ";
		cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			permissions += clsUser::enPermissions::eListClients;
		}

		cout << "\nAdd mew Client? y/n ? ";
		cin >> ans;

		if (ans == 'y' || ans == 'Y')
		{
			permissions += clsUser::enPermissions::eAddNewClient;
		}

		cout << "\nDelete Client? y/n ? ";
		cin >> ans;
		if (ans == 'y' ||ans == 'Y')
		{
			permissions += clsUser::enPermissions::eDeleteClient;
		}

		cout << "\nUpdate Client? y/n ? ";
		cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			permissions += clsUser::enPermissions::eUpdateClient;
		}

		cout << "\nFind Client? y/n ? ";
		cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			permissions += clsUser::enPermissions::eFindClient;
		}

		cout << "\nTransactions? y/n ? ";
		cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			permissions += clsUser::enPermissions::eTransactions;
		}

		cout << "\nManage Users? y/n ? ";
		cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			permissions += clsUser::enPermissions::eManageUsers;
		}

		return permissions;

	}


public:

	static void showAddNewUserScreen() {


		clsScreen::_DrawScreenHeader("\t  Add new User Screen");

		string Username = "";

		cout << "\nPlease Enter UserName:";
		Username = clsInputValidate::ReadString();

		while (clsUser::IsUserExist(Username))
		{
			cout << "\nUserName is already Used , Please try another one: ";
			Username = clsInputValidate::ReadString();
		}

		clsUser NewUser = clsUser::GetAddNewUserObject(Username);

		_ReadUserInfo(NewUser);

		clsUser::enSaveResults SaveResult;

		SaveResult = NewUser.Save();

		switch (SaveResult)
		{
		case clsUser::svFailedEmptyObject:
			cout << "\nError, User wasnt saved because it's empty!";
			break;
		case clsUser::svSucceeded:
			cout << "\nUser saved successfully!";
			break;
		case clsUser::svFailedUserExists:
			cout << "\nError, User wasnt saved because it already exists!";
			break;

		}

		_printUserInfo(NewUser);
	}
};



