#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string.h>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include "Patient.h"

using namespace std;

// enum data type definitions
enum class Choice { ADD = 1, SEARCH, UPDATE, DELETE, PRINT, END };
enum updateChoice { ID = 1, FIRSTNAME, LASTNAME, AGE, SEX, DATE, MEDICALHISTORY, FAMILYDISEASE, EXIT };

// other Functions Prototype
Choice enterChoice();
void createTextFile(fstream&);
void updateRecord(fstream&);
void newRecord(fstream&);
void deleteRecord(fstream&);
void searchRecord(fstream&);
int getAccount(const char* const);
void outputLine(ostream&, const Patient&); // prototype
void outputToConsole(Patient&);
void editRecord(Patient&);
int getAge(const string&);
string getValidStringInput(const string&);

void print(int amount)
{
	for (int i = 0; i < amount; i++)
		cout << char(205);
}

void printSingleLine(int amount)
{
	for (int i = 0; i < amount; i++)
		cout << char(196);
}

int main()
{
	system("CLS");
	system("COLOR 09");

	cout << "\n"
		"  " << char(201); print(44); cout << char(187) << "\n"
		"  " << char(186) << "              Main Menu                     " << char(186) << "\n"
		"  " << char(204); print(44); cout << char(185) << "\n"
		"  " << char(186) << "  [1] - Create a new patient file           " << char(186) << "\n"
		"  " << char(186) << "                                            " << char(186) << "\n"
		"  " << char(186) << "                                            " << char(186) << "\n"
		"  " << char(186) << "  [2] - Open an existing file               " << char(186) << "\n"
		"  " << char(186) << "                                            " << char(186) << "\n"
		"  " << char(200); print(44); cout << char(188) << "\n"
		"  Enter your choice: ";

	

	int x;
	cin >> x;
	system("CLS");
	if (x == 1)

	{
		cout << "Enter the name of the new file you would like to create with .dat extension (example.dat)" << endl;
		string name;
		cin >> name;
		ofstream outPatient{ name,  ios::binary };

		// exit program if ofstream could not open file
		if (!outPatient)
		{
			cerr << "File could not be opened." << endl;
			exit(EXIT_FAILURE);
		}

		Patient blankPatient; // constructor zeros out each data member

		// output 100 blank records to file
		for (int i{ 0 }; i < 100; i++)
		{
			outPatient.write(
				(char*)(&blankPatient), sizeof(Patient)
			);
		}

		cout << name << " file created succesfully" << endl;
	}

	cout << "Enter the name of a file you would like to open (example.dat)" << endl;
	string name;
	cin >> name;

		//open file for reading and writing
		fstream inOutPatient{ name, ios::in | ios::out | ios::binary };
		// exit program if fstream cannot open file
		if (!inOutPatient)
		{
			cerr << "File could not be opened." << endl;
			exit(1);
		}

		Choice choice; // store user choice
		
		// enable user to specify action
		while ((choice = enterChoice()) != Choice::END)
		{
			switch (choice)
			{

			case Choice::PRINT: // create text file from record file
				system("CLS");
				createTextFile(inOutPatient);
				break;
			case Choice::SEARCH:
				system("CLS");
				searchRecord(inOutPatient);
				break;
			case Choice::UPDATE: // update record
				system("CLS");
				updateRecord(inOutPatient);
				break;
			case Choice::ADD: // create record
				system("CLS");
				newRecord(inOutPatient);
				break;
			case Choice::DELETE: // delete existing record
				system("CLS");
				deleteRecord(inOutPatient);
				break;
			default: // display error if user does not select valid choice
				cerr << "Incorrect choice" << endl;
				break;
			}

			inOutPatient.clear(); // reset end-of-file indicator
		}

}

// other Functions Definition

//enable user to input menu choice
Choice enterChoice()
{
	int menuChoice;
	do
	{
		system("CLS");
		// display available options
		cout << "\n"
			"  " << char(201); print(44); cout << char(187) << "\n"
			"  " << char(186) << "                  Menu                      " << char(186) << "\n"
			"  " << char(204); print(44); cout << char(185) << "\n"
			"  " << char(186) << " 1. Add a new record                        " << char(186) << "\n"
			"  " << char(186) << "                                            " << char(186) << "\n"
			"  " << char(186) << " 2. Search a record                         " << char(186) << "\n"
			"  " << char(186) << "                                            " << char(186) << "\n"
			"  " << char(186) << " 3. Update a record                         " << char(186) << "\n"
			"  " << char(186) << "                                            " << char(186) << "\n"
			"  " << char(186) << " 4. Delete a record                         " << char(186) << "\n"
			"  " << char(186) << "                                            " << char(186) << "\n"
			"  " << char(186) << " 5. Store a formatted text file of records  " << char(186) << "\n"
			"  " << char(186) << "   (example.txt) for printing               " << char(186) << "\n"
			"  " << char(186) << "                                            " << char(186) << "\n"
			"  " << char(186) << " 6. End program                             " << char(186) << "\n"
			"  " << char(200); print(44); cout << char(188) <<
			"\n  Enter your choice: " << endl;

		
		cin >> menuChoice; // input menu selection from user

		// check if input is valid
		if (cin.fail()) {
			
			cout << "Invalid input. Please enter a valid choice." << endl;
			cin.clear();
			cin.ignore(1000, '\n');
			menuChoice = 0;
		}
	} while ((!menuChoice));
	
	return static_cast<Choice>(menuChoice);
}

// create formatted text file for printing
void createTextFile(fstream& readFromFile)
{
	cout << "Enter the name for the text file with .txt extension (example.txt)" << endl;
	string name;
	cin >> name;
	ofstream outPrintFile{ name, ios::out }; // create text file

	// exit program if ofstream cannot create file
	if (!outPrintFile)
	{
		cerr << "File could not be created." << endl;
		exit(1);
	}

	// output column heads
	/*outPrintFile << left << setw(5) << "Id" << setw(17) << "First Name"
		<< setw(17) << "Last Name" << setw(5) << "Age" << setw(5) << "Sex" << setw(11) << "Date"
		<< setw(35) << "Medical History" << setw(30) << "Family Disease" << endl;*/

	// set file-position pointer to beginning of readFromFile
	readFromFile.seekg(0);

	// read first record from record file
	Patient patient;
	readFromFile.read(
		(char*)(&patient), sizeof(Patient)
	);

	// copy all records from record file into text file
	while (readFromFile)
	{
		// write single record to text file
		if (patient.getId() != 0) // skip empty records
		{
			outputLine(outPrintFile, patient);
		}

		// read next record from record file
		readFromFile.read(
			(char*)(&patient), sizeof(Patient)
		);
	}
	cout << "Patient's text file created Succesfully\n";
}

// update patient record in the file
void updateRecord(fstream& updateFile)
{
	// obtain id number of patient to update
	int idNumber{ getAccount("Enter ID to update") };

	// move file-position pointer to correct record in file
	updateFile.seekg((idNumber - 1) * sizeof(Patient));

	// create record object and read first record from file
	Patient patient;
	updateFile.read(
		(char*)(&patient), sizeof(Patient));

	// update record
	if (patient.getId() != 0)
	{
		outputToConsole(patient); // display the record

		// request user to specify what they want to update and then update it
		editRecord(patient);

		outputToConsole(patient); // display the record

		// move file-position pointer to correct record in file
		updateFile.seekp((idNumber - 1) * sizeof(Patient));

		// write updated record over old record in file
		updateFile.write(
			(char*)(&patient), sizeof(Patient));
	}
	else // display error if account does not exist
	{
		cerr << "Id #" << idNumber << " has no information." << endl;
	}

}

// search a specific Record
void searchRecord(fstream& searchFile)
{
	// obtain id number of patient to update
	int idNumber{ getAccount("Enter ID to search") };

	// move file-position pointer to correct record in file
	searchFile.seekg((idNumber - 1) * sizeof(Patient));

	// create record object and read first record from file
	Patient patient;
	searchFile.read(
		(char*)(&patient), sizeof(Patient));

	// search record
	if (patient.getId() != 0)
	{
		outputToConsole(patient); // display the record

	}
	else // display error if account does not exist
	{
		cerr << "Id #" << idNumber << " has no information." << endl;
	}
}

// create and insert record
void newRecord(fstream& insertInFile)
{
	// obtain id number to create
	int idNumber{ getAccount("Enter new account number") };

	// move file-position pointer to correct record in file
	insertInFile.seekg((idNumber - 1) * sizeof(Patient));

	// read record from file
	Patient patient;
	insertInFile.read(
		(char*)(&patient), sizeof(Patient)
	);

	// create record, if record does not previously exist
	if (patient.getId() == 0)
	{
		patient.setId(idNumber);

		char sex;
		
		// user enters first name, last name, age, sex, date, medical history, family disease
		cin.ignore();
		patient.setFirstName(getValidStringInput("Enter firstname\n?"));
		patient.setLastName(getValidStringInput("Enter lastname\n?"));

		patient.setAge(getAge("How old is the patient ? \n?"));

		cout << "Enter sex (M/F)\n?";
		cin >> sex;
		patient.setSex(sex);

		cin.ignore();

		patient.setDate(getValidStringInput("Enter date(DD/MM/YY)\n?"));

		patient.setMedicalHistory(getValidStringInput("Enter past medical history, Enter None if there is no\n?"));

		patient.setFamilyDisease(getValidStringInput("Enter if there is any family disease, Enter None if there is no\n?"));

		// move file-position pointer to correct record in file
		insertInFile.seekp((idNumber - 1) * sizeof(Patient));

		// insert record in file
		insertInFile.write(
			(char*)(&patient), sizeof(Patient)
		);

	}
	else // display error if account already exists
	{
		cerr << "Id #" << idNumber << " already contains information." << endl;
	}
}

// delete an existing record
void deleteRecord(fstream& deleteFromFile)
{
	// obtain id no of patient
	int idNumber{ getAccount("Enter ID number to delete") };

	// move file-position pointer to correct record in file
	deleteFromFile.seekg((idNumber - 1) * sizeof(Patient));

	// read record from file
	Patient patient;
	deleteFromFile.read(
		(char*)(&patient), sizeof(Patient)
	);

	// delete record, if  record exists in file
	if (patient.getId() != 0)
	{
		outputToConsole(patient); // display the record
		cout << "Would you like to delete the record?(y for YES and n for NO)" << endl;
		char response;

		cin >> response;

		if(response == 'y' || response == 'Y')
		{
			Patient blankPatient; // create blank record
			patient = blankPatient;

			// move file-position pointer to correct record in file
			deleteFromFile.seekp((idNumber - 1) * sizeof(Patient));

			// replace existing record with blank record
			deleteFromFile.write(
				(char*)(&patient), sizeof(Patient)
			);

			cout << "Id #" << idNumber << " deleted.\n";
		}
	}
	else // display error if record does not exist
	{
		cerr << "Account #" << idNumber << " is empty.\n";
	}
}

// output the record
void outputLine(ostream& output, const Patient& record)
{
	/*output << left << setw(5) << record.getId()
		<< setw(17) << record.getFirstName()
		<< setw(17) << record.getLastName()
		<< setw(5) << record.getAge()
		<< setw(5) << record.getSex()
		<< setw(11) << record.getDate()
		<< setw(35) << record.getMedicalHistory()
		<< setw(30) << record.getFamilyDisease() << endl;*/
 output << "  ______________________________________________________________________________________\n"
		<< "|| Id: " << record.getId() << endl
		<< "|| First Name: " << record.getFirstName() << endl
		<< "|| Last Name: " << record.getLastName() << endl
		<< "|| Age: " << record.getAge() << endl
		<< "|| Gender: " << record.getSex() << endl
		<< "|| Registration Date: " << record.getDate() << endl
		<< "|| Medical History: " << record.getMedicalHistory() << endl
		<< "|| Family Disease: " << record.getFamilyDisease() << endl
		<< "  ---------------------------------------------------------------------------------------\n";
}

// obtain id-number value from user
int getAccount(const char* const prompt)
{
	int idNumber;

	do {
		cout << prompt << " (1 - 100)\n";

		// Check if the input is an integer
		if (!(cin >> idNumber)) {
			cout << "Invalid input. Please enter a valid integer.\n";
			cin.clear(); // Clear error flag
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
			continue; // Go to the next iteration
		}

		// Check if the input is within the specified range
		if (idNumber < 1 || idNumber > 100) {
			cout << "Invalid input. Please enter a number between 1 and 100.\n";
		}

	} while (idNumber < 1 || idNumber > 100);

	return idNumber;
}

// output record to the console for validation
void outputToConsole(Patient& demo)
{
	cout << "First Name: " << demo.getFirstName() << endl;
	cout << "Last Name: " << demo.getLastName() << endl;
	cout << "Age: " << demo.getAge() << endl;
	cout << "Sex: " << demo.getSex() << endl;
	cout << "Date: " << demo.getDate() << endl;
	cout << "Meidcal History: " << demo.getMedicalHistory() << endl;
	cout << "Family Diseasae: " << demo.getFamilyDisease() << endl;
}

// Prompt the user for what they want to update
updateChoice enterUpdateChoice()
{
	// display availbale choices
	cout << "\n"
		"  " << char(218); printSingleLine(30); cout << char(191) << "\n"
		"  " << char(179) << "       Update Options         " << char(179) << "\n"
		"  " << char(179); print(30); cout << char(179) << "\n"
		"  " << char(179) << "1. Update Patient's ID        " << char(179) << "\n"
		"  " << char(179) << "2. Update First Name          " << char(179) << "\n"
		"  " << char(179) << "3. Update Last Name           " << char(179) << "\n"
		"  " << char(179) << "4. Update Age                 " << char(179) << "\n"
		"  " << char(179) << "5. Update Sex                 " << char(179) << "\n"
		"  " << char(179) << "6. Update Registration Date   " << char(179) << "\n"
		"  " << char(179) << "7. Update Medical History     " << char(179) << "\n"
		"  " << char(179) << "8. Update Family Disease      " << char(179) << "\n"
		"  " << char(179) << "9. Exit                       " << char(179) << "\n"
		"  " << char(192); printSingleLine(30);  cout << char(217) << "\n"
		"  Enter your choice: " << endl;

	int menuChoice;
	cin >> menuChoice; // input menu selection from user

	return static_cast<updateChoice>(menuChoice);
}

// update a specific record in the file
void editRecord(Patient& demo)
{
	updateChoice choice;

	do
	{
		choice = enterUpdateChoice();

		if (choice == updateChoice::ID)
		{
			demo.setId(getAccount("Enter the new patient ID:/n"));
			cout << "Patient ID updated successfully.\n";
		}
		else if (choice == updateChoice::FIRSTNAME)
		{
			cin.ignore();
			demo.setFirstName(getValidStringInput("Enter the new First Name:\n"));
			cout << "First Name updated successfully.\n";
		}
		else if (choice == updateChoice::LASTNAME)
		{
			cin.ignore();
			demo.setLastName(getValidStringInput("Enter the new Last Name:\n"));
			cout << "Last Name updated successfully.\n";
		}
		else if (choice == updateChoice::AGE)
		{
			demo.setAge(getAge("Enter the new age: \n"));
			cout << "Age updated successfully.\n";
		}
		else if (choice == updateChoice::SEX)
		{
			cout << "Enter the new sex:\n";
			char sex;
			cin >> sex;
			demo.setSex(sex);
			cout << "Sex updated successfully.\n";
		}
		else if (choice == updateChoice::DATE)
		{
			cin.ignore();
			demo.setDate(getValidStringInput("Enter the new registration date:\n"));
			cout << "Date updated successfully.\n";
		}
		else if (choice == updateChoice::MEDICALHISTORY)
		{
			cin.ignore();
			demo.setMedicalHistory(getValidStringInput("Enter the new medical history:\n"));
			cout << "Medical History updated successfully.\n";
		}
		else if (choice == updateChoice::FAMILYDISEASE)
		{
			cin.ignore();
			demo.setFamilyDisease(getValidStringInput("Enter the new family disease:\n"));
			cout << "Family Disease updated successfully.\n";
		}

		else
		{
			cout << "You have entered the wrong option.\n";
		}
	} while (choice != EXIT);
	
}

// Accept valid age value from the user
int getAge(const string& prompt)
{
	int age;
	do {

		cout << prompt;
		cin >> age;

		// Check if the input is an integer
		if (!age) {
			cout << "Invalid input. Please enter a valid integer.\n";
			cin.clear(); // Clear error flag
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
			continue; // Go to the next iteration
		}

		// Check if the input is within the specified range
		if (age < 0 || age > 120) {
			cout << "Invalid input. Please enter a number between 0 and 120.\n";
		}

	} while ((!age) || (age < 0 || age > 120));

	return age;
}

// Function to get valid non-empty string input
string getValidStringInput(const string& prompt) {
	string input;

	do {
		
		cout << prompt;

		getline(std::cin, input);

		// Check if the string is empty
		if (input.empty()) {
			std::cout << "Invalid input. Please enter a non-empty string.\n";
			continue;
		}

		// Break the loop if input is valid
		break;

	} while (true);

	return input;
}

















