#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

struct BankAccount
{
	int balance{ 0 };
	int overdraft_limit{ -500 };
	
	void deposit(int amount) {
		balance += amount;
		cout << "deposted " << amount << ", balance is now balance" << endl;
	}

	void withdraw(int amount) {
		if (balance - amount >= overdraft_limit)
		{
			balance -= amount;

			cout << "withdrew " << amount
				<< ", balance is now " << balance << endl;
		}
	}

	friend ostream& operator<<(ostream& cout, BankAccount& acc)
	{
		cout << "balance: " << acc.balance << endl;
		return cout;
	}

};

struct Command
{
	virtual void call() = 0;
};

struct BankAccountCommand :Command
{
	BankAccount& account;
	enum Action {deposit, withdraw} action;
	int amount;

	BankAccountCommand(BankAccount &acc, Action act, int a)
		:account{ acc }, action{ act },amount{ a }{}

	void call() override {
		switch (action)
		{
		case deposit:
			account.deposit(amount);
			break;

		case withdraw:
			account.withdraw(amount);
			break;
		}
	}



};

int main()
{
	BankAccount ba;
	vector<BankAccountCommand> commands
	{
		BankAccountCommand{ba,BankAccountCommand::deposit, 100},
		BankAccountCommand{ba,BankAccountCommand::withdraw, 200},
	};

	cout << ba;

	for (auto& cmd : commands)
	{
		cmd.call();
	}
	cout << ba;



}
