#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"
#include "clsBankClient.h"

class clsTransferScreen : clsScreen
{

private:

	static string _ReadAccountNumber()
	{
		string AccountNumber = "";
		cout << "\nPlease enter AccountNumber? ";
		cin >> AccountNumber;
		return AccountNumber;
	}

	static void _PrintClient(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << Client.FirstName;
		cout << "\nLastName    : " << Client.LastName;
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nEmail       : " << Client.Email;
		cout << "\nPhone       : " << Client.Phone;
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nPassword    : " << Client.PinCode;
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________\n";

	}

	static double _ReadAmount(clsBankClient Client1) {
		double amount;

		cout << "\nEnter transfer Amount : ";
		cin >> amount;
		while (amount > Client1.AccountBalance)
		{
			cout << "\nAmount exceeds available balance , enter another amount: ";
			cin >> amount;
		}
		return amount;
	}
public:

	static void ShowTransferScreen() {

		_DrawScreenHeader("\t   Transfer Screen");

		string FromAccNum;

		cout << "\nEnter Acc Num to transfer from : ";

		cin >> FromAccNum;

		while (!clsBankClient::IsClientExist(FromAccNum))
		{
			cout << "\nClient with [" << FromAccNum << "] does not exist.\n";
			cout << "\nEnter Acc Num to transfer from : ";
			cin >> FromAccNum;
		}

		clsBankClient Client1 = clsBankClient::Find(FromAccNum);
		_PrintClient(Client1);

		string ToAccNum;

		cout << "\nEnter Acc Num to transfer to : ";

		cin >> ToAccNum;

		clsBankClient Client2= clsBankClient::Find(ToAccNum);
		_PrintClient(Client2);

		double amount = _ReadAmount(Client1);

		char ans = 'n';

		cout << "\nAre you sure you want to perform this operation? y/n? ";

		cin >> ans;

		if (ans == 'y' || ans == 'Y')
		{
			if (Client1.Transfer(amount, Client2,CurrentUser.UserName))
			{
				cout << "\nTransfer done succeffully\n";
			}
			else
			{
				cout << "\nTransfer Failed\n";
			}

			_PrintClient(Client1);
			_PrintClient(Client2);
		}
	}
};

