#include<iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

const string ClientsFileName = "Clients.txt";

void ShowMainMenue();
void ShowTransaction();

enum enMainMenueOptions
{
	eListClients = 1,
	eAddNewClient = 2,
	eDeleteClient = 3,
	eUpdateClient = 4,
	eFindClient = 5,
	eTransaction = 6,
	eExit = 7
};

enum enTransactionOption { eDeposite = 1, eWithDraw = 2, eTotalBalnce = 3, eMainMenu = 4 };

enum enTransactionType { eDepositTransaction = 1, eWithDrawTransaction = 2 };

struct sClient {
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};

short ReadMainMenueOption()
{
	cout << "Choose what do you want to do ? [1 to 7] ? ";
	short Choice = 0;
	cin >> Choice;
	return Choice;
}

void GoBackToMainMenue()
{
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	ShowMainMenue();
}

vector<string> SplitString(string S1, string Delim)
{
	vector<string> vString;
	short pos = 0;
	string sWord; // define a string variable
	// use find() function to get the position of the delimiters
	while ((pos = S1.find(Delim)) != std::string::npos)
	{
		sWord = S1.substr(0, pos); // store the word
		if (sWord != "")
		{
			vString.push_back(sWord);
		}
		S1.erase(0, pos + Delim.length()); /* erase() until
		positon and move to next word. */
	}
	if (S1 != "")
	{
		vString.push_back(S1); // it adds last word of the string.
	}
	return vString;
}

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{
	sClient Client;
	vector<string> vClientData;
	vClientData = SplitString(Line, Seperator);
	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);//cast string to double
	return Client;
}

vector <sClient> LoadCleintsDataFromFile(string FileName)
{
	vector <sClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);//read Mode

	if (MyFile.is_open())
	{
		string Line;
		sClient Client;
		while (getline(MyFile, Line))
		{
			Client = ConvertLinetoRecord(Line);
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return vClients;
}

void PrintClientRecordLine(sClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}

void ShowAllClientsScreen()
{
	vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	if (vClients.size() == 0)
		cout << "\t\t\t\tNo Clients Available In the System!";
	else
		for (const sClient& Client : vClients)
		{
			PrintClientRecordLine(Client);
			cout << endl;
		}

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}

bool ClientExistsByAccountNumber(const string& AccountNumber, string FileName) {

	vector <sClient> vClients;
	fstream MyFile;
	
	MyFile.open(FileName, ios::in);//read Mode
	if (MyFile.is_open())
	{
		string Line;
		sClient Client;
		
		while (getline(MyFile, Line))
		{
			Client = ConvertLinetoRecord(Line);
			if (Client.AccountNumber == AccountNumber)
			{
				MyFile.close();
				return true;
			}
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return false;
}

sClient ReadNewClient()
{
	sClient Client;
	cout << "Enter Account Number? ";
	// Usage of std::ws will extract allthe whitespace character
	getline(cin >> ws, Client.AccountNumber);

	while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
	{
		cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number ? ";
		getline(cin >> ws, Client.AccountNumber);
	}
	cout << "Enter PinCode? ";
	getline(cin, Client.PinCode);
	cout << "Enter Name? ";
	getline(cin, Client.Name);
	cout << "Enter Phone? ";
	getline(cin, Client.Phone);
	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;
	return Client;
}

void AddDataLineToFile(string FileName, string stDataLine)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);
	
	if (MyFile.is_open())
	{
		MyFile << stDataLine << endl;
		MyFile.close();
	}
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{
	string stClientRecord = "";
	stClientRecord += Client.AccountNumber + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.Name + Seperator;
	stClientRecord += Client.Phone + Seperator;
	stClientRecord += to_string(Client.AccountBalance);
	return stClientRecord;
}

void AddNewClient()
{
	sClient Client;
	Client = ReadNewClient();
	AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
}

void AddNewClients()
{
	char AddMore = 'Y';
	do
	{
		//system("cls");
		cout << "Adding New Client:\n\n";
		AddNewClient();
		cout << "\nClient Added Successfully, do you want to add more clients ? Y / N ? ";
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}

void ShowAddNewClientsScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tAdd New Clients Screen";
	cout << "\n-----------------------------------\n";

	AddNewClients();
}


vector <sClient> SaveCleintsDataToFile(string FileName, vector <sClient> vClients)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);//overwrite
	string DataLine;
	
	if (MyFile.is_open())
	{
		for (const sClient& C : vClients)
		{
			if (C.MarkForDelete == false)
			{
				//we only write records that are not marked for delete.
				DataLine = ConvertRecordToLine(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	return vClients;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
	for (sClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

bool FindClientByAccountNumber(const string& AccountNumber, const vector <sClient>& vClients, sClient& Client)
{
	for (sClient C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}


void PrintClientCard(const sClient& Client)
{
	cout << "\nThe following are the client details:\n";
	cout << "-----------------------------------";
	cout << "\nAccout Number: " << Client.AccountNumber;
	cout << "\nPin Code : " << Client.PinCode;
	cout << "\nName : " << Client.Name;
	cout << "\nPhone : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.AccountBalance;
	cout << "\n-----------------------------------\n";
}

bool DeleteClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
	sClient Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);
		cout << "\n\nAre you sure you want delete this client? y/n ? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveCleintsDataToFile(ClientsFileName, vClients);

			//Refresh Clients
			vClients = LoadCleintsDataFromFile(ClientsFileName);
			cout << "\n\nClient Deleted Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
		return false;
	}
}

string ReadClientAccountNumber()
{
	string AccountNumber = "";
	cout << "\nPlease enter AccountNumber? ";
	cin >> AccountNumber;
	return AccountNumber;
}

void ShowDeleteClientScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tDelete Client Screen";
	cout << "\n-----------------------------------\n";

	vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	DeleteClientByAccountNumber(AccountNumber, vClients);
}

sClient ChangeClientRecord(string AccountNumber)
{
	sClient Client;
	Client.AccountNumber = AccountNumber;

	cout << "\n\nEnter PinCode? ";
	getline(cin >> ws, Client.PinCode);
	cout << "Enter Name? ";
	getline(cin, Client.Name);
	cout << "Enter Phone? ";
	getline(cin, Client.Phone);
	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;

	return Client;
}

bool UpdateClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
	sClient Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);

		cout << "\n\nAre you sure you want update this client? y/n ? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			for (sClient& C : vClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ChangeClientRecord(AccountNumber);
					break;
				}
			}
			SaveCleintsDataToFile(ClientsFileName, vClients);
			cout << "\n\nClient Updated Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
		return false;
	}
}

void ShowUpdateClientScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tUpdate Client Info Screen";
	cout << "\n-----------------------------------\n";

	vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	UpdateClientByAccountNumber(AccountNumber, vClients);
}

void ShowFindClientScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tFind Client Screen";
	cout << "\n-----------------------------------\n";

	vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	sClient Client;
	string AccountNumber = ReadClientAccountNumber();

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
		PrintClientCard(Client);
	else
		cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";
}

void ShowEndScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tProgram Ends :-)";
	cout << "\n-----------------------------------\n";
}

short ReadTransactionOption()
{
	cout << "Choose what do you want to do ? [1 to 4] ? ";
	short Choice = 0;
	cin >> Choice;
	return Choice;
}

void GoBackToTransactionMenu()
{
	cout << "\n\nPress any key to go back to Transaction Menu...";
	system("pause>0");
	ShowTransaction();
}

void PerformTransactionInBalanceClient(const string& AccountNumber, const double& Amount, sClient& Client, vector<sClient>& vClients) {

	for (sClient& C : vClients) {
	
		if (C.AccountNumber == AccountNumber) {
		
			C.AccountBalance += Amount;
			Client = C;
			return;
		}
	}
}

void ProcessTransaction(const string& FileName, vector<sClient>& vClient, enTransactionType TransactionType) {

	string AccountNumber = ReadClientAccountNumber();
	sClient Client;

	while (!FindClientByAccountNumber(AccountNumber, vClient, Client)) {

		cout << "Client with [" << AccountNumber << "] does not exists.\n\n";
		AccountNumber = ReadClientAccountNumber();
	}

	PrintClientCard(Client);
	double Amount = 0;

	if (TransactionType == enTransactionType::eDepositTransaction)
		cout << "\nEnter deposite amount ? ";
	else
		cout << "\nEnter withdraw amount ? ";

	cin >> Amount;

	if (TransactionType == enTransactionType::eWithDrawTransaction)
		while (Amount > Client.AccountBalance) {
		
			cout << "Amount Exceeds the balance, you can withdraw up to " << Client.AccountBalance << endl << "Enter another amount ? ";
			cin >> Amount;
		}

	char Confirm = 'N';
	cout << "\n\nAre you sure you want perform this trasaction (Y/N) ? ";
	cin >> Confirm;

	if (Confirm == 'Y' || Confirm == 'y') {

		if (TransactionType == enTransactionType::eDepositTransaction)
			PerformTransactionInBalanceClient(AccountNumber, Amount, Client, vClient);
		else
			PerformTransactionInBalanceClient(AccountNumber, -1 * Amount, Client, vClient);
			
		SaveCleintsDataToFile(FileName, vClient);
		cout << "\nDone Successfully, new balance = " << Client.AccountBalance << ".\n";
	}
	else
		cout << "\nProcess Canceled.\n";
}

void DepositeScreen() {

	cout << "------------------------------\n";
	cout << "\tDeposite Screen\n";
	cout << "------------------------------\n\n";

	vector<sClient> vClient = LoadCleintsDataFromFile(ClientsFileName);
	
	
	ProcessTransaction(ClientsFileName, vClient, enTransactionType::eDepositTransaction);
}

void WithdrawScreen() {

	cout << "------------------------------\n";
	cout << "\tWithdraw Screen\n";
	cout << "------------------------------\n\n";

	vector<sClient> vClient = LoadCleintsDataFromFile(ClientsFileName);
	
	
	ProcessTransaction(ClientsFileName, vClient, enTransactionType::eWithDrawTransaction);
}

void TotalBalanceScreen() {

	vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
	cout << "\n_________________________________________________________";
	cout << "____________________________________________\n" << endl;

	cout << "| " << left << setw(30) << "Accout Number";
	cout << "| " << left << setw(46) << "Client Name";
	cout << "| " << left << setw(20) << "Balance";

	cout << "\n_________________________________________________________";
	cout << "____________________________________________\n" << endl;

	double TotalBalance = 0;

	if (vClients.size() == 0)
		cout << "\t\t\t\tNo Clients Available In the System!";
	else 
		for (const sClient& C : vClients) {
	
			cout << "| " << left << setw(30) << C.AccountNumber;
			cout << "| " << left << setw(46) << C.Name;
			cout << "| " << left << setw(20) << C.AccountBalance << "\n";
			TotalBalance += C.AccountBalance;
		}

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	cout << "\t\t\t\t\tTotal Balnce = " << TotalBalance << endl;
}


void PerformTransactionOption(enTransactionOption TransactionOption) {

	switch (TransactionOption) {
	
	case enTransactionOption::eDeposite:
		system("cls");
		DepositeScreen();
		GoBackToTransactionMenu();
		break;
	case enTransactionOption::eWithDraw:
		system("cls");
		WithdrawScreen();
		GoBackToTransactionMenu();
		break;
	case enTransactionOption::eTotalBalnce:
		system("cls");
		TotalBalanceScreen();
		GoBackToTransactionMenu();
		break;
	case enTransactionOption::eMainMenu:
		ShowMainMenue();
		break;
	default:
		system("cls");
		cout << "Error!\nEnter any key.....";
		system("pause>0");
		ShowTransaction();
	}
}

void ShowTransaction() {

	system("cls");
	cout << "===========================================\n";
	cout << "\tTransaction Menu Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Deposite.\n";
	cout << "\t[2] WithDraw.\n";
	cout << "\t[3] Total Balance.\n";
	cout << "\t[4] Main Menu.\n";
	cout << "===========================================\n";
	PerformTransactionOption((enTransactionOption)ReadTransactionOption());
}

void PerformMainMenuOption(enMainMenueOptions MainMenueOption)
{
	switch (MainMenueOption)
	{
	case enMainMenueOptions::eListClients:
	{
		system("cls");
		ShowAllClientsScreen();
		GoBackToMainMenue();
		break;
	}
	case enMainMenueOptions::eAddNewClient:
		system("cls");
		ShowAddNewClientsScreen();
		GoBackToMainMenue();
		break;
	case enMainMenueOptions::eDeleteClient:
		system("cls");
		ShowDeleteClientScreen();
		GoBackToMainMenue();
		break;
	case enMainMenueOptions::eUpdateClient:
		system("cls");
		ShowUpdateClientScreen();
		GoBackToMainMenue();
		break;
	case enMainMenueOptions::eFindClient:
		system("cls");
		ShowFindClientScreen();
		GoBackToMainMenue();
		break;
	case enMainMenueOptions::eTransaction:
		system("cls");
		ShowTransaction();
		break;
	case enMainMenueOptions::eExit:
		system("cls");
		ShowEndScreen();
		break;
	default:
		system("cls");
		cout << "Error!\nEnter any key.....";
		system("pause>0");
		ShowMainMenue();
	}
}

void ShowMainMenue()
{
	system("cls");
	cout << "===========================================\n";
	cout << "\t\tMain Menue Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transaction.\n";
	cout << "\t[7] Exit.\n";
	cout << "===========================================\n";
	PerformMainMenuOption((enMainMenueOptions)ReadMainMenueOption());
}

int main() {

	ShowMainMenue();
	system("pause>0");

	return 0;
}
