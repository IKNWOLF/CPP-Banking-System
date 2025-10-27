#include <iostream>
#include <vector>
#include "MyLib.h" 
#include "fstream"
#include <ctime>
#pragma warning (disable:4996)
using namespace std;
using namespace MyLib;

struct stClient {
    string AccNum;
    string name;
    string pinCode;
    string phoneNum;
    double Accbalance;
    bool MarkForDeletion = false;
};

struct stUsers {
    string name;
    string password;
    int permissions;
    bool MarkForDeletion = false;
};

// Enum declarations
enum enTransactionChoice {
    Deposit = 1,
    Withdraw = 2,
    showTotalBalances = 3,
    EMainMenu = 4,
};

enum enManagementChoice {
    ListUsers = 1,
    AddNewUser = 2,
    DeleteUser = 3,
    UpdateUser = 4,
    FindUser = 5,
    eMainMenu = 6
};

enum enMainMenuOptions {
    showClient = 1,
    AddClient = 2,
    DeleteClient = 3,
    updateClient = 4,
    FindClient = 5,
    Transactions = 6,
    Manage_Users = 7,
    Logout = 8
};

enum enMainMenuePermissions {
    eAll = -1,
    pListClients = 1,
    pAddNewClient = 2,
    pDeleteClient = 4,
    pUpdateClients = 8,
    pFindClient = 16,
    pTranactions = 32,
    pManageUsers = 64
};

const string ClientsFileName = "Myfile.txt"; //Clients File Name
const string UsersFileName = "Users.txt"; //Users File Name

stUsers CurrentUser; // Global User 

// Forward declarations
void showMenu();
void showTransactionsMenu();
void showManageUsersMenu();
void Login();
int ReadPermissionsToSet();
bool UserExistsByUsername(string Username, string FileName);

// Function implementations
stClient ReadNewClient() {
    stClient client;
    cout << "Enter acc name: \n";
    cin >> client.name;
    cout << "Enter acc num: \n";
    cin >> client.AccNum;
    cout << "Enter acc pinCode: \n";
    cin >> client.pinCode;
    cout << "Enter acc balance: \n";
    cin >> client.Accbalance;
    cout << "Enter acc phonenum: \n";
    cin >> client.phoneNum;
    return client;
}

stUsers ReadNewUser() {
    stUsers User;
    cout << "Enter User Name:\n";
    getline(cin >> ws, User.name);

    while (UserExistsByUsername(User.name, UsersFileName)) {
        cout << "\nUser with Name : " << User.name << " already exists, Enter another User:\n";
        getline(cin >> ws, User.name);
    }

    cout << "Enter Password:\n";
    getline(cin, User.password);

    User.permissions = ReadPermissionsToSet();
    return User;
}

string convertRecordToLineForClient(stClient Client, string Seperator = "#//#") {
    string stClientRecord = "";
    stClientRecord += Client.AccNum + Seperator;
    stClientRecord += Client.pinCode + Seperator;
    stClientRecord += Client.name + Seperator;
    stClientRecord += Client.phoneNum + Seperator;
    stClientRecord += to_string(Client.Accbalance);
    return stClientRecord;
}

string convertRecordToLineForUser(stUsers User, string Seperator = "#//#") {
    string stUserRecord = "";
    stUserRecord += User.name + Seperator;
    stUserRecord += User.password + Seperator;
    stUserRecord += to_string(User.permissions);
    return stUserRecord;
}

stClient convertLinetoRecordForClient(string Line, string Seperator = "#//#") {
    stClient Client;
    vector<string> vClient = splitString(Line, "#//#");
    Client.AccNum = vClient[0];
    Client.pinCode = vClient[1];
    Client.name = vClient[2];
    Client.phoneNum = vClient[3];
    Client.Accbalance = stod(vClient[4]);
    return Client;
}

stUsers convertLinetoRecordForUser(string Line, string Seperator = "#//#") {
    stUsers User;
    vector<string> vUsers = splitString(Line, "#//#");
    User.name = vUsers[0];
    User.password = vUsers[1];
    User.permissions = stoi(vUsers[2]);
    return User;
}

void AddDataLineToFile(string FileName, string stDataLine) {
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);
    if (MyFile.is_open()) {
        MyFile << stDataLine << endl;
        MyFile.close();
    }
}

bool MarkClientForDeleteByAccNum(string accNum, vector<stClient>& vClients) {
    for (stClient& C : vClients) {
        if (C.AccNum == accNum) {
            C.MarkForDeletion = true;
            return true;
        }
    }
    return false;
}

bool MarkUserForDeleteByAccNum(string UserName, vector<stUsers>& vUsers) {
    for (stUsers& U : vUsers) {
        if (U.name == UserName) {
            U.MarkForDeletion = true;
            return true;
        }
    }
    return false;
}

void saveClientsDataToFile(string FileName, vector<stClient>& vClients) {
    fstream MyFile;
    MyFile.open(FileName, ios::out);
    string Line;

    if (MyFile.is_open()) {
        for (stClient& C : vClients) {
            if (C.MarkForDeletion == false) {
                Line = convertRecordToLineForClient(C);
                MyFile << Line << endl;
            }
        }
        MyFile.close();
    }
}

void saveUsersDataToFile(string FileName, vector<stUsers>& vUsers) {
    fstream MyFile;
    MyFile.open(FileName, ios::out);

    if (MyFile.is_open()) {
        for (stUsers& U : vUsers) {
            if (!U.MarkForDeletion) {
                MyFile << convertRecordToLineForUser(U) << endl;
            }
        }
        MyFile.close();
    }
    else {
        cout << "Error: Could not save users file!\n";
    }
}

void AddnewClient() {
    stClient Client;
    Client = ReadNewClient();
    AddDataLineToFile("Myfile.txt", convertRecordToLineForClient(Client));
}

void AddnewUser() {
    stUsers User;
    User = ReadNewUser();

    // Open file in append mode
    fstream MyFile;
    MyFile.open(UsersFileName, ios::out | ios::app);

    if (MyFile.is_open()) {
        MyFile << convertRecordToLineForUser(User) << endl;
        MyFile.close();
        cout << "User added successfully!\n";
    }
    else {
        cout << "Error: Could not open users file!\n";
    }
}

vector<stClient> LoadClientsDataFromFile(string filename) {
    vector<stClient> Clients;
    fstream Myfile;
    stClient Client;
    Myfile.open(filename, ios::in);

    if (Myfile.is_open()) {
        string Line;
        while (getline(Myfile, Line)) {
            Client = convertLinetoRecordForClient(Line);
            Clients.push_back(Client);
        }
        Myfile.close();
    }
    return Clients;
}

vector<stUsers> LoadUsersDataFromFile(string filename) {
    vector<stUsers> Users;
    fstream Myfile;
    Myfile.open(filename, ios::in);

    if (Myfile.is_open()) {
        string Line;
        while (getline(Myfile, Line)) {
            if (!Line.empty()) {  // Skip empty lines
                stUsers User = convertLinetoRecordForUser(Line);
                Users.push_back(User);
            }
        }
        Myfile.close();
    }
    else {
        cout << "Error: Could not open users file!\n";
    }
    return Users;
}

void showClients(vector<stClient> Clients) {
    short cnt = 1;
    for (stClient& Client : Clients) {
        cout << "Client " << cnt++ << " : \n";
        cout << "Client num : " << Client.AccNum << endl;
        cout << "Client pincode : " << Client.pinCode << endl;
        cout << "Client name : " << Client.name << endl;
        cout << "Client phone : " << Client.phoneNum << endl;
        cout << "Client balance : " << Client.Accbalance << endl;
    }
}

void AddClients() {
    char addmore = 'Y';
    do {
        cout << "Adding new client ... \n";
        AddnewClient();
        cout << "Client added successfully, do you want to add new clients? \n";
        cin >> addmore;
    } while (toupper(addmore) == 'Y');
}

void AddUsers() {
    char addmore = 'Y';
    do {
        cout << "Adding new User ... \n";
        AddnewUser();
        cout << "User added successfully, do you want to add new Users? \n";
        cin >> addmore;
    } while (toupper(addmore) == 'Y');
}

bool findClientByAccNum(string accnum, vector<stClient> vClients, stClient& Client) {
    vClients = LoadClientsDataFromFile("Myfile.txt");
    for (stClient& C : vClients) {
        if (C.AccNum == accnum) {
            Client = C;
            return true;
        }
    }
    return false;
}

bool FindUserByUsername(string Username, vector<stUsers> vUsers, stUsers& User) {
    for (stUsers U : vUsers) {
        if (U.name == Username) {
            User = U;
            return true;
        }
    }
    return false;
}

bool UserExistsByUsername(string Username, string FileName) {
    fstream MyFile;
    MyFile.open(FileName, ios::in);
    if (MyFile.is_open()) {
        string Line;
        stUsers User;
        while (getline(MyFile, Line)) {
            User = convertLinetoRecordForUser(Line);
            if (User.name == Username) {
                MyFile.close();
                return true;
            }
        }
        MyFile.close();
    }
    return false;
}

bool findUserByNameAndPass(string name, string pass, stUsers& User) {
    vector<stUsers> vUsers = LoadUsersDataFromFile("Users.txt");
    for (stUsers& U : vUsers) {
        if (U.name == name && U.password == pass) {
            User = U;
            return true;
        }
    }
    return false;
}

bool CheckAccessPermission(enMainMenuePermissions Permission) {
    if (CurrentUser.permissions == enMainMenuePermissions::eAll)
        return true;
    if ((Permission & CurrentUser.permissions) == Permission)
        return true;
    else
        return false;
}

int ReadPermissionsToSet() {
    int Permissions = 0;
    char Answer = 'n';
    cout << "\nDo you want to give full access? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y') {
        return -1;
    }

    cout << "\nDo you want to give access to : \n ";
    cout << "\nShow Client List? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y') {
        Permissions += enMainMenuePermissions::pListClients;
    }
    cout << "\nAdd New Client? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y') {
        Permissions += enMainMenuePermissions::pAddNewClient;
    }
    cout << "\nDelete Client? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y') {
        Permissions += enMainMenuePermissions::pDeleteClient;
    }
    cout << "\nUpdate Client? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y') {
        Permissions += enMainMenuePermissions::pUpdateClients;
    }
    cout << "\nFind Client? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y') {
        Permissions += enMainMenuePermissions::pFindClient;
    }
    cout << "\nTransactions? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y') {
        Permissions += enMainMenuePermissions::pTranactions;
    }
    cout << "\nManage Users? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y') {
        Permissions += enMainMenuePermissions::pManageUsers;
    }
    return Permissions;
}

string readClientAccNum() {
    string accnum;
    cout << "Enter acc num : \n";
    cin >> accnum;
    return accnum;
}

string readUsersName() {
    string name;
    cout << "Enter Username:\n";
    cin >> name;
    return name;
}

string readUsername() {
    string name;
    cout << "Enter UserName:\n";
    cin >> name;
    return name;
}

string readUserPass() {
    string pass;
    cout << "Enter pass:\n";
    cin >> pass;
    return pass;
}

void showClientInfo(stClient Client) {
    cout << "Client num : " << Client.AccNum << endl;
    cout << "Client pincode : " << Client.pinCode << endl;
    cout << "Client name : " << Client.name << endl;
    cout << "Client phone : " << Client.phoneNum << endl;
    cout << "Client balance : " << Client.Accbalance << endl;
}

void showUserInfo(stUsers User) {
    cout << "User Name : " << User.name << endl;
    cout << "User Pass : " << User.password << endl;
}

void deleteClientByAccNum(string accNum, vector<stClient>& vClients) {
    stClient Client;
    char ans;
    if (findClientByAccNum(accNum, vClients, Client)) {
        showClientInfo(Client);
        cout << "Are you sure you want to delete this client?\n";
        cin >> ans;
        if (tolower(ans) == 'y') {
            MarkClientForDeleteByAccNum(accNum, vClients);
            saveClientsDataToFile(ClientsFileName, vClients);
            vClients = LoadClientsDataFromFile(ClientsFileName);
            cout << "Client Deleted Successfully.\n";
        }
    }
    else {
        cout << "Client with " << accNum << " not found!\n";
    }
}

void deleteUserByName(string Username, vector<stUsers>& vUsers) {
    stUsers User;
    char ans;
    if (FindUserByUsername(Username, vUsers, User)) {
        showUserInfo(User);
        cout << "Are you sure you want to delete this User?\n";
        cin >> ans;
        if (tolower(ans) == 'y') {
            MarkUserForDeleteByAccNum(Username, vUsers);
            saveUsersDataToFile(UsersFileName, vUsers);
            vUsers = LoadUsersDataFromFile(UsersFileName);
            cout << "User Deleted Successfully.\n";
        }
    }
    else {
        cout << "User with " << Username << " not found!\n";
    }
}

stClient ChangeClientRecord(string accNum) {
    stClient Client;
    Client.AccNum = accNum;
    cout << "Enter pin code : \n";
    getline(cin >> ws, Client.pinCode);
    cout << "Enter Name : \n";
    getline(cin, Client.name);
    cout << "Enter Phone:\n";
    getline(cin, Client.phoneNum);
    cout << "Enter balance:\n";
    cin >> Client.Accbalance;
    return Client;
}

stUsers ChangeUserRecord(string name) {
    stUsers User;
    User.name = name;
    cout << "Enter new password:\n";
    getline(cin, User.password);
    return User;
}

void UpdateClientByAccNum(string accNum, vector<stClient>& vClients) {
    stClient Client;
    char ans;

    if (findClientByAccNum(accNum, vClients, Client)) {
        showClientInfo(Client);
        cout << "Are you sure you want to update this Client?\n";
        cin >> ans;

        if (tolower(ans) == 'y') {
            for (stClient& C : vClients) {
                if (C.AccNum == accNum) {
                    C = ChangeClientRecord(accNum);
                    break;
                }
            }
            saveClientsDataToFile(ClientsFileName, vClients);
            vClients = LoadClientsDataFromFile(ClientsFileName);
            cout << "Client Updated successfully\n";
        }
    }
    else {
        cout << "Client with accNum : " << accNum << " not found!\n";
    }
}

void UpdateUserByName(string Name, vector<stUsers>& vUsers) {
    stUsers User;
    char ans;

    if (FindUserByUsername(Name, vUsers, User)) {
        showUserInfo(User);
        cout << "Are you sure you want to update this User?\n";
        cin >> ans;

        if (tolower(ans) == 'y') {
            for (stUsers& U : vUsers) {
                if (U.name == Name) {
                    cout << "Enter new password (leave blank to keep current): ";
                    string newPass;
                    getline(cin >> ws, newPass);
                    if (!newPass.empty()) {
                        U.password = newPass;
                    }

                    cout << "Update permissions? (y/n): ";
                    cin >> ans;
                    if (tolower(ans) == 'y') {
                        U.permissions = ReadPermissionsToSet();
                    }

                    saveUsersDataToFile(UsersFileName, vUsers);
                    cout << "User Updated successfully\n";
                    return;
                }
            }
        }
    }
    else {
        cout << "User with name : " << Name << " not found!\n";
    }
}

void showEndScreen() {
    cout << "-------------------------------------------------------\n";
    cout << "\t\t\tProgram Ends\n";
    cout << "-------------------------------------------------------\n";
}

short readMenuChoice() {
    short choice;
    do {
        cout << "Choose what do you wanna do?[1-8]\n";
        cin >> choice;
    } while (choice < 1 || choice > 8);
    return choice;
}

short readTransactionsMenuChoice() {
    short choice;
    do {
        cout << "Choose what do you wanna do?[1-4]\n";
        cin >> choice;
    } while (choice < 1 || choice > 4);
    return choice;
}

short readManagementMenuChoice() {
    short choice;
    do {
        cout << "Choose what do you wanna do?[1-6]\n";
        cin >> choice;
    } while (choice < 1 || choice > 6);
    return choice;
}

void ShowAccessDeniedMessage() {
    cout << "\n------------------------------------\n";
    cout << "Access Denied, \nYou dont Have Permission To Do this, \nPlease Conact Your Admin.";
    cout << "\n------------------------------------\n";
}

void showAllClients() {
    if (!CheckAccessPermission(enMainMenuePermissions::pListClients)) {
        ShowAccessDeniedMessage();
        showMenu();
        return;
    }

    vector<stClient> Clients = LoadClientsDataFromFile(ClientsFileName);
    cout << "\t\t\t Client List(" << Clients.size() << ") Clients\n";
    cout << "-------------------------------------------------------\n";
    cout << "| " << left << setw(15) << "Account Num";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance\n";
    cout << "--------------------------------------------------------\n";

    if (Clients.empty()) {
        cout << "\t\t\tNo Clients\n";
    }
    else {
        for (stClient& C : Clients) {
            cout << "| " << left << setw(15) << C.AccNum;
            cout << "| " << left << setw(10) << C.pinCode;
            cout << "| " << left << setw(40) << C.name;
            cout << "| " << left << setw(12) << C.phoneNum;
            cout << "| " << left << setw(12) << C.Accbalance;
            cout << endl;
        }
    }
}

void showAllUsers() {
    vector<stUsers> Users = LoadUsersDataFromFile(UsersFileName);
    cout << "\t\t\t User List(" << Users.size() << ") Users\n";
    cout << "-------------------------------------------------------\n";
    cout << "| " << left << setw(12) << "Name";
    cout << "| " << left << setw(12) << "Pass" << endl;
    cout << "-------------------------------------------------------\n";

    if (Users.empty()) {
        cout << "No Users Found!\n";
    }
    else {
        for (stUsers& User : Users) {
            cout << "| " << left << setw(12) << User.name;
            cout << "| " << left << setw(12) << User.password;
            cout << endl;
        }
    }
}

void depositBalanceByAccNum(string accnum, double amount, vector<stClient>& vClients) {
    char ans = 'y';
    cout << "\nAre you sure you want to perform this operation?\n ";
    cin >> ans;

    if (tolower(ans) == 'y') {
        for (stClient& c : vClients) {
            if (c.AccNum == accnum) {
                c.Accbalance += amount;
                saveClientsDataToFile(ClientsFileName, vClients);
                cout << "\nTransaction Completed!\nNew Balance is :" << c.Accbalance << endl;
                return;
            }
        }
    }
}

void DepositTransactionScreen() {
    cout << "-------------------------------------------------------\n";
    cout << "\t\t\tDeposit Transaction Screen\n";
    cout << "-------------------------------------------------------\n";

    stClient Client;
    vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    string AccNum = readClientAccNum();

    while (!findClientByAccNum(AccNum, vClients, Client)) {
        cout << "Client " << AccNum << " doesnt exist\n";
        AccNum = readClientAccNum();
    }

    showClientInfo(Client);
    double amount = 0;
    cout << "\nEnter deposit amount: \n";
    cin >> amount;
    depositBalanceByAccNum(AccNum, amount, vClients);
}

void WithdrawTransactionScreen() {
    cout << "-------------------------------------------------------\n";
    cout << "\t\t\tWithdraw Transaction Screen\n";
    cout << "-------------------------------------------------------\n";

    stClient Client;
    vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    string AccNum = readClientAccNum();

    while (!findClientByAccNum(AccNum, vClients, Client)) {
        cout << "Client " << AccNum << " doesnt exist\n";
        AccNum = readClientAccNum();
    }

    showClientInfo(Client);
    double amount = 0;
    cout << "\nEnter Withdraw amount: \n";
    cin >> amount;

    while (amount > Client.Accbalance) {
        cout << "\nNot enough balance to withdraw!\nPlease enter another amount\n";
        cin >> amount;
    }

    depositBalanceByAccNum(AccNum, -1 * amount, vClients);
}

void TotalBalancesTransactionScreen() {
    vector<stClient> Clients = LoadClientsDataFromFile(ClientsFileName);
    cout << "\t\t\t Balances List(" << Clients.size() << ") Clients\n";
    cout << "| " << left << setw(15) << "Account Num";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance" << endl;

    double total = 0;

    if (Clients.empty()) {
        cout << "\t\t\tNo Clients\n";
    }
    else {
        for (stClient& C : Clients) {
            cout << "| " << left << setw(15) << C.AccNum;
            cout << "| " << left << setw(40) << C.name;
            cout << "| " << left << setw(12) << C.Accbalance << endl;
            total += C.Accbalance;
        }
    }
    cout << "\t\t\t Total Balances : " << total << endl;
}

void FindClientScreen() {
    if (!CheckAccessPermission(enMainMenuePermissions::pFindClient)) {
        ShowAccessDeniedMessage();
        showMenu();
        return;
    }
    cout << "-------------------------------------------------------\n";
    cout << "\t\t\tFind Clients Screen\n";
    cout << "-------------------------------------------------------\n";
    vector<stClient> Clients = LoadClientsDataFromFile(ClientsFileName);
    string accNum = readClientAccNum();
    stClient Client;
    if (findClientByAccNum(accNum, Clients, Client)) {
        showClientInfo(Client);
    }
    else {
        cout << "\nClient not found\n";
    }
}

void FindUserScreen() {
    cout << "-------------------------------------------------------\n";
    cout << "\t\t\tFind User Screen\n";
    cout << "-------------------------------------------------------\n";
    vector<stUsers> Users = LoadUsersDataFromFile(UsersFileName);
    string name = readUsername();
    string pass = readUserPass();
    stUsers User;
    if (FindUserByUsername(name, Users, User)) {
        showUserInfo(User);
    }
    else {
        cout << "\nUser not found\n";
    }
}

void updateClientScreen() {
    if (!CheckAccessPermission(enMainMenuePermissions::pUpdateClients)) {
        ShowAccessDeniedMessage();
        showMenu();
        return;
    }
    cout << "-------------------------------------------------------\n";
    cout << "\t\t\tUpdate Clients Screen\n";
    cout << "-------------------------------------------------------\n";
    vector<stClient> Clients = LoadClientsDataFromFile(ClientsFileName);
    string accNum = readClientAccNum();
    UpdateClientByAccNum(accNum, Clients);
}

void UpdateUserScreen() {
    cout << "-------------------------------------------------------\n";
    cout << "\t\t\tUpdate Users Screen\n";
    cout << "-------------------------------------------------------\n";
    vector<stUsers> vUsers = LoadUsersDataFromFile(UsersFileName);
    string Name = readUsersName();
    UpdateUserByName(Name, vUsers);
}

void AddNewClientScreen() {
    if (!CheckAccessPermission(enMainMenuePermissions::pAddNewClient)) {
        ShowAccessDeniedMessage();
        showMenu();
        return;
    }
    cout << "-------------------------------------------------------\n";
    cout << "\t\t\tAdd new Clients Screen\n";
    cout << "-------------------------------------------------------\n";
    AddClients();
}

void AddNewUserScreen() {
    cout << "-------------------------------------------------------\n";
    cout << "\t\t\tAdd new Users Screen\n";
    cout << "-------------------------------------------------------\n";
    AddUsers();
}

void deleteClientScreen() {
    if (!CheckAccessPermission(enMainMenuePermissions::pDeleteClient)) {
        ShowAccessDeniedMessage();
        showMenu();
        return;
    }
    cout << "-------------------------------------------------------\n";
    cout << "\t\t\tDelete Client Screen\n";
    cout << "-------------------------------------------------------\n";
    vector<stClient> Clients = LoadClientsDataFromFile(ClientsFileName);
    string accNum = readClientAccNum();
    deleteClientByAccNum(accNum, Clients);
}

void DeleteUserScreen() {
    cout << "-------------------------------------------------------\n";
    cout << "\t\t\tDelete User Screen\n";
    cout << "-------------------------------------------------------\n";
    vector<stUsers> Users = LoadUsersDataFromFile(UsersFileName);
    string Username = readUsername();
    deleteUserByName(Username, Users);
}

void getBackToMenu() {
    system("pause");
    showMenu();
}

void getBackToManageMenu() {
    system("pause");
    showManageUsersMenu();
}

void GoBackToTransactionMenu() {
    system("pause");
    showTransactionsMenu();
}

void PerformManagementMenuOption(enManagementChoice Choice) {
    switch (Choice) {
    case ListUsers:
        showAllUsers();
        getBackToManageMenu();
        break;
    case AddNewUser:
        AddNewUserScreen();
        getBackToManageMenu();
        break;
    case DeleteUser:
        DeleteUserScreen();
        getBackToManageMenu();
        break;
    case UpdateUser:
        UpdateUserScreen();
        getBackToManageMenu();
        break;
    case FindUser:
        FindUserScreen();
        getBackToManageMenu();
        break;
    case eMainMenu:
        getBackToMenu();
        break;
    }
}

void PerformTransactionsMenuOption(enTransactionChoice TChoice) {
    switch (TChoice) {
    case enTransactionChoice::Deposit:
        DepositTransactionScreen();
        GoBackToTransactionMenu();
        break;
    case enTransactionChoice::Withdraw:
        WithdrawTransactionScreen();
        GoBackToTransactionMenu();
        break;
    case enTransactionChoice::showTotalBalances:
        TotalBalancesTransactionScreen();
        GoBackToTransactionMenu();
        break;
    case enTransactionChoice::EMainMenu:
        showMenu();
    }
}

void PerformMenuOption(enMainMenuOptions Choice) {
    switch (Choice) {
    case enMainMenuOptions::showClient:
        showAllClients();
        getBackToMenu();
        break;
    case enMainMenuOptions::AddClient:
        AddNewClientScreen();
        getBackToMenu();
        break;
    case enMainMenuOptions::DeleteClient:
        deleteClientScreen();
        getBackToMenu();
        break;
    case enMainMenuOptions::updateClient:
        updateClientScreen();
        getBackToMenu();
        break;
    case enMainMenuOptions::Transactions:
        showTransactionsMenu();
        break;
    case enMainMenuOptions::FindClient:
        FindClientScreen();
        getBackToMenu();
        break;
    case enMainMenuOptions::Manage_Users:
        showManageUsersMenu();
        break;
    case enMainMenuOptions::Logout:
        system("cls");
        Login();
        break;
    }
}

void showMenu() {
    cout << "==================================================\n";
    cout << "\t\tMain Menu Screen\n";
    cout << "==================================================\n";
    cout << "[1] Show Client Info\n";
    cout << "[2] Add New Client\n";
    cout << "[3] Delete Client\n";
    cout << "[4] Update Client\n";
    cout << "[5] Find Client\n";
    cout << "[6] Transactions\n";
    cout << "[7] Manage Users\n";
    cout << "[8] Logout\n";
    cout << "==================================================\n";
    PerformMenuOption(enMainMenuOptions(readMenuChoice()));
}

void showTransactionsMenu() {
    if (!CheckAccessPermission(enMainMenuePermissions::pTranactions)) {
        ShowAccessDeniedMessage();
        showMenu();
        return;
    }

    cout << "==================================================\n";
    cout << "\t\tTransactions Menu Screen\n";
    cout << "==================================================\n";
    cout << "[1] Deposit\n";
    cout << "[2] Withdraw\n";
    cout << "[3] Total Balances\n";
    cout << "[4] Main Menu\n";
    cout << "==================================================\n";
    PerformTransactionsMenuOption(enTransactionChoice(readTransactionsMenuChoice()));
}

void showManageUsersMenu() {
    if (!CheckAccessPermission(enMainMenuePermissions::pManageUsers)) {
        ShowAccessDeniedMessage();
        showMenu();
        return;
    }
    cout << "==================================================\n";
    cout << "\t\tManage Users Menu Screen\n";
    cout << "==================================================\n";
    cout << "[1] List Users\n";
    cout << "[2] Add New User\n";
    cout << "[3] Delete User\n";
    cout << "[4] Update User\n";
    cout << "[5] Find User\n";
    cout << "[6] Main Menu\n";
    cout << "==================================================\n";
    PerformManagementMenuOption(enManagementChoice(readManagementMenuChoice()));
}

bool LoadUserInfo(string name, string pass) {
    return findUserByNameAndPass(name, pass, CurrentUser);
}

void Login() {
    bool LoginFailed = false;
    string Username, Pass;

    do {
        cout << "Login Screen\n";
        if (LoginFailed) {
            cout << "Invalid Username or Password!\n";
        }
        cout << "Enter Username:\n";
        cin >> Username;
        cout << "Enter Password:\n";
        cin >> Pass;
        LoginFailed = !LoadUserInfo(Username, Pass);
    } while (LoginFailed);

    showMenu();
}

int main() {
    srand((unsigned)time(NULL));
    Login();
    return 0;
}