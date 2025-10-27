#pragma once
#include <fstream>
#include "clsScreen.h"
#include "clsString.h"
class clsCurrency : clsScreen
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1 };
	enMode _Mode;

	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;

	static clsCurrency _ConvertCurrencyLineToObject(string Line) {

		vector<string> vCurrencyLine = clsString::Split(Line, "#//#");

		return (clsCurrency(enMode::UpdateMode, vCurrencyLine[0], vCurrencyLine[1], vCurrencyLine[2], stod(vCurrencyLine[3])));
	}

	static string _ConverCurrencyObjectToLine(clsCurrency Currency, string Seperator = "#//#")
	{

		string stCurrencyRecord = "";
		stCurrencyRecord += Currency.Country() + Seperator;
		stCurrencyRecord += Currency.CurrencyCode() + Seperator;
		stCurrencyRecord += Currency.CurrencyName() + Seperator;
		stCurrencyRecord += to_string(Currency.Rate());

		return stCurrencyRecord;

	}

	static vector<clsCurrency> _LoadCurrencyDataFromFile() {

		vector<clsCurrency> vCurrencies;

		fstream MyFile;

		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile,Line))
			{
				clsCurrency Currency = _ConvertCurrencyLineToObject(Line);
				vCurrencies.push_back(Currency);
			}
			MyFile.close();
		}
		
		return vCurrencies;
	}

	static void _SaveCurrencyDataToFile(vector <clsCurrency> vCurrencys)
	{

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::out);//overwrite

		string DataLine;

		if (MyFile.is_open())
		{

			for (clsCurrency C : vCurrencys)
			{
				DataLine = _ConverCurrencyObjectToLine(C);
				MyFile << DataLine << endl;



			}

			MyFile.close();

		}

	}


	void _Update()
	{
		vector <clsCurrency> _vCurrencys;
		_vCurrencys = _LoadCurrencyDataFromFile();

		for (clsCurrency& C : _vCurrencys)
		{
			if (C.CurrencyCode() == CurrencyCode())
			{
				C = *this;
				break;
			}

		}

		_SaveCurrencyDataToFile(_vCurrencys);

	}

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}

	public:

		clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate) {
			_Mode = Mode;
			_Country = Country;
			_CurrencyCode = CurrencyCode;
			_CurrencyName = CurrencyName;
			_Rate = Rate;
		}

		bool IsEmpty() {
			return (_Mode == enMode::EmptyMode);
		}

		string Country() {
			return _Country;
		}

		string CurrencyCode() {
			return _CurrencyCode;
		}
		
		string CurrencyName() {
			return _CurrencyName;
		}

		float Rate() {
			return _Rate;
		}

		void UpdateRate(float Rate) {
			_Rate = Rate;
			_Update();
		}

		static clsCurrency FindByCode(string CurrencyCode) {

			CurrencyCode = clsString::UpperAllString(CurrencyCode);

			fstream MyFile;

			MyFile.open("Currencies.txt", ios::in);

			if (MyFile.is_open())
			{
				string Line;

				while (getline(MyFile,Line))
				{
					clsCurrency Currency = _ConvertCurrencyLineToObject(Line);
					
					if (Currency.CurrencyCode() == CurrencyCode)
					{
						MyFile.close();
						return Currency;
					}
				}
			}
			return _GetEmptyCurrencyObject();
		} 

		static   clsCurrency FindByCountry(string Country)
		{
			Country = clsString::UpperAllString(Country);

			fstream MyFile;
			MyFile.open("Currencies.txt", ios::in);//read Mode

			if (MyFile.is_open())
			{
				string Line;
				while (getline(MyFile, Line))
				{
					clsCurrency Currency = _ConvertCurrencyLineToObject(Line);
					if (clsString::UpperAllString(Currency.Country()) == Country)
					{
						MyFile.close();
						return Currency;
					}

				}

				MyFile.close();

			}
			return _GetEmptyCurrencyObject();
		}

		static bool IsCurrencyExist(string CurrencyCode)
		{
			clsCurrency C1 = clsCurrency::FindByCode(CurrencyCode);
			return (!C1.IsEmpty());

		}

		static vector <clsCurrency> GetCurrenciesList()
		{
			return _LoadCurrencyDataFromFile();
		}


		float ConvertToUSD(float amount) {
			return (float)(amount / Rate());
		}

		float ConvertToOtherCurrency(float amount,clsCurrency C2) {

			float AmountInUSD = ConvertToUSD(amount);

			if (C2.CurrencyCode() == "USD")
			{
				return AmountInUSD;
			}

			return (float)(AmountInUSD * C2.Rate());
		}
};



