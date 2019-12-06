#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <sys/stat.h>

#include "yaml-cpp/yaml.h"
using namespace std;

/*==== Global declarations ====*/

string config_file;
YAML::Node database;


/*== User input related ==*/

/**
 * Tokenize given string using 'space' character delimiter.
 * @return vector<string> Tokens
 */
vector<string> tokenize(std::string const &str) {
	vector<string> tokens;
	const char delimiter = ' ';
	stringstream ss(str);
	string s;

	while (getline(ss, s, delimiter))
		tokens.push_back(s);
	return tokens;
}

/**
 * Process user input.
 * @param string Command to process
 * @return bool False if program should quit
 */
bool processCommand(string);


/*== Database related ==*/

/**
 * Load database contents from 'persons.yml' file.
 */
void dbLoad() {
	// Check if database file exists.
	struct stat buffer;
	if (stat(config_file.c_str(), &buffer) == 0) {

		// Load it
		cout << "Database file present. Loading..." << endl;

		try {
			database = YAML::LoadFile(config_file);
			cout << "Finished." << endl;
		} catch (const YAML::ParserException& e) {
			cout << "Error ocurred: " << e.what() << endl;
		}

	} else {
		cout << "Database file not present." << endl;
	}
}

/**
 * Save database contents to 'persons.yml' file.
 */
void dbSave() {
	cout << "Saving database to file..." << endl;
	ofstream out;
	out.open(config_file, ios::out | ios::trunc);
	out << database;
	out.close();
	cout << "Done." << endl;
}

/**
 * Display database contents.
 */
void dbShow() {
	if (database.IsNull())
		cout << "Database empty." << endl;

	else {
		cout << "Current database contents:" << endl;

		YAML::Emitter out;
		out.SetOutputCharset(YAML::EscapeNonAscii);
		out << database;
		cout << out.c_str() << endl;
	}
}

/**
 * Delete database contents.
 */
void dbClear() {
	database = YAML::Load("");
	cout << "Done." << endl;
}

/*== Database user related ==*/

/**
 * Add user to database.
 */
void userAdd() {
	YAML::Node user;
	string input;

	do {
		cout << "Enter user name: ";
		getline(cin, input);
	} while(input.empty());
	user["name"] = input;

	do {
		cout << "Enter user age: ";
		getline(cin, input);
	} while(input.empty());
	user["age"] = input;

	database.push_back(user);
	cout << "User added." << endl;
}

/**
 * Add user to database.
 */
void userEdit(string user) {
	int index = stoi(user);
	if (database[index]) {
		string input;

		cout << "Enter user name [" << database[index]["name"] << "]: ";
		getline(cin, input);
		if (input != "")
			database[index]["name"] = input;

		cout << "Enter user age [" << database[index]["age"] << "]: ";
		getline(cin, input);
		if (input != "")
			database[index]["age"] = input;

		cout << "User data updated." << endl;
	} else {
		cout << "No such user." << endl;
	}
}

/**
 * Add user to database.
 */
void userRemove(string user) {
	int index = stoi(user);
	if (database[index]) {
		string name = database[index]["name"].as<string>();
		database.remove(index);
		cout << "User " << index << "[" << name << "] removed" << endl;
	} else {
		cout << "No such user." << endl;
	}
}



/*==== Entry point ====*/

int main(int argc, char** argv) {
	// Initialize empty database
	database = YAML::Load("");
	config_file = argv[0];
	config_file += ".yml";

	string command;
	bool running = true;

	cout << "Welcome! Type 'help' for list of available commands." << endl;
	while (running) {
		// Get user input
		cout << endl << "#> ";
		getline(cin, command);

		// Process it
		running = processCommand(command);
	}
	cout << "Bye." << endl;
	return 0;
}

// Implementation of processCommand function.
bool processCommand(string command) {
	// Exit program
	if (command == "exit")
		return false;

	// Tokenize command for ease of use
	vector<string> tokens = tokenize(command);

	// Display available commands
	if (tokens[0] == "help") {
		cout << "Available commands:" << endl;
		cout << "help" << '\t' << "Display this message." << endl;
		cout << "exit" << '\t' << "Stop program execution." << endl << endl;
		cout << "load" << '\t' << "Load database from file." << endl;
		cout << "save" << '\t' << "Save database to file." << endl;
		cout << "dump" << '\t' << "Display database contents." << endl;
		cout << "clear" << '\t' << "Delete database contents." << endl << endl;
		cout << "user add" << '\t' << '\t' << "Add new user to database." << endl;
		cout << "user remove INDEX" << '\t' << "Remove user at INDEX location." << endl;
		cout << "user edit INDEX" << '\t' << '\t' << "Edit user information at INDEX location." << endl;
		cout << '\t' << '\t' << '\t' << "(leaving empty answer doesn't change current information)" << endl;
		cout << "[NOTE] User index is 0-based, therefore first user is at index 0, second at index 1 and so on." << endl;
		return true;
	}
	
	// Load/Save database
	if (tokens[0] == "load") {
		dbLoad();
		return true;
	}

	if (tokens[0] == "save") {
		dbSave();
		return true;
	}

	if (tokens[0] == "dump") {
		dbShow();
		return true;
	}

	if (tokens[0] == "clear") {
		dbClear();
		return true;
	}

	if ((tokens[0] == "user") && (tokens.size() > 1)) {
		// Add user
		if (tokens[1] == "add") {
			userAdd();

		// Remove user
		} else if (tokens[1] == "rm") {
			if (tokens.size() > 2)
				userRemove(tokens[2]);
			else
				cout << "Please specify which user to remove." << endl;

		// Edit user
		} else if (tokens[1] == "edit") {
			if (tokens.size() > 2)
				userEdit(tokens[2]);
			else
				cout << "Please specify which user to edit." << endl;
		}
		return true;
	}

	cout << "Unrecognized command: " << command << endl;
	return true;
}
