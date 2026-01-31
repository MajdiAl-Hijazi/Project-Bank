#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<iomanip>

using namespace std;

const string ClientFileName = "Clients.txt";

struct sDataClients {

	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};

enum eChosenProcess { ShowClientList = 1, AddNewClient = 2, DeleteClient = 3, UpdateClientInfo = 4, FindClient = 5, Exit = 6 };

void ResetScreen() {

	system("cls");
}

vector<string> SplitString(string S1, string Sperator) {

	vector<string> vString;
	short pos;
	string Word;

	while ((pos = S1.find(Sperator)) != string::npos) {
	
		Word = S1.substr(0, pos);

		if (Word != "")
			vString.push_back(Word);

		S1.erase(0, pos + Sperator.length());
	}

	if (S1 != "")
		vString.push_back(S1);

	return vString;
}

sDataClients ConvertLineToRecord(const string& Line) {

	vector<string> vStrings = SplitString(Line, "#//#");
	sDataClients Client;

	Client.AccountNumber = vStrings[0];
	Client.PinCode = vStrings[1];
	Client.Name = vStrings[2];
	Client.Phone = vStrings[3];
	Client.AccountBalance = stod(vStrings[4]);

	return Client;
}

vector<sDataClients> LoadDataFromFile(const string& FileName) {

	vector<sDataClients> vDataClient;
	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open()) {

		string Line;

		while (getline(MyFile, Line)) {
		
			vDataClient.push_back(ConvertLineToRecord(Line));
		}

		MyFile.close();
	}

	return vDataClient;
}

void PrintHeaderShowAllClients(const short& NumOfClients) {

	cout << "                                  Client List (" << NumOfClients << ") Client(s).                                     " << endl;
	cout << "_____________________________________________________________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Account Number" << "| " << left << setw(10) << "Pin Code" << "| " << left << setw(35) << "Client Name"
		<< "| " << left << setw(10) << "Phone" << "| " << left << setw(20) << "Balance" << endl;
	cout << "_____________________________________________________________________________________________\n" << endl;
}

void PrintClients(const vector<sDataClients>& vClients) {

	if (vClients.size() == 0) {
	
		cout << "\n                                           ((Empty))                  \n";
		return;
	}

	for (const sDataClients& Client : vClients) {
	
		cout << "| " << left << setw(15) << Client.AccountNumber << "| " << left << setw(10) << Client.PinCode << "| " << left << setw(35) << Client.Name
			<< "| " << left << setw(10) << Client.Phone << "| " << left << setw(20) << Client.AccountBalance << endl;
	}

}

void PrintFooterShowAllClients() {

	cout << "\n_____________________________________________________________________________________________\n" << endl;
}

void MainMenuScreen(); //Declaration

void ShowAllClientsScreen() {

	vector<sDataClients> vDataClient = LoadDataFromFile(ClientFileName);
	PrintHeaderShowAllClients(vDataClient.size());
	PrintClients(vDataClient);
	PrintFooterShowAllClients();

	cout << "\nPress any key to go back to Main Menu....";
	system("pause>0");
	MainMenuScreen();
}

void PrintHeaderAddNewClient() {

	cout << "--------------------------------------\n";
	cout << "        Add New Client Screen         \n";
	cout << "--------------------------------------\n";
	cout << "Adding New Client :\n\n";
}

sDataClients ReadDataClient(string AccountNumber) {

	sDataClients Client;

	Client.AccountNumber = AccountNumber;
	cout << "\nEnter Pin Code ? ";
	getline(cin >> ws, Client.PinCode);
	cout << "Enter Name ? ";
	getline(cin, Client.Name);
	cout << "Enter Phone ? ";
	cin >> Client.Phone;
	cout << "Enter Account Balance ? ";
	cin >> Client.AccountBalance;

	return Client;
}

string ReadString(string Message) {

	string S1 = "";
	cout << Message;
	cin >> S1;
	return S1;
}

bool FindClientUsingAccountNumber(const string& AccountNumber) {

	fstream MyFile;
	MyFile.open(ClientFileName, ios::in);

	if (MyFile.is_open()) {
	
		string Line;

		while (getline(MyFile ,Line)) {
		
			if (ConvertLineToRecord(Line).AccountNumber == AccountNumber)
				return true;
		}

		MyFile.close();
	}

	return false;
}

bool FindClientUsingAccountNumber(const string& AccountNumber, sDataClients& Client) {

	fstream MyFile;
	MyFile.open(ClientFileName, ios::in);

	if (MyFile.is_open()) {
	
		string Line;

		while (getline(MyFile ,Line)) {
		
			if ((Client = ConvertLineToRecord(Line)).AccountNumber == AccountNumber)
				return true;
		}

		MyFile.close();
	}

	return false;
}

void PrintDataClient(sDataClients& Client) {

	cout << "\nThe following are the client details :\n";
	cout << "------------------------------------- \n";
	cout << "Account Number  : " << Client.AccountNumber << endl;
	cout << "Oin Code        : " << Client.PinCode<< endl;
	cout << "Name            : " << Client.Name<< endl;
	cout << "Phone           : " << Client.Phone<< endl;
	cout << "Account Balance : " << Client.AccountBalance<< endl;
	cout << "------------------------------------- \n";
}

bool FindClientUsingAccountNumber(const string& AccountNumber, vector<sDataClients>& vClients) {

	for (sDataClients& Client : vClients) {
	
		if (Client.AccountNumber == AccountNumber) {
		
			Client.MarkForDelete = true;
			PrintDataClient(Client);
			return true;
		}
	}

	return false;
}

bool IsFound(const string& AccountNumber, const vector<sDataClients>& vClients) {

	for (sDataClients Client : vClients) {
	
		if (Client.AccountNumber == AccountNumber) {
		
			PrintDataClient(Client);
			return true;
		}
	}

	return false;
}

string ConvertRecoredToLine(sDataClients Client, string Sperator = "#//#") {

	string S1 = "";
	S1 = Client.AccountNumber + Sperator + Client.PinCode + Sperator + Client.Name + Sperator + Client.Phone + Sperator + to_string(Client.AccountBalance);
	return S1;
}

void AddDataClientToFile(string FileName, string DataClient) {

	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open()) {
	
		MyFile << DataClient << endl;
		MyFile.close();
	}
}

void AddNewClientScreen() {

	char AddMore = 'Y';

	do {

		ResetScreen();
		PrintHeaderAddNewClient();

		string AccountNumber = ReadString("Enter Account Number ? ");

		while (FindClientUsingAccountNumber(AccountNumber)) {

			cout << "Client with [" << AccountNumber << "] already exists, Enter another Account Number ? ";
			cin >> AccountNumber;
		}

		AddDataClientToFile(ClientFileName, ConvertRecoredToLine(ReadDataClient(AccountNumber)));
		cout << "\nClient Added Successfully, do want to add more clients (Y/N) ? ";
		cin >> AddMore;

	} while (AddMore == 'Y' || AddMore == 'y');

	cout << "\nPress any key to go back to Main Menu....";
	system("pause>0");
	MainMenuScreen();
}

void PrintHeaderDeleteClient() {

	cout << "--------------------------------------\n";
	cout << "         Delete Client Screen         \n";
	cout << "--------------------------------------\n";
	cout << "Delete Client :\n\n";
}

vector<sDataClients> DeleteClientFromVector(const vector<sDataClients>& vClients) {

	vector<sDataClients> Clients;

	for (const sDataClients& C : vClients)
		if (C.MarkForDelete == false)
			Clients.push_back(C);

	return Clients;
}

void UpdateDataFile(const string& FileName, const vector<sDataClients>& vClients) {

	fstream MyFile;
	MyFile.open(FileName, ios::out);

	if (MyFile.is_open()) {
	
		for (const sDataClients& C : vClients)
			MyFile << ConvertRecoredToLine(C) << endl;

		MyFile.close();
	}
}

void DeleteClientScreen() {

	PrintHeaderDeleteClient();
	
	string AccountNumber = ReadString("Enter Account Number ? ");

	vector<sDataClients> vClients = LoadDataFromFile(ClientFileName);

	if (FindClientUsingAccountNumber(AccountNumber, vClients)) {

		char ConfirmDelete = 'Y';
		cout << "\n\nAre you sure you want this client (Y/N) ? ";
		cin >> ConfirmDelete;

		if (ConfirmDelete == 'y' || ConfirmDelete == 'Y') {

			vClients = DeleteClientFromVector(vClients);
			UpdateDataFile(ClientFileName, vClients);
			cout << "\nClient Deleted Successfully.\n";
		}
		else
			cout << "\nProcess Canceled.\n";
	}
	else
		cout << "\nClient with Account Number (" << AccountNumber << ") is not Found!\n";

	cout << "\nPress any key to go back to Main Menu....";
	system("pause>0");
	MainMenuScreen();
}

void PrintHeaderUpdateClientInfoScreen() {

	cout << "--------------------------------------\n";
	cout << "          Update Client Info          \n";
	cout << "--------------------------------------\n";
	cout << "Update Client Info :\n\n";
}

void UpdateDataClient(const string& AccountNumber, vector<sDataClients>& vClients) {

	for (sDataClients& Client : vClients) {
	
		if (Client.AccountNumber == AccountNumber) {
		
			Client = ReadDataClient(AccountNumber);
			return;
		}
	}
}

void UpdateClientInfoScreen() {

	PrintHeaderUpdateClientInfoScreen();

	string AccountNumber = ReadString("Enter Account Number ? ");
	vector<sDataClients> vClients = LoadDataFromFile(ClientFileName);

	if (IsFound(AccountNumber, vClients)) {
	
		char ConfirmUpdate = 'y';
		cout << "\n\nAre you sure you want update this client (Y/N) ? ";
		cin >> ConfirmUpdate;

		if (ConfirmUpdate == 'y' || ConfirmUpdate == 'Y') {
		
			UpdateDataClient(AccountNumber, vClients);
			UpdateDataFile(ClientFileName, vClients);
			cout << "\n\nClient Updated Successfully.\n\n";
		}
		else
			cout << "\nProcess Canceled.\n";
	}
	else
		cout << "\nClient with Account Number (" << AccountNumber << ") is not Found!\n";

	cout << "\nPress any key to go back to Main Menu....";
	system("pause>0");
	MainMenuScreen();
}

void PrintHeaderFindClientScreen() {

	cout << "--------------------------------------\n";
	cout << "          Find Client Screen          \n";
	cout << "--------------------------------------\n";
	cout << "Find Client :\n\n";
}

void FindClientScreen() {

	PrintHeaderFindClientScreen();
	string AccountNumber = ReadString("Enter Account Number ? ");
	sDataClients Client;

	if (FindClientUsingAccountNumber(AccountNumber, Client))
		PrintDataClient(Client);
	else
		cout << "\n\nClient with (" << AccountNumber << ") Not Found!\n\n";

	cout << "\nPress any key to go back to Main Menu....";
	system("pause>0");
	MainMenuScreen();
}

void ExitScreen() {

	cout << "---------------------------------\n";
	cout << "        Program Ends :-)         \n";
	cout << "---------------------------------\n";
	system("pause>0");
}

void SelectedProcess(const short& ChosenProcess) {

	switch (ChosenProcess) {
	
	case eChosenProcess::ShowClientList:
		ResetScreen();
		ShowAllClientsScreen();
		break;
	case eChosenProcess::AddNewClient:
		ResetScreen();
		AddNewClientScreen();
		break;
	case eChosenProcess::DeleteClient:
		ResetScreen();
		DeleteClientScreen();
		break;
	case eChosenProcess::UpdateClientInfo:
		ResetScreen();
		UpdateClientInfoScreen();
		break;
	case eChosenProcess::FindClient:
		ResetScreen();
		FindClientScreen();
		break;
	case eChosenProcess::Exit:
		ResetScreen();
		ExitScreen();
		break;
	default:
		ResetScreen();
		cout << "Error!\nEnter any key.....";
		system("pause>0");
		MainMenuScreen();
		break;
	}
}

void MainMenuScreen() {

	ResetScreen();

	short ChooseProcess = 6;

	cout << "=================================================\n";
	cout << "                 Main Menu Screen                \n";
	cout << "=================================================\n";
	cout << "            [1] Show Client List.\n";
	cout << "            [2] Add New Client.\n";
	cout << "            [3] Delete Client.\n";
	cout << "            [4] Update Client Info.\n";
	cout << "            [5] Find Client.\n";
	cout << "            [6] Exit.\n";
	cout << "=================================================\n";
	cout << "Choose what do you want to do ? [1 to 6] ? ";
	cin >> ChooseProcess;

	SelectedProcess(ChooseProcess);
}

void Bank() {

	MainMenuScreen();
}

int main() {

	Bank();

	return 0;
}
