#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"
class clsUpdateCurrencyScreen : protected clsScreen
{

private:

	static void _PrintCurrency(clsCurrency Currency)
	{
		cout << "\nCurrency Card:\n";
		cout << "_____________________________\n";
		cout << "\nCountry    : " << Currency.Country();
		cout << "\nCode       : " << Currency.CurrencyCode();
		cout << "\nName       : " << Currency.CurrencyName();
		cout << "\nRate(1$) = : " << Currency.Rate();

		cout << "\n_____________________________\n";

	}

	static float _ReadRate() {
		cout << "\nEnter new Rate: \n";

		float NewRate = 0;

		NewRate = clsInputValidate::ReadNumber<float>();

		return NewRate;
	}

public:

	static void ShowUpdateRateScreen() {

		clsScreen::_DrawScreenHeader("\t\tUpdate Rate Screen");

		string CurrencyCode = "";

		cout << "\nEnter Currency Code: ";

		CurrencyCode = clsInputValidate::ReadString();

		while (!clsCurrency::IsCurrencyExist(CurrencyCode))
		{
			cout << "\n Currency Not found! , Enter another Currency Code:";
			CurrencyCode = clsInputValidate::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		_PrintCurrency(Currency);

		cout << "\n Are you sure you want to update the rate for this Currency? y/n?\n";
		
		char ans = 'n';

		cin >> ans;

		if (ans == 'y' || ans == 'Y')
		{
			Currency.UpdateRate(_ReadRate());
			cout << "\nRate changed successfully!\n";
			_PrintCurrency(Currency);
		}

	}




};

