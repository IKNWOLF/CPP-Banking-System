#pragma once
#include <iostream>
#include "clsPerson.h"
using namespace std;

class clsEmployee : public clsPerson {

private:

	string _Title;
	string _Department;
	string _Salary;

public:

	clsEmployee(string FirstName, string LastName, string
		Email, string Phone, string Title, string Department, float Salary)
		: clsPerson( FirstName, LastName, Email, Phone)
	{
		_Title = Title;
		_Department = Department;
		_Salary = Salary;
	}

	void SetTitle(string Title) {
		_Title = Title;
	}

	string GetTitle() {
		return _Title;
	}

	void SetDept(string Dept) {
		_Department = Dept;
	}

	string GetDept() {
		return _Department;
	}

	void SetSalary(string Salary) {
		_Salary = Salary;
	}

	string GetSalary() {
		return _Salary;
	}

	void Print() {
		cout << "\nInfo:";
		cout << "\n___________________";
		cout << "\nFirstName : " << GetFirstName();
		cout << "\nLastName : " << GetLastName();
		cout << "\nFull Name : " << clsPerson::FirstName+clsPerson::LastName;
		cout << "\nEmail : " << GetEmail();
		cout << "\nPhone : " << GetPhone();
		cout << "\nTitle : " << _Title;
		cout << "\nDepartment: " << _Department;
		cout << "\nSalary : " << _Salary;
		cout << "\n___________________\n";
	}
};

