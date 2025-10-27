#include <iostream>
#include <vector>
#include "fstream"
#include <ctime>
#include <string>

#pragma warning (disable:4996)
using namespace std;
const string ClientsFileName = "Clients.txt"; //Clients File Name

struct stClient {
	string AccNum;
	string name;
	string pinCode;
	string phoneNum;
	double Accbalance;
	bool MarkForDeletion = false;
};
stClient CurrentClient;

enum enMainMenuOptions {
	QuickWithdraw = 1,
	NormalWithdraw = 2,
	Deposit = 3,
	CheckBalance = 4,
	Logout = 5,
};

void ShowNormalWithDrawScreen();
void PerfromNormalWithdrawOption();
void showMenu();
short ReadQuickWithdrawOption();
void PerfromQuickWithdrawOption(short QuickWithDrawOption);
void Login();

vector<string> splitString(string s, string delim) {
	vector<string> vString;
	short pos = 0;
	string sWord;

	while ((pos = s.find(delim)) != string::npos)
	{
		sWord = s.substr(0, pos); // hi my name is abdo
		if (sWord != "") {
			vString.push_back(sWord);
		}
		s.erase(0, pos + delim.length());
	}
	if (s != "") {
		vString.push_back(s);
	}
	return vString;
}

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

string convertRecordToLineForClient(stClient Client, string Seperator = "#//#") {
	string stClientRecord = "";
	stClientRecord += Client.AccNum + Seperator;
	stClientRecord += Client.pinCode + Seperator;
	stClientRecord += Client.name + Seperator;
	stClientRecord += Client.phoneNum + Seperator;
	stClientRecord += to_string(Client.Accbalance);
	return stClientRecord;
}

stClient ConvertLinetoRecordForClient(string Line, string Seperator = "#//#") {
	stClient Client;
	vector<string> vClient = splitString(Line, "#//#");
	Client.AccNum = vClient[0];
	Client.pinCode = vClient[1];
	Client.name = vClient[2];
	Client.phoneNum = vClient[3];
	Client.Accbalance = stod(vClient[4]);
	return Client;
}

vector <stClient> LoadClientsDataFromFile(string FileName)
{
	vector <stClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);//read Mode
	if (MyFile.is_open())
	{
		string Line;
		stClient Client;
		while (getline(MyFile, Line))
		{
			Client = ConvertLinetoRecordForClient(Line);
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return vClients;
}

bool FindClientByAccountNumberAndPinCode(string AccountNumber, string PinCode, stClient& Client)
{
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	for (stClient C : vClients)
	{
		if (C.AccNum == AccountNumber && C.pinCode == PinCode)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

string readClientAccNum() {
	string accnum;
	cout << "Enter acc num : \n";
	cin >> accnum;
	return accnum;
}

short readMenuChoice() {
	short choice;
	do {
		cout << "Choose what do you wanna do?[1-5]\n";
		cin >> choice;
	} while (choice < 1 || choice > 5);
	return choice;
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

double ReadDepositAmount()
{
	double Amount;
	cout << "\nEnter a positive Deposit Amount? ";
	cin >> Amount;
	while (Amount <= 0)
	{
		cout << "\nEnter a positive Deposit Amount? ";
		cin >> Amount;
	}
	return Amount;
}

int ReadWithDrawAmont()
{
	int Amount;
	cout << "\nEnter an amount multiple of 5's ? ";
	cin >> Amount;
	while (Amount % 5 != 0)
	{
		cout << "\nEnter an amount multiple of 5's ? ";
		cin >> Amount;
	}
	return Amount;
}

void DepositBalanceByAccNum(string accnum, double amount, vector<stClient>& vClients) {
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

void PerfromDepositOption() {
	double DepositAmount = ReadDepositAmount();
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	DepositBalanceByAccNum(CurrentClient.AccNum,DepositAmount, vClients);
	CurrentClient.Accbalance += DepositAmount;
}

void DepositTransactionScreen() {
	cout << "-------------------------------------------------------\n";
	cout << "\t\t\tDeposit Screen\n";
	cout << "-------------------------------------------------------\n";
	PerfromDepositOption();
	system("pause");
}

void ShowNormalWithDrawScreen()
{
	system("cls");
	cout << "===========================================\n";
	cout << "\t\tNormal Withdraw Screen\n";
	cout << "===========================================\n";
	PerfromNormalWithdrawOption();
}

void PerfromNormalWithdrawOption()
{
	int WithDrawBalance = ReadWithDrawAmont();
	if (WithDrawBalance > CurrentClient.Accbalance)
	{
		cout << "\nThe amount exceeds your balance, make another choice.\n";
		cout << "Press Anykey to continue...";
		system("pause>0");
		ShowNormalWithDrawScreen();
		return;
	}
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	DepositBalanceByAccNum(CurrentClient.AccNum, WithDrawBalance * -1, vClients);
	CurrentClient.Accbalance -= WithDrawBalance;
}

void ShowQuickWithDrawScreen()
{
	system("cls");
	cout << "===========================================\n";
	cout << "\t\tQucik Withdraw\n";
	cout << "===========================================\n";
	cout << "\t[1] 20\t\t[2] 50\n";
	cout << "\t[3] 100\t\t[4] 200\n";
	cout << "\t[5] 400\t\t[6] 600\n";
	cout << "\t[7] 800\t\t[8] 1000\n";
	cout << "\t[9] Exit\n";
	cout << "===========================================\n";
	cout << "Your Balance is " << CurrentClient.Accbalance;
	PerfromQuickWithdrawOption(ReadQuickWithdrawOption());
}

void CheckBalanceSreen() {
	cout << "-------------------------------------------------------\n";
	cout << "\t\t\tShow Balance Screen\n";
	cout << "-------------------------------------------------------\n";
	cout << "Your Accounts Balance is : " << CurrentClient.Accbalance << endl;
	system("pause");
}

void getBackToMenu() {
	system("pause");
	showMenu();
}

short getQuickWithDrawAmount(short QuickWithDrawOption)
{
	switch (QuickWithDrawOption)
	{
	case 1:
		return 20;
	case 2:
		return 50;
	case 3:
		return 100;
	case 4:
		return 200;
	case 5:
		return 400;
	case 6:
		return 600;
	case 7:
		return 800;
	case 8:
		return 1000;
	default:
		return 0;
	}
}

short ReadQuickWithdrawOption()
{
	short Choice = 0;
	while (Choice < 1 || Choice>9)
	{
		cout << "\nChoose what to do from [1] to [9] ? ";
		cin >> Choice;
	}
	return Choice;
}

void PerfromQuickWithdrawOption(short QuickWithDrawOption)
{
	if (QuickWithDrawOption == 9)//exit
		return;
	short WithDrawBalance =
		getQuickWithDrawAmount(QuickWithDrawOption);
	if (WithDrawBalance > CurrentClient.Accbalance)
	{
		cout << "\nThe amount exceeds your balance, make another choice.\n";
		cout << "Press Anykey to continue...";
		system("pause>0");
		ShowQuickWithDrawScreen();
		return;
	}
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	DepositBalanceByAccNum(CurrentClient.AccNum,WithDrawBalance * -1, vClients);
	CurrentClient.Accbalance -= WithDrawBalance;
}


void PerformMenuOption(enMainMenuOptions Choice) {
	switch (Choice)
	{
	case enMainMenuOptions::QuickWithdraw:
		system("cls");
		ShowQuickWithDrawScreen();
		showMenu();
		break;
	case enMainMenuOptions::NormalWithdraw:
		system("cls");
		ShowNormalWithDrawScreen();
		showMenu();
		break;
	case enMainMenuOptions::Deposit:
		system("cls");
		DepositTransactionScreen();
		showMenu();
		break;
	case enMainMenuOptions::CheckBalance:
		system("cls");
		CheckBalanceSreen();
		showMenu();
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
	cout << "[1] Quick Withdraw\n";
	cout << "[2] Normal Withdraw\n";
	cout << "[3] Deposit\n";
	cout << "[4] Check Balance\n";
	cout << "[5] Logout\n";
	cout << "==================================================\n";
	PerformMenuOption(enMainMenuOptions(readMenuChoice()));
}

bool LoadClientInfo(string accnum,string PinCode) {
	return FindClientByAccountNumberAndPinCode(accnum,PinCode,CurrentClient);
}


void Login() {
	bool LoginFailed = false;
	string AccNum, PinCode;

	do {
		cout << "Login Screen\n";
		if (LoginFailed) {
			cout << "Invalid AccNum or PinCode!\n";
		}
		cout << "Enter AccNum:\n";
		cin >> AccNum;
		cout << "Enter PinCode:\n";
		cin >> PinCode;
		LoginFailed = !LoadClientInfo(AccNum, PinCode);
	} while (LoginFailed);

	showMenu();

}
int main() {
	srand((unsigned)time(NULL));
	Login();
	return 0;
}



