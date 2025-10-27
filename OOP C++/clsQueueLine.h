#pragma once
using namespace std;
#include <queue>
#include <stack>
#include <string>
#include "clsDate.h"
class clsQueueLine
{
private:

	short _TotalTickets = 0;
	short _WaitingTime = 0;
	string _Prefix = "";


	class clsTicket {

	private:

		string _Prefix;
		string _FullNum;
		short _Number = 0;
		short _ServedClients = 0;
		short _WaitingClients = 0;
		short _WaitingTime = 0;
		string _TicketDate;

	public:

		clsTicket(string prefix, short number, short waitingtime, short waitingclients) {
			_Prefix = prefix;
			_Number = number;
			_WaitingTime = waitingtime;
			_WaitingClients = waitingclients;
			_TicketDate = clsDate::GetSystemDateInString();
		}

		string FullNum() {
			return _Prefix + to_string(_Number);
		}

		short ExpectedServeTime() {
			return _WaitingClients * _WaitingTime;
		}


		void Print() {
			cout << "\n\t\t\t  _______________________\n";
			cout << "\n\t\t\t\t    " << FullNum();
			cout << "\n\n\t\t\t    " << _TicketDate;
			cout << "\n\t\t\t    Wating Clients = " << _WaitingClients;
			cout << "\n\t\t\t      Serve Time In";
			cout << "\n\t\t\t       " << ExpectedServeTime() << " Minutes.";
			cout << "\n\t\t\t  _______________________\n";

		}
	};


public:

	queue <clsTicket> QueueLine;

	clsQueueLine(string prefix, short waitingtime) {

		_Prefix = prefix;
		_WaitingTime = waitingtime;

	}

	void IssueTicket() {

		_TotalTickets++;
		clsTicket Ticket(_Prefix, _TotalTickets, _WaitingTime, WaitingClients());
		QueueLine.push(Ticket);

	}


	short WaitingClients() {
		return QueueLine.size();
	}

	string WhoIsNext() {
		if (QueueLine.empty())
		{
			return "No Clients Left.";
		}
		else
		{
			return QueueLine.front().FullNum();
		}
	}

	bool ServeNextClient() {
		if (QueueLine.empty())
		{
			return false;
		}
		else
		{
			QueueLine.pop();
			return true;
		}
	}

	short ServedClients() {
		return _TotalTickets - WaitingClients();
	}


	void PrintInfo() {
		cout << "\n\t\t\t _________________________\n";
		cout << "\n\t\t\t\tQueue Info";
		cout << "\n\t\t\t _________________________\n";
		cout << "\n\t\t\t    Prefix   = " << _Prefix;
		cout << "\n\t\t\t    Total Tickets   = " << _TotalTickets;
		cout << "\n\t\t\t    Served Clients  = " << ServedClients();
		cout << "\n\t\t\t    Wating Clients  = " << WaitingClients(); ;
		cout << "\n\t\t\t _________________________\n";
		cout << "\n";
	}

	void PrintTicketsLineRTL() {
		queue<clsTicket> TempQueue = QueueLine;

		while (!TempQueue.empty())
		{
			clsTicket Ticket = TempQueue.front();
			cout << Ticket.FullNum() << " <-- ";
			TempQueue.pop();
		}
		cout << "\n";
	}

	void PrintTicketsLineLTR() {
		queue<clsTicket> TempQueue = QueueLine;
		stack<clsTicket> TempStack;

		while (!TempQueue.empty())
		{
			TempStack.push(TempQueue.front());
			TempQueue.pop();
		}

		while (!TempStack.empty())
		{
			clsTicket Ticket = TempStack.top();
			cout << Ticket.FullNum() << " --> ";
			TempStack.pop();
		}
		cout << "\n";
	}

	void PrintAllTickets() {

		cout << "\n\n\t\t\t       ---Tickets---";

		if (QueueLine.empty())
			cout << "\n\n\t\t\t     ---No Tickets---\n";

		queue <clsTicket> TempQueueLine = QueueLine;


		while (!TempQueueLine.empty())
		{
			TempQueueLine.front().Print();
			TempQueueLine.pop();
		}

	}

};
