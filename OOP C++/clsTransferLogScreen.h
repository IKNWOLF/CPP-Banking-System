#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include <vector>

class clsTransferLogScreen:protected clsScreen
{

private:

    static void PrintTransferLogRecordLine(clsBankClient::stTransferRegisterRecord TransferLogRecord)
    {

        cout << setw(8) << left << "" << "| " << setw(23) << left << TransferLogRecord.date;
        cout << "| " << setw(8) << left << TransferLogRecord.FromAccNum;
        cout << "| " << setw(8) << left << TransferLogRecord.ToAccNum;
        cout << "| " << setw(8) << left << TransferLogRecord.amount;
        cout << "| " << setw(10) << left <<TransferLogRecord.FromAccBalance;
        cout << "| " << setw(10) << left <<TransferLogRecord.ToAccBalance;
        cout << "| " << setw(8) << left << TransferLogRecord.username;


    }

public:

	static void ShowTransferLogScreen() {

        vector <clsBankClient::stTransferRegisterRecord> vTransferLogRecord = clsBankClient::GetTransfersLogList();

        string Title = "\tTransfer Log List Screen";
        string SubTitle = "\t    (" + to_string(vTransferLogRecord.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/Time";
        cout << "| " << left << setw(8) << "s.Acct";
        cout << "| " << left << setw(8) << "d.Acct";
        cout << "| " << left << setw(8) << "Amount";
        cout << "| " << left << setw(10) << "s.Balance";
        cout << "| " << left << setw(10) << "d.Balance";
        cout << "| " << left << setw(8) << "User";

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vTransferLogRecord.size() == 0)
            cout << "\t\t\t\tNo Transfers Available In the System!";
        else

            for (clsBankClient::stTransferRegisterRecord Record : vTransferLogRecord)
            {

                PrintTransferLogRecordLine(Record);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
	}
};

