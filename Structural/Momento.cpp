#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

class Momento
{
	int balance;
public:
	Momento(int b) :balance(b) {}

	friend class BankAccount;
};

class BankAccount
{
	int balance{ 0 };

public:
	BankAccount(int balance) :balance(balance) {}

	Momento deposit(int amount) {
		balance += amount;
		return {balance};
	}

	void restore(const Momento& m)
	{
		balance = m.balance;
	}

	friend ostream& operator<<(ostream& os, const BankAccount& acc)
	{
		os << "balance: " << acc.balance;
		return os;
	}

};



int main()
{
	
	BankAccount ba{ 100 };
	auto m1 = ba.deposit(50);
	auto m2 = ba.deposit(25);

	cout << ba << "\n";

	ba.restore(m1);
	cout<<"back to m1: " << ba << "\n";
	ba.restore(m2);
	cout << "back to m1: " << ba << "\n";

	

}
