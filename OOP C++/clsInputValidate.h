#pragma once
#include <iostream>
#include <string>
#include "clsString.h"
#include "clsDate.h"
#include <limits>

class clsInputValidate
{

public:


	template <typename T>

	static bool IsNumberBetween(T Number, T From, T To) {
		return (Number >= From) && (Number <= To);
	}


	static bool IsDateBetween(clsDate Date, clsDate From, clsDate To)
	{
		if ((clsDate::IsDate1AfterDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From))
			&&
			(clsDate::IsDate1BeforeDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To))
			)
		{
			return true;
		}

		if ((clsDate::IsDate1AfterDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To))
			&&
			(clsDate::IsDate1BeforeDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From))
			)
		{
			return true;
		}

		return false;
	}


	template <typename T> static T ReadNumber(string ErrorMsg = "Invalid Number, Try again:\n") {

		T number;

		while (!(cin >> number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMsg;
		}
		return number;
	}



	

	template <typename T> static T ReadNumberBetween(T From, T To, string ErrorMessage = "Number is not within range, Enter again:\n") {

		T Number = ReadNumber<T>();

		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage;
			Number = ReadNumber<T>();
		}
		return Number;

	}


	static bool IsValideDate(clsDate Date)
	{
		return	clsDate::IsValidDate(Date);
	}

	static string ReadString()
	{
		string  S1 = "";
		getline(cin >> ws, S1);
		return S1;
	}

};


		