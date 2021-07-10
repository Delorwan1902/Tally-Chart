#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstdlib>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

void runMenu();
void displayTest(const char*);
string generateTable();
void createLists(const char*);
void saveData(const char*, string);
void loadData(vector<string>);
void returnToMenu();

ifstream FileReader;
map<int, int> tallyResults; //Map to store all the dice roll scores
vector<string> tallyData;

const char tallyAbout[] = "TallyAbout.txt", savedTallyData[] = "savedTallyData.txt";

void runMenu() {
	int option = 0;
	bool exit = true;
	string theTitle = "";

	while (exit) {
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "    The Tally Ho Probability Generator     " << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "[0] End Testing the Program" << endl;
		cout << "[1] Display \"About\" Information" << endl;
		cout << "[2] Read and store data from files" << endl;
		cout << "[3] Generate a Dice Tally Table" << endl;
		cout << "[4] Save Tally Statistics to a file" << endl;
		cout << "[5] Load Tally Statistics from a file" << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "Which option would you like (0-5): ";

		while (!(cin >> option) || option < 0 || option > 5) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Input must be a integer within range (0 - 5), try again: ";
		}

		if (option == 0) {
			cout << endl << "Thank you for testing this application." << endl;
			exit = false;
		}
		else if (option == 1)
			displayTest(&tallyAbout[0]);
		else if (option == 2)
			createLists(&savedTallyData[0]);
		else if (option == 3) {
			theTitle = generateTable();
			cout << theTitle << endl;
			for (auto it = tallyResults.begin(); it != tallyResults.end(); ++it) //Displaying tally table
				cout << setw(2) << it->first << ": " << string(it->second, '*') << endl;
			cout << endl;
		}
		else if (option == 4)
			saveData(&savedTallyData[0], theTitle);
		else if (option == 5)
			loadData(tallyData);
	}
}

/*
 * displayTest function called when option 1 is chosen from runMenu function
 */
void displayTest(const char* fileName) {
	system("CLS");
	FileReader.open(fileName);
	string line = "";

	if (!FileReader) {
		cout << "Unable to open " << fileName << endl;
		exit(1);
	}
	else {
		while (getline(FileReader, line)) //Reading and displaying each line from the file
			cout << line << endl;
	}
	FileReader.close();
	cout << endl;
	returnToMenu();
}

/*
 * Task 3
 */
void createLists(const char* fileName) {
	FileReader.open(fileName);
	tallyData.clear();
	string line = "";

	if (!FileReader) {
		cout << "Unable to open " << fileName << endl;
		exit(1);
	}
	else {
		cout << endl;
		while (getline(FileReader, line))  //Reading and displaying each line from the file
			tallyData.push_back(line);

		for (auto it = tallyData.begin(); it != tallyData.end(); ++it)
			cout << *it << endl;
	}
	FileReader.close();
	returnToMenu();
}

/*
 * generateTable function called when option 3 is chosen from runMenu function
 */
string generateTable() {
	int diceToRoll = 0, rollsRequired = 0, dice = 0;
	tallyResults.clear();

	cout << "How many dice do you want to roll (1-2): ";
	while (!(cin >> diceToRoll) || diceToRoll < 1 || diceToRoll > 2) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Input must be a integer within range (1 - 2), try again: ";
	}

	cout << "How many rolls required (1-10): ";
	while (!(cin >> rollsRequired) || rollsRequired < 1 || rollsRequired > 10) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Input must be a integer within range (1 - 10), try again: ";
	}

	srand((unsigned int)time(NULL)); //Very important line for the rand() function as it intialises the sequence of pseudo-random numbers with a random seed

	if (diceToRoll == 1)
		for (int i = 0; i < rollsRequired * 10; ++i) {
			dice = (rand() % 6) + 1; //Getting random number between 1 and 6
			tallyResults[dice]++; //Updating the map
		}
	else //If diceToRoll == 2
		for (int i = 0; i < rollsRequired * 10; ++i) {
			dice = ((rand() % 6) + 1) + ((rand() % 6) + 1); //Getting random number between 2 and 12
			tallyResults[dice]++;
		}
	cout << endl;
	return "You rolled " + to_string(diceToRoll) + " dice " + to_string(rollsRequired * 10) + " times.\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
}

void saveData(const char* fileName, string theTitle) {
	ofstream fileWriter;
	char saveData;

	if (!tallyResults.empty()) {
		cout << endl << theTitle << endl;
		for (auto it = tallyResults.begin(); it != tallyResults.end(); ++it) //Displaying tally table
			cout << setw(2) << it->first << ": " << string(it->second, '*') << endl;

		cout << endl << "Do you want to save this data? (y/n) ";
		cin >> saveData;

		if (saveData == 'y') {
			fileWriter.open(fileName, ios::app);
			fileWriter << theTitle << endl;

			for (auto it = tallyResults.begin(); it != tallyResults.end(); ++it) //Displaying tally table
				fileWriter << setw(2) << it->first << ": " << string(it->second, '*') << endl;

			fileWriter << "\n"; //Space between each table set
			fileWriter.close();
			cout << "These statistics are now saved.\n" << endl;
		}
		else if (saveData == 'n')
			runMenu();
	}
	else
		cout << "You have not generated a dice table yet.\n" << endl;

	returnToMenu();
}

void loadData(vector<string> tallyData) {
	if (!tallyData.empty()) {
		cout << endl;
		for (auto it = tallyData.begin(); it != tallyData.end(); ++it)
			cout << *it << endl;
	}
	else
		cout << "ERROR: load data from file first.\n" << endl;
}


void returnToMenu() {
	system("pause");
	system("CLS");
}

int main() {
    std::cout << "Hello World!\n";
	runMenu();
}
