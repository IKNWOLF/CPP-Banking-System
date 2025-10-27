#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include <vector>
class clsUsersListScreen : clsScreen
{
private:
    static void PrintUserRecordLine(clsUser user)
    {
        cout << setw(8) << left << "" << "| " << setw(15) << left <<user.UserName ;
        cout << "| " << setw(20) << left << user.FullName();
        cout << "| " << setw(12) << left << user.Phone;
        cout << "| " << setw(20) << left << user.Email;
        cout << "| " << setw(10) << left << user.Password;
        cout << "| " << setw(12) << left << user.Permissions;

    }

public:

    static void showUserList() {
        
        vector <clsUser> vUsers = clsUser::GetUsersList();

        string Title = "\t  User List Screen";
        string SubTitle = "\t    (" + to_string(vUsers.size()) + ") Users(s).";

        _DrawScreenHeader(Title, SubTitle);


        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(15) << "UserName";
        cout << "| " << left << setw(20) << "FullName";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(12) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vUsers.size() == 0)
        {
            cout << "No Users to display!\n";
        }
        else
        {
            for (clsUser User : vUsers) {
                PrintUserRecordLine(User);
                cout << endl;
            }
        }
    }

};

