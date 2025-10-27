#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
namespace MyLib
{
	void PrintFileContent(string FileName) {
		fstream File;
		File.open(FileName, ios::in);

		if (File.is_open()) 
		{
			string Line;
			while (getline(File, Line)){
				cout << Line << endl;
			}
			File.close();
		}
	}
	void LoadDataFromFileToVector(string FileName, vector <string>& vFileContent) {

		fstream MyFile;
		MyFile.open(FileName, ios::in);

		if (MyFile.is_open()) {
			string Line;

			while (getline(MyFile,Line)) {
				vFileContent.push_back(Line);
			}
			MyFile.close();
		}

	}
	void SaveVectorToFile(string FileName, vector<string> vFileContent) {
		fstream MyFile;

		MyFile.open(FileName, ios::out);

		if (MyFile.is_open()) {
			
			for (string& Line : vFileContent) {

				if(Line!="") MyFile << Line << endl;
			}
			
		}
		MyFile.close();
	}
	void DeleteRecordFromFile(string FileName, string record) {
		vector <string> vFileContent;
		LoadDataFromFileToVector(FileName, vFileContent);

		for (string& Line : vFileContent) {
			if (Line == record) {
				Line = "";
			}
		}

			SaveVectorToFile(FileName, vFileContent);
		

	}
	int RandomNum(int from, int to) {
		return rand() % (to - from + 1) + from;
	}
	void FillMatrixWithRandomNums(int arr[3][3]) {	
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				arr[i][j] = RandomNum(1, 10);
			}
		}
	}
	
	int RowSum(int arr[3][3], int Row) {
		int sum = 0;

		for (short j = 0; j < 3; j++) {
			sum += arr[Row][j];
		}

		return sum;
	}
	void FillArrayWithSums(int arr[3][3],int newarr[3]) {
		for (int i = 0; i < 3; i++) {
			newarr[i] = RowSum(arr, i);
		}
	}
	void PrintSumOfEachRow(int arr[3]) {
		cout << "Summition for each row : \n";
		
		for (int i = 0; i < 3; i++)
		{
			cout << "Row " << i + 1 << " Sum = " << arr[i] << endl;
		}
		

	}
	int colsum(int arr[3][3],int col) {
		int sum = 0;
		
		for (short i = 0; i < 3; i++)
		{
			sum += arr[i][col];
		}
		return sum;
	}
	void FillArrWithColSums(int arr[3][3], int newarr[3]) {
		for (short i = 0; i < 3; i++)
		{
			newarr[i] = colsum(arr, i);
		}
	}
	void PrintColSums(int newarr[3]) {
		cout << "Column sums : " << endl;

		for (short i = 0; i < 3; i++)
		{
			cout << "Col " << (i + 1) << " Sum = " << newarr[i] << endl;
		}
	}

	void FillMatrixWithOrderedNums(int arr[3][3]) {
		int count = 0;
		for (short i = 0; i < 3; i++)
		{
			for (short j = 0; j < 3; j++)
			{
				arr[i][j] = ++count;
			}
		}
	}
	
	void TransposeMatrix(int arr[3][3], int arrTransposed[3][3]) {
		for (short i = 0; i < 3; i++)
		{
			for (short j = 0; j < 3; j++)
			{
				arrTransposed[i][j] = arr[j][i];
			}
		}
	}
	void PrintMatrix(int arr[3][3]) {
	
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cout << setw(3) << arr[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	void FillMultMatrix(int arr1[3][3], int arr2[3][3], int arr3[3][3]) {
		for (short i = 0; i < 3; i++)
		{
			for (short j = 0; j < 3; j++)
			{
				arr3[i][j] = arr1[i][j] * arr2[i][j];
			}
		}
	}
	void PrintMiddleRowOfMatrix(int arr[3][3],int row,int col) {
		short MiddleRow = row / 2;
		for (short j = 0; j < col; j++)
		{
			printf("%0*d", 2, arr[MiddleRow][j]);
		}
	}
	int SumOfMatrix(int matrix[3][3])	 {
		short sum = 0;
		for (short i = 0; i < 3; i++)
		{
			for (short j = 0; j < 3; j++)
			{
				sum += matrix[i][j];
			}
		}
		return sum;
	}
	bool IsBothMatricesEqual(int matrix1[3][3], int matrix2[3][3]) {
		return (SumOfMatrix(matrix1) == SumOfMatrix(matrix2));
	}
	void PrintEqualityOfMatrices(int matrix1[3][3], int matrix2[3][3]) {
		if (IsBothMatricesEqual(matrix1,matrix2)) {
			cout << "Both matrices are equal";
		}
		else cout << "nope";
	}
	bool IsBothMatricesTypical(int matrix1[3][3], int matrix2[3][3]) {
		for (short i = 0; i < 3; i++)
		{
			for (short j = 0; j < 3; j++)
			{
				if (matrix1[i][j] != matrix2[i][j]) {
					return false;
				}
			}
		}
		return true;
	}
	void PrintAreTypicalOrNot(int matrix1[3][3], int matrix2[3][3]) {
		if (IsBothMatricesEqual(matrix1, matrix2)) cout << "Typical";
		else cout << "nope";
	}
	bool checkIfIdentityMatrix(int matrix[3][3]) {
		for (short i = 0; i < 3; i++)
		{
			for (short j = 0;j<3;j++)
			{
				if (i == j && matrix[i][j] != 1) return false;
				else if (i != j && matrix[i][j] != 0) return false;
			}
		}
		return true;
	}
	bool checkIfScalarMatrix(int matrix[3][3]) {
		short num = matrix[0][0];
		for (short i = 0; i < 3; i++)
		{
			for (short j = 0; j < 3; j++)
			{
				if (i == j && matrix[i][j] != num) return false;
				else if (i != j && matrix[i][j] != 0) return false;
			}
		}
		return true;

	}

	short CountNumInMatrix(int matrix[3][3],int num) {
		short cnt = 0;
		for (short i = 0; i < 3; i++)
		{
			for (short j = 0; j < 3; j++)
			{
				if (matrix[i][j] == num) cnt++;
			}
		}
		return cnt;
	}
	bool IsNumInMatrix(int matrix[3][3], int num) {
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (matrix[i][j] == num)return true;
			}
		}
		return false;
	}
	void printIntersectedNumbers(int matrix1[3][3], int matrix2[3][3]) {
		int num;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				num = matrix1[i][j];
				if (IsNumInMatrix(matrix2,num))
				{
					cout << setw(3) << num << " ";
				}
			}
		}
	}
	
	bool isPalindromeMatrix(int matrix[3][3],int rows,int cols) {
		
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols/2; j++)
			{
				if (matrix[i][j] != matrix[i][cols - j - 1]) return false;
			}
		
		}
		return true;
	}
	void fib(int num, int a = 0, int b = 1) {
		
		if (num <= 0)return;
		cout << b << " ";

		fib(--num, b, a + b);

	}
	string ReadString() {
		string s;
		cout << "Enter the sentence: \n";
		getline(cin, s);
		return s;
	}
	void printFirstLetterInEachWord(string s) {
		bool isFirstLetter = true;
		for (int i = 0; i < s.length(); i++)
		{
			if (s[i] != ' ' && isFirstLetter) cout << s[i] << endl;
			isFirstLetter = (s[i] == ' ' ? true : false);
		}
	}
	string UpperFirstLetterInEachWord(string s) {
		bool isFirstLetter = true;
		for (int i = 0; i < s.length(); i++)
		{
			if (s[i] != ' ' && isFirstLetter) s[i] = toupper(s[i]);

			isFirstLetter = (s[i] == ' ' ? true : false);
		}
		return s;
	}
	string LowerFirstLetterInEachWord(string s) {
		bool isFirstLetter = true;
		for (int i = 0; i < s.length(); i++)
		{
			if (s[i] != ' ' && isFirstLetter) s[i] = tolower(s[i]);

			isFirstLetter = (s[i] == ' ' ? true : false);
		}
		return s;
	}
	char invertChar(char c) {
		return isupper(c) ? tolower(c) : toupper(c);
	}
	string convertAllLetters(string s) {
		for (short i = 0; i < s.length(); i++)
		{
			s[i] = invertChar(s[i]);
		}
		return s;
	}
	enum enWhatToCount
	{
		Smallletters = 0,
		Capitalletters =1,
		All=2
	};
	short CountLetters(string s, enWhatToCount WhattoCount = enWhatToCount::All) {

		if (WhattoCount == enWhatToCount::All) {
			return s.length();
		}
		short cnt = 0;

		for (short i = 0; i < s.length(); i++)
		{
			if (WhattoCount == enWhatToCount::Capitalletters && isupper(s[i])) cnt++;
			if (WhattoCount == enWhatToCount::Smallletters && islower(s[i])) cnt++;
		}
		return cnt;
	}
	short CountALetterInAString(string s, char c,bool matchCase = true) {
		short cnt = 0;
		for (short i = 0; i < s.length(); i++)
		{
			if (matchCase)
			{
				if (s[i] == c) cnt++;
			}
			else
			{
				if (tolower(s[i]) == tolower(c)) cnt++;
			}
		}
		return cnt;
	}
	char ReadChar() {
		char c;
		cout << "Enter a Character : \n";
		cin >> c;
		return c;
	}
	bool isVowel(char letter) {
		return (letter == 'a' || letter == 'o' || letter == 'e' || letter == 'i' || letter == 'u');
	}
	void printEachWordInAString(string s) {
		for (short i = 0; i < s.length(); i++)
		{
			if (s[i] != ' ') cout << s[i];
			else cout << endl;
		}
	}
	void printEachWordInAStringUsingSubString(string s) {
		string delim = " ";

		cout << "\n Your String Words are: \n\n";
		short pos = 0;
		string sWord;

		while ((pos=s.find(delim)) != string::npos)
		{
			sWord = s.substr(0, pos); // hi my name is abdo
			if (sWord != "") {
				cout << sWord << endl;
			}
			s.erase(0, pos + delim.length());
		}

		if (s != "") {
			cout << s << endl;
		}

	}
	vector<string> splitString(string s,string delim) {
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
	string trimLeft(string s) {
		for (short i = 0; i < s.length(); i++)
		{
			if (s[i] != ' ') {
				return s.substr(i, s.length() - i); // "   abdo"
			}
		}
		return "";
	}
	string trimRight(string s) {
		for (short i = s.length() - 1; i >= 0; i--)
		{
			if (s[i] != ' ') {
				return s.substr(0,i+1); // "abdo    "
			}
		}
		return "";
	}
	string trim(string s) {
		return (trimLeft(trimRight(s)))	;
	}
	string JoinVector(vector<string> vString, string delim) {
	
		string S = "";

		for (string& s : vString) {
			S = S + s + delim;
		 }

		return S.substr(0,S.length()-delim.length());
	}
	string JoinVector(string vString[],short length, string delim) {
		string s;
		for (short i = 0; i < length;i++) {
			s += vString[i] + delim;
		}
		return s.substr(0,s.length()-delim.length());
	}
	string ReverseWordsInString(string s) {
		vector<string> vString;
		string S2 = "";
		vString = splitString(s, " ");

		vector<string>::iterator iter = vString.end();

		while (iter!=vString.begin())
		{
			--iter;

			S2 += *iter + " ";			
		}
		S2 = S2.substr(0, S2.length() - 1);
		return S2;

	}
	string ReplaceWordInString(string s, string wordToReplace, string newWord) {
		short pos = s.find(wordToReplace);

		while (pos!=string::npos)
		{
			s = s.replace(pos, wordToReplace.length(), newWord);
			pos = s.find(wordToReplace);
		}
		return s;
	}
	string replacewordinstring(string s, string wordtoreplace, string newword) {
		vector<string> vString;

		vString = splitString(s, " ");

		vector<string>::iterator iter = vString.begin();

		while (iter!=vString.end())
		{
			if (*iter == wordtoreplace) {
				*iter = newword;
			}
			iter++;
		}

		return JoinVector(vString," ");
	}
	string LowerAllString(string s) {
		for (short i = 0; i < s.length(); i++)
		{
			s[i] = tolower(s[i]);
		}
		return s;

	}
	string RemovePunctuationsFromString(string S1)
	{
		string S2 = "";
		for (short i = 0; i < S1.length(); i++)
		{
			if (!ispunct(S1[i]))
			{
				S2 += S1[i];
			}
		}
		return S2;
	}
	string NumToText(int num) {

		if (num == 0) {
			return "";
		}

		if (num >= 1 && num <= 19) {
			string arr[] = { "","One","Two" ,"Three" ,"Four" ,"Five" ,
				"Six" ,"Seven" ,"Eight" ,"Nine" ,"Ten" ,"Eleven" ,"Twelve" ,"Thirteen" ,
				"Fourteen" ,"Fifteen" ,"Sixteen" ,"Seventeen" ,"Eighteen" ,"Nineteen" };

			return arr[num] + " ";
		}

		if (num >= 20 && num <= 99) {
			string arr[] = { "","","Twenty","Thirty" ,"Fourty" ,"Fifty" ,"Sixty" ,
				"Seventy" ,"Eighty" ,"Ninty" ,"Twenty" };

			return arr[num / 10] + NumToText(num % 10);
		}

		if (num >= 100 && num <= 199) {
			return "One Hundered " + NumToText(num % 100);
		}

		if (num >= 200 && num <= 999) {
			return NumToText(num / 100) + "Hundred " + NumToText(num % 100);
		}

		if (num >= 1000 && num <= 1999) {
			return "One Thousand " + NumToText(num % 1000);
		}

		if (num >= 2000 && num <= 999999) {
			return NumToText(num / 1000) + "Thousand " + NumToText(num % 1000);
		}

		if (num >= 1000000 && num <= 1999999)
		{
			return "One Million " + NumToText(num % 1000000);
		}
		if (num >= 2000000 && num <= 999999999)
		{
			return NumToText(num / 1000000) + "Millions " +
				NumToText(num % 1000000);
		}
		if (num >= 1000000000 && num <= 1999999999)
		{
			return "One Billion " + NumToText(num % 1000000000);
		}

		else
		{
			return NumToText(num / 1000000000) + "Billions " +
				NumToText(num % 1000000000);
		}

	}

	struct sDate {
		short year;
		short month;
		short day;
	};

	bool IsLeapYear(int Year) {

		return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
	}

	short NumOfDaysInYear(short Year) {
		return (IsLeapYear ? 366 : 365);
	}

	int NumOfHoursInYear(short Year) {
		return NumOfDaysInYear(Year) * 24;
	}

	int NumOfminsInYear(short Year) {
		return NumOfHoursInYear(Year) * 60;
	}

	int NumOfSecsInYear(short Year) {
		return NumOfminsInYear(Year) * 60;
	}

	int NumOfDaysInMonth(short year, short month) {

		if (month > 12 || month < 1)
		{
			return 0;
		}

		int NumOfDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

		return (month == 2) ? (IsLeapYear(year) ? 29 : 28) : NumOfDays[month - 1];
	}

	int NumOfHoursInMonth(short year, short month) {
		return NumOfDaysInMonth(year, month) * 24;
	}

	int NumOfMinsInMonth(short year, short month) {
		return NumOfHoursInMonth(year, month) * 60;
	}

	int NumOfSecsInMonth(short year, short month) {
		return NumOfMinsInMonth(year, month) * 60;
	}

	short ReadDay() {
		short day;
		cout << "Enter a day:\n";
		cin >> day;
		return day;
	}

	short ReadMonth() {
		short day;
		cout << "Enter a Month:\n";
		cin >> day;
		return day;
	}

	short ReadYear() {
		short Year;
		cout << "Enter a Year:\n";
		cin >> Year;
		return Year;
	}


	short DayOfWeekOrder(short year, short month, short day = 1) {

		short a = floor((14 - month) / 12);

		short y = year - a;

		short m = month + 12 * a - 2;

		return (day + y + (y / 4) - (y / 100) + (y / 400) + (31 * m) / 12) % 7;
	}

	short DayOfWeekOrder(sDate date) {
		return (DayOfWeekOrder(date.year, date.month, date.day));
	}

	string DayName(short day) {
		string DayName[7] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
		return DayName[day];
	}

	string MonthName(short MonthNum) {
		string Months[13] = { "","Jan","Feb","Mars","April","May","June","July","Aug","Sep","Oct","Nov","Dec" };

		return Months[MonthNum];
	}

	void PrintMonthCalender(short year, short month) {

		int NumOfDays;

		int current = DayOfWeekOrder(year, month);

		NumOfDays = NumOfDaysInMonth(year, month);

		printf("\n________________%s________________\n\n", MonthName(month).c_str());

		printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

		int i;

		for (i = 0; i < current; i++) printf("     ");

		for (int j = 1; j <= NumOfDays; j++)
		{
			printf("%5d", j);

			if (++i == 7)
			{
				i = 0;
				printf("\n");
			}
		}

		printf("\n___________________________________\n");
	}

	void PrintYearCalender(short year) {

		printf("\n___________________________________\n");
		printf("\n___________Calender: %d__________\n", year);
		printf("\n___________________________________\n");

		for (short i = 1; i <= 12; i++)
		{
			PrintMonthCalender(year, i);
			cout << endl;
		}
	}

	short NumOfDaysFromBeginningOfTheYear(short year, short month, short day) {
		short TotalDays = 0;

		for (short i = 1; i <= month - 1; i++)
		{
			TotalDays += NumOfDaysInMonth(year, i);
		}

		TotalDays += day;

		return TotalDays;
	}


	sDate DateAddDays(short Days, sDate Date) {

		short RemainingDays = Days + NumOfDaysFromBeginningOfTheYear(Date.day, Date.month, Date.year);
		short MonthDays = 0;
		Date.month = 1;

		while (true)
		{
			MonthDays = NumOfDaysInMonth(Date.month, Date.year);
			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date.month++;
				if (Date.month > 12)
				{
					Date.month = 1;
					Date.year++;
				}
			}
			else
			{
				Date.day = RemainingDays;
				break;
			}
		}
		return Date;
	}

	bool IsDate1BeforeDate2(sDate date1, sDate date2) {
		return	(date1.year < date2.year) ? true : ((date1.year == date2.year) ? (date1.month < date2.month) ? true : ((date1.month == date2.month) ? date1.day < date2.day : false) : false);
	}

	sDate ReadFullDate() {
		sDate date;

		date.day = ReadDay();
		date.month = ReadMonth();
		date.year = ReadYear();

		return date;
	}

	bool IsDate1EqualDate2(sDate date1, sDate date2) {
		return (date1.day == date2.day) ? ((date1.month == date2.month) ? (date1.year == date2.year) : false) : false;
	}

	bool LastDayInMonth(sDate date) {

		return date.day == NumOfDaysInMonth(date.year, date.month);

	}

	bool LastMonthInYear(short month) {
		return month == 12;
	}

	bool IsDate1AfterDate2(sDate date1, sDate date2) {
		return(!IsDate1BeforeDate2(date1, date2) && !IsDate1EqualDate2(date1, date2));
	}

	sDate addOneDay(sDate& date) {

		if (LastMonthInYear(date.month))
		{
			if (NumOfDaysInMonth(date.year, date.month) == date.day)
			{
				date.year += 1;
				date.month = 1;
				date.day = 1;
			}
		}

		else if (NumOfDaysInMonth(date.year, date.month) == date.day) {
			date.day = 1;
			date.month += 1;
		}
		else date.day += 1;

		return date;
	}

	void SwapDates(sDate& Date1, sDate& Date2)
	{
		sDate TempDate;
		TempDate.year = Date1.year;
		TempDate.month = Date1.month;
		TempDate.day = Date1.day;
		Date1.year = Date2.year;
		Date1.month = Date2.month;
		Date1.day = Date2.day;
		Date2.year = TempDate.year;
		Date2.month = TempDate.month;
		Date2.day = TempDate.day;
	}

	int GetDifferenceInDays(sDate Date1, sDate Date2, bool IncludeEndDay = false)
	{

		int Days = 0;
		short SwapFlagValue = 1;

		if (!IsDate1BeforeDate2(Date1, Date2))
		{
			//Swap Dates
			SwapDates(Date1, Date2);
			SwapFlagValue = -1;
		}

		while (IsDate1BeforeDate2(Date1, Date2))
		{
			Days++;
			Date1 = addOneDay(Date1);
		}
		return IncludeEndDay ? ++Days * SwapFlagValue : Days * SwapFlagValue;
	}

	sDate GetSystemDate() {
		time_t now = time(0);
		tm localTime;
		localtime_s(&localTime, &now); // safe version of localtime

		sDate date;
		date.day = static_cast<short>(localTime.tm_mday);
		date.month = static_cast<short>(localTime.tm_mon + 1); // tm_mon is 0-based
		date.year = static_cast<short>(localTime.tm_year + 1900); // tm_year is years since 1900

		return date;
	}

	sDate IncreaseDateByOneDay(sDate Date)
	{
		if (LastDayInMonth(Date))
		{
			if (LastMonthInYear(Date.month))
			{
				Date.month = 1;
				Date.day = 1;
				Date.year++;
			}
			else
			{
				Date.day = 1;
				Date.month++;
			}
		}
		else
		{
			Date.day++;
		}
		return Date;
	}
	sDate IncreaseDateByOneWeek(sDate Date)
	{
		for (int i = 1; i <= 7; i++)
		{
			Date = IncreaseDateByOneDay(Date);
		}
		return Date;
	}
	sDate IncreaseDateByXWeeks(short Weeks, sDate Date)
	{
		for (short i = 1; i <= Weeks; i++)
		{
			Date = IncreaseDateByOneWeek(Date);
		}
		return Date;
	}

	sDate IncreaseDateByOneMonth(sDate Date)
	{
		if (Date.month == 12)
		{
			Date.month = 1;
			Date.year++;
		}
		else
		{
			Date.month++;
		}

		short NumberOfDaysInCurrentMonth =
			NumOfDaysInMonth(Date.month, Date.year);
		if (Date.day > NumberOfDaysInCurrentMonth)
		{
			Date.day = NumberOfDaysInCurrentMonth;
		}
		return Date;
	}
	sDate IncreaseDateByXDays(short Days, sDate Date)
	{
		for (short i = 1; i <= Days; i++)
		{
			Date = IncreaseDateByOneDay(Date);
		}
		return Date;
	}
	sDate IncreaseDateByXMonths(short Months, sDate Date)
	{
		for (short i = 1; i <= Months; i++)
		{
			Date = IncreaseDateByOneMonth(Date);
		}
		return Date;
	}

	sDate IncreaseDateByOneYear(sDate Date)
	{
		Date.year++;
		return Date;
	}
	sDate IncreaseDateByXYears(short Years, sDate Date)
	{
		for (short i = 1; i <= Years; i++)
		{
			Date = IncreaseDateByOneYear(Date);
		}
		return Date;
	}
	sDate IncreaseDateByXYearsFaster(short Years, sDate Date)
	{
		Date.year += Years;
		return Date;
	}
	sDate IncreaseDateByOneDecade(sDate Date)
	{
		//Period of 10 years
		Date.year += 10;
		return Date;
	}
	sDate IncreaseDateByXDecades(short Decade, sDate Date)
	{
		for (short i = 1; i <= Decade * 10; i++)
		{
			Date = IncreaseDateByOneYear(Date);
		}
		return Date;
	}
	sDate IncreaseDateByXDecadesFaster(short Decade, sDate Date)
	{
		Date.year += Decade * 10;
		return Date;
	}

	sDate IncreaseDateByOneCentury(sDate Date)
	{
		//Period of 100 years
		Date.year += 100;
		return Date;
	}
	sDate IncreaseDateByOneMillennium(sDate Date)
	{
		//Period of 1000 years
		Date.year += 1000;
		return Date;
	}

	sDate DecreaseDateByOneDay(sDate Date)
	{
		if (Date.day == 1)
		{
			if (Date.month == 1)
			{
				Date.month = 12;
				Date.day = 31;
				Date.year--;
			}
			else
			{
				Date.month--;
				Date.day = NumOfDaysInMonth(Date.month, Date.year);
			}
		}
		else
		{
			Date.day--;
		}
		return Date;
	}
	sDate DecreaseDateByOneWeek(sDate Date)
	{
		for (int i = 1; i <= 7; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}
	sDate DecreaseDateByXWeeks(short Weeks, sDate Date)
	{
		for (short i = 1; i <= Weeks; i++)
		{
			Date = DecreaseDateByOneWeek(Date);
		}
		return Date;
	}

	sDate DecreaseDateByOneMonth(sDate Date)
	{
		if (Date.month == 1)
		{
			Date.month = 12;
			Date.year--;
		}
		else Date.month--;

		short NumberOfDaysInCurrentMonth =
			NumOfDaysInMonth(Date.month, Date.year);
		if (Date.day > NumberOfDaysInCurrentMonth)
		{
			Date.day = NumberOfDaysInCurrentMonth;
		}
		return Date;
	}
	sDate DecreaseDateByXDays(short Days, sDate Date)
	{
		for (short i = 1; i <= Days; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}
	sDate DecreaseDateByXMonths(short Months, sDate Date)
	{
		for (short i = 1; i <= Months; i++)
		{
			Date = DecreaseDateByOneMonth(Date);
		}
		return Date;
	}

	sDate DecreaseDateByOneYear(sDate Date)
	{
		Date.year--;
		return Date;
	}
	sDate DecreaseDateByXYears(short Years, sDate Date)
	{
		for (short i = 1; i <= Years; i++)
		{
			Date = DecreaseDateByOneYear(Date);
		}
		return Date;
	}
	sDate DecreaseDateByXYearsFaster(short Years, sDate Date)
	{
		Date.year -= Years;
		return Date;
	}
	sDate DecreaseDateByOneDecade(sDate Date)
	{
		//Period of 10 years
		Date.year -= 10;
		return Date;
	}
	sDate DecreaseDateByXDecades(short Decade, sDate Date)
	{
		for (short i = 1; i <= Decade * 10; i++)
		{
			Date = DecreaseDateByOneYear(Date);
		}
		return Date;
	}
	sDate DecreaseDateByXDecadesFaster(short Decade, sDate Date)
	{
		Date.year -= Decade * 10;
		return Date;
	}

	sDate DecreaseDateByOneCentury(sDate Date)
	{
		//Period of 100 years
		Date.year -= 100;
		return Date;
	}
	sDate DecreaseDateByOneMillennium(sDate Date)
	{
		//Period of 1000 years
		Date.year -= 1000;
		return Date;
	}

	bool isEndOfWeek(sDate date) {
		return DayOfWeekOrder(date) == 6;
	}

	bool isWeekEnd(sDate date) {
		short dayIndex = DayOfWeekOrder(date);
		return (dayIndex == 5 || dayIndex == 6);
	}

	bool isBusinessDay(sDate date) {
		return !isWeekEnd(date);
	}

	short DaysUntilTheEndOfWeek(sDate date) {
		return (6 - DayOfWeekOrder(date));
	}

	short DaysUntilTheEndOfMonth(sDate date) {
		sDate EndOfMonth;

		EndOfMonth.day = NumOfDaysInMonth(date.year, date.month);
		EndOfMonth.month = date.month;
		EndOfMonth.year = date.year;

		return GetDifferenceInDays(date, EndOfMonth, true);

	}

	short DaysUntilTheEndOfYear(sDate date) {
		sDate EndOfMonth;

		EndOfMonth.day = 31;
		EndOfMonth.month = 12;
		EndOfMonth.year = date.year;

		return GetDifferenceInDays(date, EndOfMonth, true);

	}

	short NumOfVacationDays(sDate start, sDate end) {
		short days = 0;
		while (IsDate1BeforeDate2(start, end))
		{
			if (isBusinessDay(start)) {
				days++;
			}
			start = IncreaseDateByOneDay(start);
		}
		return days;
	}

	sDate VacationReturnDate(sDate& StartDate, short VacDays = 4) {

		short WeekEndCnt = 0;

		for (short i = 1; i <= VacDays + WeekEndCnt; i++)
		{
			if (isWeekEnd(StartDate))
			{
				WeekEndCnt++;
			}
			StartDate = IncreaseDateByOneDay(StartDate);
		}

		while (isWeekEnd(StartDate))
		{
			StartDate = IncreaseDateByOneDay(StartDate);
		}
		return StartDate;
	}

	enum enDateCompare { Before = -1, Equal = 0, After = 1 };
	enDateCompare CompareDates(sDate Date1, sDate Date2)
	{
		if (IsDate1BeforeDate2(Date1, Date2)) return enDateCompare::Before;
		if (IsDate1EqualDate2(Date1, Date2)) return enDateCompare::Equal;
		return enDateCompare::After;
	}


	struct stPeriod {
		sDate StartDate;
		sDate EndDate;
	};

	stPeriod ReadPeriod() {
		stPeriod period;
		cout << "Enter Start Date:\n";
		period.StartDate = ReadFullDate();
		cout << "Enter End Date:\n";
		period.EndDate = ReadFullDate();
		return period;
	}

	bool IsOverLapPeriods(stPeriod period1, stPeriod period2) {
		if (
			CompareDates(period2.EndDate, period1.StartDate) == enDateCompare::Before
			||
			CompareDates(period1.StartDate, period2.EndDate) == enDateCompare::After
			)
			return false;
		else
			return true;
	}

	int PeriodLengthInDays(stPeriod period, bool includeLastDay = false) {
		return GetDifferenceInDays(period.StartDate, period.EndDate, includeLastDay);
	}

	bool IsDateWithinPeriod(stPeriod period, sDate date) {
		return !(CompareDates(date, period.StartDate) == enDateCompare::Before
			||
			CompareDates(period.StartDate, date) == enDateCompare::After);
	}

	int CountOverlapDays(stPeriod Period1, stPeriod Period2)
	{
		int Period1Length = PeriodLengthInDays(Period1, true);
		int Period2Length = PeriodLengthInDays(Period2, true);
		int OverlapDays = 0;
		if (!IsOverLapPeriods(Period1, Period2))
			return 0;
		if (Period1Length < Period2Length)
		{
			while (IsDate1BeforeDate2(Period1.StartDate, Period1.EndDate))
			{
				if (IsDateWithinPeriod(Period2, Period1.StartDate)) OverlapDays++;
				Period1.StartDate = IncreaseDateByOneDay(Period1.StartDate);
			}
		}
		else
		{
			while (IsDate1BeforeDate2(Period2.StartDate, Period2.EndDate))
			{
				if (IsDateWithinPeriod(Period1, Period2.StartDate)) OverlapDays++;
				Period2.StartDate = IncreaseDateByOneDay(Period2.StartDate);
			}
		}
		return OverlapDays;
	}

	bool IsValidDate(sDate date) {
		if (date.day > 31 || date.day < 28) return false;
		if (date.month > 12 || date.month < 1) return false;
		if (date.day > NumOfDaysInMonth(date.year, date.month)) return false;
		return true;
	}

	string ReadDateString(string msg) {
		string datestring;

		cout << msg << endl;
		getline(cin >> ws, datestring);

		return datestring;
	}

	sDate StringtoDate(string datestring) {
		sDate date;
		vector<string>vDate;

		vDate = splitString(datestring, "/");
		date.day = stoi(vDate[0]);
		date.month = stoi(vDate[1]);
		date.year = stoi(vDate[2]);

		return date;
	}

	string DatetoString(sDate date) {
		return to_string(date.day) + "/" + to_string(date.month) + "/" + to_string(date.year);
	}

	string FormatDate(sDate date, string dateformat = "dd/mm/yyyy") {
		string FormattedDateString = "";

		FormattedDateString = replacewordinstring(dateformat, "dd", to_string(date.day));
		FormattedDateString = replacewordinstring(dateformat, "mm", to_string(date.month));
		FormattedDateString = replacewordinstring(dateformat, "yyyy", to_string(date.year));

		return FormattedDateString;
	}

	}

	
	

