#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include <iomanip>

class clsUpdateUserScreen:clsScreen
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

	static int _ReadPermissionsToSet() {

		int permissions = 0;

		char ans = 'n';

		cout << "\nDo you want to give full access to User ?y/n? ";
		cin >> ans;

		if (ans == 'y' || ans == 'Y')
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
		if (ans == 'y' || ans == 'Y')
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

		cout << "\nShow Logins Register? y/n ? ";
		cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			permissions += clsUser::enPermissions::eLoginsRegister;
		}

		return permissions;

	}

public:

	static void ShowUpdateUserScreen() {

		clsScreen::_DrawScreenHeader("\t Update User Screen");

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
		
		char ans = 'n';

		cout << "Are you sure you want to update this user? y/n? ";
		cin >> ans;

		if (ans == 'y' || ans == 'Y')
		{
			_ReadUserInfo(UserToUpdate);
			
			clsUser::enSaveResults SaveResult;

			SaveResult = UserToUpdate.Save();

			switch (SaveResult)
			{
			case clsUser::svFailedEmptyObject:
				cout << "Error,Empty User";
				break;
			case clsUser::svSucceeded:
				cout << "User updated successfully!";
				_PrintUserInfo(UserToUpdate);
				break;
			
			}
		}
	}


};

