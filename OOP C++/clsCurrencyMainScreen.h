#pragma once
#include <iostream>
#include "clsCurrency.h"
#include "clsScreen.h"
#include <iomanip>
#include "clsInputValidate.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyScreen.h"
#include "clsCurrencyCalcScreen.h"
class clsCurrencyMainScreen : protected clsScreen
{

private:

    enum enCurrencyMenuOption {
        eListCurrencies = 1, eFindCurrency = 2, eUpdateRate = 3, eCurrencyCalc = 4, eMainMenu = 5
    };


    static short _ReadCurrencyMenuOption() {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
        short Choice = clsInputValidate::ReadNumberBetween(1, 5, "Enter Number between 1 to 5? ");
        return Choice;
    }

    static void _GoBackToCurrencyMenu() {
        cout << "\n\n Press any key to go back to Currency Menu...";
        system("pause>0");
        ShowCurrencyScreen();
    }


    static void _ShowListCurrenciesScreen(){
        clsCurrenciesListScreen::ListCurrencies();
    }

    static void _ShowFindCurrencyScreen() {
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }

    static void _ShowUpdateRateScreen() {
        clsUpdateCurrencyScreen::ShowUpdateRateScreen();
    }

    static void _ShowCurrencyCalcScreen() {
        clsCurrencyCalcScreen::ShowCurrencyCalculatorScreen();
    }
    static void _PerfromCurrencyMenuOption(enCurrencyMenuOption Option) {

        switch (Option) 
        {
        case clsCurrencyMainScreen::eListCurrencies:
            system("cls");
            _ShowListCurrenciesScreen();
            _GoBackToCurrencyMenu();
            break;
        case clsCurrencyMainScreen::eFindCurrency:
            _ShowFindCurrencyScreen();
            _GoBackToCurrencyMenu();
            break;
        case clsCurrencyMainScreen::eUpdateRate:
            _ShowUpdateRateScreen();
            _GoBackToCurrencyMenu();
            break;
        case clsCurrencyMainScreen::eCurrencyCalc:
            _ShowCurrencyCalcScreen();
            _GoBackToCurrencyMenu();
            break;
        case clsCurrencyMainScreen::eMainMenu:
 
            break;
        }
    }

public:

	static void ShowCurrencyScreen() {

        system("cls");

		clsScreen::_DrawScreenHeader("Currency Exchange Main Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\tCurrency Exchange Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
        cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
        cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
        cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
        cout << setw(37) << left << "" << "\t[5] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromCurrencyMenuOption((enCurrencyMenuOption)_ReadCurrencyMenuOption());

	}
};

