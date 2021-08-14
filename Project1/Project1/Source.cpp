#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
using namespace std;

void delay(int num_of_seconds);
void Login_system();
void Register_system();

/*Tasks as below:
- Login system
- Check whether your input value (account/password) is correct or not.
- Register Account
- Check whether the account is existed or not.
- Check balance in your account.
- Deposit functionality.
- Withdraw functionality.
- Manage data of user.
*/

int main() {
	// Register or Login
	fstream file;
	file.open("Account_List.txt", ios::app);
	file << "------------------------\n";
	file.close();
	string ans_1;
	do {
		string ans;
		system("cls");
		cout << "Hello User, do you have any account ?";
		cout << "\nIf yes, please enter 1";
		cout << "\nIf no, please enter 2";
		cout << "\nYour answer is ";
		cin >> ans;
		if (ans == "1") {
			Login_system();
		}
		else if (ans == "2") {
			Register_system();
		}
		else {
			system("CLS");
			cout << "\nDo you wanna continue ?";
			cout << "\nIf yes, please enter 1";
			cout << "\nIf no, please enter 2";
			cout << "\nYour answer is: ";
			cin >> ans_1;
		}
	} while (ans_1 == "1");
		//num = stoi(ans_1);
	return 0;
}

void Register_system() {
	system("cls");
	string account, pass;
	int cnt = 0;
	fstream file;
	do {
		cout << "**********Register Account**********";
		cout << "\nEnter your account: ";
		cin >> account;
		cout << "\nEnter your password: ";
		cin >> pass;
		file.open("Account_List.txt", ios::in);
		if (file.is_open()) {
			string str;
			// Start check whether this account is existed.
			while (getline(file, str)) {
				if (account == str) {
					cout << "\nThis account is existed. Please try again\n!";
					cnt = 0;
					break;
				}
				else {
					cnt = 1;
				}
			}
			// Stop check whether this account is existed.
		}
		file.close();
	} while (cnt != 1);
	// Start write data to file.
	file.open("Account_List.txt", ios::app);
	if (file.is_open()) {
		file << account << "\n";
		file << pass << "\n";
		file.close();
	}
	// Stop write data to file.
}

void Login_system() {
	system("cls");
	string account, pass;
	fstream file;
	int cnt = 0, opt = 0;
	double balance = 0;
	do {
		cnt = 0;
		cout << "**********LOGIN SYSTEM**********\n";
		cout << "Enter your account: ";
		cin >> account;
		cout << "Enter your password: ";
		cin >> pass;

		// Check whether the account is correct
		file.open("Account_List.txt", ios::in);
		if (file.is_open()) {
			string str;
			while(getline(file, str)) {
				if (str == account) {
					cnt++;
				}
				else if (cnt == 1) {
					if (str == pass) {
						cnt++;
						break;
					}
					else {
						cnt = 0;
					}
				}
				else {
					// nothing to do
				}
			}
		}
		file.close();
		file.open(account, ios::app);
		file << 0;
		file.close();
		system("cls");
		cout << "Login Failed, please try again\n";
		cout << endl << endl;
	} while (cnt != 2);
	system("CLS");
	cout << "Login successful";
	delay(3);
	// Functionality of banking
	system("cls");
	do {
		system("CLS");
		cout << "**********Menu**********\n";
		cout << "1. Check balance\n";
		cout << "2. Deposit\n";
		cout << "3. Withdraw\n";
		cout << "4. Exit\n";
		cout << "Option: ";
		cin >> opt;
		system("cls");
		switch (opt)
		{
		case 1: {
			string str;
			file.open(account, ios::in);
			getline(file, str);
			balance = stod(str);
			cout << "Balance: " << balance << "$";
			delay(5);
			file.close();
			break;
		}
		case 2: {
			double depositAmount;
			string str;
			cout << "Deposit amount: ";
			cin >> depositAmount;
			// Get Data
			file.open(account, ios::in);
			getline(file, str);
			balance = stod(str);
			balance += depositAmount;
			file.close();
			// Save data
			file.open(account, ios::out);
			file << balance;
			file.close();
			break;
		}
		case 3:
			cout << "Withdraw amount: ";
			double withdrawAmount;
			string str;
			cin >> withdrawAmount;
			// Get Data
			file.open(account, ios::in);
			getline(file, str);
			balance = stod(str);
			file.close();
			if (withdrawAmount <= balance) {
				balance -= withdrawAmount;
				// Save Data
				file.open(account, ios::out);
				file << balance;
				file.close();
			}
			else
			{
				cout << "Not enough money" << endl;
				delay(5);
			}
			break;
		}
	} while (opt != 4);
}

void delay(int num_of_seconds) {
	int milli_seconds = 1000 * num_of_seconds;
	clock_t start_time = clock();
	while (clock() < start_time + milli_seconds);
}